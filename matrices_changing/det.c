#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double det(double **matrix, int n);
void input(double **matrix, int *n, int *m);
void output(double det);

int main() {
    double **matrix = NULL;
    int n, m;
    double determinant;

    input(matrix, &n, &m);
    determinant = det(matrix, n);
    output(determinant);
}

double det(double **matrix, int n) {
    double det = 1, temp;

    // Gaussian elimination to obtain the upper triangular form
    for (int k = 0; k < n; k++) {
        int i_max = k;
        double v_max = matrix[i_max][k];

        for (int i = k + 1; i < n; i++) {
            if (fabs(matrix[i][k]) > fabs(v_max)) {
                v_max = matrix[i][k];
                i_max = i;
            }
        }

        if (fabs(v_max) < 1e-10) {
            // The matrix is singular
            return 0;
        }

        if (i_max != k) {
            // Swap rows k and i_max
            double *temp = matrix[k];
            matrix[k] = matrix[i_max];
            matrix[i_max] = temp;

            // Change the sign of the determinant
            det = -det;
        }

        // Perform row operations
        for (int i = k + 1; i < n; i++) {
            temp = matrix[i][k] / matrix[k][k];

            for (int j = k + 1; j < n; j++) {
                matrix[i][j] -= temp * matrix[k][j];
            }

            matrix[i][k] = 0;
        }

        // Multiply diagonal elements
        det *= matrix[k][k];
    }

    return det;
}

void input(double **matrix, int *n, int *m) {
    if (scanf("%d %d", n, m) != 2) {
        printf("n/a\n");
        exit(1);
    }

    if (*n != *m) {
        printf("n/a\n");
        exit(1);
    }

    matrix = (double **)malloc(*n * sizeof(double *));

    if (matrix == NULL) {
        printf("n/a\n");
        exit(1);
    }

    for (int i = 0; i < *n; i++) {
        matrix[i] = (double *)malloc(*m * sizeof(double));

        if (matrix[i] == NULL) {
            printf("n/a\n");
            exit(1);
        }

        for (int j = 0; j < *m; j++) {
            if (scanf("%lf", &matrix[i][j]) != 1) {
                printf("n/a\n");
                exit(1);
            }
        }
    }
}

void output(double det) {
    if (isnan(det)) {
        printf("n/a\n");
    } else {
        printf("%.6lf\n", det);
    }
}