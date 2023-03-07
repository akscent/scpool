#include <stdio.h>

// identification length
#define LEN 100 

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);

int main() {
    int num1[LEN], num2[LEN], sum_result[LEN + 1], sub_result[LEN], sum_length, sub_length;

    // read the first numbers
    int i = 0, c;
    int prev_was_digit = 0; // keep tracker of previous character that was a digit

    // a loop for reading the first row while we do not have end \n
    while ((c = getchar()) != '\n' && i < LEN) {
        if (c == ' ') {
            prev_was_digit = 0; // reset flag when space is found
            continue;  // skip spaces
        }
        if (c < '0') {
            printf("n/a\n");
            return 1;
        }
        if (prev_was_digit) {
            printf("n/a\n"); // if a digit follows a digit with no space in between
            return 1;
        }
        num1[i++] = c - '0'; // make number from ASCII and writing in i and than i++
        prev_was_digit = 1; // set the flag to indicate that the current character is a digit
    }
    int num1_length = i;
    i = 0;
    prev_was_digit = 0;
    while ((c = getchar()) != '\n' && i < LEN) {
        if (c == ' ') {
            prev_was_digit = 0;
            continue;
        }
        if (c < '0') {
            printf("n/a\n");
            return 1;
        }
        if (prev_was_digit) {
            printf("n/a\n");
            return 1;
        }
        num2[i++] = c - '0';
        prev_was_digit = 1;
    }
    int num2_length = i;

    sum(num1, num1_length, num2, num2_length, sum_result, &sum_length);
    sub(num1, num1_length, num2, num2_length, sub_result, &sub_length);

    // loops for print results
    for (int i = 0; i < sum_length; i++) {
        printf("%d ", sum_result[i]);
    }
    printf("\n");

    // if sub_result return negative, it means the subtraction result is negative
    if (sub_result[0] == -1) {
        printf("n/a\n");
    } else {
        for (int i = 0; i < sub_length; i++) {
            printf("%d ", sub_result[i]);
        }
    }
    return 0;
}





void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length)
{
    // initialize the result array
    int carry = 0;
    // то есть если длина первого массива больше длины второго массива, мы записываем в переменную результирующая длина длину 1 и наоборот
    *result_length = len1 > len2 ? len1 : len2;
    for (int i = 0; i < *result_length; i++) {
        // в д1 записываем элементы масисва1, начиная с последнего, если длина больше и, тогда записываем нули
        int d1 = i < len1 ? buff1[len1 - i - 1] : 0;
        // в д2 записываем элементы массива2 с тем же условием 
        int d2 = i < len2 ? buff2[len2 - i - 1] : 0;
        // сумма этих двух чисел
        int sum = d1 + d2 + carry;
        // например 17 на 10 = 1,7
        carry = sum / 10;
        // записываем в массив по индексу с конца остаток от деления, например 7
        result[*result_length - i - 1] = sum % 10;
        // и так в ходе цикла записываем весь массив с конца, получается сложение в столбик
        // поскольку кэрри = 1,7 на следущей итерации он прибавляется в сумму в таком виде
        // таким образом единица переносится по рангу вверх
    }
    
    // если кэрри в конечном счете остается больше 0, то есть хранит в себе остаток верхних единиц
    if (carry > 0) {
        result[*result_length] = carry;
        // тогда мы добавляем этот остаток как новый разряд в массив
        (*result_length)++;
    }
        // далее удаляем возможно оставшиеся нули в начале массива
        // пока длина массива больше одного и начальный элемент массива равен нулю переписываем массив и отнимаем 1 от его длинны
        // выполняем цикл замены чисел в предшествующем индексе числом в последующем индексе
    while (*result_length > 1 && result[0] == 0) {
        for (int i = 0; i < *result_length - 1; i++) {
            result[i] = result[i + 1];
        }
    (*result_length)--;
    }
}

void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    // check if buff2 is greater than buff1
    if (len2 > len1 || (len2 == len1 && buff2[0] > buff1[0])) { // если первый элемент массива2 больше, чем массива1, разность не взять
        result[0] = -1; // special value indicating "n/a"
        *result_length = 1;
        return;
    }

    // initialize the result array
    int borrow = 0;
    *result_length = len1; // длина первого массива, т.к. она всегда больше
    for (int i = 0; i < *result_length; i++) {
        int d1 = buff1[len1 - i - 1];
        int d2 = i < len2 ? buff2[len2 - i - 1] : 0;
        int diff = d1 - d2 - borrow;
        if (diff < 0) {
            diff +=10;
            borrow = 1;
        } else {
            borrow = 0;
        }
    result[*result_length - i - 1] = diff;
    }

    // remove leading zeros
    while (*result_length > 1 && result[0] == 0) {
        for (int i = 0; i < *result_length - 1; i++) {
            result[i] = result[i + 1];
        }
    (*result_length)--;
    }
}