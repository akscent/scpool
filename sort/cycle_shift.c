#include <stdio.h>

void input(int *buffer, int *n, int *c, int *char_exist);
void output(int *buffer, int n);
void cycle_shift(int *buffer, int n, int c);

int main() {
    int buffer[10]; // max buffer size is 10
    int char_exist = 0;
    int n, c;

    input(buffer, &n, &c, &char_exist);
    if (n > 10 || n < 1) {
        printf("n/a");
        return 0;
    }
    if (char_exist != 0) {
        printf("n/a");
        return 0;
    }
    cycle_shift(buffer, n, c);
    output(buffer, n);

    return 0;
}

void input(int *buffer, int *n, int *c, int *char_exist) {
    scanf("%d", n);
    int count = 0;
    for (int i = 0; i < *n; i++) {
        scanf("%d", &buffer[i]);
    }
    char st;
    while (count < 1) {
        scanf("%d", &c[count]);
        count++;
        if (count == 1) {
            if (scanf("%c", &st) != EOF && st != '\n') {
                *char_exist = 1;
            }
        }
    }
}

void cycle_shift(int *buffer, int n, int c) {
    if (c < 0) {
        c = n + c;
    }
    c = c % n;
    for (int i = 0; i < c; i++) {
        int temp = buffer[0];
        for (int j = 0; j < n - 1; j++) {
            buffer[j] = buffer[j + 1];
        }
        buffer[n - 1] = temp;
    }
}

void output(int *buffer, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", buffer[i]);
    }
}