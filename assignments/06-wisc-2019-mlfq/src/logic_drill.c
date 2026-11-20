/* Assignment-specific causal worksheet. The original university kernel is in upstream/.
 * INT64_MIN represents an UNIMPLEMENTED student function, not a kernel failure.
 * The twenty fixtures are CONSTRUCTED tests, never measured machine data.
 * Build: make all ; observe: make status ; prove completed work: make check
 */
#define _POSIX_C_SOURCE 200809L
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
struct state { int64_t value[6]; };
typedef int64_t (*operation)(const struct state *);
static int64_t blank_01_initial_queue_assignment(const struct state *s)
{
    (void)s;
    /* FILL: initial_queue_assignment. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_02_choose_highest_priority(const struct state *s)
{
    (void)s;
    /* FILL: choose_highest_priority. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_03_charge_elapsed_cpu(const struct state *s)
{
    (void)s;
    /* FILL: charge_elapsed_cpu. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_04_test_expired_quantum(const struct state *s)
{
    (void)s;
    /* FILL: test_expired_quantum. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_05_test_runnable_state(const struct state *s)
{
    (void)s;
    /* FILL: test_runnable_state. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_06_bound_queue_level(const struct state *s)
{
    (void)s;
    /* FILL: bound_queue_level. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_07_measure_waiting_ticks(const struct state *s)
{
    (void)s;
    /* FILL: measure_waiting_ticks. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_08_reject_outside_queue(const struct state *s)
{
    (void)s;
    /* FILL: reject_outside_queue. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_09_sum_ready_work(const struct state *s)
{
    (void)s;
    /* FILL: sum_ready_work. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_10_reject_bad_parameter(const struct state *s)
{
    (void)s;
    /* FILL: reject_bad_parameter. Do not alter the case data. */
    return INT64_MIN;
}

struct trial { unsigned slot; struct state input; int64_t expected; };
int main(int argc, char **argv)
{
    const operation op[10] = {
    blank_01_initial_queue_assignment,
    blank_02_choose_highest_priority,
    blank_03_charge_elapsed_cpu,
    blank_04_test_expired_quantum,
    blank_05_test_runnable_state,
    blank_06_bound_queue_level,
    blank_07_measure_waiting_ticks,
    blank_08_reject_outside_queue,
    blank_09_sum_ready_work,
    blank_10_reject_bad_parameter
    };
    const struct trial samples[20] = {
    {0, {{47, 0, 0, 0, 0, 0}}, 47},
    {0, {{300, 0, 0, 0, 0, 0}}, 300},
    {1, {{11, 3, 7, 0, 0, 0}}, 1},
    {1, {{4, 8, 2, 0, 0, 0}}, 2},
    {2, {{100, 7, 0, 0, 0, 0}}, 107},
    {2, {{2, 10, 0, 0, 0, 0}}, 12},
    {3, {{5, 3, 0, 0, 0, 0}}, 1},
    {3, {{2, 7, 0, 0, 0, 0}}, 0},
    {4, {{19, 16, 0, 0, 0, 0}}, 1},
    {4, {{3, 16, 0, 0, 0, 0}}, 0},
    {5, {{3, 8, 0, 0, 0, 0}}, 3},
    {5, {{12, 7, 0, 0, 0, 0}}, 7},
    {6, {{150, 100, 0, 0, 0, 0}}, 50},
    {6, {{180, 120, 0, 0, 0, 0}}, 60},
    {7, {{4096, 4096, 12288, 0, 0, 0}}, 1},
    {7, {{16384, 4096, 12288, 0, 0, 0}}, 0},
    {8, {{10, 20, 30, 0, 0, 0}}, 60},
    {8, {{4, 9, 16, 0, 0, 0}}, 29},
    {9, {{0, 0, 0, 0, 0, 0}}, -1},
    {9, {{17, 0, 0, 0, 0, 0}}, 0},
    };
    unsigned pass = 0, blank = 0, fail = 0;
    for (size_t i = 0; i < sizeof(samples)/sizeof(samples[0]); ++i) {
        const struct trial *p = &samples[i];
        const int64_t actual = op[p->slot](&p->input);
        const int missing = actual == INT64_MIN;
        const int correct = !missing && actual == p->expected;
        if (missing) ++blank;
        else if (correct) ++pass;
        else ++fail;
        printf("slot=%02u input=[%" PRId64 ",%" PRId64 ",%" PRId64 ",%" PRId64 ",%" PRId64 ",%" PRId64 "] actual=%" PRId64 " expected=%" PRId64 " %s\n",
            p->slot + 1, p->input.value[0], p->input.value[1], p->input.value[2],
            p->input.value[3], p->input.value[4], p->input.value[5],
            actual, p->expected, missing ? "BLANK" : correct ? "PASS" : "FAIL");
    }
    printf("pass=%u blank=%u fail=%u\n", pass, blank, fail);
    if (argc == 2 && strcmp(argv[1], "--status") == 0) return 0;
    return (blank || fail) ? 1 : 0;
}
