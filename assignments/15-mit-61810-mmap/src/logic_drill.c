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
static int64_t blank_01_check_mapping_address(const struct state *s)
{
    (void)s;
    /* FILL: check_mapping_address. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_02_round_size_to_page_boundary(const struct state *s)
{
    (void)s;
    /* FILL: round_size_to_page_boundary. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_03_round_fault_address_down(const struct state *s)
{
    (void)s;
    /* FILL: round_fault_address_down. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_04_number_of_pages_to_load(const struct state *s)
{
    (void)s;
    /* FILL: number_of_pages_to_load. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_05_validate_nonzero_mapping(const struct state *s)
{
    (void)s;
    /* FILL: validate_nonzero_mapping. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_06_check_unmap_overlap(const struct state *s)
{
    (void)s;
    /* FILL: check_unmap_overlap. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_07_test_writable_mapping(const struct state *s)
{
    (void)s;
    /* FILL: test_writable_mapping. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_08_cap_written_bytes(const struct state *s)
{
    (void)s;
    /* FILL: cap_written_bytes. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_09_increment_mapping_reference(const struct state *s)
{
    (void)s;
    /* FILL: increment_mapping_reference. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_10_copy_inherited_file_offset(const struct state *s)
{
    (void)s;
    /* FILL: copy_inherited_file_offset. Do not alter the case data. */
    return INT64_MIN;
}

struct trial { unsigned slot; struct state input; int64_t expected; };
int main(int argc, char **argv)
{
    const operation op[10] = {
    blank_01_check_mapping_address,
    blank_02_round_size_to_page_boundary,
    blank_03_round_fault_address_down,
    blank_04_number_of_pages_to_load,
    blank_05_validate_nonzero_mapping,
    blank_06_check_unmap_overlap,
    blank_07_test_writable_mapping,
    blank_08_cap_written_bytes,
    blank_09_increment_mapping_reference,
    blank_10_copy_inherited_file_offset
    };
    const struct trial samples[20] = {
    {0, {{4096, 4096, 12288, 0, 0, 0}}, 1},
    {0, {{16384, 4096, 12288, 0, 0, 0}}, 0},
    {1, {{4097, 4096, 0, 0, 0, 0}}, 8192},
    {1, {{8192, 4096, 0, 0, 0, 0}}, 8192},
    {2, {{4660, 4096, 0, 0, 0, 0}}, 4096},
    {2, {{8192, 4096, 0, 0, 0, 0}}, 8192},
    {3, {{4097, 4096, 0, 0, 0, 0}}, 2},
    {3, {{8192, 4096, 0, 0, 0, 0}}, 2},
    {4, {{0, 0, 0, 0, 0, 0}}, -1},
    {4, {{17, 0, 0, 0, 0, 0}}, 0},
    {5, {{0, 4096, 2048, 8192, 0, 0}}, 1},
    {5, {{0, 4096, 4096, 8192, 0, 0}}, 0},
    {6, {{19, 16, 0, 0, 0, 0}}, 1},
    {6, {{3, 16, 0, 0, 0, 0}}, 0},
    {7, {{3, 8, 0, 0, 0, 0}}, 3},
    {7, {{12, 7, 0, 0, 0, 0}}, 7},
    {8, {{100, 7, 0, 0, 0, 0}}, 107},
    {8, {{2, 10, 0, 0, 0, 0}}, 12},
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
