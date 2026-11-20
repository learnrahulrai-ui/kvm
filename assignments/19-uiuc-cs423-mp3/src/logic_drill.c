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
static int64_t blank_01_reject_invalid_registration(const struct state *s)
{
    (void)s;
    /* FILL: reject_invalid_registration. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_02_test_task_registered(const struct state *s)
{
    (void)s;
    /* FILL: test_task_registered. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_03_minor_faults_since_last_sample(const struct state *s)
{
    (void)s;
    /* FILL: minor_faults_since_last_sample. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_04_advance_sample_counter(const struct state *s)
{
    (void)s;
    /* FILL: advance_sample_counter. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_05_total_fault_events(const struct state *s)
{
    (void)s;
    /* FILL: total_fault_events. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_06_derive_cpu_utilisation_percent(const struct state *s)
{
    (void)s;
    /* FILL: derive_cpu_utilisation_percent. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_07_check_pid_in_valid_range(const struct state *s)
{
    (void)s;
    /* FILL: check_pid_in_valid_range. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_08_bound_buffer_index(const struct state *s)
{
    (void)s;
    /* FILL: bound_buffer_index. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_09_choose_peak_fault_rate(const struct state *s)
{
    (void)s;
    /* FILL: choose_peak_fault_rate. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_10_copy_task_id(const struct state *s)
{
    (void)s;
    /* FILL: copy_task_id. Do not alter the case data. */
    return INT64_MIN;
}

struct trial { unsigned slot; struct state input; int64_t expected; };
int main(int argc, char **argv)
{
    const operation op[10] = {
    blank_01_reject_invalid_registration,
    blank_02_test_task_registered,
    blank_03_minor_faults_since_last_sample,
    blank_04_advance_sample_counter,
    blank_05_total_fault_events,
    blank_06_derive_cpu_utilisation_percent,
    blank_07_check_pid_in_valid_range,
    blank_08_bound_buffer_index,
    blank_09_choose_peak_fault_rate,
    blank_10_copy_task_id
    };
    const struct trial samples[20] = {
    {0, {{0, 0, 0, 0, 0, 0}}, -1},
    {0, {{17, 0, 0, 0, 0, 0}}, 0},
    {1, {{19, 16, 0, 0, 0, 0}}, 1},
    {1, {{3, 16, 0, 0, 0, 0}}, 0},
    {2, {{150, 100, 0, 0, 0, 0}}, 50},
    {2, {{180, 120, 0, 0, 0, 0}}, 60},
    {3, {{100, 7, 0, 0, 0, 0}}, 107},
    {3, {{2, 10, 0, 0, 0, 0}}, 12},
    {4, {{10, 20, 30, 0, 0, 0}}, 60},
    {4, {{4, 9, 16, 0, 0, 0}}, 29},
    {5, {{5, 10, 0, 0, 0, 0}}, 50},
    {5, {{3, 12, 0, 0, 0, 0}}, 25},
    {6, {{4096, 4096, 12288, 0, 0, 0}}, 1},
    {6, {{16384, 4096, 12288, 0, 0, 0}}, 0},
    {7, {{3, 8, 0, 0, 0, 0}}, 3},
    {7, {{12, 7, 0, 0, 0, 0}}, 7},
    {8, {{3, 8, 0, 0, 0, 0}}, 8},
    {8, {{12, 7, 0, 0, 0, 0}}, 12},
    {9, {{47, 0, 0, 0, 0, 0}}, 47},
    {9, {{300, 0, 0, 0, 0, 0}}, 300},
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
