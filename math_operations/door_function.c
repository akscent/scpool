

#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846
#define NUM_VALUES 42
#define X_MIN -PI
#define X_MAX PI
#define X_STEP (2 * PI) / (NUM_VALUES - 1)
#define PRECISION 7

double witch_of_agnesi(double x) { return 1 / (1 + x * x); }

double lemniscate_of_bernoulli(double x) { return sqrt(1 - (x * x) / 4); }

double quadratic_hyperbola(double x) { return sqrt(1 + x * x); }

int main(int argc, char *argv[]) {
    double x;
    for (int i = 0; i < NUM_VALUES; i++) {
        x = X_MIN + i * X_STEP;
        printf("%.*lf|%.*lf|%.*lf|%.*lf\n", PRECISION, x, PRECISION, witch_of_agnesi(x), PRECISION,
               lemniscate_of_bernoulli(x), PRECISION, quadratic_hyperbola(x));
    }

    return 0;
}
// ./a.out > src/data/door_data.txt
