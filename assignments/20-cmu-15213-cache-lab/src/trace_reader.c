/* Valgrind lackey trace input parser; leaves LRU, hit/miss and eviction
 * calculations for the student. Counts M as two data operations, ignores I.
 * Compiles under -std=c11 -Wall -Wextra -Werror -Wpedantic.
 */
#define _POSIX_C_SOURCE 200809L
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv) {
    if (argc != 2) { fputs("usage: trace_reader tracefile\n", stderr); return 2; }
    FILE *f = fopen(argv[1], "r");
    if (!f) { perror("tracefile"); return 2; }
    char *line = NULL; size_t capacity = 0;
    uint64_t instruction = 0, logical_accesses = 0, data_records = 0, bytes = 0;
    while (getline(&line, &capacity, f) >= 0) {
        char op = 0, extra = 0;
        unsigned long long address = 0;
        unsigned length = 0;
        if (sscanf(line, " %c %llx,%u %c", &op, &address, &length, &extra) != 3 || length == 0) {
            fprintf(stderr, "bad trace: %s", line); free(line); fclose(f); return 2;
        }
        (void)address;
        if (op == 'I') { ++instruction; continue; }
        if (op != 'L' && op != 'S' && op != 'M') { fputs("unknown operation\n", stderr); free(line); fclose(f); return 2; }
        ++data_records;
        logical_accesses += (op == 'M' ? 2U : 1U);
        bytes += length * (op == 'M' ? 2U : 1U);
    }
    free(line); fclose(f);
    printf("instruction=%" PRIu64 " data_records=%" PRIu64 " accesses=%" PRIu64 " access_bytes=%" PRIu64 "\n",instruction,data_records,logical_accesses,bytes);
    puts("No cache hits, misses or evictions calculated: LRU policy remains for the student.");
    return 0;
}
