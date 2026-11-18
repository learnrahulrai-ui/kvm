/* Original human report: https://lkml.iu.edu/hypermail/linux/kernel/2610.3/01150.html
 * This reproducer is a standalone C program and does not modify kernel logic.
 * 600000 getpgid calls, exit 0. No BPF hook attached. Kernel bug NOT reproduced.
 * Strict GCC and sanitizer compilations were reported clean; not re-run by this publication step.
 * Build: gcc -std=c11 -O0 -g3 -Wall -Wextra -Werror -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wstrict-prototypes -fno-omit-frame-pointer -pthread syscall_pressure.c -o candidate.debug
 * Full compiler diagnostics, source provenance and reproduction limitations in research/2026-10-bpf-preemption/CUMULATIVE_EVIDENCE.txt
 */
/* Real syscall load. Does not itself establish a BPF missing-event defect.
 * USER_SOURCE_ERRORS: none supplied. Keep earlier compile-errors below.
 */
#define _GNU_SOURCE
#include <errno.h>
#include <pthread.h>
#include <stddef.h>
#include <sched.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
typedef struct { uint64_t observed, errors; } Record;
static Record records[2];
static atomic_uint ready;
static atomic_uint finish;
static void pin_to_first_allowed_cpu(void)
{
    cpu_set_t allowed, selected;
    if (sched_getaffinity(0, sizeof(allowed), &allowed)) _Exit(2);
    int chosen=-1;
    for (int i=0; i<CPU_SETSIZE; i++) /* ORIGINAL COMPILE ERROR: CPU_ISSET(i, ...) triggered -Wsign-conversion at this line. */
    if (CPU_ISSET((size_t)i,&allowed)) { chosen=i; break; }
    if (chosen<0) _Exit(2);
    CPU_ZERO(&selected); /* ORIGINAL COMPILE ERROR: CPU_SET(chosen, ...) triggered -Wsign-conversion at this line. */
    CPU_SET((size_t)chosen,&selected);
    if (sched_setaffinity(0,sizeof(selected),&selected)) _Exit(2);
}
static void *drive_kernel_calls(void *id_arg)
{
    const uintptr_t id=(uintptr_t)id_arg;
    pin_to_first_allowed_cpu();
    atomic_fetch_add_explicit(&ready,1,memory_order_release);
    while(atomic_load_explicit(&ready,memory_order_acquire)!=2) { sched_yield(); }
    for (uint64_t i=0;i<300000;i++) {
        const pid_t v=getpgid(0);
        records[id].observed++;
        records[id].errors += (v == (pid_t)-1);
        if (id == 1 && (i%16)==0) sched_yield();
    }
    atomic_fetch_add_explicit(&finish,1,memory_order_release);
    return NULL;
}
int main(void)
{
    pthread_t a,b;
    if (pthread_create(&a,NULL,drive_kernel_calls,(void *)(uintptr_t)0)) return 2;
    if (pthread_create(&b,NULL,drive_kernel_calls,(void *)(uintptr_t)1)) return 2;
    if (pthread_join(a,NULL)||pthread_join(b,NULL)) return 2;
    if (atomic_load_explicit(&finish,memory_order_acquire)!=2) return 3;
    if (records[0].observed!=300000 || records[1].observed!=300000) return 4;
    if (records[0].errors||records[1].errors) return 5;
    return 0;
}
