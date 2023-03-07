#include "levels.h"

Level *read_levels_table(char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    // Get the number of records
    fseek(fp, 0, SEEK_END);
    int num_records = ftell(fp) / sizeof(Level);
    fseek(fp, 0, SEEK_SET);

    // Allocate memory for the levels array
    Level *levels = (Level *)malloc(num_records * sizeof(Level));

    // Read the levels from the file
    fread(levels, sizeof(Level), num_records, fp);

    // Close the file
    fclose(fp);

    return levels;
}

int get_num_levels(char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    // Get the number of records
    fseek(fp, 0, SEEK_END);
    int num_records = ftell(fp) / sizeof(Level);
    fseek(fp, 0, SEEK_SET);

    // Close the file
    fclose(fp);

    return num_records;
}

void print_levels(Level *levels, int num_levels) {
    printf("Memory Level\tCell Number\tSecurity flag\n");
    for (int i = 0; i < num_levels; i++) {
        printf("%d\t\t%d\t\t%d\n", levels[i].memory_level, levels[i].num_cells, levels[i].security_flag);
    }
}

void insert_levels(Level *levels, int num_levels, int memory_level, int num_cells) {
    int index = -1;
    for (int i = 0; i < num_levels; i++) {
        if (levels[i].security_flag == 1) {
            index = i;
            break;
        }
    }
    if (index == -1) {  // No available index, append to the end
        index = num_levels;
    }
    // Set levels values
    levels[index].memory_level = memory_level;
    levels[index].num_cells = num_cells;
    levels[index].security_flag = 0;
}

void update_level(Level *levels, int num_levels, int memory_level, int num_cells) {
    for (int i = 0; i < num_levels; i++) {
        if (levels[i].memory_level == memory_level && levels[i].security_flag != 1) {
            levels[i].num_cells = num_cells;
            break;
        }
    }
}

void delete_level(Level *levels, int num_levels, int memory_level) {
    for (int i = 0; i < num_levels; i++) {
        if (levels[i].memory_level == memory_level && levels[i].security_flag != 1) {
            levels[i].security_flag = 1;
            break;
        }
    }
}