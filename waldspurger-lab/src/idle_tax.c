/* ESX 2002 section 5.2. An algebraic policy calculator, not host page reclaim. */
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int parse(const char *text, double *out)
{
    char *end = NULL;
    errno = 0;
    double v = strtod(text, &end);
    if (errno || end == text || *end != '\0' || !isfinite(v))
        return -1;
    *out = v;
    return 0;
}
int main(int argc, char **argv)
{
    double x[7];
    if (argc != 8) {
        fprintf(stderr, "usage: idle_tax S_A P_A f_A S_B P_B f_B tax\n");
        return 2;
    }
    for (int i = 0; i < 7; ++i) {
        if (parse(argv[i + 1], &x[i])) {
            fprintf(stderr, "invalid number at input %d\n", i + 1);
            return 2;
        }
    }
    if (x[0] <= 0 || x[1] <= 0 || x[3] <= 0 || x[4] <= 0 ||
        x[2] < 0 || x[2] > 1 || x[5] < 0 || x[5] > 1 ||
        x[6] < 0 || x[6] >= 1) {
        fprintf(stderr, "require positive shares/pages, 0<=f<=1, 0<=tax<1\n");
        return 2;
    }
    const double k = 1.0 / (1.0 - x[6]);
    const double a_denom = x[1] * (x[2] + k * (1.0 - x[2]));
    const double b_denom = x[4] * (x[5] + k * (1.0 - x[5]));
    const double a = x[0] / a_denom;
    const double b = x[3] / b_denom;
    printf("tax=%.9f idle_cost=%.9f\n", x[6], k);
    printf("A active_fraction=%.9f adjusted_pages=%.9f score=%.9f\n", x[2], a_denom, a);
    printf("B active_fraction=%.9f adjusted_pages=%.9f score=%.9f\n", x[5], b_denom, b);
    puts(a < b ? "lower_score=A" : (b < a ? "lower_score=B" : "lower_score=tie"));
    return 0;
}
