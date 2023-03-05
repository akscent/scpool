#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

struct DoorStateNode {
    struct DoorState* state;
    struct DoorStateNode* next;
};

void read_record(FILE* fp, struct DoorState* state) {
  fread(state, sizeof(struct DoorState), 1, fp);
}

void write_record(FILE* fp, struct DoorState* state) {
  fwrite(state, sizeof(struct DoorState), 1, fp);
}

/*
Данная функция используется для сравнения двух элементов типа struct DoorState, 
которые представляют собой записи состояния двери. Функция сравнивает элементы 
по полю времени (год, месяц, день, час, минута, секунда) и возвращает результат сравнения в виде целого числа.
*/
int compare_records(const void* a, const void* b) {
  const struct DoorState* state1 = (const struct DoorState*)a;
  const struct DoorState* state2 = (const struct DoorState*)b;
  int result = state1->year - state2->year;
  if (result != 0) return result;
  result = state1->month - state2->month;
  if (result != 0) return result;
  result = state1->day - state2->day;
  if (result != 0) return result;
  result = state1->hour - state2->hour;
  if (result != 0) return result;
  result = state1->minute - state2->minute;
  if (result != 0) return result;
  result = state1->second - state2->second;
  return result;
}

// void sort_records(const char* file_path) {
//   FILE* fp = fopen(file_path, "r+b");
//   if (!fp) {
//     printf("n/a\n");
//     return;
//   }
//   struct DoorState state;
//   size_t num_records = 0;
//   while (!feof(fp)) {
//     read_record(fp, &state);
//     if (!feof(fp)) {
//       num_records++;
//     }
//   }
//   if (num_records == 0) {
//     printf("n/a\n");
//     fclose(fp);
//     return;
//   }
//   struct DoorState* records =
//       (struct DoorState*)malloc(num_records * sizeof(struct DoorState));
//   rewind(fp);
//   for (size_t i = 0; i < num_records; i++) {
//     read_record(fp, &records[i]);
//   }
//   qsort(records, num_records, sizeof(struct DoorState), compare_records);
//   fclose(fp);
//   fp = fopen(file_path, "w+b");
//   for (size_t i = 0; i < num_records; i++) {
//     write_record(fp, &records[i]);
//   }
//   fclose(fp);
//   free(records);
// }

// void add_record(const char* file_path) {
//   FILE* fp = fopen(file_path, "a+b");
//   if (!fp) {
//     printf("n/a\n");
//     return;
//   }
//   struct DoorState state;
//   printf("Enter year: ");
//   scanf("%d", &state.year);
//   printf("Enter month: ");
//   scanf("%d", &state.month);
//   printf("Enter day: ");
//   scanf("%d", &state.day);
//   printf("Enter hour: ");
//   scanf("%d", &state.hour);
//   printf("Enter minute: ");
//   scanf("%d", &state.minute);
//   printf("Enter second: ");
//   scanf("%d", &state.second);
//   printf("Enter status (0 or 1): ");
//   scanf("%d", &state.status);
//   printf("Enter code: ");
//   scanf("%d", &state.code);
//   write_record(fp, &state);
//   fclose(fp);
//   sort_records(file_path);
//   printf("Sorted file contents:\n");
//   print_records(file_path);
// }

/*
Функция, которая печатает строку
*/
void print_record(const struct DoorState* state) {
  printf("%04d %d %d %d %d %d %d %d\n", state->year, state->month,
         state->day, state->hour, state->minute, state->second, state->status,
         state->code);
}

/*
Функция для преобразования пути к файлу в путь через родительскую директорию для текущего файла
*/
void get_parent_directory(const char* file_path, char* parent_path) {
  strcpy(parent_path, "../");
  strcat(parent_path, file_path);
}

/*
Функция выводит содержимое файла, который содержит записи датах. 
Она начинается с вызова функции get_parent_directory, которая извлекает путь к родительской директории, 
в которой находится файл. Затем функция пытается открыть файл с помощью функции fopen, 
используя бинарный режим чтения "rb". Если файл не удается открыть, 
функция выводит сообщение "n/a not open" и завершает работу. Если файл открыт успешно, 
функция считывает записи из файла с помощью цикла while и функции read_record, 
затем выводит каждую запись с помощью функции print_record. 
Функция также подсчитывает количество записей и выводит сообщение "n/a num rec" в случае, 
если в файле не найдено ни одной записи. После завершения работы с файлом, функция закрывает его с помощью функции fclose.
*/
void print_records(const char* file_path) {
    char parent_path[256];
get_parent_directory(file_path, parent_path);
printf("%s\n", parent_path);
FILE* fp = fopen(parent_path, "rb");
  if (!fp) {
    printf("n/a not open\n");
    return;
  }
  struct DoorState state;
  size_t num_records = 0;
  while (!feof(fp)) {
    read_record(fp, &state);
    if (!feof(fp)) {
      print_record(&state);
      num_records++;
    }
  }
  if (num_records == 0) {
    printf("n/a num rec\n");
  }
  fclose(fp);
}

/*
Функция считывает записи из бинарного файла, сортирует их по отметкам даты и времени, 
а затем записывает отсортированные записи обратно в тот же файл. 
Сначала функция получает путь к родительскому каталогу файла с помощью функции get_parent_directory. 
Затем она открывает файл в бинарном режиме чтения-записи с помощью fopen. 
Функция считывает записи из файла в связанный список, где каждый узел списка содержит одну запись DoorState. 
Записи сортируются с помощью функции compare_records, которая сравнивает две записи на основе их меток даты и времени. 
После создания и сортировки связанного списка функция записывает записи обратно в файл в отсортированном порядке, 
используя функцию write_record. Наконец, функция закрывает файл и освобождает память, используемую связанным списком. 
Однако в этой функции есть баг: при выделении памяти для нового узла в связанном списке она выделяет память только для 
самого узла, но не для записи DoorState, которую он будет хранить. 
Это приводит к неопределенному поведению при попытке скопировать данные состояния в неинициализированную память. 
Чтобы это исправить, функция также должна выделять память для записи DoorState с помощью malloc.
*/
void sort_records(const char* file_path) {
    char parent_path[256];
    get_parent_directory(file_path, parent_path);
    FILE* fp = fopen(parent_path, "r+b");
    if (!fp) {
        printf("File not found.\n");
        return;
    }
    struct DoorState state;
    size_t num_records = 0;
    while (fread(&state, sizeof(struct DoorState), 1, fp) == 1) {
        num_records++;
    }
    if (num_records == 0) {
        printf("No records found in file.\n");
        fclose(fp);
        return;
    }
    rewind(fp);
    // First, read the records into a dynamic array
    struct DoorState* records = (struct DoorState*)malloc(sizeof(struct DoorState) * num_records);
    for (size_t i = 0; i < num_records; i++) {
        fread(&records[i], sizeof(struct DoorState), 1, fp);
    }
    fclose(fp);
    // Then sort the array
    qsort(records, num_records, sizeof(struct DoorState), compare_records);
    // Finally, write the sorted records back to the file
    fp = fopen(parent_path, "w+b");
    if (!fp) {
        printf("Could not open file for writing.\n");
        free(records);
        return;
    }
    for (size_t i = 0; i < num_records; i++) {
        fwrite(&records[i], sizeof(struct DoorState), 1, fp);
    }
    fclose(fp);
    free(records);
}

void add_record(const char* file_path) {
  char parent_path[256];
get_parent_directory(file_path, parent_path);
FILE* fp = fopen(parent_path, "r+b");
  if (!fp) {
    printf("n/a\n");
    return;
  }
  struct DoorState state;
  char c;
  if (scanf("%d %d %d %d %d %d %d %d%c", &state.year, &state.month, &state.day, 
                                        &state.hour, &state.minute, &state.second, &state.status, &state.code, &c) != 9 && c!= '\n') {
        printf("n/a\n");
        return;
    }
  write_record(fp, &state);
  fclose(fp);
}

int main() {
//   if (argc != 2) {
//     printf("Usage: state_sort file_path\n");
//     return 1;
//   }
  char path[64];
  scanf_s("%63s", path, 64);
  const char* file_path = path;
  int choice;
  while (1) {
    // printf("\nMenu:\n");
    // printf("0. Print records\n");
    // printf("1. Sort records\n");
    // printf("2. Add record and sort\n");
    // printf("3. Exit\n");
    // printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
      case 0:
        print_records(file_path);
        break;
      case 1:
        sort_records(file_path);
        print_records(file_path);
        break;
      case 2:
        add_record(file_path);
        sort_records(file_path);
        print_records(file_path);
        break;
      case 3:
        return 0;
      default:
        printf("n/a\n");
        break;
    }
  }
}

