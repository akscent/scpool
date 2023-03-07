#ifndef STATUS_EVENT_FILE_H
#define STATUS_EVENT_FILE_H

#include "shared.h"

Status_Event *read_status_events_table(char *filename);
int get_num_status_events(char *filename);
void print_status_event(Status_Event *status_event, int num_status_event);
void insert_status_event(Status_Event *status_events, int num_status_events, int module_id, int new_status,
                         char *date, char *time);
void update_status_event(Status_Event *status_events, int num_status_events, int id, int module_id,
                         int new_status, char *date, char *time);
void delete_status_event(Status_Event *status_events, int num_status_events, int id);

#endif /* STATUS_EVENT_FILE_H */