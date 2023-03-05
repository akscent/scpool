#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PATH_LENGTH 56
#define MAX_DATE_LENGTH 11

struct temp {
    int year;
    int mon;
    int day;
};
struct DoorState {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int status;
    int code;
};
void get_parent_directory(const char* file_path, char* parent_path) {
    strcpy(parent_path, "../");
    strcat(parent_path, file_path);
}
// void write_record(FILE* fp, const struct DoorState* state) {
//     fwrite(state, sizeof(struct DoorState), 1, fp);
// }
void read_each_record(FILE* fp, struct DoorState* state) {
    fread(state, sizeof(struct DoorState), 1, fp);
}
// void read_record(FILE* fp, int index, struct DoorState* state) {
//     fread(state, sizeof(struct DoorState), index, fp);
// }
void print_record(const struct DoorState* state) {
    printf("%04d %d %d %d %d %d %d %d\n", state->year, state->month, state->day, state->hour, state->minute,
           state->second, state->status, state->code);
}
void print_records(const char* file_path) {
    char parent_path[256];
    get_parent_directory(file_path, parent_path);
    printf("%s\n", parent_path);
    FILE* fp = fopen(parent_path, "rb");
    if (!fp) {
        printf("n/a\n");
        return;
    }
    struct DoorState state;
    size_t num_records = 0;
    while (!feof(fp)) {
        read_each_record(fp, &state);
        if (!feof(fp)) {
            print_record(&state);
            num_records++;
        }
    }
    if (num_records == 0) {
        printf("n/a\n");
    }
    fclose(fp);
}

// int count_records(FILE* fp) {
//     fseek(fp, 0, SEEK_END);
//     long file_size = ftell(fp);
//     return file_size / (sizeof(time_t) + sizeof(int));
// }

int compare_date(const struct DoorState* state, const struct temp* date) {
    if (state->year < date->year) {
        return -1;
    } else if (state->year > date->year) {
        return 1;
    } else if (state->month < date->mon) {
        return -1;
    } else if (state->month > date->mon) {
        return 1;
    } else if (state->day < date->day) {
        return -1;
    } else if (state->day > date->day) {
        return 1;
    } else {
        return 0;
    }
}
int parse_date(const char* str, struct temp* date) {
    if (sscanf(str, "%d.%d.%d", &date->day, &date->mon, &date->year) != 3) {
        return 0;
    }
    return 1;
}

/*
Функция принимает два необязательных аргумента: префикс и суффикс. 
Их можно использовать для настройки имени временного файла. 
Генерирует временную метку на основе текущего времени, используя функции time и localtime. 
Он создает временную строку пути к файлу, используя sprintf, с заполнителем XXXXXX, 
где функция mkstemp заменит его уникальным идентификатором. 
Далее идет вызов mkstemp для создания фактического временного файла со сгенерированным путем к файлу. 
Он закрывает файловый дескриптор, возвращенный mkstemp, так как нам нужен только путь к файлу. 
Возвращает копию сгенерированной строки пути к файлу с помощью strdup.
*/
// char* tempfile_path(const char* prefix, const char* suffix) {
//     char temp_path[MAX_PATH_LENGTH];
//     char timestamp[20];
//     time_t t = time(NULL);
//     struct tm tm = *localtime(&t);
//     sprintf(timestamp, "%04d%02d%02d%02d%02d%02d", 
//             tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

//     sprintf(temp_path, "%s%s%sXXXXXX%s", 
//             "/tmp/", prefix ? prefix : "", timestamp, suffix ? suffix : "");

//     int fd = mkstemp(temp_path);
//     if (fd == -1) {
//         perror("mkstemp");
//         return NULL;
//     }

//     fclose(fd);

//     return strdup(temp_path);
// }

void clear(const char* file_path, const char* start_date_str, const char* end_date_str) {
    char parent_path[MAX_PATH_LENGTH];
    get_parent_directory(file_path, parent_path);
    printf("%s\n", parent_path);
    FILE* fp = fopen(parent_path, "r+b");
    if (!fp) {
        printf("n/a\n");
        return;
    }
    struct temp start_date, end_date;
    if (!parse_date(start_date_str, &start_date) || !parse_date(end_date_str, &end_date)) {
        printf("n/a\n");
        fclose(fp);
        return;
    }

    // Find the start and end indices
    int start_index = -1;
    int end_index = -1;
    struct DoorState state;
    for (int i = 0; ; i++) {
        if (fread(&state, sizeof(struct DoorState), 1, fp) != 1) {
            break; // end of file
        }
        if (compare_date(&state, &start_date) >= 0) {
            start_index = i;
            break;
        }
    }
    if (start_index == -1) {
        printf("n/a\n");
        fclose(fp);
        return;
    }
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    int num_records = file_size / sizeof(struct DoorState);
    for (int i = num_records - 1; i >= 0; i--) {
        fseek(fp, i * sizeof(struct DoorState), SEEK_SET);
        if (fread(&state, sizeof(struct DoorState), 1, fp) != 1) {
            printf("n/a\n");
            fclose(fp);
            return;
        }
        if (compare_date(&state, &end_date) <= 0) {
            end_index = i;
            break;
        }
    }
    if (end_index == -1) {
        printf("n/a\n");
        fclose(fp);
        return;
    }

    // копирование записей (кроме удаляемых) во временный файл
    FILE* temp_fp = tmpfile();
    for (int i = 0; i < start_index; i++) {
        fseek(fp, i * sizeof(struct DoorState), SEEK_SET);
        if (fread(&state, sizeof(struct DoorState), 1, fp) != 1) {
            printf("n/a\n");
            fclose(fp);
            fclose(temp_fp);
            return;
        }
        if (i >= end_index) {
            fwrite(&state, sizeof(struct DoorState), 1, temp_fp);
        }
    }
    for (int i = end_index + 1; i < num_records; i++) {

        // fseek определяет текущую позицию 
        // i * sizeof(struct DoorState) - смещение в байтах от начала файла, 
        // в котором находится запись с индексом i. 
        // sizeof(struct DoorState) возвращает размер в байтах структуры struct DoorState, 
        // представляющей одну запись в файле.
        fseek(fp, i * sizeof(struct DoorState), SEEK_SET);
        if (fread(&state, sizeof(struct DoorState), 1, fp) != 1) {
            printf("n/a\n");
            fclose(fp);
            fclose(temp_fp);
            return;
        }
        fwrite(&state, sizeof(struct DoorState), 1, temp_fp);
    }

    // Запись временного файла обратно в оригинальный 
    remove(parent_path);
    fseek(temp_fp, 0, SEEK_SET);
    FILE* new_fp = fopen(parent_path, "w+b");
    if (!new_fp) {
        printf("n/a\n");
        fclose(fp);
        fclose(temp_fp);
        return;
    }
    for (;;) {
        if (fread(&state, sizeof(struct DoorState), 1, temp_fp) != 1) {
break; // end of file
}
fwrite(&state, sizeof(struct DoorState), 1, new_fp);
}
// Close all files and remove temporary file
fclose(fp);
fclose(temp_fp);
fclose(new_fp);
}

int main() {
    char path[MAX_PATH_LENGTH];
    scanf("%55s", path);
    const char* file_path = path;
    char start_date_str[MAX_DATE_LENGTH], end_date_str[MAX_DATE_LENGTH];
    scanf("%10s %10s", start_date_str, end_date_str);
    clear(file_path, start_date_str, end_date_str);
    print_records(file_path);
    return 0;
}
