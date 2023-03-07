
/*
gcc -Wall -Wextra -Werror text_processor.c s21_string.c -o ../build/Quest_8
*/
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

#define MAX_INPUT_LENGTH 100

int main(int argc, char *argv[]) {
    if (argc != 2 || s21_strcmp(argv[1], "-w") != 0) {
        printf("n/a\n");
        return 0;
    }
    char width_str[10];
    printf("Enter line width: ");
    fgets(width_str, 10, stdin);
    int width = 0;
    for (int i = 0; i < s21_strlen(width_str); i++) {
        if (width_str[i] >= '0' && width_str[i] <= '9') {
            width = width * 10 + (width_str[i] - '0');
        } else {
            break;
        }
    }
    char input[MAX_INPUT_LENGTH];
    printf("Enter text: ");
    fgets(input, MAX_INPUT_LENGTH, stdin);

    int current_len = 0;
    int word_len = 0;
    char *word = s21_strtok(input, " ");
    while (word != NULL) {
        word_len = s21_strlen(word);
        if (current_len == 0) {
            printf("%s", word);
            current_len += word_len;
        } else if (current_len + 1 + word_len <= width) {
            printf(" %s", word);
            current_len += 1 + word_len;
        } else if (word_len > width) {
            printf("\n");
            for (int i = 0; i < word_len; i += width) {
                if (i + width < word_len) {
                    printf("%.5s-\n", word + i);
                } else {
                    printf("%.5s\n", word + i);
                }
            }
            current_len = 0;
        } else {
            printf("\n%s", word);
            current_len = word_len;
        }
        word = s21_strtok(NULL, " ");
        if (word != NULL && s21_strlen(word) + 1 > width) {
            printf("\n");
            for (int i = 0; i < s21_strlen(word); i += width) {
                if (i + width < s21_strlen(word)) {
                    printf("%.5s-\n", word + i);
                } else {
                    printf("%.5s\n", word + i);
                }
            }
            current_len = 0;
            word = s21_strtok(NULL, " ");
        }
    }

    if (current_len != 0) {
        printf("\n");
    }

    return 0;
}
