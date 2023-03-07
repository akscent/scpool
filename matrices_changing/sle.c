#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void swap_rows(double **matrix, int row1, int row2, int m) {
    for (int j = 0; j < m; j++) {
        double temp = matrix[row1][j];
        matrix[row1][j] = matrix[row2][j];
        matrix[row2][j] = temp;
    }
}

int sle(double **matrix, int n, int m, double *roots) {
    for (int i = 0; i < n; i++) {
        int max_row = i;
        for (int j = i + 1; j < n; j++) {
            if (fabs(matrix[j][i]) > fabs(matrix[max_row][i])) {
                max_row = j;
            }
        }
        if (matrix[max_row][i] == 0) {
            return 0;
        }
        swap_rows(matrix, i, max_row, m);
        double pivot = matrix[i][i];
        for (int j = i + 1; j < m; j++) {
            matrix[i][j] /= pivot;
        }
        matrix[i][i] = 1;
        for (int j = i + 1; j < n; j++) {
            double factor = matrix[j][i];
            for (int k = i + 1; k < m; k++) {
                matrix[j][k] -= factor * matrix[i][k];
            }
            matrix[j][i] = 0;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < m - 1; j++) {
            sum += matrix[i][j] * roots[j];
        }
        roots[i] = matrix[i][m - 1] - sum;
    }
    return 1;
}

void input(double **matrix, int *n, int *m) {
    scanf("%d %d", n, m);
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }
}

void output(double **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%.6lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

void output_roots(double *roots, int n) {
    for (int i = 0; i < n; i++) {
        if (isnan(roots[i])) {
            printf("n/a");
        } else {
            printf("%.6lf", roots[i]);
        }
        if (i < n - 1) {
            printf(" ");
        }
    }
}

int main() {
    int n = 0, m;
    double **matrix = NULL;
    matrix = malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(m * sizeof(double));
    }
    double *roots;

    input(matrix, &n, &m);

    roots = malloc(n * sizeof(double));
    if (roots == NULL) {
        printf("Error: Failed to allocate memory for roots.\n");
        return 1;
    }

    int status = sle(matrix, n, m, roots);

    if (status == 0) {
        output_roots(roots, n);
    } else {
        printf("n/a");
    }

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(roots);

    return 0;
}
