#include <stdio.h>

void quicksort(int *arr, int low, int high);
void heapsort(int *arr, int n);
void heapify(int *arr, int n, int i);
void swap(int *a, int *b);
void print_array(int *arr, int n);

int main() {
    int arr[10];
    int max_elements = 10;
    int count = 0;

    // Loop to read in values from input
    while (count < max_elements) {
        // Read in integer value from input
        if (scanf("%d", &arr[count]) != 1) {
            printf("n/a\n");
            return 0;
        }
        count++;
        if (count == max_elements) {
            char c;
            // Read in a single character from input
            if (scanf("%c", &c) != EOF && c != '\n') {
                printf("n/a");
                return 0;
            }
        }
    }

    // number of elements
    int n = sizeof(arr) / sizeof(arr[0]);

    // Sort using quicksort
    quicksort(arr, 0, n - 1);
    print_array(arr, n);

    // Sort using heapsort
    heapsort(arr, n);
    print_array(arr, n);

    return 0;
}

// Quicksort
void quicksort(int *arr, int low, int high) {
    if (low < high) {
        // Choose pivot as the last element
        int pivot = arr[high];

        // Partition the array around pivot and get index of pivot
        int i = low - 1;
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[i + 1], &arr[high]);
        int pi = i + 1;

        // Recursively sort the sub-arrays
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Heapsort
void heapsort(int *arr, int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(&arr[0], &arr[i]);

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// To heapify a subtree rooted with node i which is an index in arr[]
void heapify(int *arr, int n, int i) {
    int largest = i;    // Initialize largest as root
    int l = 2 * i + 1;  // left = 2*i + 1
    int r = 2 * i + 2;  // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }

    // If largest is not root
    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Print the elements of an array

void print_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");
}