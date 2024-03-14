#include <stdio.h>
#define MAX_X 25
#define MAX_Y 81

int check_rocket(int i, int j, int x_rocket, int y_rocket){
    //Проверка где находятся ракетки
    int flag = (i == x_rocket && j == y_rocket) || (i == x_rocket + 1 && j == y_rocket) ||
                 (i == x_rocket - 1 && j == y_rocket);
    return flag;
}

void inside_field(int i, int j, int xball, int yball, int x1_rocket, int x2_rocket, int y1_rocket, int y2_rocket){
    //Печаетаем "объекты" внутри поля по координатам
    if (i == xball && j == yball)
        printf("0");
    else if (check_rocket(i, j, x1_rocket, y1_rocket))
        printf("[");
    else if (check_rocket(i, j, x2_rocket, y2_rocket))
        printf("]");  
    else if (j == 41)
        printf("*");
    else {
        printf(" ");
    }
}

void print_all(int i, int j, int xball, int yball, int x1_rocket, int y1_rocket, int x2_rocket,
               int y2_rocket) {
    //Печатаем по координатам все поле
    if (i != 0 && i != MAX_X && j != 0 && j != MAX_Y) {
        inside_field(i, j, xball, yball, x1_rocket, x2_rocket, y1_rocket, y2_rocket);
    } else if (j == 0) {
        printf("|");
    } else if (j == MAX_Y) {
        printf("|\n");
    } else {
        printf("#");
    }
}

void print_field(int xball, int yball, int x1_rocket, int y1_rocket, int x2_rocket, int y2_rocket) {
    for (int i = 0; i <= MAX_X; i++) {
        for (int j = 0; j <= MAX_Y; j++) {
            print_all(i, j, xball, yball, x1_rocket, y1_rocket, x2_rocket, y2_rocket);
        }
    }
}

void show_score(int score1, int score2) {
    //Показывает счет на определенном расстояние
    for (int i = 0; i <= 51; i++) {
        if (i == 0) {
            printf("Первый игрок: %d", score1);
        } else if (i == 51) {
            printf("Второй игрок: %d", score2);
        } else {
            printf(" ");
        }
    }
}

void print_winner(int score1, int score2, int flag) {
    if (flag == 0) {
        printf("Победил первый игрок со счетом %d:%d", score1, score2);
    }
    if (flag == 1) {
        printf("Победил второй игрок со счетом %d:%d", score1, score2);
    }
}

int ball_and_rocket(int xball, int yball, int x_rocket, int y_rocket){
    //
    int flag = 0;
    if((xball == x_rocket && yball == y_rocket - 1) ||
                           (xball == x_rocket + 1 && yball == y_rocket - 1) ||
                           (xball == x_rocket - 1 && yball == y_rocket - 1)){
                            flag = 1;
                           }
    return flag;
}

void redirect_0(int *xball, int *yball, int *check_dir, int *score, int x2_rocket, int y2_rocket){
    if(*xball <= 1){
        *check_dir = 1;
    }
    else if(*yball == MAX_Y - 1){
        *score +=1;
        *yball = 41;
        *xball = 13;
    }
    else if(ball_and_rocket(*xball, *yball, x2_rocket, y2_rocket)){
        *check_dir = 2;
    }
    else{
        *xball-=1;
        *yball+=1;
    }
}

void redirect_1(int *xball, int *yball, int *check_dir, int *score, int x2_rocket, int y2_rocket){
    if(*xball >= MAX_X - 1){
        *check_dir = 0;
    }
    else if(*yball == MAX_Y - 1){
        *score+=1;
        *yball = 41;
        *xball = 13;
    }
    else if(ball_and_rocket(*xball, *yball, x2_rocket, y2_rocket)){
        *check_dir = 3;
    }
    else{
        *xball+=1;
        *yball+=1;
    }
}

void redirect_2(int *xball, int *yball, int *check_dir, int *score, int x1_rocket, int y1_rocket){
    if(*xball <= 1){
        *check_dir = 3;
    }
    else if(*yball == 1){
        *score+=1;
    }
    else if(ball_and_rocket(*xball, *yball, x1_rocket, y1_rocket)){
        *check_dir = 0;
    }
    else{
        *xball-=1;
        *yball-=1;
    }
}

void redirect_3(int *xball, int *yball, int *check_dir, int *score, int x1_rocket, int y1_rocket){
    if(*xball <= MAX_X - 1){
        *check_dir = 2;
    }
    else if(*yball == 1){
        *score+=1;
        *yball = 41;
        *xball = 13;
    }
    else if(ball_and_rocket(*xball, *yball, x1_rocket, y1_rocket)){
        *check_dir = 1;
    }
    else{
        *xball+=1;
        *yball-=1;
    }
}

void game_button(int *x1_rocket, int *x2_rocket){
    char c = getchar();
    if (c == 'a' && *x1_rocket != 2) *x1_rocket-=1;
    if (c == 'z' && *x1_rocket != 23) *x1_rocket+=1;
    if (c == 'k' && *x2_rocket != 2) *x2_rocket-=1;
    if (c == 'm' && *x2_rocket != 23) *x2_rocket+=1;
}

void end_game(int *flag_finish, int score1, int score2){
    if (score1 == 21 && score1 > score2) {
        print_winner(score1, score2, 0);
        *flag_finish = 1;
    }
    if (score2 == 21 && score2 > score1) {
        print_winner(score1, score2, 1);
        *flag_finish = 1;
    }
}


void Pong() {
    //Главная функция, в которой происходят все действия
    int x1_rocket = 13;
    int y1_rocket = 1;
    int x2_rocket = 13;
    int y2_rocket = 80;

    int score1 = 0;
    int score2 = 0;

    int yball = 41;
    int xball = 13;
    int check_dir = 0;

    int flag_finish = 0;

    while (1) {
        end_game(&flag_finish, score1, score2);
        if (flag_finish) {
            break;
        }
        show_score(score1, score2);
        printf("\n");
        print_field(xball, yball, x1_rocket, y1_rocket, x2_rocket, y2_rocket);

        game_button(&x1_rocket, &x2_rocket);
        //Реализация смены направления мяча 
        if (check_dir == 0) {
            redirect_0(&xball, &yball, &check_dir, &score1, x2_rocket, y2_rocket);
        }
        if (check_dir == 1) {
            redirect_1(&xball, &yball, &check_dir, &score1, x2_rocket, y2_rocket);
        }
        if (check_dir == 2) {
            redirect_2(&xball, &yball, &check_dir, &score2, x1_rocket, y1_rocket);
        }
        if (check_dir == 3) {
            redirect_3(&xball, &yball, &check_dir, &score2, x1_rocket, y1_rocket);
        }
        printf("\033c");
    }
}

int main(void) {
    Pong();
    return 0;
}
