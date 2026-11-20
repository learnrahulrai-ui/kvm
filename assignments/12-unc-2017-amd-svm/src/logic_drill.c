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
static int64_t blank_01_detect_svm_enabled(const struct state *s)
{
    (void)s;
    /* FILL: detect_svm_enabled. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_02_validate_nested_page_range(const struct state *s)
{
    (void)s;
    /* FILL: validate_nested_page_range. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_03_align_guest_page(const struct state *s)
{
    (void)s;
    /* FILL: align_guest_page. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_04_enable_vmcb_intercept(const struct state *s)
{
    (void)s;
    /* FILL: enable_vmcb_intercept. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_05_clear_nested_write_permission(const struct state *s)
{
    (void)s;
    /* FILL: clear_nested_write_permission. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_06_dispatch_vmexit_reason(const struct state *s)
{
    (void)s;
    /* FILL: dispatch_vmexit_reason. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_07_choose_smallest_service_queue(const struct state *s)
{
    (void)s;
    /* FILL: choose_smallest_service_queue. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_08_validate_vmcb_length(const struct state *s)
{
    (void)s;
    /* FILL: validate_vmcb_length. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_09_copy_guest_state_field(const struct state *s)
{
    (void)s;
    /* FILL: copy_guest_state_field. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_10_measure_exit_count_delta(const struct state *s)
{
    (void)s;
    /* FILL: measure_exit_count_delta. Do not alter the case data. */
    return INT64_MIN;
}

struct trial { unsigned slot; struct state input; int64_t expected; };
int main(int argc, char **argv)
{
    const operation op[10] = {
    blank_01_detect_svm_enabled,
    blank_02_validate_nested_page_range,
    blank_03_align_guest_page,
    blank_04_enable_vmcb_intercept,
    blank_05_clear_nested_write_permission,
    blank_06_dispatch_vmexit_reason,
    blank_07_choose_smallest_service_queue,
    blank_08_validate_vmcb_length,
    blank_09_copy_guest_state_field,
    blank_10_measure_exit_count_delta
    };
    const struct trial samples[20] = {
    {0, {{19, 16, 0, 0, 0, 0}}, 1},
    {0, {{3, 16, 0, 0, 0, 0}}, 0},
    {1, {{4096, 4096, 12288, 0, 0, 0}}, 1},
    {1, {{16384, 4096, 12288, 0, 0, 0}}, 0},
    {2, {{4660, 4096, 0, 0, 0, 0}}, 4096},
    {2, {{8192, 4096, 0, 0, 0, 0}}, 8192},
    {3, {{3, 4, 0, 0, 0, 0}}, 7},
    {3, {{1, 16, 0, 0, 0, 0}}, 17},
    {4, {{23, 4, 0, 0, 0, 0}}, 19},
    {4, {{17, 16, 0, 0, 0, 0}}, 1},
    {5, {{30, 20, 10, 14, 0, 0}}, 0},
    {5, {{30, 20, 10, 52, 0, 0}}, 2},
    {6, {{11, 3, 7, 0, 0, 0}}, 1},
    {6, {{4, 8, 2, 0, 0, 0}}, 2},
    {7, {{0, 0, 0, 0, 0, 0}}, -1},
    {7, {{17, 0, 0, 0, 0, 0}}, 0},
    {8, {{47, 0, 0, 0, 0, 0}}, 47},
    {8, {{300, 0, 0, 0, 0, 0}}, 300},
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
