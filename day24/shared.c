
/*
Здесь table — указатель на начало данных таблицы, num_records — количество записей в таблице, 
record_size — размер каждой записи в байтах, а filter_func — функция, которая принимает указатель 
записи и возвращает логическое значение, указывающее, является ли запись должна быть включена в вывод или нет.
*/
void select_records(void *table, int num_records, int record_size, int (*filter_func)(void *)) {
    for (int i = 0; i < num_records; i++) {
        void *record = (char *)table + i * record_size;
        if (filter_func(record)) {
            // Print record data
        }
    }
}

/*
Здесь table — это указатель на начало данных таблицы, num_records — указатель на количество записей в таблице, 
max_records — указатель на максимальное количество записей, которое может храниться в таблице, запись — это указатель 
на данные для новой добавляемой записи, а размер_записи — размер каждой записи в байтах.
*/
void insert_record(void **table, int *num_records, int *max_records, void *record, int record_size) {
    if (*num_records == *max_records) {
        // Allocate more memory for table
        *max_records += 10;
        *table = realloc(*table, *max_records * record_size);
    }

    // Add new record to end of table
    void *new_record = (char *)*table + *num_records * record_size;
    memcpy(new_record, record, record_size);

    *num_records += 1;
}

/*
Здесь table — указатель на начало данных таблицы, num_records — количество записей в таблице, 
record_size — размер каждой записи в байтах, filter_func — функция, которая принимает указатель 
записи и возвращает логическое значение, указывающее, является ли запись должна быть обновлена ​​или нет, 
а update_func — это функция, которая принимает указатель записи и обновляет ее данные.
*/
void update_records(void *table, int num_records, int record_size, int (*filter_func)(void *), void (*update_func)(void *)) {
    for (int i = 0; i < num_records; i++) {
        void *record = (char *)table + i * record_size;
        if (filter_func(record)) {
            update_func(record);
        }
    }
}


void delete_records(void *table, int *num_records, int record_size, int (*filter_func)(void *)) {
    int num_deleted = 0;
    for (int i = 0; i < *num_records; i++) {
        void *record = (char *)table + i * record_size;
        if (filter_func(record)) {
            num_deleted++;
        } else if (num_deleted > 0) {
            // Move record data up to fill gap
            void *dest = (char *)table + (i - num_deleted) * record_size;
            memcpy(dest, record, record_size);
        }
    }

    // Reduce number of records in table
    *num_records -= num_deleted;
}


/*
for modules, for example
*/
// // SELECT function
// int select_modules(Module *modules, int num_modules, char *condition, Module **result_set) {
//     int count = 0;
//     for (int i = 0; i < num_modules; i++) {
//         if (condition == NULL || strcmp(condition, "") == 0 || strstr(modules[i].name, condition) != NULL) {
//             result_set[count] = &modules[i];
//             count++;
//         }
//     }
//     return count;
// }

// // INSERT function
// void insert_module(Module *modules, int *num_modules, char *name, int memory_level, int cell_number) {
//     int id = *num_modules + 1; // Generate new ID
//     // Find first available index in modules array
//     int index = -1;
//     for (int i = 0; i < MAX_MODULES; i++) {
//         if (modules[i].id == 0) {
//             index = i;
//             break;
//         }
//     }
//     if (index != -1) {
//         modules[index].id = id;
//         strcpy(modules[index].name, name);
//         modules[index].memory_level = memory_level;
//         modules[index].cell_number = cell_number;
//         modules[index].deleted = 0;
//         (*num_modules)++;
//     }
// }

// // UPDATE function
// void update_module(Module *modules, int num_modules, int id, char *name, int memory_level, int cell_number) {
//     for (int i = 0; i < num_modules; i++) {
//         if (modules[i].id == id) {
//             strcpy(modules[i].name, name);
//             modules[i].memory_level = memory_level;
//             modules[i].cell_number = cell_number;
//             break;
//         }
//     }
// }

// // DELETE function
// void delete_module(Module *modules, int num_modules, int id) {
//     for (int i = 0; i < num_modules; i++) {
//         if (modules[i].id == id) {
//             modules[i].deleted = 1;
//             break;
//         }
//     }
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 30

// Define struct for Module table
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int memory_level;
    int cell_number;
    int deleted;
} Module;

// Define struct for Level table
typedef struct {
    int memory_level;
    int num_cells;
    int security_flag;
} Level;

// Define struct for Status_Event table
typedef struct {
    int id;
    int module_id;
    int new_status;
    char date[11];
    char time[9];
} Status_Event;

// Define function to select all active modules
void select_all_active_modules(Module *modules, int num_modules) {
    printf("Active Modules:\n");
    for (int i = 0; i < num_modules; i++) {
        if (modules[i].deleted == 0) {
            printf("ID: %d, Name: %s, Memory Level: %d, Cell Number: %d\n",
                   modules[i].id, modules[i].name, modules[i].memory_level, modules[i].cell_number);
        }
    }
}

// Define function to delete modules by ids
void delete_modules_by_ids(Module *modules, int num_modules, int *ids, int num_ids) {
    for (int i = 0; i < num_ids; i++) {
        int id = ids[i];
        for (int j = 0; j < num_modules; j++) {
            if (modules[j].id == id) {
                modules[j].deleted = 1;
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
            modules[i].deleted = 1;
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
            printf("Moved module with ID %d to Memory Level %d, Cell Number %d\n",
                   id, new_memory_level, new_cell_number);
            break;
        }
    }
}

// Define function to set protection flag of the specified memory level
void set_protection_flag_of_memory_level(Level *levels, int num_levels, int memory_level, int flag) {
    for (int i = 0; i < num_levels; i++) {
        if (levels[i].memory_level == memory_level) {
            levels[i].security_flag = flag;
            printf("Set protection flag of Memory Level %d to %d\n", memory_level, flag);
            break;
        }
    }
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

Status_Event *read_status_events_table(char *filename) {
  FILE *fp = fopen(filename, "rb");
  if (fp == NULL) {
    printf("Error opening file %s\n", filename);
    exit(1);
  }

  // Get the number of records
  fseek(fp, 0, SEEK_END);
  int num_records = ftell(fp) / sizeof(Status_Event);
  fseek(fp, 0, SEEK_SET);

  // Allocate memory for the status events array
  Status_Event *status_events =
      (Status_Event *)malloc(num_records * sizeof(Status_Event));

  // Read the status events from the file
  fread(status_events, sizeof(Status_Event), num_records, fp);

  // Close the file
  fclose(fp);

  return status_events;
}

int get_num_status_events(char *filename) {
  FILE *fp = fopen(filename, "rb");
  if (fp == NULL) {
    printf("Error opening file %s\n", filename);
    exit(1);
  }

  // Get the number of records
  fseek(fp, 0, SEEK_END);
  long num_bytes = ftell(fp);
  int num_records = (int)(num_bytes / sizeof(Status_Event));
  fclose(fp);
  return num_records;
}

Status_Event *read_status_events_table(char *filename) {
  // Get the number of records in the file
  int num_records = get_num_status_events(filename);
  // Allocate memory for the array of records
  Status_Event *status_events =
      (Status_Event *)malloc(num_records * sizeof(Status_Event));
  if (status_events == NULL) {
    printf("Error allocating memory for status_events\n");
    exit(1);
  }

  // Read the records from the file
  FILE *fp = fopen(filename, "rb");
  if (fp == NULL) {
    printf("Error opening file %s\n", filename);
    exit(1);
  }

  fread(status_events, sizeof(Status_Event), num_records, fp);

  fclose(fp);
  return status_events;
}

void print_modules(Module modules[], int num_modules) {
    printf("Module ID\tName\n");
    for (int i = 0; i < num_modules; i++) {
        printf("%d\t\t%s\n", modules[i].id, modules[i].name);
    }
}

void print_levels(Level levels[], int num_levels) {
    printf("Level ID\tName\n");
    for (int i = 0; i < num_levels; i++) {
        printf("%d\t\t%s\n", levels[i].id, levels[i].name);
    }
}

void print_status_events(Status_Event status_events[], int num_status_events) {
    printf("Event ID\tName\t\t\tLevel ID\n");
    for (int i = 0; i < num_status_events; i++) {
        printf("%d\t\t%s\t\t%d\n", status_events[i].id, status_events[i].name, status_events[i].level_id);
    }
}

// Get the filename for the index of a table and column
char *get_index_filename(const char *table, const char *column) {
    char *filename = malloc(strlen(table) + strlen(column) + 5);
    sprintf(filename, "%s.%s.idx", table, column);
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
    sprintf(data_filename, "%s.dat", table);

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

// Create an index file for a table and column
void create_index(const char *table, const char *column) {
    char *filename = get_index_filename(table, column);

    char *data_filename = malloc(strlen(table) + 5);
    sprintf(data_filename, "%s.dat", table);

    FILE *data_file = fopen(data_filename, "rb");
    FILE *index_file = fopen(filename, "wb");

    if (!data_file || !index_file) {
        fclose(data_file);
        fclose(index_file);
        free(filename);
        free(data_filename);
        return;
    }

    fseek(data_file, 0, SEEK_END);
    long file_size = ftell(data_file);
    long num_entries = file_size / sizeof(Module);

    int *ids = malloc(num_entries * sizeof(int));
    if (!ids) {
        fclose(data_file);
        fclose(index_file);
        free(filename);
        free(data_filename);
        return;
    }

    rewind(data_file);

    for (int i = 0; i < num_entries; i++) {
        Module module;
        fread(&module, sizeof(Module), 1, data_file);
        ids[i] = module.id;
    }

    fwrite(ids, sizeof(int), num_entries, index_file);

    fclose(data_file);
    fclose(index_file);
    free(ids);
    free(filename);
    free(data_filename);
}


int main() {
    int id = 1;  // The identifier of the row to retrieve
    Module row;  // The structure to store the row data

    if (get_row_by_id("modules", "id", id, &row)) {
        printf("Module %d: %s\n", row.id, row.name);
    } else {
        printf("Module with id %d not found\n", id);
    }

    return 0;
}