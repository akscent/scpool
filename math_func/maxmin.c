#include <stdio.h>

void maxmin(int prob1, int prob2, int prob3, int *max, int *min);

/* Find a max & min probabilities */
int main() {
    int x, y, z;
    int nums_scanned;
    nums_scanned = scanf("%d %d %d", &x, &y, &z);
    /* Как учесть ввод большего количества символов*/

    if (nums_scanned != 3) {
        printf("n/a\n");
        return 1;
    }

    if (x != (int)x || y != (int)y || z != (int)z) {
        printf("n/a\n");
        return 1;
    }

    int max, min;

    maxmin(x, y, z, &max, &min);

    printf("%d %d", max, min);

    return 0;
}

/* This function should be kept !!! (Your AI) */
/* But errors & bugs should be fixed         */
void maxmin(int prob1, int prob2, int prob3, int *max, int *min) {
    *max = *min = prob1;

    if (prob2 > *max) *max = prob2;
    if (prob2 < *min) *min = prob2;

    if (prob3 > *max) *max = prob3;
    if (prob3 < *min) *min = prob3;
}
