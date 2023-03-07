#include <stdio.h>
#include <stdlib.h>

void sort_vertical(int **matrix, int n, int m, int **result_matrix) {
    int i, j, k;
    for (j = 0; j < m; j++) {
        if (j % 2 == 0) {
            for (i = 0; i < n; i++) {
                result_matrix[i][j] = matrix[i][j];
            }
        } else {
            for (i = n - 1, k = 0; i >= 0; i--, k++) {
                result_matrix[k][i] = matrix[i][j];
            }
        }
    }
}

void sort_horizontal(int **matrix, int n, int m, int **result_matrix) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        if (i % 2 == 0) {
            for (j = 0; j < m; j++) {
                result_matrix[i][j] = matrix[i][j];
            }
        } else {
            for (j = m - 1, k = 0; j >= 0; j--, k++) {
                result_matrix[k][i] = matrix[i][j];
            }
        }
    }
}

void input(int ***matrix, int *n, int *m) {
    int i, j;

    scanf("%d%d", n, m);

    *matrix = (int **)malloc(*n * sizeof(int *));
    for (i = 0; i < *n; i++) {
        (*matrix)[i] = (int *)malloc(*m * sizeof(int));
        for (j = 0; j < *m; j++) {
            scanf("%d", &(*matrix)[i][j]);
        }
    }
}

void output(int **matrix, int n, int m) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int **matrix, **result;
    int n, m;

    input(&matrix, &n, &m);

    result = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        result[i] = (int *)malloc(m * sizeof(int));
    }

    sort_vertical(matrix, n, m, result);
    output(result, n, m);
    printf("\n");

    sort_horizontal(matrix, n, m, result);
    output(result, n, m);

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
        free(result[i]);
    }
    free(matrix);
    free(result);
}