#ifndef ARRAY_FILE_H
#define ARRAY_FILE_H

#include <stdio.h>
#include <string.h>
#include <time.h>

struct DoorState {
    time_t timestamp;
    int is_open;
};

void write_record(FILE* fp, const struct DoorState* state) {
    fwrite(&state->timestamp, sizeof(time_t), 1, fp);
    fwrite(&state->is_open, sizeof(int), 1, fp);
}

void read_record(FILE* fp, int index, struct DoorState* state) {
    fseek(fp, index * (sizeof(time_t) + sizeof(int)), SEEK_SET);
    fread(&state->timestamp, sizeof(time_t), 1, fp);
    fread(&state->is_open, sizeof(int), 1, fp);
}

void read_tmp_record(FILE* fp, struct DoorState* state) {
    fread(&state->timestamp, sizeof(time_t), 1, fp);
    fread(&state->is_open, sizeof(int), 1, fp);
}

size_t count_records(FILE* fp) {
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    return file_size / (sizeof(time_t) + sizeof(int));
}

int compare_date(const struct DoorState* state, const struct tm* date) {
    struct tm* state_date = localtime(&state->timestamp);
    if (state_date->tm_year < date->tm_year) {
        return -1;
    } else if (state_date->tm_year > date->tm_year) {
        return 1;
    } else if (state_date->tm_mon < date->tm_mon) {
        return -1;
    } else if (state_date->tm_mon > date->tm_mon) {
        return 1;
    } else if (state_date->tm_mday < date->tm_mday) {
        return -1;
    } else if (state_date->tm_mday > date->tm_mday) {
        return 1;
    } else {
        return 0;
    }
}

int parse_date(const char* str, struct tm* date) {
    if (sscanf(str, "%d.%d.%d", &date->tm_mday, &date->tm_mon, &date->tm_year) != 3) {
        return 0;
    }
    date->tm_year -= 1900;
    date->tm_mon -= 1;
    date->tm_hour = 0;
    date->tm_min = 0;
    date->tm_sec = 0;
    date->tm_isdst = -1;
    return 1;
}


void get_parent_directory(const char* file_path, char* parent_path) {
  const char* sep = strrchr(file_path, '/');
  if (sep == NULL) {
    sep = strrchr(file_path, '\\');
  }
  if (sep == NULL) {
    strcpy(parent_path, "..");
  } else {
    size_t n = sep - file_path;
    strncpy(parent_path, file_path, n);
    parent_path[n] = '\0';
    strcat(parent_path, "/..");
  }
}

#endif /* ARRAY_FILE_H */
