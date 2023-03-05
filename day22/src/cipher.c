#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 1000
#define MAX_STRING_LENGTH 10000

int read_file(char* filename) {
    char* buffer = NULL;
    long length;
    FILE* f = fopen(filename, "rb");
    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length + 1);
        if (buffer) {
            fread(buffer, 1, length, f);
            buffer[length] = '\0';
            printf("%s\n", buffer);
            free(buffer);
        }
        fclose(f);
        return 0;
    } else {
        printf("n/a\n");
        return -1;
    }
}

int write_file(char* filename, char* str) {
    FILE* f = fopen(filename, "a");
    if (f) {
        fprintf(f, "%s\n", str);
        fclose(f);
        return 0;
    } else {
        printf("n/a\n");
        return -1;
    }
}

int main() {
    char filename[MAX_FILENAME_LENGTH];
    char input[MAX_STRING_LENGTH];
    int choice = 0;

    while (choice != -1) {
        scanf("%d", &choice);
        getchar(); // consume the newline character from scanf

        switch (choice) {
            case 1:
                fgets(filename, MAX_FILENAME_LENGTH, stdin);
                filename[strcspn(filename, "\n")] = '\0'; // remove trailing newline character
                read_file(filename);
                printf("\n");
                break;
            case 2:
                fgets(input, MAX_STRING_LENGTH, stdin);
                input[strcspn(input, "\n")] = '\0'; // remove trailing newline character
                
                fgets(filename, MAX_FILENAME_LENGTH, stdin);
                filename[strcspn(filename, "\n")] = '\0'; // remove trailing newline character
                write_file(filename, input);
                read_file(filename);
                printf("\n");
                break;
            case -1:
                break;
            default:
                printf("Invalid choice.\n\n");
        }
    }

    return 0;
}

