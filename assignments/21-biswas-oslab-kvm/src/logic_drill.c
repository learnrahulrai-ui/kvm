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
static int64_t blank_01_validate_positive_region_size(const struct state *s)
{
    (void)s;
    /* FILL: validate_positive_region_size. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_02_guest_address_in_region(const struct state *s)
{
    (void)s;
    /* FILL: guest_address_in_region. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_03_calculate_guest_page_count(const struct state *s)
{
    (void)s;
    /* FILL: calculate_guest_page_count. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_04_test_guest_permission_bit(const struct state *s)
{
    (void)s;
    /* FILL: test_guest_permission_bit. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_05_remove_guest_write_permission(const struct state *s)
{
    (void)s;
    /* FILL: remove_guest_write_permission. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_06_enable_guest_permission_bit(const struct state *s)
{
    (void)s;
    /* FILL: enable_guest_permission_bit. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_07_detect_overlapping_memslots(const struct state *s)
{
    (void)s;
    /* FILL: detect_overlapping_memslots. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_08_copy_guest_register_value(const struct state *s)
{
    (void)s;
    /* FILL: copy_guest_register_value. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_09_measure_exit_counter_change(const struct state *s)
{
    (void)s;
    /* FILL: measure_exit_counter_change. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_10_limit_io_transfer_length(const struct state *s)
{
    (void)s;
    /* FILL: limit_io_transfer_length. Do not alter the case data. */
    return INT64_MIN;
}

struct trial { unsigned slot; struct state input; int64_t expected; };
int main(int argc, char **argv)
{
    const operation op[10] = {
    blank_01_validate_positive_region_size,
    blank_02_guest_address_in_region,
    blank_03_calculate_guest_page_count,
    blank_04_test_guest_permission_bit,
    blank_05_remove_guest_write_permission,
    blank_06_enable_guest_permission_bit,
    blank_07_detect_overlapping_memslots,
    blank_08_copy_guest_register_value,
    blank_09_measure_exit_counter_change,
    blank_10_limit_io_transfer_length
    };
    const struct trial samples[20] = {
    {0, {{0, 0, 0, 0, 0, 0}}, -1},
    {0, {{17, 0, 0, 0, 0, 0}}, 0},
    {1, {{4096, 4096, 12288, 0, 0, 0}}, 1},
    {1, {{16384, 4096, 12288, 0, 0, 0}}, 0},
    {2, {{4097, 4096, 0, 0, 0, 0}}, 2},
    {2, {{8192, 4096, 0, 0, 0, 0}}, 2},
    {3, {{19, 16, 0, 0, 0, 0}}, 1},
    {3, {{3, 16, 0, 0, 0, 0}}, 0},
    {4, {{23, 4, 0, 0, 0, 0}}, 19},
    {4, {{17, 16, 0, 0, 0, 0}}, 1},
    {5, {{3, 4, 0, 0, 0, 0}}, 7},
    {5, {{1, 16, 0, 0, 0, 0}}, 17},
    {6, {{0, 4096, 2048, 8192, 0, 0}}, 1},
    {6, {{0, 4096, 4096, 8192, 0, 0}}, 0},
    {7, {{47, 0, 0, 0, 0, 0}}, 47},
    {7, {{300, 0, 0, 0, 0, 0}}, 300},
    {8, {{150, 100, 0, 0, 0, 0}}, 50},
    {8, {{180, 120, 0, 0, 0, 0}}, 60},
    {9, {{3, 8, 0, 0, 0, 0}}, 3},
    {9, {{12, 7, 0, 0, 0, 0}}, 7},
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
