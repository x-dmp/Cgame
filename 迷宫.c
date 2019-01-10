#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#define MAXLENGTH 25
#define MAXWIDTH 30
 
#define BorderMark 1
#define WallMark 0
#define RouteMark -1
#define PlayerMark 2

#define YES 1
#define NO 0


void CreatMap(int map[MAXLENGTH][MAXWIDTH]);
void FindRoute(int map[MAXLENGTH][MAXWIDTH], int x, int y);
void PrintMaze(int map[MAXLENGTH][MAXWIDTH]);
void CreatMaze(int map[MAXLENGTH][MAXWIDTH]);
void FindExit(int map[MAXLENGTH][MAXWIDTH]);
void StartGame(void);
void color(short int num);
int gotoxy(int x, int y);
void ControlGame(void);
void SetPlayer(int map[MAXLENGTH][MAXWIDTH]);


int main(void)
{
	StartGame();
	ControlGame();

	return 0;
}

//设置玩家位置
void SetPlayer(int map[MAXLENGTH][MAXWIDTH])
{
	map[0][1] = 2;
}

//主体
void ControlGame(void)
{
	int map[MAXLENGTH][MAXWIDTH], x = 0, y = 1;
	
	CreatMaze(map);

	while (1)
	{
		//读取到【↑，w】且上方有路不出界
        if ((GetAsyncKeyState(VK_UP) || GetAsyncKeyState(87)) && map[x - 1][y] == RouteMark && x > 0)
        {
            map[x][y] = RouteMark;
			gotoxy(y * 2, x);
			printf("  ");
			x--;
			gotoxy(y * 2, x);
			printf("★");
			map[x][y] = PlayerMark;
        }
		//读取到【↓，s】且下方有路不出界
        else if ((GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(83)) && map[x + 1][y] == RouteMark && x < MAXLENGTH - 1)
        {
            map[x][y] = RouteMark;
			gotoxy(y * 2, x);
			printf("  ");
			x++;
			gotoxy(y * 2, x);
			printf("★");
			map[x][y] = PlayerMark;
        }
		//读取到【←，a】且左方有路不出界
        else if ((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(65)) && map[x][y - 1] == RouteMark && y > 0)
        {
            map[x][y] = RouteMark;
			gotoxy(y * 2, x);
			printf("  ");
			y--;
			gotoxy(y * 2, x);
			printf("★");
			map[x][y] = PlayerMark;
        }
		//读取到【→，d】且右方有路不出界
        else if ((GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(68)) && map[x][y + 1] == RouteMark && y < MAXWIDTH - 1)
        {
            map[x][y] = RouteMark;
			gotoxy(y * 2, x);
			printf("  ");
			y++;
			gotoxy(y * 2, x);
			printf("★");
			map[x][y] = PlayerMark;
        }
		if (map[MAXLENGTH - 1][MAXWIDTH - 2] == PlayerMark)
		{
			system("cls");
			gotoxy(3, 3);
			printf("welldone");
			break;
		}
		Sleep(150);
	}
	
}

void StartGame(void)
{
	short int i;

	printf("温馨提示：请使用键盘操作（鼠标点击可能会导致程序出错）\n");
    printf("╔═══════════════════════════════════════════════════════════════════════════════════════════════════════╗ \n");
    for (i = 0; i < 45; i++)
	{
		printf("║												　　　　║ \n");
	}
    printf("╚═══════════════════════════════════════════════════════════════════════════════════════════════════════╝ \n");
	gotoxy(50, 2);
	color(3);
	printf("迷 宫");
	for (i = 15; ; i--)
	{
		gotoxy(45, 4);
		color(i);
		printf("按任意键加载程序");
		Sleep(600);
		if (i == 1)
		{
			i = 15;
		}
		if (kbhit())	//判断是否按键，等待输入按键为0，按键为1
		{
			break;
		}
	}
}



/*↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓*/

void color(short int num)
{
	HANDLE hConsole = GetStdHandle((STD_OUTPUT_HANDLE));
	SetConsoleTextAttribute(hConsole, num);
}




int gotoxy(int x, int y)
{  
    HANDLE handle;	//定义句柄变量handle，创建一个句柄
    COORD pos;	//定义结构体coord (坐标系coord)
    pos.X = x;	//横坐标x
    pos.Y = y;	//纵坐标y
    handle = GetStdHandle(STD_OUTPUT_HANDLE);	//获取控制台输出句柄(值为-11)
    SetConsoleCursorPosition(handle, pos);	//移动光标
	return YES;
}

/*↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑*/


void CreatMaze(int map[MAXLENGTH][MAXWIDTH])
{

	
	srand((unsigned)time(NULL));
	CreatMap(map);
	FindRoute(map, 1, 1);
	FindExit(map);
	SetPlayer(map);
	PrintMaze(map);
}

//生成地图
void CreatMap(int map[MAXLENGTH][MAXWIDTH])
{
	int i, j;

	for (i = 0; i < MAXLENGTH; i++)
	{
		for (j = 0; j < MAXWIDTH; j++)
		{
			if (i == 0 || j == 0 || i == MAXLENGTH - 1 || j == MAXWIDTH - 1)
			{
				map[i][j] = 1;
			}
			else
			{
				map[i][j] = 0;
			}
		}
	}
}


//挖路
void FindRoute(int map[MAXLENGTH][MAXWIDTH], int x, int y)
{
	int Direction[4] = {0, 0, 0, 0};
	int i, k, flag = 0;

	map[x][y] = -1;

	while (Direction[0] != 1 || Direction[1] != 1 || Direction[2] != 1 || Direction[3] != 1)
	{
		i = rand() % 4;
		if (Direction[i] != 1)
		{
			Direction[i] = 1;
		}
		for (k = 0; k < 1; k++)
		{
			if (i == 0)/*上*/
			{
				if (x - 1 > 0)
				{
					if (map[x - 2][y] != RouteMark && map[x - 1][y] == WallMark && map[x - 1][y - 1] != RouteMark && map[x - 1][y + 1] != RouteMark)
					{
						x--;
						flag = 1;
					}
				}
			}
			else if (i == 1)/*下*/
			{
				if (x + 1 < MAXLENGTH - 1)
				{
					if (map[x + 2][y] != RouteMark && map[x + 1][y] == WallMark && map[x + 1][y - 1] != RouteMark && map[x + 1][y + 1] != RouteMark)
					{
						x++;
						flag = 1;
					}
				}
			}
			else if (i == 2)/*左*/
			{
				if (y - 1 > 0)
				{
					if (map[x][y - 2] != RouteMark && map[x][y - 1] == WallMark && map[x - 1][y - 1] != RouteMark && map[x + 1][y - 1] != RouteMark)
					{
						y--;
						flag = 1;
					}
				}
			}
			else if (i == 3)/*右*/
			{
				if (y + 1 < MAXWIDTH - 1)
				{
					if (map[x][y + 2] != RouteMark && map[x][y + 1] == WallMark && map[x - 1][y + 1] != RouteMark && map[x + 1][y + 1] != RouteMark)
					{
						y++;
						flag = 1;
					}
				}
			}
			if (flag == 1)
			{
				FindRoute(map, x, y);
			}
			flag = 0;
		}
	}
}

//打印迷宫
void PrintMaze(int map[MAXLENGTH][MAXWIDTH])
{
	int i, j;
	

	
	system("cls");
	for (i = 0; i < MAXLENGTH; i++)
	{
		for (j = 0; j < MAXWIDTH; j++)
		{
			color(14);
			if (map[i][j] == 1)
			{
				printf("█");
			}
			else if (map[i][j] == 0)
			{
				printf("█");
			}
			else if (map[i][j] == -1)
			{
				printf("  ");
			}
			else if (map[i][j] == 2)
			{
				color(4);
				printf("★");
			}
		}
		printf("\n");
	}


}
//设置出入口
void FindExit(int map[MAXLENGTH][MAXWIDTH])
{
	int i;

	i = 0;
	while (1)
	{
		map[MAXLENGTH - 1 - i][MAXWIDTH - 2] = -1;
		map[0][1] = -1;
		if (map[MAXLENGTH - 2 - i][MAXWIDTH - 2] == -1 || map[MAXLENGTH - 1 - i][MAXWIDTH - 3] == -1)
		{
			break;
		}
		i++;
	}
}
