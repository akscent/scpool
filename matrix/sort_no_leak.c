#include <stdio.h>
#include <stdlib.h>

// Function to sort an array of integers in ascending order
void Sort(int *arr, int len) {
    int i, j;
    for (i = 1; i < len; i++) {
        for (j = 0; j < len - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int max_elements = 10;

    // allocate memory for the array dynamically
    int *number = (int *)malloc(max_elements * sizeof(int));
    if (number == NULL) {
        printf("n/a\n");
        return 0;
    }
    int i = 0;
    while (i < max_elements) {
        if (scanf("%d", &number[i]) != 1) {
            printf("n/a\n");
            free(number);
            return 0;
        }
        i++;
        if (i == max_elements) {
            char c;
            if (scanf("%c", &c) != EOF && c != '\n') {
                printf("n/a");
                free(number);
                return 0;
            }
        }
    }
    Sort(number, max_elements);
    for (int i = 0; i < max_elements; i++) {
        printf("%d ", *(number + i));
    }

    // free the memory allocated for the array
    free(number);
    return 0;
}