#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"
#include <string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

void init_arr(char arr[ROWS][COLS], int rows, int cols)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
			arr[i][j] = ' ';
	}
}
void display_arr(char arr[ROWS][COLS], int rows, int cols)
{
	int i= 0;
	for (i = 0; i < rows; i++)
	{
		printf(" %c | %c | %c | %c | %c | %c | %c | %c | %c | %c \n", 
			arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4], arr[i][5], arr[i][6], arr[i][7], arr[i][8],arr[i][9]);
		if (i < rows - 1)
		{	
			printf("---|---|---|---|---|---|---|---|---|---\n");
		}
	}
}
void player_move(char arr[ROWS][COLS], int rows, int cols)
{
	int x = 0;
	int y = 0;
	printf("请输入坐标：x y\n");
	while (1)
	{
		scanf("%d %d", &x, &y);
		fflush(stdin);
		x--;
		y--;
		if ((x >= 0) && (x <= rows)&&(y >= 0) && (y <= cols))
		{
			if (arr[x][y] == ' ')
			{
				arr[x][y] = '1';
				break;
			}
			else
			{
				printf("输入有问题\n");
			}
		}
		else
		{
			printf("输入有问题\n");
		}
	}
}
void computer_move(char arr[ROWS][COLS], int rows, int cols)
{
	printf("让电脑想想\n");
	//Sleep(100);
	rows = rand() % ROWS;
	cols = rand() % ROWS;
	while (arr[rows][cols]!=' ')
	{		
		rows = rand() % ROWS;
		cols = rand() % ROWS;
	}
	arr[rows][cols] = '#';
}
char check_win(char arr[ROWS][COLS], int rows, int cols)
{
	int i = 0, j = 0;
	for (i = 0; i < rows; i++)//判断十行
	{
		if ((arr[i][0] == arr[i][1]) && (arr[i][1] == arr[i][2]) && (arr[i][0] != ' '))
			return arr[i][0];
		if ((arr[i][1] == arr[i][2]) && (arr[i][2] == arr[i][3]) && (arr[i][1] != ' '))
			return arr[i][1];
		if ((arr[i][2] == arr[i][3]) && (arr[i][3] == arr[i][4]) && (arr[i][2] != ' '))
			return arr[i][2];
	}
	for (j = 0; j <= cols; j++)//判断十列
	{	
		if ((arr[0][j] == arr[1][j]) && (arr[1][j] == arr[2][j]) && (arr[0][j] != ' '))
			return arr[0][j];
		if ((arr[1][j] == arr[2][j]) && (arr[2][j] == arr[3][j]) && (arr[1][j] != ' '))
			return arr[1][j];
		if ((arr[2][j] == arr[3][j]) && (arr[3][j] == arr[4][j]) && (arr[2][j] != ' '))
			return arr[2][j];
	}
	int m;
 for (m = 0; m < ROWS - 2; m++)
  {
	for (j = m; j < COLS - 2; j++)
	{
		for (i = 0; i < ROWS - 2; i++)
		{
			if ((arr[i][j] == arr[i + 1][j + 1]) && (arr[i + 1][j + 1] == arr[i + 2][j + 2]) && (arr[i][j] != ' '))
				return arr[i][j];
		}
	}
	for (j = m; j < COLS - 2; j++)
	{
		for (i = 2; i < ROWS; i++)
		{
			if ((arr[i][j] == arr[i - 1][j + 1]) && (arr[i - 1][j + 1] == arr[i - 2][j + 2]) && (arr[i][j] != ' '))
				return arr[i][j];
		}
	}
 }
		if (is_full(arr, rows, cols))
		{
			return 'R';//平局
		}
		return ' ';
}
static int is_full(char arr[ROWS][COLS], int rows, int cols)
{
	int i = 0, j = 0;
	for (i = 0; i <= rows; i++)
	{
		for (j = 0; j <= cols; j++)
		{
			if (arr[i][j] == ' ')
				return 0;
		}
	}
	return 1;
}
