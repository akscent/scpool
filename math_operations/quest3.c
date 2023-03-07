
#include <stdio.h>

int fibonacci(int n) {
    if (n <= 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main(int argc, char *argv[]) {
    int n, result;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) == 1) {
        if (n >= 0) {
            result = fibonacci(n);
            printf(" %dth number in Fibonacci sequence: %d\n", n, result);
        } else {
            printf("n/a\n");
        }
    } else {
        printf("n/a\n");
    }
    return 0;
}
