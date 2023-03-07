#ifndef STATESORT
#define STATESORT

#include "binary.h"

void engine();

void read_path(char *path);
void read_command(int *command);

void sort_engine(char *path);
void print_engine(char *path);
void write_engine(char *path);

filestate file_state(char *filename);

int equal_datetime(datetime record_i, datetime record_j);
long int datetime_to_int(datetime record);
datetime read_datetime();

void clean_buffer();

#endif
