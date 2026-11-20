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
static int64_t blank_01_detect_write_protection(const struct state *s)
{
    (void)s;
    /* FILL: detect_write_protection. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_02_clear_write_flag_during_fork(const struct state *s)
{
    (void)s;
    /* FILL: clear_write_flag_during_fork. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_03_copy_original_page_identity(const struct state *s)
{
    (void)s;
    /* FILL: copy_original_page_identity. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_04_increment_shared_page_refcount(const struct state *s)
{
    (void)s;
    /* FILL: increment_shared_page_refcount. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_05_decrement_refcount_on_release(const struct state *s)
{
    (void)s;
    /* FILL: decrement_refcount_on_release. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_06_validate_fault_address(const struct state *s)
{
    (void)s;
    /* FILL: validate_fault_address. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_07_mark_private_page_writable(const struct state *s)
{
    (void)s;
    /* FILL: mark_private_page_writable. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_08_reject_invalid_refcount(const struct state *s)
{
    (void)s;
    /* FILL: reject_invalid_refcount. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_09_align_fault_to_base_page(const struct state *s)
{
    (void)s;
    /* FILL: align_fault_to_base_page. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_10_is_page_shared_by_multiple_mappings(const struct state *s)
{
    (void)s;
    /* FILL: is_page_shared_by_multiple_mappings. Do not alter the case data. */
    return INT64_MIN;
}

struct trial { unsigned slot; struct state input; int64_t expected; };
int main(int argc, char **argv)
{
    const operation op[10] = {
    blank_01_detect_write_protection,
    blank_02_clear_write_flag_during_fork,
    blank_03_copy_original_page_identity,
    blank_04_increment_shared_page_refcount,
    blank_05_decrement_refcount_on_release,
    blank_06_validate_fault_address,
    blank_07_mark_private_page_writable,
    blank_08_reject_invalid_refcount,
    blank_09_align_fault_to_base_page,
    blank_10_is_page_shared_by_multiple_mappings
    };
    const struct trial samples[20] = {
    {0, {{19, 4, 0, 0, 0, 0}}, 1},
    {0, {{23, 4, 0, 0, 0, 0}}, 0},
    {1, {{23, 4, 0, 0, 0, 0}}, 19},
    {1, {{17, 16, 0, 0, 0, 0}}, 1},
    {2, {{47, 0, 0, 0, 0, 0}}, 47},
    {2, {{300, 0, 0, 0, 0, 0}}, 300},
    {3, {{1, 0, 0, 0, 0, 0}}, 2},
    {3, {{4, 0, 0, 0, 0, 0}}, 5},
    {4, {{1, 0, 0, 0, 0, 0}}, 0},
    {4, {{4, 0, 0, 0, 0, 0}}, 3},
    {5, {{4096, 4096, 12288, 0, 0, 0}}, 1},
    {5, {{16384, 4096, 12288, 0, 0, 0}}, 0},
    {6, {{19, 4, 0, 0, 0, 0}}, 23},
    {6, {{1, 4, 0, 0, 0, 0}}, 5},
    {7, {{0, 0, 0, 0, 0, 0}}, -1},
    {7, {{17, 0, 0, 0, 0, 0}}, 0},
    {8, {{4660, 4096, 0, 0, 0, 0}}, 4096},
    {8, {{8192, 4096, 0, 0, 0, 0}}, 8192},
    {9, {{2, 0, 0, 0, 0, 0}}, 1},
    {9, {{1, 0, 0, 0, 0, 0}}, 0},
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
