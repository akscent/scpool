#ifndef S21_STRING_H
#define S21_STRING_H

int s21_strlen(const char *str);
int s21_strcmp(const char *str1, const char *str2);
char *s21_strcpy(char *restrict dest, const char *restrict src);
char *s21_strcat(char *restrict dest, const char *restrict src);
char *s21_strchr(const char *s, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

#endif  // S21_STRING_H

#ifndef NULL
#define NULL ((void *)0)
#endif
