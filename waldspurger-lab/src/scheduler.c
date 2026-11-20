/* Two runnable clients: isolate ticket -> grant from any host scheduling claim. */
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static uint64_t rand_state = UINT64_C(0x9e3779b97f4a7c15);
static uint64_t random64(void)
{
    rand_state ^= rand_state >> 12;
    rand_state ^= rand_state << 25;
    rand_state ^= rand_state >> 27;
    return rand_state * UINT64_C(2685821657736338717);
}
static int parse(const char *s, uint64_t *out)
{
    char *end = NULL;
    errno = 0;
    unsigned long long v = strtoull(s, &end, 10);
    if (errno || end == s || *end || s[0] == '-')
        return -1;
    *out = (uint64_t)v;
    return 0;
}
int main(int argc, char **argv)
{
    uint64_t rounds, a, b;
    if (argc != 5 || (strcmp(argv[1], "stride") && strcmp(argv[1], "lottery")) ||
        parse(argv[2], &rounds) || parse(argv[3], &a) || parse(argv[4], &b) ||
        rounds < 1 || rounds > UINT64_C(10000000) || a == 0 || b == 0 ||
        a > UINT64_C(1000000000) || b > UINT64_C(1000000000)) {
        fprintf(stderr, "usage: scheduler stride|lottery rounds tickets_A tickets_B\n");
        return 2;
    }
    uint64_t count_a = 0, count_b = 0;
    long double pass_a = 0, pass_b = 0;
    const uint64_t total = a + b;
    const uint64_t reject = (uint64_t)(-total) % total;
    for (uint64_t i = 0; i < rounds; ++i) {
        int winner_a;
        if (!strcmp(argv[1], "stride")) {
            winner_a = pass_a <= pass_b;
        } else {
            uint64_t sample;
            do { sample = random64(); } while (sample < reject);
            winner_a = (sample % total) < a;
        }
        if (winner_a) {
            ++count_a;
            pass_a += 1.0L / (long double)a;
        } else {
            ++count_b;
            pass_b += 1.0L / (long double)b;
        }
    }
    printf("policy=%s rounds=%" PRIu64 " tickets_A=%" PRIu64
           " tickets_B=%" PRIu64 "\n", argv[1], rounds, a, b);
    printf("A=%" PRIu64 " B=%" PRIu64 " expected_share_A=%.9Lf"
           " observed_share_A=%.9Lf\n",
           count_a, count_b, (long double)a / (long double)total,
           (long double)count_a / (long double)rounds);
    return 0;
}
