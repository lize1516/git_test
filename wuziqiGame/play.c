#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"
#include <string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
void menu()
{
	printf("*******************************\n");
	printf("*******  三子棋小游戏  ********\n");
	printf("**** 1.play         0.exit ****\n");
	printf("*******************************\n");
}
void game()
{
	char arr[ROWS][COLS];
	char ret = ' ';
	init_arr(arr, ROWS, COLS);
	display_arr(arr, ROWS, COLS);
	while (1)
	{
		player_move(arr, ROWS, COLS);
		display_arr(arr, ROWS, COLS);
		ret = (check_win(arr, ROWS, COLS));
		if (ret != ' ')
			break;
		system("cls");
		computer_move(arr, ROWS, COLS);
		display_arr(arr, ROWS, COLS);
		ret = (check_win(arr, ROWS, COLS));
		if (ret != ' ')
			break;
	}
	if (ret == '1')
		printf("恭喜你，你胜了\n");
	else if (ret == '#')
		printf("电脑胜\n");
	if (ret == 'R')
		printf("平局\n");
}
int main()
{
	int input = 0;
	do
	{
		menu();
		printf("请选择:\n");
		scanf("%d", &input);
		fflush(stdin);
		switch (input)
		{
		case 1:
			printf("play game:\n");
			game();
			break;
		case 0:
			printf("Exit game");
			Sleep(2000);
			break;
		default:
			printf("输入错误 请重新输入\n");
			break;
		}
	} 
	while (input);
	return 0;
}