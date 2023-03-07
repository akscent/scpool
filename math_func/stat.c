#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

// Input function with loop
int input(int *a, int *n) {
    scanf("%d", n);
    for (int i = 0; i < *n; i++) {
        scanf("%d", &a[i]);
    }
}

// Output function with loop
void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// Function to calculate max
int max(int *a, int n) {
    int max = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}

// Function to calculate min
int min(int *a, int n) {
    int min = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < min) {
            min = a[i];
        }
    }
    return min;
}

// Function to calculate mean of array
double mean(int *a, int n) {
    int sum = 0;

    // Calculate sum of all numbers in the array
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return (double)sum / n;
}

// Function to calculate variance of array
double variance(int *a, int n) {
    double mean_v = mean(a, n);
    double sum = 0;

    // Calculate variance using formula
    for (int i = 0; i < n; i++) {
        sum += (a[i] - mean_v) * (a[i] - mean_v);
    }
    return sum / n;
}

// Output Result function with all variables
void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6f %.6f", max_v, min_v, mean_v, variance_v);
}

// Main function with calculating
int main() {
    int n, data[NMAX];
    input(data, &n);
    output(data, n);
    output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));
    return 0;
}
