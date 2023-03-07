

#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ROW 25  // Buffer field height
#define COL 80  // Buffer field width

int **current_array();
int **future_array();
char **display_array();
void free_array(int **cur, int **fut, char **dis);
void buffer(int **cur);
void logic(int **cur, int **fut, int *popul);
void display(int **cur, char **dis, int step);
int files_import(int **cur, int *speed);

int main() {
    int **cur = current_array();
    int **fut = future_array();
    char **dis = display_array();
    int speed = 0, popul = 1, step = 0;
    char space;
    files_import(cur, &speed);
    speed = (500000 / speed);
    struct pollfd fds[1];
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    do {
        display(cur, dis, ++step);
        logic(cur, fut, &popul);
        usleep(speed);
        system("clear");
        int poll_status = poll(fds, 1, 0);
        if (poll_status == -1) {
            printf("Ошибка poll");
            break;
        } else if (poll_status > 0) {
            if (fds[0].revents & POLLIN) {
                char buf[2];
                int n = read(STDIN_FILENO, buf, 2);
                if (n < 0) {
                    printf("Ошибка чтения");
                    break;
                } else if (n > 0) {
                    space = buf[0];
                }
            }
        }
    } while (popul != 0 && space != 'q');
    if (space == 'q') {
        printf("Игра окончена по волеизъявлению игрока");
    } else {
        printf("Игра окончена");
    }
    free_array(cur, fut, dis);
    return 0;
}

int **current_array() {
    int **cur = NULL;
    cur = (int **)calloc(ROW, sizeof(int *));
    for (int i = 0; i < ROW; i++) {
        cur[i] = (int *)calloc(COL, sizeof(int));
    }
    return cur;
}

int **future_array() { return current_array(); }

char **display_array() {
    char **dis = NULL;
    dis = (char **)calloc((ROW - 2), sizeof(char *));
    for (int i = 0; i < ROW - 2; i++) {
        dis[i] = (char *)calloc((COL - 2), sizeof(char));
    }
    return dis;
}

void free_array(int **cur, int **fut, char **dis) {
    for (int i = 0; i < ROW; i++) {
        free(cur[i]);
    }
    free(cur);

    for (int i = 0; i < ROW; i++) {
        free(fut[i]);
    }
    free(fut);

    for (int i = 0; i < ROW - 2; i++) {
        free(dis[i]);
    }
    free(dis);
}

void buffer(int **cur) {
    cur[0][0] = cur[ROW - 2][COL - 2];
    cur[0][COL - 1] = cur[ROW - 2][1];
    cur[ROW - 1][COL - 1] = cur[1][1];
    cur[ROW - 1][0] = cur[1][COL - 2];

    for (int j = 1; j < COL - 1; j++) {
        cur[0][j] = cur[ROW - 2][j];
        cur[ROW - 1][j] = cur[1][j];
    }
    for (int i = 1; i < ROW - 1; i++) {
        cur[i][0] = cur[i][COL - 2];
        cur[i][COL - 1] = cur[i][1];
    }
}

void logic(int **cur, int **fut, int *popul) {
    int count;
    buffer(cur);
    for (int i = 1; i < ROW - 1; i++) {
        for (int j = 1; j < COL - 1; j++) {
            count = cur[i - 1][j - 1] + cur[i - 1][j] + cur[i - 1][j + 1] + cur[i][j - 1] + cur[i][j + 1] +
                    cur[i + 1][j - 1] + cur[i + 1][j] + cur[i + 1][j + 1];
            if (count == 3) {
                fut[i][j] = 1;
            } else if (count == 2) {
                fut[i][j] = cur[i][j];
            } else {
                fut[i][j] = 0;
            }
        }
    }
    *popul = 0;
    for (int i = 0; i < ROW - 2; i++) {
        for (int j = 0; j < COL - 2; j++) {
            if (cur[i][j] > fut[i][j]) {
                *popul += cur[i][j] - fut[i][j];
            } else {
                *popul += fut[i][j] - cur[i][j];
            }
            *popul += fut[i][j] - cur[i][j];
        }
    }
    for (int i = 0; i < ROW - 2; i++) {
        for (int j = 0; j < COL - 2; j++) {
            cur[i][j] = fut[i][j];
        }
    }
}

void display(int **cur, char **dis, int step) {
    printf("Step: %d\n", step);
    for (int i = 0; i < ROW - 2; i++) {
        for (int j = 0; j < COL - 2; j++) {
            if (cur[i + 1][j + 1] == 1) {
                dis[i][j] = '0';
            } else {
                dis[i][j] = ' ';
            }
            printf("%c", dis[i][j]);
        }
        printf("\n");
    }
}

int files_import(int **cur, int *speed) {
    FILE *fp;
    char temp;
    int version, flag_err = 0;
    *speed = 0;
    system("clear");
    printf("Введите коэффициент скорости: \n1. - Медленно <...> 5.  - Быстро\n");
    scanf("%d", speed);
    printf(
        "На выбор у вас есть 5 инициирующих начало игры файла:\n1) Озеро\n2) "
        "Гурман (осцилятор)\n3) Звездный корабль\n4) Паук\n5) Поломанное "
        "ружье Госпера\nВведите номер инициирующего файла: 1 to 5: ");

    if (scanf("%d%c", &version, &temp) != 2 && temp != '\n') {
        flag_err = 1;
    }

    switch (version) {
        case 1:
            if ((fp = fopen("files/lake.txt", "r")) == NULL) {
                flag_err = 1;
            }
            break;
        case 2:
            if ((fp = fopen("files/gourment.txt", "r")) == NULL) {
                flag_err = 1;
            }
            break;
        case 3:
            if ((fp = fopen("files/ship.txt", "r")) == NULL) {
                flag_err = 1;
            }
            break;
        case 4:
            if ((fp = fopen("files/spider.txt", "r")) == NULL) {
                flag_err = 1;
            }
            break;
        case 5:
            if ((fp = fopen("files/gosper.txt", "r")) == NULL) {
                flag_err = 1;
            }
            break;
        default:
            flag_err = 1;
            break;
    }

    if (!flag_err) {
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                char ch = 0;
                if ((ch = fgetc(fp)) == EOF) {
                    flag_err = 1;
                    break;
                }
                if (ch == '\n') {
                    if ((ch = fgetc(fp)) == EOF) {
                        flag_err = 1;
                    }
                    break;
                }
                if (ch == '0') cur[i][j] = 0;
                if (ch == '1') cur[i][j] = 1;
            }
            if (flag_err == 1) break;
        }
        fclose(fp);
    }
    return flag_err;
}