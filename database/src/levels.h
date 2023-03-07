#ifndef LEVELS_FILE_H
#define LEVELS_FILE_H

#include "shared.h"

Level *read_levels_table(char *filename);
int get_num_levels(char *filename);
void print_levels(Level *levels, int num_levels);
void insert_levels(Level *levels, int num_levels, int memory_level, int num_cells);
void update_level(Level *levels, int num_levels, int memory_level, int num_cells);
void delete_level(Level *levels, int num_levels, int memory_level);

#endif /* LEVELS_FILE_H */