#include <stdio.h>

int main() {
  float a, b; // input 2 integers

  printf("Enter two numbers separated by a space: ");

  // check 2 integer input
  if (scanf("%f %f", &a, &b) != 2) {
    printf("n/a\n");
    return 1;
  }
  // check non-decimal
  if (a != (int)a || b != (int)b) {
    printf("n/a\n");
    return 1;
  }

  int max(int x, int y) { // create max function
    if (x > y) {
      return x;
    } else {
      return y;
    }
  }
  // calculate and print max

  int maximum = max(a, b);

  printf("Maximum number: %d \n", maximum);

  return 0;
}
