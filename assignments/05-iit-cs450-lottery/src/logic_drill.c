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
static int64_t blank_01_reject_invalid_tickets(const struct state *s)
{
    (void)s;
    /* FILL: reject_invalid_tickets. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_02_inherit_tickets_at_fork(const struct state *s)
{
    (void)s;
    /* FILL: inherit_tickets_at_fork. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_03_count_runnable_tickets(const struct state *s)
{
    (void)s;
    /* FILL: count_runnable_tickets. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_04_select_lottery_winner(const struct state *s)
{
    (void)s;
    /* FILL: select_lottery_winner. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_05_select_minimum_runnable(const struct state *s)
{
    (void)s;
    /* FILL: select_minimum_runnable. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_06_charge_scheduled_ticks(const struct state *s)
{
    (void)s;
    /* FILL: charge_scheduled_ticks. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_07_check_process_is_running(const struct state *s)
{
    (void)s;
    /* FILL: check_process_is_running. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_08_validate_guest_pointer_range(const struct state *s)
{
    (void)s;
    /* FILL: validate_guest_pointer_range. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_09_compute_observed_cpu_share(const struct state *s)
{
    (void)s;
    /* FILL: compute_observed_cpu_share. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_10_measure_cpu_time_delta(const struct state *s)
{
    (void)s;
    /* FILL: measure_cpu_time_delta. Do not alter the case data. */
    return INT64_MIN;
}

struct trial { unsigned slot; struct state input; int64_t expected; };
int main(int argc, char **argv)
{
    const operation op[10] = {
    blank_01_reject_invalid_tickets,
    blank_02_inherit_tickets_at_fork,
    blank_03_count_runnable_tickets,
    blank_04_select_lottery_winner,
    blank_05_select_minimum_runnable,
    blank_06_charge_scheduled_ticks,
    blank_07_check_process_is_running,
    blank_08_validate_guest_pointer_range,
    blank_09_compute_observed_cpu_share,
    blank_10_measure_cpu_time_delta
    };
    const struct trial samples[20] = {
    {0, {{0, 0, 0, 0, 0, 0}}, -1},
    {0, {{17, 0, 0, 0, 0, 0}}, 0},
    {1, {{47, 0, 0, 0, 0, 0}}, 47},
    {1, {{300, 0, 0, 0, 0, 0}}, 300},
    {2, {{10, 20, 30, 0, 0, 0}}, 60},
    {2, {{4, 9, 16, 0, 0, 0}}, 29},
    {3, {{30, 20, 10, 14, 0, 0}}, 0},
    {3, {{30, 20, 10, 52, 0, 0}}, 2},
    {4, {{11, 3, 7, 0, 0, 0}}, 1},
    {4, {{4, 8, 2, 0, 0, 0}}, 2},
    {5, {{100, 7, 0, 0, 0, 0}}, 107},
    {5, {{2, 10, 0, 0, 0, 0}}, 12},
    {6, {{19, 16, 0, 0, 0, 0}}, 1},
    {6, {{3, 16, 0, 0, 0, 0}}, 0},
    {7, {{1024, 2048, 64, 0, 0, 0}}, 1},
    {7, {{2040, 2048, 64, 0, 0, 0}}, 0},
    {8, {{5, 10, 0, 0, 0, 0}}, 50},
    {8, {{3, 12, 0, 0, 0, 0}}, 25},
    {9, {{150, 100, 0, 0, 0, 0}}, 50},
    {9, {{180, 120, 0, 0, 0, 0}}, 60},
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
