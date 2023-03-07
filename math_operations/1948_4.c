#include <stdio.h>
#include <math.h>

int main()
{
    unsigned n;
    printf("Enter a number: ");
    scanf("%u", &n);
    unsigned maxN = sqrt(n);
    unsigned d[maxN + 1] = {0, 1};

    for (unsigned x = 2; x <= maxN; ++x)
        if (!d[x])
            for (unsigned q = x; q <= maxN; q += x)
                d[q] = x;

    printf("The largest factor of %u is %u.\n", n, d[n]);

    return 0;
}
