
#include <math.h>
#include <stdio.h>

double important_function(double x) {
  return ceil(1000 * (7e-3 * pow(x, 4) + ((22.8 * pow(x, 1.0/3.0) - 1000) * x + 3) / (x * x / 2) - x * pow(10 + x, 2/x) - 1.01)) / 1000;
}

int main(int argc, char* argv[]) {
  double x;
  printf("Enter a number: ");
  // check int input
  if (scanf("%lf", &x) != 1) { // check numbers
    printf("n/a\n");
    return 1;
  }
  printf("Result: %.1lf\n", important_function(x));
  return 0;
}
