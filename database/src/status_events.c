#include "status_events.h"

Status_Event *read_status_events_table(char *filename) {
    // Get the number of records in the file
    int num_records = get_num_status_events(filename);
    // Allocate memory for the array of records
    Status_Event *status_events = (Status_Event *)malloc(num_records * sizeof(Status_Event));
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

void print_status_event(Status_Event status_event[], int num_status_event) {
    printf("Event ID\tstatus_events ID\tNew Status\tDate\t\tTime\n");
    for (int i = 0; i < num_status_event; i++) {
        printf("%d\t\t%d\t\t\t%d\t\t%s\t%s\n", status_event[i].id, status_event[i].module_id,
               status_event[i].new_status, status_event[i].date, status_event[i].time);
    }
}

void insert_status_event(Status_Event *status_events, int num_status_events, int module_id, int new_status,
                         char *date, char *time) {
    int id = num_status_events + 1;  // Generate new ID
    // Find first available index
    int index = -1;
    for (int i = 0; i < num_status_events; i++) {
        if (status_events[i].new_status == 1) {
            index = i;
            break;
        }
    }
    if (index == -1) {  // No available index, append to the end
        index = num_status_events;
    }
    // Set status_event values
    status_events[index].id = id;
    status_events[index].module_id = module_id;
    status_events[index].new_status = new_status;
    strncpy(status_events[index].date, date, 11);
    strncpy(status_events[index].time, time, 9);
}

void update_status_event(Status_Event *status_events, int num_status_events, int id, int module_id,
                         int new_status, char *date, char *time) {
    for (int i = 0; i < num_status_events; i++) {
        if (status_events[i].id == id) {
            status_events[i].module_id = module_id;
            status_events[i].new_status = new_status;
            strncpy(status_events[i].date, date, 11);
            strncpy(status_events[i].time, time, 9);
            break;
        }
    }
}

void delete_status_event(Status_Event *status_events, int num_status_events, int id) {
    for (int i = 0; i < num_status_events; i++) {
        if (status_events[i].id == id) {
            status_events[i].new_status = 0;
            break;
        }
    }
}