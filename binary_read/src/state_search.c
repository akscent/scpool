
#include "state_search.h"

#include <stdio.h>
#include <stdlib.h>

#include "binary.h"

int main() {
    engine();
    return 0;
}

void engine() {
    char path[256];

    read_path(path);
    filestate file = file_state(path);

    if (file.is_exist == 0) {
        printf("n/a");
        exit(1);
    }

    date date_record;
    date_record = read_date(date_record);
    seach_record(path, date_record);
}

date read_date() {
    date date_record;
    scanf("%d . %d . %d", &date_record.day, &date_record.month, &date_record.year);
    clean_buffer();
    return date_record;
}

void seach_record(char *path, date date_record) {
    FILE *file = fopen(path, "rb");

    int count_records = get_file_size_in_bytes(file) / sizeof(datetime);

    for (int idx = 0; idx < count_records; idx++) {
        datetime current_record = read_record_from_file(file, idx);
        if (current_record.year == date_record.year && current_record.month == date_record.month &&
            current_record.day == date_record.day) {
            printf("%d", current_record.code);
            break;
        }
    }
    fclose(file);
}

void read_path(char *path) {
    scanf("%256s", path);
    clean_buffer();
}

filestate file_state(char *filename) {
    filestate statefile;
    FILE *file = fopen(filename, "rb+");
    statefile.is_exist = 0;
    statefile.is_full = 0;

    if (file) {
        statefile.is_exist = 1;
        if (get_file_size_in_bytes(file) > 0) statefile.is_full = 1;
        fclose(file);
    }
    return statefile;
}

void clean_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}