#include "binary.h"

#include <stdio.h>
#include <stdlib.h>

datetime read_record_from_file(FILE *file, int index) {
    int offset = index * sizeof(datetime);
    fseek(file, offset, SEEK_SET);

    datetime record;
    fread(&record, sizeof(datetime), 1, file);
    rewind(file);

    return record;
}

void write_record_in_file(FILE *pfile, const datetime *record_to_write, int index) {
    int offset = index * sizeof(datetime);
    fseek(pfile, offset, SEEK_SET);
    fwrite(record_to_write, sizeof(datetime), 1, pfile);
    fflush(pfile);
    rewind(pfile);
}

void write_record_in_end_file(FILE *pfile, const datetime *record_to_write) {
    fseek(pfile, 0, SEEK_END);
    fwrite(record_to_write, sizeof(datetime), 1, pfile);
    fflush(pfile);
    rewind(pfile);
}

void swap_records_in_file(FILE *pfile, int record_index1, int record_index2) {
    datetime record1 = read_record_from_file(pfile, record_index1);
    datetime record2 = read_record_from_file(pfile, record_index2);

    write_record_in_file(pfile, &record1, record_index2);
    write_record_in_file(pfile, &record2, record_index1);
}

int get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return size;
}

int get_records_count_in_file(FILE *pfile) { return get_file_size_in_bytes(pfile) / sizeof(datetime); }
