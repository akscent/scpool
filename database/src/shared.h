#ifndef SHARED_FILE_H
#define SHARED_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 30

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int memory_level;
    int cell_number;
    int security_flag;
} Module;

typedef struct {
    int memory_level;
    int num_cells;
    int security_flag;
} Level;

typedef struct {
    int id;
    int module_id;
    int new_status;
    char date[11];
    char time[9];
} Status_Event;

void select_records(void *table, int num_records, int record_size, int (*filter_func)(void *));
void insert_record(void **table, int *num_records, int *max_records, void *record, int record_size);
void update_records(void *table, int num_records, int record_size, int (*filter_func)(void *),
                    void (*update_func)(void *));
void delete_records(void *table, int *num_records, int record_size, int (*filter_func)(void *));
char *get_index_filename(const char *table, const char *column);
int binary_search(const char *filename, int id);
int get_row_by_id(const char *table, const char *column, int id, void *row);
void create_index(const char *table, const char *column);
void select_active_modules(Module *modules, int num_modules);
void delete_modules_by_ids(Module *modules, int num_modules, const char *ids, int num_ids);
void set_module_protected_mode_by_id(Module *modules, int num_modules, int id);
void move_module_by_id(Module *modules, int num_modules, int id, int new_memory_level, int new_cell_number);
void set_protection_flag(Level *levels, int num_levels, int memory_level, int flag);

#endif /* SHARED_FILE_H */