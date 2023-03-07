#include "clear_state.h"

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

    read_path(path);
    filestate file = file_state(path);

    if (file.is_exist == 0) {
        printf("n/a");
        exit(1);
    }
    sort_engine(path);
    daterange date_record;
    date_record = read_date(date_record);
    rewrite(path, date_record);
}

daterange read_date() {
    daterange date_record;
    scanf("%d.%d.%d %d.%d.%d", &date_record.from_day, &date_record.from_month, &date_record.from_year,
          &date_record.to_day, &date_record.to_month, &date_record.to_year);
    clean_buffer();
    return date_record;
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

void rewrite(char *path, daterange delete) {
    FILE *file_from = fopen(path, "rb+");
    char *temp = "temp";
    FILE *file_to = fopen(temp, "wb+");

    int count_records = get_file_size_in_bytes(file_from) / sizeof(datetime);

    for (int idx = 0; idx < count_records; idx++) {
        datetime cr = read_record_from_file(file_from, idx);
        if (equal_date(cr, delete) == 1) {
            write_record_in_end_file(file_to, &cr);
            printf("%d %d %d %d %d %d %d %d\n", cr.year, cr.month, cr.day, cr.hour, cr.minutes, cr.seconds,
                   cr.status, cr.code);
        }
    }

    fclose(file_from);
    fclose(file_to);
    remove(path);
    rename(temp, path);
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

int equal_date(datetime current, daterange delete) {
    int res = 1;

    int curtime = current.year * 10000000 + current.month * 10000 + current.day;
    int from = delete.from_year * 10000000 + delete.from_month * 10000 + delete.from_day;
    int to = delete.to_year * 10000000 + delete.to_month * 10000 + delete.to_day;

    if (curtime >= from && curtime <= to) res = 0;

    return res;
}