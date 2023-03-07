#ifndef BINARY
#define BINARY

#include <stdio.h>
#include <stdlib.h>

typedef struct filestate {
    int is_exist;
    int is_full;
} filestate;

typedef struct datetime {
    int year;
    int month;
    int day;
    int hour;
    int minutes;
    int seconds;
    int status;
    int code;
} datetime;

typedef struct date {
    int year;
    int month;
    int day;
} date;

typedef struct daterange {
    int from_year;
    int from_month;
    int from_day;
    int to_year;
    int to_month;
    int to_day;
} daterange;

typedef struct range {
    int from;
    int to;
} range;

datetime read_record_from_file(FILE *file, int index);
void write_record_in_file(FILE *pfile, const datetime *record_to_write, int index);
void write_record_in_end_file(FILE *pfile, const datetime *record_to_write);
void swap_records_in_file(FILE *pfile, int record_index1, int record_index2);
int get_file_size_in_bytes(FILE *pfile);
int get_records_count_in_file(FILE *pfile);

#endif