#include "modules.h"

int get_num_modules(char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    // Get the number of records
    fseek(fp, 0, SEEK_END);
    int num_records = ftell(fp) / sizeof(Module);
    fseek(fp, 0, SEEK_SET);

    // Close the file
    fclose(fp);

    return num_records;
}

Module *read_modules_table(char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    // Get the number of records
    fseek(fp, 0, SEEK_END);
    int num_records = ftell(fp) / sizeof(Module);
    fseek(fp, 0, SEEK_SET);

    // Allocate memory for the modules array
    Module *modules = (Module *)malloc(num_records * sizeof(Module));

    // Read the modules from the file
    fread(modules, sizeof(Module), num_records, fp);

    // Close the file
    fclose(fp);

    return modules;
}

void print_modules(Module *modules, int num_modules) {
    printf("Module ID\tName\t\tMemory Level\tCell Number\tSecurity flag\n");
    for (int i = 0; i < num_modules; i++) {
        printf("%d\t\t%s\t\t%d\t\t%d\t\t%d\n", modules[i].id, modules[i].name, modules[i].memory_level,
               modules[i].cell_number, modules[i].security_flag);
    }
}

// Insert new module into the table
void insert_module(Module *modules, int num_modules, char *name, int memory_level, int cell_number) {
    int id = num_modules + 1;  // Generate new ID
    // Find first available index
    int index = -1;
    for (int i = 0; i < num_modules; i++) {
        if (modules[i].security_flag == 1) {
            index = i;
            break;
        }
    }
    if (index == -1) {  // No available index, append to the end
        index = num_modules;
    }
    // Set module values
    modules[index].id = id;
    strncpy(modules[index].name, name, 30);
    modules[index].memory_level = memory_level;
    modules[index].cell_number = cell_number;
    modules[index].security_flag = 0;
}

// Update module with given ID
void update_module(Module *modules, int num_modules, int id, char *name, int memory_level, int cell_number) {
    for (int i = 0; i < num_modules; i++) {
        if (modules[i].id == id && modules[i].security_flag != 1) {
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
        if (modules[i].id == id && modules[i].security_flag != 1) {
            modules[i].security_flag = 1;
            break;
        }
    }
}