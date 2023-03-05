#include <stdio.h>
#include <string.h>

#define MAX_PATH_LENGTH 256
#define MAX_DATE_LENGTH 11

struct DoorState {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int code;
};

// Функция для чтения бинарных файлов
int read_record(FILE* file, struct DoorState* state) {
    return fread(state, sizeof(struct DoorState), 1, file);
}

// функция для конвертации строки в элементы
void parse_date(int* year, int* month, int* day, const char* date_str) {
    sscanf(date_str, "%d.%d.%d", day, month, year);
    printf("%d %d %d\n", *day, *month, *year);
}

// функция для сравнения дат
int compare_dates(int year1, int month1, int day1, int year2, int month2, int day2) {
    if (year1 < year2) return -1;
    if (year1 > year2) return 1;
    if (month1 < month2) return -1;
    if (month1 > month2) return 1;
    if (day1 < day2) return -1;
    if (day1 > day2) return 1;
    return 0;
}

// Функция для преобразования пути к файлу в относительный путь
void get_parent_directory(const char* file_path, char* parent_path) {
    strcpy(parent_path, "../");
    strcat(parent_path, file_path);
}

// Поиск даты в файле - можно вынести в отдельную функцию
int main() {
    char path[MAX_PATH_LENGTH];
    scanf("%255s", path);
    const char* file_path = path;
    char parent_path[MAX_PATH_LENGTH];
    get_parent_directory(file_path, parent_path);
    FILE* fp = fopen(parent_path, "rb");
    if (!fp) {
        printf("Could not open file.\n");
        return 2;
    }
    char date_str[MAX_DATE_LENGTH];
    scanf("%10s", date_str);
    int search_year, search_month, search_day;
    parse_date(&search_year, &search_month, &search_day, date_str);
    struct DoorState state;
    while (read_record(fp, &state)) {
        if (compare_dates(state.year, state.month, state.day, search_year, search_month, search_day) == 0) {
            printf("%d\n", state.code);
            fclose(fp);
            return 0;
        }
    }
    printf("n/a\n");
    fclose(fp);
    return 3;
}


// int search_by_date(const char* file_path, int search_year, int search_month, int search_day) {
//     char parent_path[MAX_PATH_LENGTH];
//     get_parent_directory(file_path, parent_path);
//     FILE* fp = fopen(parent_path, "rb");
//     if (!fp) {
//         printf("Could not open file.\n");
//         return 2;
//     }
//     struct DoorState state;
//     while (read_record(fp, &state)) {
//         if (compare_dates(state.year, state.month, state.day, search_year, search_month, search_day) == 0) {
//             printf("%d\n", state.code);
//             fclose(fp);
//             return 0;
//         }
//     }
//     printf("n/a\n");
//     fclose(fp);
//     return 3;
// }


// int main() {
//     char path[MAX_PATH_LENGTH];
//     scanf("%255s", path);
//     const char* file_path = path;
//     char date_str[MAX_DATE_LENGTH];
//     scanf("%10s", date_str);
//     int search_year, search_month, search_day;
//     parse_date(&search_year, &search_month, &search_day, date_str);
//     return search_by_date(file_path, search_year, search_month, search_day);
// }
