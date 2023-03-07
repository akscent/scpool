#include <stdio.h>

int main() {
    float x, y;
    int nums_scanned;

    printf("Enter two floating-point numbers separated by a space: ");
    nums_scanned = scanf("%f %f", &x, &y);
    
    if (nums_scanned != 2) { // check int
        printf("n/a\n");
        return 1;
    }

    if (x*x + y*y < 25) {
        printf("GOTCHA\n");
    } else {
        printf("MISS\n");
    }

    return 0;
}
