#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846
#define NUM_VALUES 42
#define X_MIN -PI
#define X_MAX PI
#define X_STEP (2 * PI) / (NUM_VALUES - 1)
#define PRECISION 7
#define Y_MIN -2
#define Y_MAX 2
#define Y_STEP (Y_MAX - Y_MIN) / 20.0

double witch_of_agnesi(double x) { return 1 / (1 + x * x); }

double lemniscate_of_bernoulli(double x) { return sqrt(1 - (x * x) / 4); }

double quadratic_hyperbola(double x) { return sqrt(1 + x * x); }

void draw_graph(double (*f)(double), char *name) {
    printf("%s:\n", name);
    for (double y = Y_MAX; y >= Y_MIN; y -= Y_STEP) {
        for (int i = 0; i < NUM_VALUES; i++) {
            double x = X_MIN + i * X_STEP;
            if (f(x) >= y - Y_STEP / 2.0 && f(x) <= y + Y_STEP / 2.0) {
                printf("-");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    draw_graph(witch_of_agnesi, "Witch of Agnesi");
    draw_graph(lemniscate_of_bernoulli, "Lemniscate of Bernoulli");
    draw_graph(quadratic_hyperbola, "Quadratic Hyperbola");
    return 0;
}