#include <stdio.h>
#include <stdlib.h>

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
    int max_elements;
    if (scanf("%d", &max_elements) != 1 || max_elements < 1 || max_elements > 100) {
        printf("n/a\n");
        return 0;
    }

    // Allocate memory for the array dynamically
    // сначала инициация массива, int* приведение типа к типу указателя (для одноерного массива)
    // и выделяем равное максимальному количеству элементов байты в памяти
    int *number = (int *)malloc(max_elements * sizeof(int));
    if (number == NULL) {
        printf("n/a");
        return 0;
    }
    int i;
    while (i < max_elements) {
        // считываем элемент и записываем в массив
        if (scanf("%d", &number[i]) != 1) {
            printf("n/a");
            return 0;
        }
        i++;
        if (i == max_elements) {
            // если введено больше символов, чем нужно
            char c;
            if (scanf("%c", &c) != EOF && c != '\n') {
                printf("n/a");
                return 0;
            }
        }
    }

    Sort(number, max_elements);
    for (int i = 0; i < max_elements; i++) {
        printf("%d ", *(number + i));
    }
    free(number);
    return 0;
}