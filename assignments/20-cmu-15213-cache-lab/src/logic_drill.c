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
static int64_t blank_01_decode_block_base(const struct state *s)
{
    (void)s;
    /* FILL: decode_block_base. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_02_test_line_valid(const struct state *s)
{
    (void)s;
    /* FILL: test_line_valid. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_03_pick_oldest_lru_line(const struct state *s)
{
    (void)s;
    /* FILL: pick_oldest_lru_line. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_04_advance_access_timestamp(const struct state *s)
{
    (void)s;
    /* FILL: advance_access_timestamp. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_05_check_memory_access_in_range(const struct state *s)
{
    (void)s;
    /* FILL: check_memory_access_in_range. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_06_count_spanned_cache_lines(const struct state *s)
{
    (void)s;
    /* FILL: count_spanned_cache_lines. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_07_count_total_cache_lines(const struct state *s)
{
    (void)s;
    /* FILL: count_total_cache_lines. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_08_copy_cache_tag(const struct state *s)
{
    (void)s;
    /* FILL: copy_cache_tag. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_09_limit_way_index(const struct state *s)
{
    (void)s;
    /* FILL: limit_way_index. Do not alter the case data. */
    return INT64_MIN;
}

static int64_t blank_10_measure_reuse_age_delta(const struct state *s)
{
    (void)s;
    /* FILL: measure_reuse_age_delta. Do not alter the case data. */
    return INT64_MIN;
}

struct trial { unsigned slot; struct state input; int64_t expected; };
int main(int argc, char **argv)
{
    const operation op[10] = {
    blank_01_decode_block_base,
    blank_02_test_line_valid,
    blank_03_pick_oldest_lru_line,
    blank_04_advance_access_timestamp,
    blank_05_check_memory_access_in_range,
    blank_06_count_spanned_cache_lines,
    blank_07_count_total_cache_lines,
    blank_08_copy_cache_tag,
    blank_09_limit_way_index,
    blank_10_measure_reuse_age_delta
    };
    const struct trial samples[20] = {
    {0, {{4660, 4096, 0, 0, 0, 0}}, 4096},
    {0, {{8192, 4096, 0, 0, 0, 0}}, 8192},
    {1, {{19, 16, 0, 0, 0, 0}}, 1},
    {1, {{3, 16, 0, 0, 0, 0}}, 0},
    {2, {{11, 3, 7, 0, 0, 0}}, 1},
    {2, {{4, 8, 2, 0, 0, 0}}, 2},
    {3, {{100, 7, 0, 0, 0, 0}}, 107},
    {3, {{2, 10, 0, 0, 0, 0}}, 12},
    {4, {{4096, 4096, 12288, 0, 0, 0}}, 1},
    {4, {{16384, 4096, 12288, 0, 0, 0}}, 0},
    {5, {{4097, 4096, 0, 0, 0, 0}}, 2},
    {5, {{8192, 4096, 0, 0, 0, 0}}, 2},
    {6, {{64, 4, 0, 0, 0, 0}}, 256},
    {6, {{16, 8, 0, 0, 0, 0}}, 128},
    {7, {{47, 0, 0, 0, 0, 0}}, 47},
    {7, {{300, 0, 0, 0, 0, 0}}, 300},
    {8, {{3, 8, 0, 0, 0, 0}}, 3},
    {8, {{12, 7, 0, 0, 0, 0}}, 7},
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
