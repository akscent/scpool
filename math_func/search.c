#include <stdio.h>
#define NMAX 30

// Input function to read data from user and store in array
int input(int *a, int *n) {
    int i;
    int count = 0;

    // Read input of size n only 1 %d symbol
    while (count < 1 && scanf("%d", &n[count]) == 1) {
        count++;
    }

    // Check if input size n is valid
    if (count != 1) {
        printf("n/a");
        return 0;
    }
    if (n[0] <= 0 || n[0] > NMAX) {
        printf("n/a");
        return 0;
    }

    // Read n numbers from second string and store in array
    for (i = 0; i < n[0]; i++) {
        if (scanf("%d", &a[i]) != 1) {
            printf("n/a");
            return 0;
        }
    }
    return 1;
}

// my_sqrt function for calculating square root using binary algorithm
double my_sqrt(double num) {
    double low = 0, high = num;
    double mid;
    while (high - low > 0.000001) {
        mid = (low + high) / 2;
        if (mid * mid > num) {
            high = mid;
        } else {
            low = mid;
        }
    }
    return low;
}

// Function to calculate mean of array
double mean(int *a, int n) {
    int i;
    double sum = 0;

    // Calculate sum of all numbers in the array
    for (i = 0; i < n; i++) {
        sum += a[i];
    }

    // Return mean
    return sum / n;
}

// Function to calculate variance of the array
double variance(int *a, int n) {
    int i;
    double mean_v = mean(a, n);
    double sum = 0;

    // Calculate variance using formula
    for (i = 0; i < n; i++) {
        sum += (a[i] - mean_v) * (a[i] - mean_v);
    }
    return sum / n;
}

// Search function to find number that meets conditions
int search(int *a, int n, double mean, double variance) {
    int i;

    // Check if number meets conditions
    for (i = 0; i < n; i++) {
        if (a[i] % 2 == 0 && a[i] >= mean && a[i] <= mean + 3 * my_sqrt(variance) && a[i] != 0) {
            return a[i];
        }
    }
    return 0;
}

// Main function for calculating
int main() {
    int n, data[NMAX];
    input(data, &n);
    double mean_v = mean(data, n);
    double variance_v = variance(data, n);
    int result = search(data, n, mean_v, variance_v);
    printf("%d", result);
    return 0;
}
