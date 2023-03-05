#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
Функция принимает в качестве аргумента имя файла, открывает файл в режиме "добавления" ("a") 
и возвращает указатель на структуру FILE, представляющую открытый файл. Если функция fopen 
не может открыть файл (возвращает NULL), сообщение об ошибке «n/a открытие файла» 
Таким образом, эта функция открывает файл журнала в режиме добавления и возвращает указатель 
на открытый файл или завершает работу программы с сообщением об ошибке, если файл не может быть открыт.
*/
FILE* log_init(char *filename) {
    FILE* log_file = fopen(filename, "a");
    if (log_file == NULL) {
        printf("n/a opening file\n");
        exit(1);
    }
    return log_file;
}

/*
Функция содержит: message: переменная char*, сообщение журнала, которое будет записано в файл журнала. 
level: Переменная перечисления, представляющая уровень серьезности сообщения журнала. 
Сначала функция определяет строковое представление уровня журнала на основе параметра уровня с помощью оператора switch. 
Затем он извлекает текущее время и форматирует его в строку с помощью функции strftime. 
Затем функция записывает сообщение журнала в файл журнала в формате «[отметка времени] уровень: сообщение», 
где отметка времени — это отформатированная строка времени, уровень — строковое представление уровня журнала, 
а сообщение — входной параметр сообщения. Затем функция сбрасывает поток вывода, чтобы гарантировать, 
что сообщение журнала будет немедленно записано в файл. Наконец, функция возвращает количество байтов, записанных в файл.
*/
int logcat(FILE* log_file, char *filename, char *message, log_level level) {
    char *level_str;
    switch(level) {
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
        printf("n/a log file.\n");
        exit(1);
    }
    return status;
}
