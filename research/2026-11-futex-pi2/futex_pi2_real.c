/* Original human report: https://lists.openwall.net/linux-kernel/2026/11/10/1519
 * This reproducer is a standalone C program and does not modify kernel logic.
 * Local runtime exit 2 due to real-time scheduling permission. Kernel bug NOT reproduced.
 * Strict GCC and sanitizer compilations were reported clean; not re-run by this publication step.
 * Build: gcc -std=c11 -O0 -g3 -Wall -Wextra -Werror -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wstrict-prototypes -fno-omit-frame-pointer -pthread futex_pi2_real.c -o candidate.debug
 * Full compiler diagnostics, source provenance and reproduction limitations in research/2026-11-futex-pi2/CUMULATIVE_EVIDENCE.txt
 */
/* Adapted from Alexander Krabler's real futex PI2 reproducer, November 10, 2026.
 * https://lists.openwall.net/linux-kernel/2026/11/10/1519
 * 0 = waiter resumed before sampling, 1 = waiter had not resumed, 2 = setup failed.
 * These outcomes alone are not definitive proof of an upstream bug.
 * User supplied no source errors. Preserve our compile errors in the notes.
 */
#define _GNU_SOURCE
#include <errno.h>
#include <linux/futex.h>
#include <pthread.h>
#include <stddef.h>
#include <sched.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <time.h>
#include <unistd.h>

static uint32_t pi_word;
static atomic_bool waiter_completed;

static int64_t monotonic_ns(void)
{
    struct timespec t;
    if (clock_gettime(CLOCK_MONOTONIC, &t) != 0) _Exit(2);
    return (int64_t)t.tv_sec * 1000000000LL + t.tv_nsec;
}
static void attach_one_allowed_cpu(void)
{
    cpu_set_t allowed, selected;
    if (sched_getaffinity(0, sizeof(allowed), &allowed) != 0) _Exit(2);
    int chosen = -1;
    for (int i = 0; i < CPU_SETSIZE; ++i) {
        /* ORIGINAL COMPILE ERROR: CPU_ISSET(i, ...) triggered -Wsign-conversion here. */
        if (CPU_ISSET((size_t)i, &allowed)) { chosen = i; break; }
    }
    if (chosen < 0) _Exit(2);
    CPU_ZERO(&selected);
    /* ORIGINAL COMPILE ERROR: CPU_SET(chosen, ...) triggered -Wsign-conversion here. */
    CPU_SET((size_t)chosen, &selected);
    if (sched_setaffinity(0, sizeof(selected), &selected) != 0) _Exit(2);
}
static void set_fifo(int prio)
{
    const struct sched_param s = {.sched_priority = prio};
    if (sched_setscheduler(0, SCHED_FIFO, &s) != 0) _Exit(2);
}
static int lock_with_one_millisecond_timeout(void)
{
    const int64_t deadline = monotonic_ns() + 1000000LL;
    const struct timespec abs_deadline = {
        .tv_sec = (time_t)(deadline / 1000000000LL),
        .tv_nsec = (long)(deadline % 1000000000LL)
    };
    if (syscall(SYS_futex, &pi_word, FUTEX_LOCK_PI2, 0, &abs_deadline, NULL, 0) != -1)
        return 0;
    return errno;
}
static void *competing_waiter(void *unused)
{
    (void)unused;
    const int result = lock_with_one_millisecond_timeout();
    if (result != ETIMEDOUT) _Exit(2);
    atomic_store_explicit(&waiter_completed, true, memory_order_release);
    return NULL;
}
static void occupy_cpu_ten_milliseconds(void)
{
    const int64_t start = monotonic_ns();
    while (monotonic_ns() - start < 10000000LL) { }
}
int main(void)
{
    pi_word = (uint32_t)syscall(SYS_gettid);
    attach_one_allowed_cpu();
    set_fifo(2);
    pthread_t waiter;
    if (pthread_create(&waiter, NULL, competing_waiter, NULL) != 0) return 2;
    set_fifo(1);
    occupy_cpu_ten_milliseconds();
    const bool seen = atomic_load_explicit(&waiter_completed, memory_order_acquire);
    if (pthread_join(waiter, NULL) != 0) return 2;
    return seen ? 0 : 1;
}
