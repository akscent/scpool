
#include "shared.h"

// Get the filename for the index of a table and column
char *get_index_filename(const char *table, const char *column) {
    char *filename = malloc(strlen(table) + strlen(column) + 5);
    sprintf(filename, "../materials/master_%s.%s.db", table, column);
    return filename;
}

// Binary search on an index file for a given identifier
int binary_search(const char *filename, int id) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    long num_entries = file_size / sizeof(int);

    int first = 0;
    int last = num_entries - 1;

    while (first <= last) {
        int middle = (first + last) / 2;

        int value;
        fseek(file, middle * sizeof(int), SEEK_SET);
        fread(&value, sizeof(int), 1, file);

        if (value == id) {
            fclose(file);
            return middle;
        } else if (value < id) {
            first = middle + 1;
        } else {
            last = middle - 1;
        }
    }

    fclose(file);
    return -1;
}

// Retrieve a row from a table by its identifier
int get_row_by_id(const char *table, const char *column, int id, void *row) {
    char *filename = get_index_filename(table, column);
    int position = binary_search(filename, id);
    free(filename);

    if (position == -1) {
        return 0;
    }

    char *data_filename = malloc(strlen(table) + 5);
    sprintf(data_filename, "../materials/master_%s.db", table);

    FILE *file = fopen(data_filename, "rb");
    if (!file) {
        free(data_filename);
        return 0;
    }

    fseek(file, position * sizeof(Module), SEEK_SET);
    fread(row, sizeof(Module), 1, file);

    fclose(file);
    free(data_filename);

    return 1;
}

// Define function to select all active modules
void select_active_modules(Module *modules, int num_modules) {
    printf("Active Modules:\n");
    for (int i = 0; i < num_modules; i++) {
        if (modules[i].security_flag == 0) {
            printf("ID: %d, Name: %s, Memory Level: %d, Cell Number: %d\n", modules[i].id, modules[i].name,
                   modules[i].memory_level, modules[i].cell_number);
        }
    }
}

// Define function to delete modules by ids
void delete_modules_by_ids(Module *modules, int num_modules, const char *ids, int num_ids) {
    for (int i = 0; i < num_ids; i++) {
        int id = ids[i];
        for (int j = 0; j < num_modules; j++) {
            if (modules[j].id == id) {
                modules[j].security_flag = 1;
                printf("Deleted module with ID %d\n", id);
                break;
            }
        }
    }
}

// Define function to set protected mode for module by id
void set_module_protected_mode_by_id(Module *modules, int num_modules, int id) {
    for (int i = 0; i < num_modules; i++) {
        if (modules[i].id == id) {
            modules[i].security_flag = 1;
            printf("Set protected mode for module with ID %d\n", id);
            break;
        }
    }
}

// Define function to move module by id to specified memory level and cell
void move_module_by_id(Module *modules, int num_modules, int id, int new_memory_level, int new_cell_number) {
    for (int i = 0; i < num_modules; i++) {
        if (modules[i].id == id) {
            modules[i].memory_level = new_memory_level;
            modules[i].cell_number = new_cell_number;
            printf("Moved module with ID %d to Memory Level %d, Cell Number %d\n", id, new_memory_level,
                   new_cell_number);
            break;
        }
    }
}

// Define function to set protection flag of the specified memory level
void set_protection_flag(Level *levels, int num_levels, int memory_level, int flag) {
    for (int i = 0; i < num_levels; i++) {
        if (levels[i].memory_level == memory_level) {
            levels[i].security_flag = flag;
            printf("Set protection flag of Memory Level %d to %d\n", memory_level, flag);
            break;
        }
    }
}