#include "logger.h"

FILE* log_init(char* filename) {
    FILE* log_file = fopen(filename, "a");
    if (log_file == NULL) {
        printf("n/a\n");
        exit(1);
    }
    return log_file;
}

int logcat(FILE* log_file, char* filename, char* message, log_level level) {
    char* level_str;
    switch (level) {
        case DEBUG:
            level_str = "DEBUG";
            break;
        case INFO:
            level_str = "INFO";
            break;
        case WARNING:
            level_str = "WARNING";
            break;
        case ERROR:
            level_str = "ERROR";
            break;
        default:
            level_str = "UNKNOWN";
            break;
    }

    char timestamp[20];
    time_t now = time(NULL);
    strftime(timestamp, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));

    int bytes_written = fprintf(log_file, "[%s] %s: %s (%s)\n", timestamp, level_str, message, filename);
    fflush(log_file);

    return bytes_written;
}

int log_close(FILE* log_file) {
    int status = fclose(log_file);
    if (status != 0) {
        printf("n/a\n");
        exit(1);
    }
    return status;
}