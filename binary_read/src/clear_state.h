
#ifndef STATECLEAR
#define STATECLEAR

#include "binary.h"

void engine();
void seach_record(char *path, date date_record);
void sort_engine(char *path);
daterange read_date();
range date_to_int(daterange r1);
void rewrite(char *path, daterange delete);
filestate file_state(char *filename);
void clean_buffer();
int equal_datetime(datetime r1, datetime r2);
int equal_date(datetime current, daterange delete);
void read_path(char *path);

#endif
