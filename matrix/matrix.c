#include <stdio.h>
#include <stdlib.h>

int** allocate_matrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    return matrix;
}

int** allocate_matrix_row_major(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    int* data = (int*)malloc(rows * cols * sizeof(int));
    for (int i = 0; i < rows; i++) {
        matrix[i] = data + i * cols;
    }
    return matrix;
}

int** allocate_matrix_col_major(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    int* data = (int*)malloc(rows * cols * sizeof(int));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i] = data + j * rows + i;
        }
    }
    return matrix;
}

int** static_matrix(int rows, int cols) {
    int** matrix;
    static int static_matrix[100][100] = {0};
    int* data = &static_matrix[0][0];
    matrix = (int**)malloc(sizeof(int*) * rows);
    for (int i = 0; i < rows; i++) {
        matrix[i] = data + i * cols;
    }
    return matrix;
}

void free_matrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int rows, cols, choice;
    int** matrix = NULL;
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
        printf("n/a");
        return 0;
    }
    // Read matrix dimensions from input
    if (scanf("%d %d", &rows, &cols) != 2) {
        printf("n/a");
        return 0;
    }
    // Allocate memory for matrix based on user's choice
    switch (choice) {
        case 1:
            if (rows > 100 || cols > 100) {
                printf("n/a");
                return 0;
            }
            matrix = static_matrix(rows, cols);
            break;
        case 2:
            matrix = allocate_matrix_row_major(rows, cols);
            break;
        case 3:
            matrix = allocate_matrix_col_major(rows, cols);
            break;
        case 4:
            matrix = allocate_matrix(rows, cols);
            break;
        default:
            printf("n/a");
            return 0;
    }

    // Read matrix elements from input
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                free_matrix(matrix, rows);
                printf("n/a");
                return 0;
            }
        }
    }

    // Print matrix elements
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", *(matrix[i] + j));
            if (j != cols - 1) {
                printf(" ");
            }
        }
        if (i != rows - 1) {
            printf("\n");
        }
    }
    return 0;
}