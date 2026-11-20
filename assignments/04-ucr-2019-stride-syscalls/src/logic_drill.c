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
static int64_t blank_01_validate_ticket_update(const struct state *s)
{
    (void)s;
    /* FILL: validate_ticket_update. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_02_sum_runnable_tickets(const struct state *s)
{
    (void)s;
    /* FILL: sum_runnable_tickets. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_03_draw_lottery_winner(const struct state *s)
{
    (void)s;
    /* FILL: draw_lottery_winner. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_04_derive_stride_increment(const struct state *s)
{
    (void)s;
    /* FILL: derive_stride_increment. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_05_select_minimum_pass(const struct state *s)
{
    (void)s;
    /* FILL: select_minimum_pass. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_06_increment_service_counter(const struct state *s)
{
    (void)s;
    /* FILL: increment_service_counter. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_07_inherit_ticket_setting(const struct state *s)
{
    (void)s;
    /* FILL: inherit_ticket_setting. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_08_detect_runnable_status(const struct state *s)
{
    (void)s;
    /* FILL: detect_runnable_status. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_09_derive_share_percent(const struct state *s)
{
    (void)s;
    /* FILL: derive_share_percent. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_10_measure_runtime_delta(const struct state *s)
{
    (void)s;
    /* FILL: measure_runtime_delta. Do not alter the case data. */
    return INT64_MIN;
}

struct trial { unsigned slot; struct state input; int64_t expected; };
int main(int argc, char **argv)
{
    const operation op[10] = {
    blank_01_validate_ticket_update,
    blank_02_sum_runnable_tickets,
    blank_03_draw_lottery_winner,
    blank_04_derive_stride_increment,
    blank_05_select_minimum_pass,
    blank_06_increment_service_counter,
    blank_07_inherit_ticket_setting,
    blank_08_detect_runnable_status,
    blank_09_derive_share_percent,
    blank_10_measure_runtime_delta
    };
    const struct trial samples[20] = {
    {0, {{0, 0, 0, 0, 0, 0}}, -1},
    {0, {{17, 0, 0, 0, 0, 0}}, 0},
    {1, {{10, 20, 30, 0, 0, 0}}, 60},
    {1, {{4, 9, 16, 0, 0, 0}}, 29},
    {2, {{30, 20, 10, 14, 0, 0}}, 0},
    {2, {{30, 20, 10, 52, 0, 0}}, 2},
    {3, {{10000, 100, 0, 0, 0, 0}}, 100},
    {3, {{10000, 200, 0, 0, 0, 0}}, 50},
    {4, {{11, 3, 7, 0, 0, 0}}, 1},
    {4, {{4, 8, 2, 0, 0, 0}}, 2},
    {5, {{100, 7, 0, 0, 0, 0}}, 107},
    {5, {{2, 10, 0, 0, 0, 0}}, 12},
    {6, {{47, 0, 0, 0, 0, 0}}, 47},
    {6, {{300, 0, 0, 0, 0, 0}}, 300},
    {7, {{19, 16, 0, 0, 0, 0}}, 1},
    {7, {{3, 16, 0, 0, 0, 0}}, 0},
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
