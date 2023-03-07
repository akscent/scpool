#include "print_module.h"

#include <stdio.h>
#include <time.h>

char print_char(char ch) { return putchar(ch); }

void print_log(char (*print)(char), char* current_time, char* message) {
    char log_str[100];
    sprintf(log_str, "%s %s %s", Log_prefix, current_time, message);
    for (int i = 0; log_str[i] != '\0'; i++) {
        print(log_str[i]);
    }
}
