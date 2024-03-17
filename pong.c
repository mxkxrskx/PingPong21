#include <stdio.h>
#include <stdbool.h>

#define ROWS 25
#define COLUMNS 81
#define WIN_SCORE 21
#define COLUMN_LEFT_ROCKET 1
#define COLUMN_RIGHT_ROCKET COLUMNS-1
#define DEBUG_MODE 0

enum Dir {
	RIGHT_UP,
  	RIGHT_DOWN,
  	LEFT_UP,
  	LEFT_DOWN	
};
typedef enum Dir Dir;

bool is_rocket(int row, int column, int row_rocket, int column_rocket){
    //Проверка где находятся ракетки
    return ((row == row_rocket) || (row == row_rocket + 1) || (row == row_rocket - 1)) && (column == column_rocket);
}

char inside_field(int row, int column, int row_ball, int column_ball, int row_left_rocket, int row_right_rocket){
    //Печаетаем "объекты" внутри поля по координатам	
  	char c = ' ';
    if (row == row_ball && column == column_ball){
        c = '0'; 
    }
    else if (is_rocket(row, column, row_left_rocket, COLUMN_LEFT_ROCKET)){
        c = '[';
    } 
    else if (is_rocket(row, column, row_right_rocket, COLUMN_RIGHT_ROCKET)){
        c = ']';  
    }
    else if (column == COLUMNS/2){
        c = '*';
    }
  	return c;
}

char field_value(int row,				       int column,
                 int row_ball,		     int column_ball,
                 int row_left_rocket,
                 int row_right_rocket) {
    //Печатаем по координатам все поле
  	char c;
    if(row != 0 && row != ROWS && column != 0 && column != COLUMNS){
        c = inside_field(row, column, row_ball, column_ball, row_left_rocket, row_right_rocket);
    }
    else if(column == 0 || column == COLUMNS){
        c = '|';
    }
    else{
        c = '#';
    }
    return c;
}

void print_space(int column){
    if(column == COLUMNS){
        printf("\n");
    }
}

void print_field(int row_ball, int column_ball, int row_left_rocket, int row_right_rocket) {
    for (int row = 0; row <= ROWS; row++) {
        for (int column = 0; column <= COLUMNS; column++) {
            printf("%c", field_value(row, column, row_ball, column_ball, row_left_rocket, row_right_rocket));
            print_space(column);
        }
    }
}

void show_score(int score_left, int score_right) {
    printf("Первый игрок: %d", score_left);
    int str_len_one = 15;
    for (int i = 0; i <= COLUMNS - str_len_one*2 - (score_left > 9) - (score_right > 9); i+=1)
    {
        printf(" ");
    }
    printf("Второй игрок: %d", score_right);
}

void print_winner(int score_left, int score_right, int flag) {
    if (flag == 0) {
        printf("Победил первый игрок со счетом %d:%d\n", score_left, score_right);
    }
    if (flag == 1) {
        printf("Победил второй игрок со счетом %d:%d\n", score_left, score_right);
    }
}

bool ball_and_rocket(int row_ball, int column_ball, int row_rocket, int column_rocket) {
    if(column_ball > COLUMNS/2) column_rocket--;
    if(column_ball < COLUMNS/2) column_rocket++;
    return (row_ball == row_rocket || row_ball == row_rocket + 1 || row_ball == row_rocket - 1) && column_ball == column_rocket;
}

void redirect_right_up(int *row_ball, int *column_ball, Dir *dir_ball, int *score, int row_right_rocket){
    if(*row_ball <= 1){
         *dir_ball = RIGHT_DOWN;
    }
    else if(*column_ball == COLUMNS - 1){
         *score +=1;
         *column_ball = COLUMNS/2;
         *row_ball = ROWS/2;
    }
    else if(ball_and_rocket(*row_ball, *column_ball, row_right_rocket, COLUMN_RIGHT_ROCKET)){
         *dir_ball = LEFT_UP;
    }
    else{
         *row_ball-=1;
         *column_ball+=1;
    }
}

void redirect_right_down(int *row_ball, int *column_ball, Dir* dir_ball, int *score, int row_right_rocket){
    if(*row_ball >= ROWS - 1){
        *dir_ball = RIGHT_UP;
    }
    else if(*column_ball == COLUMNS - 1){
        *score+=1;
        *column_ball = COLUMNS/2;
        *row_ball = ROWS/2;
    }
    else if(ball_and_rocket(*row_ball, *column_ball, row_right_rocket, COLUMN_RIGHT_ROCKET)){
        *dir_ball = LEFT_DOWN;
    }
    else{
        *row_ball+=1;
        *column_ball+=1;
    }
}

void redirect_left_up(int *row_ball, int *column_ball, Dir* dir_ball, int *score, int row_left_rocket){
    if(*row_ball <= 1){
        *dir_ball = LEFT_DOWN;
    }
    else if(*column_ball == 1){
        *score+=1;
    }
    else if(ball_and_rocket(*row_ball, *column_ball, row_left_rocket, COLUMN_LEFT_ROCKET)){
        *dir_ball = RIGHT_UP;
    }
    else{
        *row_ball-=1;
        *column_ball-=1;
    }
}

void redirect_left_down(int *row_ball, int *column_ball, Dir* dir_ball, int *score, int row_left_rocket){
    if(*row_ball >= ROWS - 1){
        *dir_ball = LEFT_UP;
    }
    else if(*column_ball == 1){
        *score+=1;
        *column_ball = COLUMNS/2;
        *row_ball = ROWS/2;
    }
    else if(ball_and_rocket(*row_ball, *column_ball, row_left_rocket, COLUMN_LEFT_ROCKET)){
        *dir_ball = RIGHT_DOWN;
    }
    else{
        *row_ball+=1;
        *column_ball-=1;
    }
}

void game_button(int *row_left_rocket, int *row_right_rocket){
    char c = getchar();
    if (c == 'a' && *row_left_rocket != 2) *row_left_rocket-=1;
    if (c == 'z' && *row_left_rocket != ROWS-2) *row_left_rocket+=1;
    if (c == 'k' && *row_right_rocket != 2) *row_right_rocket-=1;
    if (c == 'm' && *row_right_rocket != ROWS-2) *row_right_rocket+=1;
}

void end_game(int score_left, int score_right){
    if (score_left == WIN_SCORE && score_left > score_right) {
        print_winner(score_left, score_right, 0);
    }
    if (score_right == WIN_SCORE && score_right > score_left) {
        print_winner(score_left, score_right, 1);
    }
}

bool is_end_game(int score_left, int score_right) {
  bool flag = 0;
  if(score_left == WIN_SCORE || score_right == WIN_SCORE){
    flag = 1;
  }
  return flag;
}

void Pong() {
    //Главная функция, в которой происходят все действия
    int row_left_rocket = ROWS/2;
    int row_right_rocket = ROWS/2;

    int score_left = 0;
    int score_right = 0;

    int column_ball = COLUMNS/2;
    int row_ball = ROWS/2;
    Dir dir_ball = RIGHT_UP;

    while (is_end_game(score_left, score_right) == false) {
        show_score(score_left, score_right);
        printf("\n");
        print_field(row_ball, column_ball, row_left_rocket, row_right_rocket);

        game_button(&row_left_rocket, &row_right_rocket);
        switch (dir_ball)
        {
        case RIGHT_UP:
            redirect_right_up(&row_ball, &column_ball, &dir_ball, &score_left, row_right_rocket);
            break;
        case RIGHT_DOWN:
            redirect_right_down(&row_ball, &column_ball, &dir_ball, &score_left, row_right_rocket);
            break;
        case LEFT_UP:
            redirect_left_up(&row_ball, &column_ball, &dir_ball, &score_right, row_left_rocket);
            break;
        case LEFT_DOWN:
        	redirect_left_down(&row_ball, &column_ball, &dir_ball, &score_right, row_left_rocket);
            break;
        }
        printf("\033c");
    }
  end_game(score_left, score_right);
}

int main(void) {
    Pong();
    return 0;
}