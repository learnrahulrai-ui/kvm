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
static int64_t blank_01_measure_vcpu_cpu_time_delta(const struct state *s)
{
    (void)s;
    /* FILL: measure_vcpu_cpu_time_delta. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_02_derive_percent_cpu_use(const struct state *s)
{
    (void)s;
    /* FILL: derive_percent_cpu_use. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_03_choose_highest_pcpu_load(const struct state *s)
{
    (void)s;
    /* FILL: choose_highest_pcpu_load. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_04_choose_least_loaded_pcpu(const struct state *s)
{
    (void)s;
    /* FILL: choose_least_loaded_pcpu. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_05_limit_balloon_allocation(const struct state *s)
{
    (void)s;
    /* FILL: limit_balloon_allocation. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_06_validate_requested_resources(const struct state *s)
{
    (void)s;
    /* FILL: validate_requested_resources. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_07_total_guest_memory_target(const struct state *s)
{
    (void)s;
    /* FILL: total_guest_memory_target. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_08_pages_required_for_balloon(const struct state *s)
{
    (void)s;
    /* FILL: pages_required_for_balloon. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_09_check_target_address_range(const struct state *s)
{
    (void)s;
    /* FILL: check_target_address_range. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_10_verify_vm_state_flag(const struct state *s)
{
    (void)s;
    /* FILL: verify_vm_state_flag. Do not alter the case data. */
    return INT64_MIN;
}

struct trial { unsigned slot; struct state input; int64_t expected; };
int main(int argc, char **argv)
{
    const operation op[10] = {
    blank_01_measure_vcpu_cpu_time_delta,
    blank_02_derive_percent_cpu_use,
    blank_03_choose_highest_pcpu_load,
    blank_04_choose_least_loaded_pcpu,
    blank_05_limit_balloon_allocation,
    blank_06_validate_requested_resources,
    blank_07_total_guest_memory_target,
    blank_08_pages_required_for_balloon,
    blank_09_check_target_address_range,
    blank_10_verify_vm_state_flag
    };
    const struct trial samples[20] = {
    {0, {{150, 100, 0, 0, 0, 0}}, 50},
    {0, {{180, 120, 0, 0, 0, 0}}, 60},
    {1, {{5, 10, 0, 0, 0, 0}}, 50},
    {1, {{3, 12, 0, 0, 0, 0}}, 25},
    {2, {{11, 3, 7, 0, 0, 0}}, 0},
    {2, {{4, 8, 12, 0, 0, 0}}, 2},
    {3, {{11, 3, 7, 0, 0, 0}}, 1},
    {3, {{4, 8, 2, 0, 0, 0}}, 2},
    {4, {{3, 8, 0, 0, 0, 0}}, 3},
    {4, {{12, 7, 0, 0, 0, 0}}, 7},
    {5, {{0, 0, 0, 0, 0, 0}}, -1},
    {5, {{17, 0, 0, 0, 0, 0}}, 0},
    {6, {{10, 20, 30, 0, 0, 0}}, 60},
    {6, {{4, 9, 16, 0, 0, 0}}, 29},
    {7, {{4097, 4096, 0, 0, 0, 0}}, 2},
    {7, {{8192, 4096, 0, 0, 0, 0}}, 2},
    {8, {{4096, 4096, 12288, 0, 0, 0}}, 1},
    {8, {{16384, 4096, 12288, 0, 0, 0}}, 0},
    {9, {{19, 16, 0, 0, 0, 0}}, 1},
    {9, {{3, 16, 0, 0, 0, 0}}, 0},
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
