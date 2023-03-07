#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>

int s21_strlen_test(void) {
    const char *str1 = "Hello, world!";  // normal value
    const char *str2 = "";               // normal value with empty string
    const char *str3 = "\n\t\v\f\r";     // normal value with control characters
    const char *str4 = "foo\0bar";       // abnormal value with null character
    const char *str5 = "a\377";          // abnormal value with octal escape sequence
    const char *str6 =
        ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123"
         "456789!\"#$%&'()*+,-./"
         ":;<=>?@[\\]^_`{|}~");  // boundary value with long string

    int result = 1;

    printf("%s\n", str1);
    printf("%d\n", s21_strlen(str1));
    if (s21_strlen(str1) != 13) {
        printf("FAIL\n");
        result = 0;
    } else {
        printf("SUCCESS\n");
    }

    printf("%s\n", str2);
    printf("%d\n", s21_strlen(str2));
    if (s21_strlen(str2) != 0) {
        printf("FAIL\n");
        result = 0;
    } else {
        printf("SUCCESS\n");
    }

    printf("%s\n", str3);
    printf("%d\n", s21_strlen(str3));
    if (s21_strlen(str3) != 5) {
        printf("FAIL\n");
        result = 0;
    } else {
        printf("SUCCESS\n");
    }

    printf("%s\n", str4);
    printf("%d", s21_strlen(str4));
    if (s21_strlen(str4) != 3) {
        printf("FAIL\n");
        result = 0;
    } else {
        printf("SUCCESS\n");
    }

    printf("%s\n", str5);
    printf("%d\n", s21_strlen(str5));
    if (s21_strlen(str5) != 2) {
        printf("FAIL\n");
        result = 0;
    } else {
        printf("SUCCESS\n");
    }

    printf("%s\n", str6);
    printf("%d\n", s21_strlen(str6));
    if (s21_strlen(str6) != 94) {
        printf("FAIL");
        result = 0;
    } else {
        printf("SUCCESS");
    }

    return result;
}

int s21_strcmp_test(void) {
    const char *str1a = "Hello, world!";  // normal value
    const char *str1b = "Hello, world!";
    const char *str4a = "abc\0def";  // abnormal value with null character
    const char *str4b = "abc\0xyz";
    const char *str6a = "abcdefg";  // boundary value with short string
    const char *str6b = "abcdefh";

    int result = 1;

    printf("%s %s\n", str1a, str1b);
    printf("%d\n", s21_strcmp(str1a, str1b));
    if (s21_strcmp(str1a, str1b) != 0) {
        printf("FAIL\n");
        result = 0;
    } else {
        printf("SUCCESS\n");
    }

    printf("%s %s\n", str4a, str4b);
    printf("%d\n", s21_strcmp(str4a, str4b));
    if (s21_strcmp(str1a, str1b) != 0) {
        printf("FAIL\n");
        result = 0;
    } else {
        printf("SUCCESS\n");
    }
    printf("%s %s\n", str6a, str6b);
    printf("%d\n", s21_strcmp(str6a, str6b));
    if (s21_strcmp(str1a, str1b) != 0) {
        printf("FAIL");
        result = 0;
    } else {
        printf("SUCCESS");
    }
    return result;
}

int s21_strcpy_test(void) {
    const char *src1 = "Hello, world!";  // normal value
    char *dst1 = malloc(s21_strlen(src1) + 1);
    s21_strcpy(dst1, src1);
    const char *src3 =
        "This is a long string that will test the boundary of "
        "s21_strcpy function";  // boundary value with
                                // long string
    char *dst3 = malloc(s21_strlen(src3) + 1);
    s21_strcpy(dst3, src3);
    const char *src4 = "string with\0null character";  // abnormal value with null character
    char *dst4 = malloc(s21_strlen(src4) + 1);
    s21_strcpy(dst4, src4);
    int result = 1;

    printf("%s\n", src1);
    printf("%s\n", dst1);
    if (s21_strcmp(dst1, src1) != 0) {
        printf("FAIL\n");
        result = 0;
    } else {
        printf("SUCCESS\n");
    }

    printf("%s\n", src3);
    printf("%s\n", dst3);
    if (s21_strcmp(dst3, src3) != 0) {
        printf("FAIL\n");
        result = 0;
    } else {
        printf("SUCCESS\n");
    }

    printf("%s\n", src4);
    printf("%s\n", dst4);
    if (s21_strcmp(dst4, src4) != 0) {
        printf("FAIL");
        result = 0;
    } else {
        printf("SUCCESS");
    }

    free(dst1);
    free(dst3);
    free(dst4);

    return result;
}

int s21_strcat_test(void) {
    char dest1[20] = "Hello, ";
    const char *src1 = "world!";  // normal value
    s21_strcat(dest1, src1);
    printf("%s %s\n", "Hello,", "world!");
    printf("%s\n", dest1);
    if (s21_strcmp(dest1, "Hello, world!") != 0) {
        printf("FAIL\n");
        return 0;
    } else {
        printf("SUCCESS\n");
    }

    char dest2[5] = "123\0";
    const char *src2 = "456";  // abnormal value with null character
    s21_strcat(dest2, src2);
    printf("%s %s\n", "123\0", "456");
    printf("%s\n", dest2);
    if (s21_strcmp(dest2, "123456") != 0) {
        printf("FAIL\n");
        return 0;
    } else {
        printf("SUCCESS\n");
    }

    char dest3[100] = "";
    const char *src3 =
        "This is a long string that will test the boundary of "
        "s21_strcat function";  // boundary value with
                                // long string
    s21_strcat(dest3, src3);
    printf("%s %s\n", "",
           "This is a long string that will test the boundary of s21_strcat "
           "function");
    printf("%s\n", dest3);
    if (s21_strcmp(dest3,
                   "This is a long string that will test the boundary of "
                   "s21_strcat function") != 0) {
        printf("FAIL");
        return 0;
    } else {
        printf("SUCCESS");
    }

    return 1;
}

int s21_strchr_test(void) {
    const char *str1 = "Hello, world!";  // normal value
    const char *res = s21_strchr(str1, 'o');
    printf("%s %c\n", str1, 'o');
    printf("%s\n", res);
    if (s21_strlen(res) != s21_strlen(str1) - 4) {
        printf("FAIL\n");
        return 0;
    } else {
        printf("SUCCESS\n");
    }

    const char *str2 = "string with\0null character";  // abnormal value with null character
    const char *res2 = s21_strchr(str2, '\0');
    printf("%s %c\n", str2, '\0');
    printf("%s\n", res2);
    if (s21_strlen(res2) != s21_strlen(str2) - 11) {
        printf("FAIL\n");
        return 0;
    } else {
        printf("SUCCESS\n");
    }

    const char *str3 =
        "This is a long string that will test the boundary of "
        "s21_strchr function";  // boundary value with
                                // long string
    const char *res3 = s21_strchr(str3, 's');
    printf("%s %c\n", str3, 's');
    printf("%s\n", res3);
    if (s21_strlen(res3) != s21_strlen(str3) - 3) {
        printf("FAIL\n");
        return 0;
    } else {
        printf("SUCCESS");
    }
    return 1;
}

int s21_strstr_test(void) {
    const char *haystack1 = "Hello, world!";  // normal value
    const char *needle1 = "world";
    char *res1 = s21_strstr(haystack1, needle1);
    printf("%s %s\n", haystack1, needle1);
    printf("%s\n", res1);
    if (s21_strlen(res1) != s21_strlen(haystack1) - 7) {
        printf("FAIL\n");
        return 0;
    } else {
        printf("SUCCESS\n");
    }

    const char *haystack2 = "string with null character";  // abnormal value with null character
    const char *needle2 = "null";
    char *res2 = s21_strstr(haystack2, needle2);
    printf("%s %s\n", haystack2, needle2);
    printf("%s\n", res2);
    if (s21_strlen(res2) != s21_strlen(haystack2) - 12) {
        printf("FAIL\n");
        return 0;
    } else {
        printf("SUCCESS\n");
    }

    const char *haystack3 =
        "This is a long string that will test the boundary "
        "of s21_strstr function";  // boundary value with
                                   // long string
    const char *needle3 = "s21_strstr";
    char *res3 = s21_strstr(haystack3, needle3);
    printf("%s %s\n", haystack3, needle3);
    printf("%s\n", res3);
    if (s21_strlen(res3) != s21_strlen(haystack3) - 53) {
        printf("FAIL");
        return 0;
    } else {
        printf("SUCCESS");
    }
    return 1;
}

int s21_strtok_test(void) {
    char str1[] = "Hello, world! How are you today?";  // normal value
    const char *delim = " ";
    char *token1;
    token1 = s21_strtok(str1, delim);  // get first token
    printf("%s %s\n", str1, delim);
    printf("%s\n", token1);
    if (s21_strlen(token1) != 6) {
        printf("FAIL\n");
        return 0;
    } else {
        printf("SUCCESS\n");
    }
    char str2[] = "Hello,\0world!";  // abnormal value with null character
    const char *delim2 = ",\0";
    char *token2 = s21_strtok(str2, delim2);
    printf("%s %s\n", str2, delim2);
    printf("%s\n", token2);
    if (s21_strlen(token2) != 5) {
        printf("FAIL\n");
        return 0;
    } else {
        printf("SUCCESS\n");
    }

    char str3[] =
        "a||b||c||d||e||f||g||h||i||j||k||l||m||n||o||p||q||r||s||t||u|"
        "|v||w||x||y||z";  // boundary value
                           // with long string
    const char *delim3 = "||";
    char *token3 = s21_strtok(str3, delim3);
    printf("%s %s\n", str3, delim3);
    printf("%s\n", token3);
    if (s21_strlen(token3) != 1) {
        printf("FAIL");
        return 0;
    } else {
        printf("SUCCESS");
    }
    return 1;
}

int main(void) {
#ifdef STRLEN
    s21_strlen_test();
#endif

#ifdef STRCMP
    s21_strcmp_test();
#endif

#ifdef STRCPY
    s21_strcpy_test();
#endif

#ifdef STRCAT
    s21_strcat_test();
#endif

#ifdef STRCHR
    s21_strchr_test();
#endif

#ifdef STRSTR
    s21_strstr_test();
#endif

#ifdef STRTOK
    s21_strtok_test();
#endif

    return 0;
}
