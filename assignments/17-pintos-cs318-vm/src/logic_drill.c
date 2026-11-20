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
static int64_t blank_01_validate_faulting_address(const struct state *s)
{
    (void)s;
    /* FILL: validate_faulting_address. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_02_first_unreferenced_from_clock_hand(const struct state *s)
{
    (void)s;
    /* FILL: first_unreferenced_from_clock_hand. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_03_clear_accessed_flag(const struct state *s)
{
    (void)s;
    /* FILL: clear_accessed_flag. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_04_test_dirty_flag(const struct state *s)
{
    (void)s;
    /* FILL: test_dirty_flag. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_05_align_fault_to_page(const struct state *s)
{
    (void)s;
    /* FILL: align_fault_to_page. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_06_calculate_swap_slots_required(const struct state *s)
{
    (void)s;
    /* FILL: calculate_swap_slots_required. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_07_validate_stack_growth_size(const struct state *s)
{
    (void)s;
    /* FILL: validate_stack_growth_size. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_08_increment_frame_reference(const struct state *s)
{
    (void)s;
    /* FILL: increment_frame_reference. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_09_bound_swap_slot_number(const struct state *s)
{
    (void)s;
    /* FILL: bound_swap_slot_number. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_10_save_swap_slot_index(const struct state *s)
{
    (void)s;
    /* FILL: save_swap_slot_index. Do not alter the case data. */
    return INT64_MIN;
}

struct trial { unsigned slot; struct state input; int64_t expected; };
int main(int argc, char **argv)
{
    const operation op[10] = {
    blank_01_validate_faulting_address,
    blank_02_first_unreferenced_from_clock_hand,
    blank_03_clear_accessed_flag,
    blank_04_test_dirty_flag,
    blank_05_align_fault_to_page,
    blank_06_calculate_swap_slots_required,
    blank_07_validate_stack_growth_size,
    blank_08_increment_frame_reference,
    blank_09_bound_swap_slot_number,
    blank_10_save_swap_slot_index
    };
    const struct trial samples[20] = {
    {0, {{4096, 4096, 12288, 0, 0, 0}}, 1},
    {0, {{16384, 4096, 12288, 0, 0, 0}}, 0},
    {1, {{1, 0, 1, 1, 0, 0}}, 1},
    {1, {{1, 1, 0, 1, 3, 0}}, 2},
    {2, {{23, 4, 0, 0, 0, 0}}, 19},
    {2, {{17, 16, 0, 0, 0, 0}}, 1},
    {3, {{19, 16, 0, 0, 0, 0}}, 1},
    {3, {{3, 16, 0, 0, 0, 0}}, 0},
    {4, {{4660, 4096, 0, 0, 0, 0}}, 4096},
    {4, {{8192, 4096, 0, 0, 0, 0}}, 8192},
    {5, {{4097, 4096, 0, 0, 0, 0}}, 2},
    {5, {{8192, 4096, 0, 0, 0, 0}}, 2},
    {6, {{0, 0, 0, 0, 0, 0}}, -1},
    {6, {{17, 0, 0, 0, 0, 0}}, 0},
    {7, {{1, 0, 0, 0, 0, 0}}, 2},
    {7, {{4, 0, 0, 0, 0, 0}}, 5},
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
