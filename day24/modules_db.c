#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modules_table.h"
#include "levels_table.h"
#include "status_events_table.h"

int interface() {
  // Read data from database files
  Module *modules = read_modules_table("modules.db");
  int num_modules = get_num_modules("modules.db");
  Level *levels = read_levels_table("levels.db");
  int num_levels = get_num_levels("levels.db");
  StatusEvent *status_events = read_status_events_table("status_events.db");
  int num_status_events = get_num_status_events("status_events.db");

  // Control menu loop
  int operation, table, num_records;
  do {
    // Print menu options
    printf("Please choose an operation:\n");
    printf(" 1. SELECT\n");
    printf(" 2. INSERT\n");
    printf(" 3. UPDATE\n");
    printf(" 4. DELETE\n");
    printf(" 5. Get all active additional modules (last module status is 1)\n");
    printf(" 6. Delete modules by ids\n");
    printf(" 7. Set protected mode for module by id\n");
    printf(" 8. Move module by id to specified memory level and cell\n");
    printf(" 9. Set protection flag of the specified memory level\n");
    printf("> ");
    scanf("%d", &operation);

    // Handle user input
    switch (operation) {
      case 1:  // SELECT
        printf("Please choose a table:\n");
        printf(" 1. Modules\n");
        printf(" 2. Levels\n");
        printf(" 3. Status events\n");
        printf("> ");
        scanf("%d", &table);
        printf(
            "Insert the number of records or leave empty to output all of "
            "them: ");
        scanf("%d", &num_records);

        // Call corresponding function for SELECT operation
        switch (table) {
          case 1:  // Modules
            if (num_records == 0) {
              print_modules_table(modules, num_modules);
            } else {
              print_n_modules(modules, num_modules, num_records);
            }
            break;
          case 2:  // Levels
            if (num_records == 0) {
              print_levels_table(levels, num_levels);
            } else {
              print_n_levels(levels, num_levels, num_records);
            }
            break;
          case 3:  // Status events
            if (num_records == 0) {
              print_status_events_table(status_events, num_status_events);
            } else {
              print_n_status_events(status_events, num_status_events,
                                    num_records);
            }
            break;
          default:
            printf("Invalid table selection.\n");
            break;
        }
        break;

      case 2:  // INSERT
        printf("Please choose a table:\n");
        printf(" 1. Modules\n");
        printf(" 2. Levels\n");
        printf(" 3. Status events\n");
        printf("> ");
        scanf("%d", &table);

        // Call corresponding function for INSERT operation
        switch (table) {
          case 1:  // Modules
            char name[30];
            int num_modules, memory_level, cell_number;
            printf("Please enter the num modules: ");
            scanf("%d", &num_modules);
            printf("Enter module name: ");
            scanf("%s", name);
            printf("Enter memory level: ");
            scanf("%d", &memory_level);
            printf("Enter cell number: ");
            scanf("%d", &cell_number);
            insert_module(modules, num_modules, name, memory_level,
                          cell_number);
            printf("Module added successfully!\n");
            break;
          case 2:  // Levels
            int num_levels, memory_level, num_cell, security_flag;
            printf("Please enter the num: ");
            scanf("%d", &num_levels);
            printf("Enter memory level: ");
            scanf("%d", &memory_level);
            printf("Enter cell number: ");
            scanf("%d", &num_cell);
            printf("Enter security flag: ");
            scanf("%d", &security_flag);
            insert_level(levels, num_levels, memory_level, num_cell,
                         security_flag);
            printf("Level added successfully!\n");
            break;
          case 3:  // Status events
            int num_status_event, module_id, new_status;
            char date[11], time[9];
            printf("Enter module ID: ");
            scanf("%d", &module_id);
            printf("Enter new status: ");
            scanf("%d", &new_status);
            printf("Enter date (dd.mm.yyyy): ");
            scanf("%s", date);
            printf("Enter time (hh:mm:ss): ");
            scanf("%s", time);
            insert_status_event(status_events, num_status_events, module_id,
                                new_status, date, time);
            printf("Status event added successfully!\n");
            break;
          default:
            printf("Invalid table selection.\n");
        }
        break;
      case 3:  // UPDATE
        printf("Please choose a table:\n");
        printf("1. Modules\n");
        printf("2. Levels\n");
        printf("3. Status events\n");
        scanf("%d", &table);
        switch (table) {
          case 1:  // Modules
            int id, num_modules, memory_level, cell_number;
            char name[30];
            printf("Please enter the ID of the module to update: ");
            scanf("%d", &id);
            printf("Please enter the new name of the module: ");
            scanf("%s", name);
            printf("Please enter the new memory level of the module: ");
            scanf("%d", &memory_level);
            printf("Please enter the new cell number of the module: ");
            scanf("%d", &cell_number);
            update_module(modules, num_modules, id, name, memory_level,
                          cell_number);
            printf("Module updated successfully!\n");
            break;
          case 2:  // Levels
            int memory_level, num_cells, security_flag;
            char date[11], time[9];
            printf("Please enter the number of the level to update: ");
            scanf("%d", &memory_level);
            printf("Please enter the new number of cells for the level: ");
            scanf("%d", &num_cells);
            printf("Please enter the new security flag for the level: ");
            scanf("%d", &security_flag);
            update_level(levels, num_levels, memory_level, num_cells,
                         security_flag);
            printf("Level updated successfully!\n");
            break;
          case 3:  // Status events
            int id, num_status_events, module_id, new_status;
            char date[11], time[9];
            printf("Please enter the ID of the status event to update: ");
            scanf("%d", &id);
            printf("Please enter the new module ID: ");
            scanf("%d", &module_id);
            printf("Please enter the new status: ");
            scanf("%d", &new_status);
            printf("Please enter the new date (dd.mm.yyyy): ");
            scanf("%s", date);
            printf("Please enter the new time (hh:mm:ss): ");
            scanf("%s", time);
            update_status_event(status_events, num_status_events, id, module_id,
                                new_status, date, time);
            printf("Status event updated successfully!\n");
            break;
          default:
            printf("Invalid table selection.\n");
        }
        break;
      case 4:  // DELETE
        printf("Please choose a table:\n");
        printf("1. Modules\n");
        printf("2. Levels\n");
        printf("3. Status events\n");
        scanf("%d", &table);
        switch (table) {
          case 1:  // Modules
            int id;
            printf("Enter the ID of the module to delete: ");
            scanf("%d", &id);
            delete_module_by_id(modules, num_modules, id);
            printf("Module with ID %d has been deleted.\n", id);
            break;
          case 2:  // Levels
            int level_number;
            printf("Enter the level number to delete: ");
            scanf("%d", &level_number);
            delete_level_by_number(levels, num_levels, level_number);
            printf("Level %d has been deleted.\n", level_number);
            break;
          case 3:  // Status events
            int id;
            printf("Enter the ID of the status event to delete: ");
            scanf("%d", &id);
            delete_status_event_by_id(status_events, num_status_events, id);
            printf("Status event with ID %d has been deleted.\n", id);
            break;
          default:
            printf("Invalid table selection.\n");
            break;
        }
        break;
    case 5: // Get all active additional modules
        select_all_active_modules(modules, num_modules);
        break;
    case 6: // Delete modules by ids
        printf("Please enter IDs of modules to delete (comma separated): ");
        fgets(input, 1024, stdin);
        ids = split_input(input, &num_ids);
        delete_modules_by_id(modules, &num_modules, ids, num_ids);
        free(ids);
        break;
    case 7: // Set protected mode for module by id
        printf("Please enter module ID: ");
        scanf("%d", &module_id);
        set_protected_mode(modules, num_modules, module_id);
        break;
    case 8: // Move module by id to specified memory level and cell
        printf("Please enter module ID: ");
        scanf("%d", &module_id);
        printf("Please enter new memory level: ");
        scanf("%d", &new_memory_level);
        printf("Please enter new cell number: ");
        scanf("%d", &new_cell_number);
        move_module(modules, num_modules, module_id, new_memory_level, new_cell_number);
        break;
    case 9: // Set protection flag of the specified memory level
        printf("Please enter memory level number: ");
        scanf("%d", &memory_level);
        set_protection_flag(levels, num_levels, memory_level);
        break;
      default:
        printf("Invalid operation selection.\n");
        break;
    }
  }
}

  int main() {
    int num_modules = 0;
    int num_levels = 0;
    int num_status_events = 0;
    Module modules[MAX_MODULES];
    Level levels[MAX_LEVELS];
    StatusEvent status_events[MAX_STATUS_EVENTS];
    read_modules_file(modules, &num_modules);
    read_levels_file(levels, &num_levels);
    read_status_events_file(status_events, &num_status_events);

    printf("Initial Modules table:\n");
    print_modules(modules, num_modules);

    printf("\nInitial Levels table:\n");
    print_levels(levels, num_levels);

    printf("\nInitial Status Events table:\n");
    print_status_events(status_events, num_status_events);

    // Set initial values
    modules[0].id = 0;
    strcpy(modules[0].name, "Main AI Module");
    modules[0].memory_level = 1;
    modules[0].cell_number = 1;
    modules[0].delete_flag = 0;

    levels[0].memory_level_number = 1;
    levels[0].num_cells = 1;
    levels[0].security_flag = 0;

    num_modules++;
    num_levels++;

    // Update Modules and Levels files with initial values
    write_modules_file(modules, num_modules);
    write_levels_file(levels, num_levels);

    printf("\nInitial tables after adding main module:\n");
    printf("Modules table:\n");
    print_modules(modules, num_modules);
    printf("\nLevels table:\n");
    print_levels(levels, num_levels);

    control_menu(modules, num_modules, levels, num_levels, status_events,
                 num_status_events);

    // Update Modules, Levels and Status Events files after changes
    write_modules_file(modules, num_modules);
    write_levels_file(levels, num_levels);
    write_status_events_file(status_events, num_status_events);

    return 0;
  }