#include "state_sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "binary.h"

int main() {
    engine();
    return 0;
}

void engine() {
    char path[256];
    int command = 0;
    read_path(path);
    filestate file = file_state(path);

    if (file.is_exist == 0) {
        printf("n/a");
        exit(1);
    }

    read_command(&command);

    if (file.is_exist && file.is_full && command == 0) {
        print_engine(path);
    }

    else if (file.is_exist && file.is_full && command == 1) {
        sort_engine(path);
        print_engine(path);
    }

    else if (file.is_exist && command == 2) {
        write_engine(path);
        sort_engine(path);
        print_engine(path);
    }

    else
        printf("n/a");
}

void sort_engine(char *path) {
    FILE *file = fopen(path, "rb+");
    int count_records = get_records_count_in_file(file);

    for (int iter = 0; iter < count_records; iter++) {
        for (int idx = 0; idx < count_records - 1; idx++) {
            datetime record_1 = read_record_from_file(file, idx);
            datetime record_2 = read_record_from_file(file, idx + 1);
            int rec = equal_datetime(record_1, record_2);
            if (rec == 1) swap_records_in_file(file, idx, idx + 1);
        }
    }
    fclose(file);
}

void print_engine(char *path) {
    FILE *file = fopen(path, "rb");

    int count_records = get_file_size_in_bytes(file) / sizeof(datetime);

    for (int idx = 0; idx < count_records; idx++) {
        datetime r = read_record_from_file(file, idx);
        printf("%d %d %d %d %d %d %d %d\n", r.year, r.month, r.day, r.hour, r.minutes, r.seconds, r.status,
               r.code);
    }
    fclose(file);
}

void write_engine(char *path) {
    datetime record = read_datetime();
    FILE *file = fopen(path, "rb+");
    write_record_in_end_file(file, &record);
    fclose(file);
}

int equal_datetime(datetime r1, datetime r2) {
    struct tm rec1, rec2;
    int rec = 0;

    rec1.tm_year = r1.year;
    rec1.tm_mon = r1.month;
    rec1.tm_mday = r1.day;
    rec1.tm_hour = r1.hour;
    rec1.tm_min = r1.minutes;
    rec1.tm_sec = r1.seconds;

    rec2.tm_year = r2.year;
    rec2.tm_mon = r2.month;
    rec2.tm_mday = r2.day;
    rec2.tm_hour = r2.hour;
    rec2.tm_min = r2.minutes;
    rec2.tm_sec = r2.seconds;

    int dt1 = mktime(&rec1);
    int dt2 = mktime(&rec2);

    if (dt1 > dt2) rec = 1;
    return rec;
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

void read_path(char *path) { scanf("%256s", path); }

void read_command(int *command) { scanf("%d", command); }

datetime read_datetime() {
    datetime r;
    scanf("%d %d %d", &r.year, &r.month, &r.day);
    scanf("%d %d %d", &r.hour, &r.minutes, &r.seconds);
    scanf("%d %d", &r.status, &r.code);
    return r;
}
