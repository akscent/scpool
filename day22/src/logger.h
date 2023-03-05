#ifndef LOGGER_H
#define LOGGER_H

typedef enum {
    DEBUG,
    INFO,
    WARNING,
    ERROR
} log_level;

FILE* log_init(char *filename);
int logcat(FILE* log_file, char *filename, char *message, log_level level);
int log_close(FILE* log_file);

#endif
