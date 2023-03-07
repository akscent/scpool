#include <math.h>
#include <stdio.h>

// function for abs
int f_abs(int y) {
    if (y < 0) {
        y = (-1) * y;
    }
    return y;
}

// search divisions in subsequence
int division(int i, int n) {
    if (i == n) {
        return 0;
    }

    for (int k = i; k <= n; k += i) {
        if (n == k + i) {
            return 0;
        }
    }

    return 1;
}

void sieveOfEratosthenes(int n) {
    int i, j;
    int prime[n + 1];
    for (i = 0; i <= n; i++) prime[i] = 1;
    prime[0] = prime[1] = 0;
    int m = sqrt(n);
    for (i = 2; i <= m; i++) {
        if (prime[i]) {
            for (j = i * i; j <= n; j += i) prime[j] = 0;
        }
    }
    // printf("The prime numbers up to %d are: \n", n);
    int max = -1;  // search maximum
    for (i = 2; i <= n; i++)
        if (prime[i] != 0 && division(i, n) == 0) {
            // printf("%d ", i);
            if (i > max) {  // determination of the maximum
                max = i;
            }
        }
    printf("\n");
    printf("The maximum value is: %d\n", max);
}

int main() {
    int n;
    printf("Enter the maximum number to check for primes: ");
    scanf("%d", &n);
    sieveOfEratosthenes(f_abs(n));
    return 0;
}
