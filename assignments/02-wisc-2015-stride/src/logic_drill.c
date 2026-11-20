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
static int64_t blank_01_validate_new_tickets(const struct state *s)
{
    (void)s;
    /* FILL: validate_new_tickets. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_02_derive_stride_increment(const struct state *s)
{
    (void)s;
    /* FILL: derive_stride_increment. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_03_choose_smallest_pass(const struct state *s)
{
    (void)s;
    /* FILL: choose_smallest_pass. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_04_charge_runtime(const struct state *s)
{
    (void)s;
    /* FILL: charge_runtime. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_05_inherit_parent_tickets(const struct state *s)
{
    (void)s;
    /* FILL: inherit_parent_tickets. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_06_normalise_smallest_pass(const struct state *s)
{
    (void)s;
    /* FILL: normalise_smallest_pass. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_07_compute_service_gap(const struct state *s)
{
    (void)s;
    /* FILL: compute_service_gap. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_08_check_runnable_state(const struct state *s)
{
    (void)s;
    /* FILL: check_runnable_state. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_09_sum_competing_tickets(const struct state *s)
{
    (void)s;
    /* FILL: sum_competing_tickets. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_10_derive_observed_cpu_share(const struct state *s)
{
    (void)s;
    /* FILL: derive_observed_cpu_share. Do not alter the case data. */
    return INT64_MIN;
}

struct trial { unsigned slot; struct state input; int64_t expected; };
int main(int argc, char **argv)
{
    const operation op[10] = {
    blank_01_validate_new_tickets,
    blank_02_derive_stride_increment,
    blank_03_choose_smallest_pass,
    blank_04_charge_runtime,
    blank_05_inherit_parent_tickets,
    blank_06_normalise_smallest_pass,
    blank_07_compute_service_gap,
    blank_08_check_runnable_state,
    blank_09_sum_competing_tickets,
    blank_10_derive_observed_cpu_share
    };
    const struct trial samples[20] = {
    {0, {{0, 0, 0, 0, 0, 0}}, -1},
    {0, {{17, 0, 0, 0, 0, 0}}, 0},
    {1, {{10000, 100, 0, 0, 0, 0}}, 100},
    {1, {{10000, 200, 0, 0, 0, 0}}, 50},
    {2, {{11, 3, 7, 0, 0, 0}}, 1},
    {2, {{4, 8, 2, 0, 0, 0}}, 2},
    {3, {{100, 7, 0, 0, 0, 0}}, 107},
    {3, {{2, 10, 0, 0, 0, 0}}, 12},
    {4, {{47, 0, 0, 0, 0, 0}}, 47},
    {4, {{300, 0, 0, 0, 0, 0}}, 300},
    {5, {{3, 8, 0, 0, 0, 0}}, 3},
    {5, {{12, 7, 0, 0, 0, 0}}, 7},
    {6, {{150, 100, 0, 0, 0, 0}}, 50},
    {6, {{180, 120, 0, 0, 0, 0}}, 60},
    {7, {{19, 16, 0, 0, 0, 0}}, 1},
    {7, {{3, 16, 0, 0, 0, 0}}, 0},
    {8, {{10, 20, 30, 0, 0, 0}}, 60},
    {8, {{4, 9, 16, 0, 0, 0}}, 29},
    {9, {{5, 10, 0, 0, 0, 0}}, 50},
    {9, {{3, 12, 0, 0, 0, 0}}, 25},
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
