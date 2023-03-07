#include <stdio.h>

int check_player1_pos(int row, int col, int player1_center) {
    if ((row >= player1_center - 1 && row <= player1_center + 1) && col == 3) return 1;
    return 0;
}

int check_player2_pos(int row, int col, int player2_center) {
    if ((row >= player2_center - 1 && row <= player2_center + 1) && col == 76) return 1;
    return 0;
}

void print_row(int row, int ball_x, int ball_y, int player1_center, int player2_center, int player1_score,
               int player2_score) {
    for (int col = 0; col < 80; col++) {
        if ((row == 0 || col == 0 || row == 24 || col == 79) && row < 25) {
            printf("#");
        } else if (col == ball_x && row == ball_y) {
            printf("o");
        } else if (check_player1_pos(row, col, player1_center) ||
                   check_player2_pos(row, col, player2_center)) {
            printf("|");
        } else if (col == 39 && row < 25) {
            printf("|");
        } else if (col == 38 && row == 27) {
            printf(":");
        } else if (row == 27 && col == 34) {
            printf("%d", player1_score);
        } else if (row == 27 && col == 43) {
            printf("%d", player2_score);
        } else {
            printf(" ");
        }
    }
    printf("\n");
}

int check_hor_wall(int row) { return (row == 1 || row == 23) ? 1 : 0; }

int check_ver_wall(int col) { return (col == 1 || col == 78) ? 1 : 0; }

int check_racquet_hit(int ball_x, int ball_y, int player1_center, int player2_center) {
    if ((ball_x == 2 && (ball_y >= player1_center - 1 && ball_y <= player1_center + 1)) ||
        (ball_x == 77 && (ball_y >= player2_center - 1 && ball_y <= player2_center + 1)))
        return 1;
    return 0;
}

void print_map(int player1_center, int player2_center, int ball_x, int ball_y, int player1_score,
               int player2_score) {
    for (int row = 0; row < 28; row++) {
        print_row(row, ball_x, ball_y, player1_center, player2_center, player1_score, player2_score);
    }
}

void run_game(int player1_center, int player2_center, int player1_score, int player2_score) {
    int turn = 0;
    int vector_x = 1, vector_y = 1, ball_x = 39, ball_y = 11;
    char c;
    while (player1_score < 21 && player2_score < 21) {
        print_map(player1_center, player2_center, ball_x, ball_y, player1_score, player2_score);
        if (check_hor_wall(ball_y)) {
            vector_y = (vector_y == 1) ? -1 : 1;
        }

        if (check_ver_wall(ball_x) || check_racquet_hit(ball_x, ball_y, player1_center, player2_center)) {
            vector_x = (vector_x == 1) ? -1 : 1;
        }

        if (ball_x == 1) {
            player2_score = player2_score + 1;
        } else if (ball_x == 78) {
            player1_score = player1_score + 1;
        }

        ball_x += vector_x;
        ball_y -= vector_y;

        scanf("%c", &c);
        if (c == 'a' && player1_center > 2 && turn == 0) {
            player1_center = player1_center - 3;
            turn++;
        } else if (c == 'z' && player1_center < 22 && turn == 0) {
            player1_center = player1_center + 3;
            turn++;
        } else if (c == 'k' && player2_center > 2 && turn == 1) {
            player2_center = player2_center - 3;
            turn--;
        } else if (c == 'm' && player2_center < 22 && turn == 1) {
            player2_center = player2_center + 3;
            turn--;
        } else if (c == ' ') {
            (turn == 0) ? turn++ : turn--;
        } else if (c == (char)27)
            return;
    }

    if (player1_score == 21) {
        printf("Congranulation! Player 1 wins!\n");
    }
    if (player2_score == 21) {
        printf("Congratulation! Player 2 wins!\n");
    }
}

int main() {
    int player1_center = 10, player2_center = 10, player1_score = 0, player2_score = 0;
    run_game(player1_center, player2_center, player1_score, player2_score);
    if (player1_score == 21) {
        printf("Player 1 wins!\n");
    }
    if (player2_score == 21) {
        printf("Player 2 wins!\n");
    }
    return 0;
}
