#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> // for DIR

#define MAX_FILENAME_LENGTH 1000

#define MAX_STRING_LENGTH 10000

// Read file function
int read_file(char* filename) {
  char* buffer = NULL;
  long length;  // long for f- functions

  /*
  Режим rb открывает файл только для чтения,
  в бинарном режиме,
  и предполагает, что файл уже существует.
  Если файла нет или не удается открыть файл
  для чтения, fopen() вернет NULL.
  */
  FILE* f = fopen(filename, "rb");
  if (f) {
    fseek(f, 0, SEEK_END);  // устанавливает указатель на конец файла.
    length = ftell(f);  // получает текущую позицию указателя в файле, которая
                        // соответствует размеру файла в байтах.
    fseek(f, 0, SEEK_SET);  //  возвращает указатель на начало файла.
    buffer =
        malloc(length + 1);  // выделяет в динамической памяти буфер размером,
                             // достаточным для хранения содержимого файла.

    if (buffer) {
      fread(buffer, 1, length, f);  // читает содержимое файла в буфер
      buffer[length] = '\0';
      printf("%s\n", buffer);
      free(buffer);
    }
    fclose(f);
    return 0;
  } else {
    printf("n/a\n");
    return -1;
  }
}

int write_file(char* filename, char* str) {
  FILE* f = fopen(filename, "a");  // a - режим добавления
  if (f) {
    fprintf(f, "%s\n", str);  // дописывает str в конце файла
    fclose(f);
    return 0;
  } else {
    printf("n/a\n");
    return -1;
  }
}

/* Эта функция принимает в качестве параметров путь к каталогу, имя файла и
размер сдвига и шифрует содержимое указанного файла шифром Цезаря с заданным
сдвигом.
*/
void encrypt_file(const char* directory_path, const char* file_name, int shift) {
  char file_path[MAX_FILENAME_LENGTH];
  sprintf(file_path, "%s/%s", directory_path, file_name);

  // Открывает файл для чтения и записи
  FILE* file = fopen(file_path, "r+");

  if (file) {

    // Чек длины файла
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // выделение достаточного количества ячеек памяти
    char* buffer = malloc(length + 1);
    if (buffer) {

      // чтение и запись в буфер
      fread(buffer, 1, length, file);
      buffer[length] = '\0'; // предотвращение безграничного чтения

      // Шифр цезаря
      for (int i = 0; buffer[i] != '\0'; i++) {
        char c = buffer[i];
        if (c >= 'a' && c <= 'z') {
          c = 'a' + ((c - 'a' + shift) % 26); // 
        } else if (c >= 'A' && c <= 'Z') {
          c = 'A' + ((c - 'A' + shift) % 26); // 
        }
        buffer[i] = c;
      }

      // запись шифровки в буфер
      fseek(file, 0, SEEK_SET);
      fwrite(buffer, 1, length, file);
      free(buffer);
    }
    fclose(file);
  }
}

/*
Функция принимает два аргумента, путь к каталогу и имя файла, который нужно очистить. 
Сначала функция создает полный путь к файлу, объединяя путь к каталогу и имя файла с помощью функции sprintf. 
Затем он открывает файл в режиме записи, fopen с флагом «w», которая обрезает файл 
до нулевой длины, если он существует, или создает новый пустой файл, если он не существует. 
Если файл успешно открыт, функция немедленно закрывает его с помощью функции fclose. 
Это приводит к очистке файла, поскольку любое существующее содержимое в файле будет удалено 
при закрытии файла. Таким образом, функция clear_file очищает содержимое файла, 
открывая его в режиме записи, который усекает файл до нулевой длины, а затем сразу же закрывает его.
*/
void clear_file(const char* directory_path, const char* file_name) {
  char file_path[MAX_FILENAME_LENGTH];
  sprintf(file_path, "%s/%s", directory_path, file_name);
  FILE* file = fopen(file_path, "w");
  if (file) {
    fclose(file);
  }
}

/*
Эта функция обрабатывает все файлы в каталоге, вызывая две другие функции — encrypt_file и clear_file.
Функция принимает два аргумента — путь каталога для обработки и значение сдвига для шифрования. 
Он начинается с открытия каталога с помощью opendir и проверки его успешного открытия. 
Если каталог не может быть открыт, выводится сообщение об ошибке. Затем функция считывает каждую запись 
в каталоге, используя readdir, пока не обработает все файлы в каталоге. Для каждого файла он создает полный путь, 
объединяя путь к каталогу и имя файла, и открывает файл для чтения с помощью fopen. 
Если файл можно открыть, он закрывается, а его имя проверяется, чтобы увидеть, заканчивается ли оно расширением .t. 
Если расширение присутствует, файл шифруется с помощью encrypt_file, а затем очищается с помощью clear_file. 
После того, как все файлы в каталоге обработаны, каталог закрывается с помощью closedir.
*/
void process_files(const char* directory_path, int shift) {
  DIR* directory = opendir(directory_path);
  if (!directory) {
    printf("n/a dir %s\n", directory_path);
    return;
  }

  struct dirent* entry;
  while ((entry = readdir(directory)) != NULL) {
    char file_path[MAX_FILENAME_LENGTH];
    sprintf(file_path, "%s/%s", directory_path, entry->d_name);

    FILE* file = fopen(file_path, "r");
    if (file) {
      fclose(file);
      char* file_name = entry->d_name;
      size_t file_name_length = strlen(file_name);

      if (file_name_length >= 2 && file_name[file_name_length - 2] == '.' &&
          file_name[file_name_length - 1] ==
              't') {  // if file name ends with ".t"
                        encrypt_file(directory_path, file_name, shift);
                        clear_file(directory_path, file_name);
        }
    }
  }
  closedir(directory);
}

void menu() {
  int input = 0;
  char file_path[MAX_FILENAME_LENGTH];
  int shift = 0;

  while (input != -1) {

    scanf("%d", &input);

    switch (input) {
      case 1:
        scanf("%s", file_path);
        read_file(file_path);
        printf("\n");
        break;
      case 2:
        scanf("%s", file_path);
        append_file(file_path);
        printf("\n");
        break;
      case 3:
        // printf("Enter directory path:\n");
        scanf("%s", file_path);
        // printf("Enter Caesar cipher shift:\n");
        scanf("%d", &shift);
        encrypt_files(file_path, shift);
        printf("\n");
        break;
      case -1:
        break;
      default:
        printf("n/a\n\n");
        break;
    }
  }
}

int main() {
  menu();
  return 0;
}
