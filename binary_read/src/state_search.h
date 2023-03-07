#ifndef STATESEARCH
#define STATESEARCH
#include "binary.h"

date read_date();
void seach_record(char *path, date date_record);
void engine();
void read_path(char *path);
filestate file_state(char *filename);
void clean_buffer();

#endif
