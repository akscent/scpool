/*------------------------------------
        Здравствуй, человек!
        Чтобы получить ключ
        поработай с комментариями.
-------------------------------------*/

#include <stdio.h>

void input(int *buffer, int *length, int *char_exis);
void output(int sum, int *buffer, int length);
int sum_numbers(int *buffer, int length);
int find_numbers(int *buffer, int length, int *numbers);

/*------------------------------------
        Функция получает массив данных
        через stdin.
        Выдает в stdout особую сумму
        и сформированный массив
        специальных элементов
        (выбранных с помощью найденной суммы):
        это и будет частью ключа
-------------------------------------*/

int main() {
    int buffer[10], length;
    int char_exist = 0;
    input(buffer, &length, &char_exist);
    if (char_exist != 0) {
        printf("n/a");
        return 0;
    }

    // такого случая наверное вообще не может быть
    if (length > 10 || sizeof(buffer) / sizeof(buffer[0]) != length) {
        printf("n/a");
        return 0;
    }
    int sum = sum_numbers(buffer, length);
    if (sum == 0) {
        printf("n/a");
        return 0;
    }
    int numbers[10];
    int count = find_numbers(buffer, length, numbers);
    if (count == 0) {
        printf("n/a");
        return 0;
    }
    output(sum, numbers, count);
    return 0;
}

/*------------------------------------
        Функция должна находить
        сумму четных элементов
        с 0-й позиции.
-------------------------------------*/

int sum_numbers(int *buffer, int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] % 2 == 0) {
            sum += buffer[i];
        }
    }
    return sum;
}

/*------------------------------------
        Функция должна находить
        все элементы, на которые нацело
        делится переданное число и
        записывает их в выходной массив.
-------------------------------------*/

int find_numbers(int *buffer, int length, int *numbers) {
    int sum = sum_numbers(buffer, length);
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] != 0 && sum % (buffer[i]) == 0) {
            numbers[count] = buffer[i];
            count++;
        }
    }

    return count;
}

void input(int *buffer, int *length, int *char_exist) {
    scanf("%d", length);
    int count = 0;
    char c;
    while (count < length[0]) {
        scanf("%d", &buffer[count]);
        count++;
        if (count == length[0]) {
            if (scanf("%c", &c) != EOF && c != '\n') {
                *char_exist = 1;
            }
        }
    }
}

void output(int sum, int *buffer, int length) {
    printf("%d\n", sum);
    for (int i = 0; i < length; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}