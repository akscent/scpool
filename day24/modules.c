#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modules.h"

// Select all modules from the table
Module* select_all_modules(Module *modules, int num_modules) {
    Module *result = malloc(sizeof(Module) * num_modules);
    int j = 0;
    for (int i = 0; i < num_modules; i++) {
        if (modules[i].delete_flag != 1) {
            result[j] = modules[i];
            j++;
        }
    }
    return result;
}

// Insert new module into the table
void insert_module(Module *modules, int *num_modules, char *name, int memory_level, int cell_number) {
    int id = *num_modules + 1; // Generate new ID
    // Find first available index
    int index = -1;
    for (int i = 0; i < *num_modules; i++) {
        if (modules[i].delete_flag == 1) {
            index = i;
            break;
        }
    }
    if (index == -1) { // No available index, append to the end
        index = *num_modules;
        *num_modules += 1;
    }
    // Set module values
    modules[index].module_id = id;
    strncpy(modules[index].name, name, 30);
    modules[index].memory_level = memory_level;
    modules[index].cell_number = cell_number;
    modules[index].delete_flag = 0;
}

// Update module with given ID
void update_module(Module *modules, int num_modules, int id, char *name, int memory_level, int cell_number) {
    for (int i = 0; i < num_modules; i++) {
        if (modules[i].module_id == id && modules[i].delete_flag != 1) {
            strncpy(modules[i].name, name, 30);
            modules[i].memory_level = memory_level;
            modules[i].cell_number = cell_number;
            break;
        }
    }
}

// Delete module with given ID
void delete_module(Module *modules, int num_modules, int id) {
    for (int i = 0; i < num_modules; i++) {
        if (modules[i].module_id == id && modules[i].delete_flag != 1) {
            modules[i].delete_flag = 1;
            break;
        }
    }
}

