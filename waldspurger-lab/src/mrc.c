/* Exact LRU MRC plus fixed-rate spatial sampling teaching baseline.
 * This is NOT the adaptive fixed-size SHARDS implementation.
 * Maximum unique block identities=4096; O(accesses * identities).
 */
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_IDS 4096
static char names[MAX_IDS][64];
static int64_t previous[MAX_IDS];
static uint64_t hits[6], misses[6];
static const uint32_t capacities[6] = {1, 2, 3, 4, 8, 16};
static uint64_t hash_name(const char *s)
{
    uint64_t h = UINT64_C(14695981039346656037);
    for (; *s; ++s) {
        h ^= (unsigned char)*s;
        h *= UINT64_C(1099511628211);
    }
    return h;
}
int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "usage: mrc trace.txt sample_permille (1..1000; 1000 exact)\n");
        return 2;
    }
    char *end = NULL;
    errno = 0;
    unsigned long rate = strtoul(argv[2], &end, 10);
    if (errno || end == argv[2] || *end || rate == 0 || rate > 1000) {
        fprintf(stderr, "sample_permille must be 1..1000\n");
        return 2;
    }
    FILE *in = fopen(argv[1], "r");
    if (!in) { perror(argv[1]); return 2; }
    int64_t count = 0;
    int distinct = 0;
    char token[64];
    uint64_t scanned = 0, selected = 0;
    while (fscanf(in, "%63s", token) == 1) {
        ++scanned;
        if (scanned > 200000) { fprintf(stderr, "trace too long (max 200000)\n"); fclose(in); return 2; }
        if (hash_name(token) % 1000 >= rate)
            continue;
        ++selected;
        int id = 0;
        while (id < distinct && strcmp(names[id], token)) ++id;
        if (id == distinct) {
            if (distinct == MAX_IDS) { fprintf(stderr, "too many unique blocks\n"); fclose(in); return 2; }
            strcpy(names[id], token);
            previous[id] = -1;
            ++distinct;
        }
        int64_t distance = -1;
        if (previous[id] >= 0) {
            distance = 0;
            for (int j = 0; j < distinct; ++j)
                if (j != id && previous[j] > previous[id]) ++distance;
        }
        /* d_sample is exact for retained identities. d_sample/R is a
         * statistical estimate for the unsampled identity population. */
        double scaled = distance < 0 ? -1.0 : (double)distance * 1000.0 / (double)rate;
        for (int c = 0; c < 6; ++c) {
            if (distance < 0 || scaled >= (double)capacities[c]) ++misses[c];
            else ++hits[c];
        }
        previous[id] = count++;
    }
    if (ferror(in)) { perror("trace read"); fclose(in); return 2; }
    fclose(in);
    printf("scanned=%" PRIu64 " selected=%" PRIu64 " unique_selected=%d rate=%lu/1000\n",
           scanned, selected, distinct, rate);
    printf("capacity,hits,misses,miss_ratio\n");
    for (int c = 0; c < 6; ++c) {
        const uint64_t n = hits[c] + misses[c];
        printf("%u,%" PRIu64 ",%" PRIu64 ",%.9f\n", capacities[c],
               hits[c], misses[c], n ? (double)misses[c]/(double)n : 0.0);
    }
    return 0;
}
