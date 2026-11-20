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
static int64_t blank_01_validate_page_address(const struct state *s)
{
    (void)s;
    /* FILL: validate_page_address. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_02_check_reference_bit(const struct state *s)
{
    (void)s;
    /* FILL: check_reference_bit. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_03_choose_clock_victim(const struct state *s)
{
    (void)s;
    /* FILL: choose_clock_victim. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_04_clear_reference_permission(const struct state *s)
{
    (void)s;
    /* FILL: clear_reference_permission. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_05_page_align_fault(const struct state *s)
{
    (void)s;
    /* FILL: page_align_fault. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_06_calculate_swap_pages(const struct state *s)
{
    (void)s;
    /* FILL: calculate_swap_pages. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_07_reject_zero_page_size(const struct state *s)
{
    (void)s;
    /* FILL: reject_zero_page_size. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_08_increment_clock_hand(const struct state *s)
{
    (void)s;
    /* FILL: increment_clock_hand. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_09_bound_frame_allocation(const struct state *s)
{
    (void)s;
    /* FILL: bound_frame_allocation. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_10_copy_disk_slot_number(const struct state *s)
{
    (void)s;
    /* FILL: copy_disk_slot_number. Do not alter the case data. */
    return INT64_MIN;
}

struct trial { unsigned slot; struct state input; int64_t expected; };
int main(int argc, char **argv)
{
    const operation op[10] = {
    blank_01_validate_page_address,
    blank_02_check_reference_bit,
    blank_03_choose_clock_victim,
    blank_04_clear_reference_permission,
    blank_05_page_align_fault,
    blank_06_calculate_swap_pages,
    blank_07_reject_zero_page_size,
    blank_08_increment_clock_hand,
    blank_09_bound_frame_allocation,
    blank_10_copy_disk_slot_number
    };
    const struct trial samples[20] = {
    {0, {{4096, 4096, 12288, 0, 0, 0}}, 1},
    {0, {{16384, 4096, 12288, 0, 0, 0}}, 0},
    {1, {{19, 16, 0, 0, 0, 0}}, 1},
    {1, {{3, 16, 0, 0, 0, 0}}, 0},
    {2, {{11, 3, 7, 0, 0, 0}}, 1},
    {2, {{4, 8, 2, 0, 0, 0}}, 2},
    {3, {{23, 4, 0, 0, 0, 0}}, 19},
    {3, {{17, 16, 0, 0, 0, 0}}, 1},
    {4, {{4660, 4096, 0, 0, 0, 0}}, 4096},
    {4, {{8192, 4096, 0, 0, 0, 0}}, 8192},
    {5, {{4097, 4096, 0, 0, 0, 0}}, 2},
    {5, {{8192, 4096, 0, 0, 0, 0}}, 2},
    {6, {{0, 0, 0, 0, 0, 0}}, -1},
    {6, {{17, 0, 0, 0, 0, 0}}, 0},
    {7, {{100, 7, 0, 0, 0, 0}}, 107},
    {7, {{2, 10, 0, 0, 0, 0}}, 12},
    {8, {{3, 8, 0, 0, 0, 0}}, 3},
    {8, {{12, 7, 0, 0, 0, 0}}, 7},
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
