#include <stdio.h>
#include <math.h>

#define MAXN 1048576
unsigned d[MAXN] = {0,1};
int main () {
    for (unsigned x=2; x<MAXN; x++) 
    if (!d[x])
    for (unsigned q = x; q < MAXN; q += x) 
    d[q] = x;

    for (unsigned q=1; q<MAXN; q*=100)
    for (unsigned w=0; w<16; ++w)
    printf("%u - %u\n", q+w, d[q+w] );
    return 0; 
}