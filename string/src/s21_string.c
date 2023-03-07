
#include "s21_string.h"

int s21_strlen(const char *str) {
    int len = 0;
    while (*str++ != '\0') {
        len++;
    }
    return len;
}

int s21_strcmp(const char *str1, const char *str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] < str2[i]) {
            return -1;
        } else if (str1[i] > str2[i]) {
            return 1;
        }
        i++;
    }
    if (str1[i] == '\0' && str2[i] == '\0') {
        return 0;
    } else if (str1[i] == '\0') {
        return -1;
    } else {
        return 1;
    }
}

char *s21_strcpy(char *restrict dest, const char *restrict src) {
    char *result = dest;
    while (*src != '\0') {
        *dest++ = *src++;
    }
    *dest = '\0';
    return result;
}

char *s21_strcat(char *restrict dest, const char *restrict src) {
    char *dest_start = dest;
    while (*dest != '\0') {
        dest++;
    }
    while ((*dest++ = *src++) != '\0')
        ;
    return dest_start;
}

char *s21_strchr(const char *s, int c) {
    while (*s != '\0') {
        if (*s == c) {
            return (char *)s;
        }
        s++;
    }
    if (c == '\0') {
        return (char *)s;
    }
    return NULL;
}

char *s21_strstr(const char *haystack, const char *needle) {
    if (*needle == '\0') {
        return (char *)haystack;
    }

    for (; *haystack != '\0'; ++haystack) {
        if (*haystack == *needle) {
            const char *h = haystack;
            const char *n = needle;

            for (; *n != '\0' && *h == *n; ++h, ++n) {
            }

            if (*n == '\0') {
                return (char *)haystack;
            }
        }
    }

    return NULL;
}

char *s21_strtok(char *str, const char *delim) {
    static char *token = NULL;
    if (str)
        token = str;
    else if (!token)
        return NULL;

    char *start = token;
    char *end;
    while (*token != '\0') {
        const char *d = delim;
        while (*d != '\0') {
            if (*token == *d) {
                *token = '\0';
                end = token;
                token++;
                if (start == end) {
                    start = token;
                    break;
                }
                return start;
            }
            d++;
        }
        token++;
    }

    if (start == token) {
        return NULL;
    } else {
        return start;
    }
}
