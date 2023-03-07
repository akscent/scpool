#ifndef MODULES_FILE_H
#define MODULES_FILE_H

#include "shared.h"

Module *select_modules(Module *modules, int num_modules);
int get_num_modules(char *filename);
Module *read_modules_table(char *filename);
void print_modules(Module *modules, int num_modules);
void insert_module(Module *modules, int num_modules, char *name, int memory_level, int cell_number);
void update_module(Module *modules, int num_modules, int id, char *name, int memory_level, int cell_number);
void delete_module(Module *modules, int num_modules, int id);

#endif /* MODULES_FILE_H */