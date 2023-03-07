#include "levels.h"
#include "modules.h"
#include "status_events.h"

void print_operation_interface() {
    printf("Please choose a table:\n");
    printf(" 1. Modules\n");
    printf(" 2. Levels\n");
    printf(" 3. Status events\n");
    printf("> ");
}
void print_menu_interface() {
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
    printf("10. Binary search for ID by column\n");
    printf("> ");
}
void interface() {
    // Read data from database files
    Module *modules = read_modules_table("../materials/master_modules.db");
    int num_modules = get_num_modules("../materials/master_modules.db");
    Level *levels = read_levels_table("../materials/master_levels.db");
    int num_levels = get_num_levels("../materials/master_levels.db");
    Status_Event *status_events = read_status_events_table("../materials/master_status_events.db");
    int num_status_events = get_num_status_events("../materials/master_status_events.db");
    int table, num_records, operation;
    char name[MAX_NAME_LENGTH];
    int id, memory_level, num_ids, flag, module_id, new_status, cell_number, security_flag, num_cell;
    char date[11], time[9];
    char ids[10];

    // Control menu loop
    do {
        // Print menu options
        print_menu_interface();
        scanf("%d", &operation);

        // Handle user input
        switch (operation) {
            case 1:  // SELECT
                print_operation_interface();
                scanf("%d", &table);
                printf(
                    "Insert the number of records or leave empty to output all of "
                    "them: ");
                scanf("%d", &num_records);
                switch (table) {
                    case 1:  // Modules
                        if (num_records == 0) {
                            print_modules(modules, num_modules);
                        } else {
                            print_modules(modules, num_records);
                        }
                        break;
                    case 2:  // Levels
                        if (num_records == 0) {
                            print_levels(levels, num_levels);
                        } else {
                            print_levels(levels, num_records);
                        }
                        break;
                    case 3:  // Status events
                        if (num_records == 0) {
                            print_status_event(status_events, num_status_events);
                        } else {
                            print_status_event(status_events, num_records);
                        }
                        break;
                    default:
                        printf("Invalid table selection.\n");
                        break;
                }
                break;

            case 2:  // INSERT
                print_operation_interface();
                scanf("%d", &table);
                switch (table) {
                    case 1:  // Modules
                        printf("Enter module name: ");
                        scanf("%29s", name);
                        printf("Enter memory level: ");
                        scanf("%d", &memory_level);
                        printf("Enter cell number: ");
                        scanf("%d", &cell_number);
                        printf("Enter security flag: ");
                        scanf("%d", &security_flag);
                        insert_module(modules, num_modules, name, memory_level, cell_number);
                        printf("Module added successfully!\n");
                        break;
                    case 2:  // Levels
                        printf("Enter memory level: ");
                        scanf("%d", &memory_level);
                        printf("Enter cell number: ");
                        scanf("%d", &num_cell);
                        insert_levels(levels, num_levels, memory_level, num_cell);
                        printf("Level added successfully!\n");
                        break;
                    case 3:  // Status events
                        printf("Enter module ID: ");
                        scanf("%d", &module_id);
                        printf("Enter new status: ");
                        scanf("%d", &new_status);
                        printf("Enter date (dd.mm.yyyy): ");
                        scanf("%10s", date);
                        printf("Enter time (hh:mm:ss): ");
                        scanf("%8s", time);
                        insert_status_event(status_events, num_status_events, module_id, new_status, date,
                                            time);
                        printf("Status event added successfully!\n");
                        break;
                    default:
                        printf("Invalid table selection.\n");
                }
                break;
            case 3:  // UPDATE
                print_operation_interface();
                scanf("%d", &table);
                switch (table) {
                    case 1:  // Modules
                        printf("Please enter the ID of the module to update: ");
                        scanf("%d", &id);
                        printf("Please enter the new name of the module: ");
                        scanf("%29s", name);
                        printf("Please enter the new memory level of the module: ");
                        scanf("%d", &memory_level);
                        printf("Please enter the new cell number of the module: ");
                        scanf("%d", &cell_number);
                        update_module(modules, num_modules, id, name, memory_level, cell_number);
                        printf("Module updated successfully!\n");
                        break;
                    case 2:  // Levels
                        printf("Please enter the number of the level to update: ");
                        scanf("%d", &memory_level);
                        printf("Please enter the new number of cells for the level: ");
                        scanf("%d", &num_cell);
                        update_level(levels, num_levels, memory_level, num_cell);
                        printf("Level updated successfully!\n");
                        break;
                    case 3:  // Status events
                        printf("Please enter the ID of the status event to update: ");
                        scanf("%d", &id);
                        printf("Please enter the new module ID: ");
                        scanf("%d", &module_id);
                        printf("Please enter the new status: ");
                        scanf("%d", &new_status);
                        printf("Please enter the new date (dd.mm.yyyy): ");
                        scanf("%10s", date);
                        printf("Please enter the new time (hh:mm:ss): ");
                        scanf("%8s", time);
                        update_status_event(status_events, num_status_events, id, module_id, new_status, date,
                                            time);
                        printf("Status event updated successfully!\n");
                        break;
                    default:
                        printf("Invalid table selection.\n");
                }
                break;
            case 4:  // DELETE
                print_operation_interface();
                scanf("%d", &table);
                switch (table) {
                    case 1:  // Modules
                        printf("Enter the ID of the module to delete: ");
                        scanf("%d", &id);
                        delete_module(modules, num_modules, id);
                        printf("Module with ID %d has been deleted.\n", id);
                        break;
                    case 2:  // Levels
                        printf("Enter the memory level to delete: ");
                        scanf("%d", &memory_level);
                        delete_level(levels, num_levels, memory_level);
                        printf("Level %d has been deleted.\n", memory_level);
                        break;
                    case 3:  // Status events
                        printf("Enter the ID of the status event to delete: ");
                        scanf("%d", &id);
                        delete_status_event(status_events, num_status_events, id);
                        printf("Status event with ID %d has been deleted.\n", id);
                        break;
                    default:
                        printf("Invalid table selection.\n");
                }
                break;
            case 5:  // Get all active additional modules
                select_active_modules(modules, num_modules);
                break;
            case 6:  // Delete modules by ids

                printf("Please enter IDs of modules to delete (comma separated): ");
                fgets(ids, 10, stdin);
                printf("Please enter count your IDs:");
                scanf("%d", &num_ids);
                // ids = strtok(ids, &num_ids);
                delete_modules_by_ids(modules, num_modules, ids, num_ids);
                // free(ids);
                break;
            case 7:  // Set protected mode for module by id
                printf("Please enter module ID: ");
                scanf("%d", &module_id);
                set_module_protected_mode_by_id(modules, num_modules, module_id);
                break;
            case 8:  // Move module by id to specified memory level and cell
                printf("Please enter module ID: ");
                scanf("%d", &module_id);
                printf("Please enter new memory level: ");
                scanf("%d", &memory_level);
                printf("Please enter new cell number: ");
                scanf("%d", &cell_number);
                move_module_by_id(modules, num_modules, module_id, memory_level, cell_number);
                break;
            case 9:  // Set protection flag of the specified memory level
                printf("Please enter protection flag: ");
                scanf("%d", &flag);
                printf("Please enter memory level number: ");
                scanf("%d", &memory_level);
                set_protection_flag(levels, num_levels, memory_level, flag);
                break;
            case 10:  // Binary searching
                print_operation_interface();
                scanf("%d", &table);
                switch (table) {
                    case 1:  // Modules
                        printf("Please enter ID: ");
                        scanf("%d", &id);
                        if (get_row_by_id("modules", "id", id, &modules)) {
                            printf("Module %d: %s\n", modules->id, modules->name);
                        } else {
                            printf("Module with id %d not found\n", id);
                        }
                        break;
                    case 2:  // Levels
                        printf("Please enter ID: ");
                        scanf("%d", &id);
                        if (get_row_by_id("levels", "num_cells", id, &levels)) {
                            printf("Level %d\n", levels->num_cells);
                        } else {
                            printf("Level with id %d not found\n", id);
                        }
                        break;
                    case 3:  // Status events
                        printf("Please enter ID: ");
                        scanf("%d", &id);
                        if (get_row_by_id("status_events", "id", id, &status_events)) {
                            printf("Status Event %d: %d\n", status_events->id, status_events->module_id);
                        } else {
                            printf("Status Event with id %d not found\n", id);
                        }
                        break;
                    default:
                        printf("Invalid table selection.\n");
                }
                break;
            default:
                printf("Invalid operation selection.\n");
        }
    } while (operation <= 10);
}

int main() {
    interface();
    return 0;
}