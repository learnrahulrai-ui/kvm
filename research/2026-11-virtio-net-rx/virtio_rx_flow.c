/* Original human report: https://lkml.iu.edu/hypermail/linux/kernel/2611.1/11430.html
 * This reproducer is a standalone C program and does not modify kernel logic.
 * 8388608 bytes transferred and checked on loopback, exit 0. No virtio-net NIC exercised. Kernel bug NOT reproduced.
 * Strict GCC and sanitizer compilations were reported clean; not re-run by this publication step.
 * Build: gcc -std=c11 -O0 -g3 -Wall -Wextra -Werror -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wstrict-prototypes -fno-omit-frame-pointer -pthread virtio_rx_flow.c -o candidate.debug
 * Full compiler diagnostics, source provenance and reproduction limitations in research/2026-11-virtio-net-rx/CUMULATIVE_EVIDENCE.txt
 */
/* Real Linux TCP receiving workload; no printf/cout.
 * --self uses loopback and does NOT exercise virtio-net.
 * --listen in guest with virtio-net and --send GUEST_IP on host can exercise RX.
 * USER_SOURCE_ERRORS: none. Local trivial compiler errors in comments below.
 */
#define _POSIX_C_SOURCE 200809L
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
enum { PORT = 43219, CHUNK = 8192, ROUNDS = 1024, EXPECT_BYTES = CHUNK * ROUNDS };
typedef struct { atomic_uint_fast64_t bytes; atomic_uint_fast64_t sum; atomic_uint errors; } Evidence;
static Evidence evidence;
static int make_listener(void)
{
    const int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) return -1;
    const int yes = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) != 0) { close(fd); return -1; }
    struct sockaddr_in addr = { .sin_family = AF_INET, .sin_port = htons(PORT), .sin_addr = { .s_addr = htonl(INADDR_ANY) } };
    if (bind(fd, (const struct sockaddr *)&addr, sizeof(addr)) != 0 || listen(fd, 1) != 0) { close(fd); return -1; }
    return fd;
}
static void *receive_worker(void *raw)
{
    const int fd = *(const int *)raw;
    uint8_t data[CHUNK];
    for (;;) {
        const ssize_t n = recv(fd, data, sizeof(data), 0);
        if (n == 0) break;
        if (n < 0) {
            if (errno == EINTR) continue;
            atomic_fetch_add(&evidence.errors, errno == EAGAIN || errno == EWOULDBLOCK ? 3U : 2U);
            break;
        }
        uint64_t sum = 0;
        for (size_t i = 0; i < (size_t)n; ++i) sum += data[i];
        atomic_fetch_add(&evidence.bytes, (uint64_t)n);
        atomic_fetch_add(&evidence.sum, sum);
    }
    return NULL;
}
static int receive_flow(int listener)
{
    /* ORIGINAL COMPILE ERROR: const int fd made &fd incompatible with pthread_create(void *). */
    int fd = accept(listener, NULL, NULL);
    close(listener);
    if (fd < 0) return 2;
    const struct timeval tv = { .tv_sec = 8, .tv_usec = 0 };
    if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv))) { close(fd); return 2; }
    pthread_t a, b;
    if (pthread_create(&a, NULL, receive_worker, &fd)) { close(fd); return 2; }
    if (pthread_create(&b, NULL, receive_worker, &fd)) { shutdown(fd, SHUT_RDWR); pthread_join(a, NULL); close(fd); return 2; }
    pthread_join(a, NULL);
    pthread_join(b, NULL);
    close(fd);
    const unsigned e = atomic_load(&evidence.errors);
    if (e) return e >= 3 ? 3 : 2;
    if (atomic_load(&evidence.bytes) != EXPECT_BYTES) return 1;
    if (atomic_load(&evidence.sum) != (uint64_t)EXPECT_BYTES * 90U) return 1;
    return 0;
}
static int send_flow(const char *ipv4)
{
    const int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) return 2;
    struct sockaddr_in addr = { .sin_family = AF_INET, .sin_port = htons(PORT) };
    if (inet_pton(AF_INET, ipv4, &addr.sin_addr) != 1) { close(fd); return 2; }
    if (connect(fd, (const struct sockaddr *)&addr, sizeof(addr)) != 0) { close(fd); return 2; }
    uint8_t data[CHUNK];
    memset(data, 90, sizeof(data));
    for (int chunk = 0; chunk < ROUNDS; ++chunk) {
        size_t done = 0;
        while (done < sizeof(data)) {
            const ssize_t n = send(fd, data + done, sizeof(data) - done, MSG_NOSIGNAL);
            if (n < 0 && errno == EINTR) continue;
            if (n <= 0) { close(fd); return 2; }
            done += (size_t)n;
        }
    }
    if (shutdown(fd, SHUT_WR) != 0) { close(fd); return 2; }
    close(fd);
    return 0;
}
static void *self_sender(void *unused)
{
    (void)unused;
    const int status = send_flow("127.0.0.1");
    return (void *)(uintptr_t)(unsigned)status;
}
int main(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "--listen") == 0) {
        const int listen_fd = make_listener();
        return listen_fd < 0 ? 2 : receive_flow(listen_fd);
    }
    if (argc == 3 && strcmp(argv[1], "--send") == 0) return send_flow(argv[2]);
    if (argc == 2 && strcmp(argv[1], "--self") == 0) {
        const int listen_fd = make_listener();
        if (listen_fd < 0) return 2;
        pthread_t sender;
        if (pthread_create(&sender, NULL, self_sender, NULL)) { close(listen_fd); return 2; }
        const int received = receive_flow(listen_fd);
        void *result = NULL;
        if (pthread_join(sender, &result) != 0) return 2;
        if ((uintptr_t)result != 0U) return 2;
        return received;
    }
    return 2;
}
