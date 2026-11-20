/* Independent setup harness. NOT a solved university assignment.
 * Reads observed numeric triples and computes their totals.
 * --puzzle deliberately reports INCOMPLETE until you implement the ten
 * assignment-specific hooks, whose names are in CHALLENGES.md.
 */
#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct observation { uint64_t first, second, third; };
static int read_one(const char *line, struct observation *o) {
    char tail = 0;
    if (sscanf(line, "%" SCNu64 ",%" SCNu64 ",%" SCNu64 " %c",
               &o->first, &o->second, &o->third, &tail) != 3) return -1;
    return 0;
}
int main(int argc, char **argv) {
    int puzzle = (argc == 3 && strcmp(argv[1], "--puzzle") == 0);
    const char *path = puzzle ? argv[2] : (argc == 2 ? argv[1] : NULL);
    if (!path) { fputs("usage: fixture_reader [--puzzle] observations.csv\n", stderr); return 2; }
    FILE *f = fopen(path, "r");
    if (!f) { perror("fopen"); return 2; }
    char *line = NULL; size_t cap = 0; ssize_t n = 0;
    uint64_t count = 0, sum_first = 0, sum_second = 0, sum_third = 0;
    while ((n = getline(&line, &cap, f)) >= 0) {
        (void)n;
        if (line[0] == '#' || line[0] == '\n') continue;
        struct observation o;
        if (read_one(line, &o) || UINT64_MAX - sum_first < o.first ||
            UINT64_MAX - sum_second < o.second || UINT64_MAX - sum_third < o.third) {
            fprintf(stderr, "invalid or overflowing record %" PRIu64 "\n", count + 1);
            free(line); fclose(f); return 2;
        }
        sum_first += o.first; sum_second += o.second; sum_third += o.third; ++count;
    }
    if (ferror(f)) { perror("read"); free(line); fclose(f); return 2; }
    free(line); fclose(f);
    printf("records=%" PRIu64 " first=%" PRIu64 " second=%" PRIu64 " third=%" PRIu64 "\n",
           count, sum_first, sum_second, sum_third);
    if (puzzle) { fputs("INCOMPLETE: 10 kernel/VM/cache decision hooks are reserved for the student\n", stderr); return 77; }
    return count ? 0 : 2;
}
