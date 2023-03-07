
#include <stdio.h>
#include <stdlib.h>

char decode_char(char c) {
    if (c >= 'a' && c <= 'z') {
        return 'z' - c + 'a';
    } else if (c >= 'A' && c <= 'Z') {
        return 'Z' - c + 'A';
    } else {
        return c;
    }
}

int main(int argc, char *argv[]) {
    int mode = -1;
    char input_str[100];
    int i;
    char encoded;

    if (argc != 2) {
        printf("Usage: %s 0 (for encoding) or 1 (for decoding)\n", argv[0]);
        return 1;
    }

    mode = atoi(argv[1]);

    if (mode != 0 && mode != 1) {
        printf("Usage: %s 0 (for encoding) or 1 (for decoding)\n", argv[0]);
        return 1;
    }

    printf("Enter the string: ");
    scanf("%s", input_str);

    for (i = 0; input_str[i] != '\0'; i++) {
        if (mode == 0) {
            encoded = encode_char(input_str[i]);
        } else {
            encoded = decode_char(input_str[i]);
        }

        if (encoded == 'n/a') {
            printf("n/a");
            return 1;
        } else {
            printf("%c ", encoded);
        }
    }

    printf("\n");

    return 0;
}
