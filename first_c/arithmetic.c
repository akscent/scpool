#include <stdio.h>

int main() {
    float a, b; // float need to decimal detected
    int nums_scanned; // variable to evaluate presence of 2 numbers

    printf("Enter two integers sep by space: ");
    nums_scanned = scanf("%f %f", &a, &b);

    if (nums_scanned != 2) { // check numbers
        printf("n/a\n");
        return 1;
    }

    if (a != (int) a || b != (int) b) { // check non-decimal with int type = float type
        printf("n/a\n");
        return 1;
    }
    // calculating and print sum, difference, multiplication, and degree
    int sum = a + b;
    int diff = a - b;
    int multip = a * b;

    int degree;
    char *grade; // var for output degree replace by n/a
    if ((int)b == 0) {
        grade = "n/a\n";
        printf("%d %d %d %s\n", sum, diff, multip, grade); // replace 4s out
    } else {
        degree = a / b;
        ((int) degree == 0) ? printf("%d %d %d" " ~0\n", sum, diff, multip) // replace rounded value ~0
        :
        printf("%d %d %d %d\n", sum, diff, multip, degree);
    }

    return 0;
}
