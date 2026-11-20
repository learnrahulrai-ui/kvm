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
static int64_t blank_01_find_superpage_base(const struct state *s)
{
    (void)s;
    /* FILL: find_superpage_base. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_02_find_superpage_end(const struct state *s)
{
    (void)s;
    /* FILL: find_superpage_end. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_03_count_4k_pages_in_region(const struct state *s)
{
    (void)s;
    /* FILL: count_4k_pages_in_region. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_04_verify_address_inside_mapping(const struct state *s)
{
    (void)s;
    /* FILL: verify_address_inside_mapping. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_05_test_present_flag(const struct state *s)
{
    (void)s;
    /* FILL: test_present_flag. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_06_set_leaf_permission(const struct state *s)
{
    (void)s;
    /* FILL: set_leaf_permission. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_07_remove_parent_write_bit(const struct state *s)
{
    (void)s;
    /* FILL: remove_parent_write_bit. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_08_validate_superpage_size(const struct state *s)
{
    (void)s;
    /* FILL: validate_superpage_size. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_09_limit_copy_length(const struct state *s)
{
    (void)s;
    /* FILL: limit_copy_length. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_10_inherit_physical_page_index(const struct state *s)
{
    (void)s;
    /* FILL: inherit_physical_page_index. Do not alter the case data. */
    return INT64_MIN;
}

struct trial { unsigned slot; struct state input; int64_t expected; };
int main(int argc, char **argv)
{
    const operation op[10] = {
    blank_01_find_superpage_base,
    blank_02_find_superpage_end,
    blank_03_count_4k_pages_in_region,
    blank_04_verify_address_inside_mapping,
    blank_05_test_present_flag,
    blank_06_set_leaf_permission,
    blank_07_remove_parent_write_bit,
    blank_08_validate_superpage_size,
    blank_09_limit_copy_length,
    blank_10_inherit_physical_page_index
    };
    const struct trial samples[20] = {
    {0, {{4660, 4096, 0, 0, 0, 0}}, 4096},
    {0, {{8192, 4096, 0, 0, 0, 0}}, 8192},
    {1, {{4097, 4096, 0, 0, 0, 0}}, 8192},
    {1, {{8192, 4096, 0, 0, 0, 0}}, 8192},
    {2, {{2097152, 4096, 0, 0, 0, 0}}, 512},
    {2, {{4194304, 4096, 0, 0, 0, 0}}, 1024},
    {3, {{4096, 4096, 12288, 0, 0, 0}}, 1},
    {3, {{16384, 4096, 12288, 0, 0, 0}}, 0},
    {4, {{19, 16, 0, 0, 0, 0}}, 1},
    {4, {{3, 16, 0, 0, 0, 0}}, 0},
    {5, {{3, 4, 0, 0, 0, 0}}, 7},
    {5, {{1, 16, 0, 0, 0, 0}}, 17},
    {6, {{23, 4, 0, 0, 0, 0}}, 19},
    {6, {{17, 16, 0, 0, 0, 0}}, 1},
    {7, {{0, 0, 0, 0, 0, 0}}, -1},
    {7, {{17, 0, 0, 0, 0, 0}}, 0},
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
