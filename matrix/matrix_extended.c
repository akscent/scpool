#include <stdio.h>
#include <stdlib.h>

// Function to allocate memory for a matrix using the calloc function

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

// Function to free memory allocated for a matrix
void FreeMemory(int** matrix) { free(matrix); }

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
                printf("n/a");
                FreeMemory(matrix);
                return 0;
            }
        }
    }

    // Find maximum element in each row and minimum element in each column
    int* max_row = calloc(rows, sizeof(int));
    int* min_col = calloc(cols, sizeof(int));
    for (int i = 0; i < rows; i++) {
        max_row[i] = matrix[i][0];
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] > max_row[i]) {
                max_row[i] = matrix[i][j];
            }
            if (i == 0 || matrix[i][j] < min_col[j]) {
                min_col[j] = matrix[i][j];
            }
        }
    }

    // Print matrix elements
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", matrix[i][j]);
            if (j != cols - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }

    // Print maximum elements in each row
    for (int i = 0; i < rows; i++) {
        printf("%d", max_row[i]);
        if (i != rows - 1) {
            printf(" ");
        }
    }
    printf("\n");

    // Print minimum elements in each column
    for (int j = 0; j < cols; j++) {
        printf("%d", min_col[j]);
        if (j != cols - 1) {
            printf(" ");
        }
    }

    // Free allocated memory
    FreeMemory(matrix);
    free(max_row);
    free(min_col);

    return 0;
}