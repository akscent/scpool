#include <stdio.h>
#include <stdlib.h>

int input(int ***matrix, int *n, int *m) {
    if (scanf("%d %d", n, m) != 2) return 0;
    *matrix = (int **)malloc((*n) * sizeof(int *));
    if (!(*matrix)) return 0;
    for (int i = 0; i < (*n); i++) {
        (*matrix)[i] = (int *)malloc((*m) * sizeof(int));
        if (!(*matrix)[i]) {
            for (int j = 0; j < i; j++) {
                free((*matrix)[j]);
            }
            free(*matrix);
            return 0;
        }
    }
    for (int i = 0; i < (*n); i++) {
        for (int j = 0; j < (*m); j++) {
            if (scanf("%d", &(*matrix)[i][j]) != 1) {
                for (int k = 0; k < i; k++) {
                    free((*matrix)[k]);
                }
                free(*matrix);
                return 0;
            }
        }
    }
    return 1;
}

void output(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int sum(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int ***matrix_result, int *n_result, int *m_result) {
    if (n_first != n_second || m_first != m_second) return 0;
    *n_result = n_first;
    *m_result = m_first;
    *matrix_result = (int **)malloc((*n_result) * sizeof(int *));
    if (!(*matrix_result)) return 0;
    for (int i = 0; i < (*n_result); i++) {
        (*matrix_result)[i] = (int *)malloc((*m_result) * sizeof(int));
        if (!(*matrix_result)[i]) {
            for (int j = 0; j < i; j++) {
                free((*matrix_result)[j]);
            }
            free(*matrix_result);
            return 0;
        }
    }
    for (int i = 0; i < (*n_result); i++) {
        for (int j = 0; j < (*m_result); j++) {
            (*matrix_result)[i][j] = matrix_first[i][j] + matrix_second[i][j];
        }
    }
    return 1;
}

int transpose(int ***matrix, int n, int m) {
    int **matrix_transposed = (int **)malloc(m * sizeof(int *));
    if (!matrix_transposed) return 0;
    for (int i = 0; i < m; i++) {
        matrix_transposed[i] = (int *)malloc(n * sizeof(int));
        if (!matrix_transposed[i]) {
            for (int j = 0; j < i; j++) free(matrix_transposed[j]);
            free(matrix_transposed);
            return 0;
        }
        for (int j = 0; j < n; j++) matrix_transposed[i][j] = (*matrix)[j][i];
    }
    for (int i = 0; i < n; i++) free((*matrix)[i]);
    free(*matrix);
    *matrix = matrix_transposed;
    return 1;
}

int mul(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int ***matrix_result, int *n_result, int *m_result) {
    if (m_first != n_second) return 0;
    *n_result = n_first;
    *m_result = m_second;
    *matrix_result = (int **)malloc((*n_result) * sizeof(int *));
    if (!(*matrix_result)) return 0;
    for (int i = 0; i < (*n_result); i++) {
        (*matrix_result)[i] = (int *)malloc((*m_result) * sizeof(int));
        if (!(*matrix_result)[i]) {
            for (int j = 0; j < i; j++) {
                free((*matrix_result)[j]);
            }
            free(*matrix_result);
            return 0;
        }
        for (int j = 0; j < (*m_result); j++) {
            (*matrix_result)[i][j] = 0;
            for (int k = 0; k < m_first; k++)
                (*matrix_result)[i][j] += matrix_first[i][k] * matrix_second[k][j];
        }
    }
    return 1;
}

int main() {
    int operation, n1, m1, n2, m2, n_res, m_res;
    int **matrix1, **matrix2, **result;

    // Read the operation type
    if (scanf("%d", &operation) != 1) {
        printf("n/a");
        return 0;
    }

    // Read the first matrix
    if (input(&matrix1, &n1, &m1) == 0) {
        printf("n/a");
        return 0;
    }

    // Read the second matrix
    if ((operation == 1 || operation == 2) && input(&matrix2, &n2, &m2) == 0) {
        printf("n/a");
        return 0;
    }

    // Perform the selected operation
    switch (operation) {
        case 1:
            if (n1 != n2 || m1 != m2) {
                printf("n/a");
                break;
            }
            if (sum(matrix1, n1, m1, matrix2, n2, m2, &result, &n_res, &m_res) == 0) {
                printf("n/a");
                break;
            }
            output(result, n_res, m_res);
            break;

        case 2:
            if (m1 != n2) {
                printf("n/a");
                break;
            }
            if (mul(matrix1, n1, m1, matrix2, n2, m2, &result, &n_res, &m_res) == 0) {
                printf("n/a");
                break;
            }
            output(result, n_res, m_res);
            break;

        case 3:
            if (transpose(&matrix1, n1, m1) == 0) {
                printf("n/a");
                break;
            }
            output(matrix1, m1, n1);
            break;

        default:
            printf("n/a");
            break;
    }

    // Free memory
    for (int i = 0; i < n1; i++) {
        free(matrix1[i]);
    }
    free(matrix1);

    if (operation == 1 || operation == 2) {
        for (int i = 0; i < n2; i++) {
            free(matrix2[i]);
        }
        free(matrix2);
    }

    if (operation == 1 || operation == 2 || operation == 3) {
        for (int i = 0; i < n_res; i++) {
            free(result[i]);
        }
    }
    return 0;
}