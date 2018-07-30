#ifndef _GAME_H__
#define _GAME_H__
#define ROWS 10
#define COLS 10

void init_arr(char arr[ROWS][COLS], int rows, int cols);       //将数组元素全都初始化成空格
void display_arr(char arr[ROWS][COLS], int rows, int cols);    //显示棋盘
void player_move(char arr[ROWS][COLS], int rows, int cols);     //玩家落子
char check_win(char arr[ROWS][COLS], int rows, int cols);        //判断胜负
void computer_move(char arr[ROWS][COLS], int rows, int cols);    //电脑落子
int is_full(char arr[ROWS][COLS], int rows, int cols);          //判断棋盘是否已满

#endif //GAME_H__