#include <stdio.h>

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
    // set array length
    int number[10];

    // set max number of elements in array
    int max_elements = 10;

    // set counter for while loop
    int count = 0;

    // Loop to read in values from input
    while (count < max_elements) {
        // Read in integer value from input and store in array 'number'
        if (scanf("%d", &number[count]) != 1) {
            printf("n/a\n");
            return 0;
        }
        count++;

        // We have maximum number of elements (10), than check any remaining characters input buffer
        if (count == max_elements) {
            char c;
            // Read in a single character from input and check if it is more than 10 (not end-of-file or \n) -
            // n/a
            if (scanf("%c", &c) != EOF && c != '\n') {
                printf("n/a");
                return 0;
            }
        }
    }

    // Sort array in ascending order
    Sort(number, max_elements);

    // Print out the sorted array
    for (int i = 0; i < max_elements; i++) {
        printf("%d ", *(number + i));
    }
    printf("\n");

    return 0;
}