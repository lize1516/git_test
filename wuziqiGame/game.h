#ifndef _GAME_H__
#define _GAME_H__
#define ROWS 10
#define COLS 10

void init_arr(char arr[ROWS][COLS], int rows, int cols);       //������Ԫ��ȫ����ʼ���ɿո�
void display_arr(char arr[ROWS][COLS], int rows, int cols);    //��ʾ����
void player_move(char arr[ROWS][COLS], int rows, int cols);     //�������
char check_win(char arr[ROWS][COLS], int rows, int cols);        //�ж�ʤ��
void computer_move(char arr[ROWS][COLS], int rows, int cols);    //��������
int is_full(char arr[ROWS][COLS], int rows, int cols);          //�ж������Ƿ�����

#endif //GAME_H__