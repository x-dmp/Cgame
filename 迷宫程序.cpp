#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <graphics.h>
#pragma comment (lib, "Winmm.lib")

#define MAXLENGTH 56
#define MAXWIDTH 68
#define BorderMark 1
#define WallMark 0
#define RouteMark -1
#define PlayerMark 2

void CreatMap(int map[MAXLENGTH][MAXWIDTH], int flag);
void FindRoute(int map[MAXLENGTH][MAXWIDTH], int x, int y, int flag);
void PrintMaze(int map[MAXLENGTH][MAXWIDTH], int flag);
void CreatMaze(int map[MAXLENGTH][MAXWIDTH], int flag);
void FindExit(int map[MAXLENGTH][MAXWIDTH], int flag);
int StartGame(void);
int ControlGame(int flag);
void SetPlayer(int map[MAXLENGTH][MAXWIDTH]);
void Teaching(void);
int ChoosingDifficulty(void);
void refreshtime(int flag);
int Pause(int map[MAXLENGTH][MAXWIDTH], int flag);

int main(void)
{
	int flag = 0;

	initgraph(1280, 720);
	PlaySound ("mazefile\\mainost.wav",NULL,SND_FILENAME | SND_ASYNC);

	while (1)
	{
		if (flag == 0)
		{
			flag = StartGame();
		}
		else if (flag == 1)
		{
			flag = ChoosingDifficulty();
			flag = ControlGame(flag);
		}
		else if (flag == 2)
		{
			Teaching();
			flag = 0;
		}
		else if (flag == 3)
		{
			return 0;
			closegraph();
		}
	}
	return 1;
}

int StartGame(void)
{
	MOUSEMSG m;
	IMAGE img;	// 定义 IMAGE 对象
	loadimage(&img, _T("mazefile\\start.png"));	// 读取图片到 img 对象中
	putimage(0, 0, &img);
	
	while(1)
	{
		// 获取一条鼠标消息
		m = GetMouseMsg();

		if (m.uMsg == WM_LBUTTONDOWN && m.x > 177 && m.x < 494 && m.y > 239 && m.y < 344)// 鼠标移动的时候画红色的小点
		{
			return 1;
		}
		if (m.uMsg == WM_LBUTTONDOWN && m.x > 177 && m.x < 494 && m.y > 373 && m.y < 478)// 鼠标移动的时候画红色的小点
		{
			return 2;
		}
		if (m.uMsg == WM_LBUTTONDOWN && m.x > 177 && m.x < 494 && m.y > 506 && m.y < 611)// 鼠标移动的时候画红色的小点
		{
			return 3;
		}
	}
}

void Teaching(void)
{
	MOUSEMSG m;
	IMAGE img;	// 定义 IMAGE 对象

	loadimage(&img, _T("mazefile\\teaching.png"));	// 读取图片到 img 对象中
	putimage(0, 0, &img);
	while(1)
	{
		// 获取一条鼠标消息
		m = GetMouseMsg();

		if (m.uMsg == WM_LBUTTONDOWN)
		{
			break ;
		}
	}
}

//选择难度
int ChoosingDifficulty(void)
{
	MOUSEMSG m;
	IMAGE img;	// 定义 IMAGE 对象

	loadimage(&img, _T("mazefile\\chodif.png"));	// 读取图片到 img 对象中
	putimage(0, 0, &img);
	while(1)
	{
		// 获取一条鼠标消息
		m = GetMouseMsg();

		if (m.uMsg == WM_LBUTTONDOWN && m.x > 480 && m.x < 797 && m.y > 250 && m.y < 355)
		{
			return 1;
		}
		if (m.uMsg == WM_LBUTTONDOWN && m.x > 480 && m.x < 797 && m.y > 457 && m.y < 562)
		{
			return 2;
		}
	}
}

//主体
int ControlGame(int flag)
{
	int map[MAXLENGTH][MAXWIDTH], x = 0, y = 1, px, py, pl, maxlenth, maxwidth, flag0;
	IMAGE imga, imgb, imgc;	// 定义 IMAGE 对象
	MOUSEMSG m;

	flag0 = flag;
	if (flag == 1)
	{
		maxlenth = MAXLENGTH / 4;
		maxwidth = MAXWIDTH / 4;
		loadimage(&imga, _T("mazefile\\youriteme.png"));
		loadimage(&imgb, _T("mazefile\\roade.png"));
		pl = 30;
	}
	else if (flag == 2)
	{
		maxlenth = MAXLENGTH;
		maxwidth = MAXWIDTH;
		loadimage(&imga, _T("mazefile\\youritemh.png"));
		loadimage(&imgb, _T("mazefile\\roadh.png"));
		pl = 8;
	}
	loadimage(&imgc, _T("mazefile\\end.png"));

	
	CreatMaze(map, flag);
	px = pl + 130;
	py = 180;
	refreshtime(0);

	while (1)
	{
		refreshtime(1);
		//读取到【↑，w】且上方有路不出界
        if ((GetAsyncKeyState(VK_UP) || GetAsyncKeyState(87)) && map[x - 1][y] == RouteMark && x > 0)
        {
            map[x][y] = RouteMark;
			putimage(px, py, &imgb);
			x--;
			py -= pl;
			putimage(px, py, &imga);
			map[x][y] = PlayerMark;
        }
		//读取到【↓，s】且下方有路不出界
        else if ((GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(83)) && map[x + 1][y] == RouteMark && x < maxlenth - 1)
        {
            map[x][y] = RouteMark;
			putimage(px, py, &imgb);
			x++;
			py += pl;
			putimage(px, py, &imga);
			map[x][y] = PlayerMark;
        }
		//读取到【←，a】且左方有路不出界
        else if ((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(65)) && map[x][y - 1] == RouteMark && y > 0)
        {
            map[x][y] = RouteMark;
			putimage(px, py, &imgb);
			y--;
			px -= pl;
			putimage(px, py, &imga);
			map[x][y] = PlayerMark;
        }
		//读取到【→，d】且右方有路不出界
        else if ((GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(68)) && map[x][y + 1] == RouteMark && y < maxwidth - 1)
        {
            map[x][y] = RouteMark;
			putimage(px, py, &imgb);
			y++;
			px += pl;
			putimage(px, py, &imga);
			map[x][y] = PlayerMark;
        }
		//读取到【Esc】
		else if (GetAsyncKeyState(27))
        {
            flag = flag0;
			flag = Pause(map, flag);
			if (flag == 0)
			{
				return 0;
			}
        }
		if (map[maxlenth - 1][maxwidth - 2] == PlayerMark)
		{
			putimage(0, 0, &imgc);
			while(1)
			{
				// 获取一条鼠标消息
				m = GetMouseMsg();
				if (m.uMsg == WM_LBUTTONDOWN)
				{
					break;
				}
			}
			return 0;
		}
		Sleep(150);
	}
}

void CreatMaze(int map[MAXLENGTH][MAXWIDTH], int flag)
{

	
	srand((unsigned)time(NULL));
	CreatMap(map, flag);
	FindRoute(map, 1, 1, flag);
	FindExit(map, flag);
	SetPlayer(map);
	PrintMaze(map, flag);
}

//生成地图
void CreatMap(int map[MAXLENGTH][MAXWIDTH], int flag)
{
	int i, j;
	int maxlenth, maxwidth;

	if (flag == 1)
	{
		maxlenth = MAXLENGTH / 4;
		maxwidth = MAXWIDTH / 4;
	}
	else if(flag == 2)
	{
		maxlenth = MAXLENGTH;
		maxwidth = MAXWIDTH;
	}
	for (i = 0; i < maxlenth; i++)
	{
		for (j = 0; j < maxwidth; j++)
		{
			if (i == 0 || j == 0 || i == maxlenth - 1 || j == maxwidth - 1)
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
void FindRoute(int map[MAXLENGTH][MAXWIDTH], int x, int y, int flag)//在x y的坐标位置开始挖，本题我默认从（1,1）挖，flag为难度的判断标记
{
	int Direction[4] = {0, 0, 0, 0};//来记录四个方向是否被判断过，分别是上下左右，如果被判断过则变为1
	int i, c = 0;//i随机数 c是判断是否挖过路
	int maxlenth, maxwidth;//地图的长和宽

	if (flag == 1)//简单模式长和宽缩小四倍
	{
		maxlenth = MAXLENGTH / 4;
		maxwidth = MAXWIDTH / 4;
	}
	else if(flag == 2)//困难模式不变
	{
		maxlenth = MAXLENGTH;
		maxwidth = MAXWIDTH;
	}

	map[x][y] = -1;//把当前的单位挖成路

	while (Direction[0] != 1 || Direction[1] != 1 || Direction[2] != 1 || Direction[3] != 1)//只要四个方向有一个没判断过就执行循环
	{
		i = rand() % 4;//随机一个方向
		if (Direction[i] != 1)//将此方向记录为判断过
		{
			Direction[i] = 1;
		}
		if (i == 0)/*上*/
		{
			//如果往上不会出界
			if (x - 1 > 0)
			{
				//如果即将挖的一格及其周围都是墙
				if (map[x - 2][y] != RouteMark && map[x - 1][y] == WallMark && map[x - 1][y - 1] != RouteMark && map[x - 1][y + 1] != RouteMark)
				{
					x--;//坐标向上移一格
					c = 1;//路挖成功的判断标记
				}
			}
		}
		else if (i == 1)/*下*/
		{
			//如果往下不会出界
			if (x + 1 < maxlenth - 1)
			{
				//如果即将挖的一格及其周围都是墙
				if (map[x + 2][y] != RouteMark && map[x + 1][y] == WallMark && map[x + 1][y - 1] != RouteMark && map[x + 1][y + 1] != RouteMark)
				{
					x++;//坐标向下移一格
					c = 1;//路挖成功的判断标记
				}
			}
		}
		else if (i == 2)/*左*/
		{
			//如果往左不会出界
			if (y - 1 > 0)
			{
				//如果即将挖的一格及其周围都是墙
				if (map[x][y - 2] != RouteMark && map[x][y - 1] == WallMark && map[x - 1][y - 1] != RouteMark && map[x + 1][y - 1] != RouteMark)
				{
					y--;//坐标向左移一格
					c = 1;//路挖成功的判断标记
				}
			}
		}
		else if (i == 3)/*右*/
		{
			//如果往右不会出界
			if (y + 1 < maxwidth - 1)
			{
				//如果即将挖的一格及其周围都是墙
				if (map[x][y + 2] != RouteMark && map[x][y + 1] == WallMark && map[x - 1][y + 1] != RouteMark && map[x + 1][y + 1] != RouteMark)
				{
					y++;//坐标向右移一格
					c = 1;//路挖成功的判断标记
				}
			}
		}
		//如果路挖成功了
		if (c == 1)
		{
			FindRoute(map, x, y, flag);//使用新的坐标进行挖路 函数自我嵌套
		}
		c = 0;
	}
}

//设置出入口
void FindExit(int map[MAXLENGTH][MAXWIDTH], int flag)
{
	int i;
	int maxlenth, maxwidth;

	if (flag == 1)
	{
		maxlenth = MAXLENGTH / 4;
		maxwidth = MAXWIDTH / 4;
	}
	else if (flag == 2)
	{
		maxlenth = MAXLENGTH;
		maxwidth = MAXWIDTH;
	}

	i = 0;
	while (1)
	{
		map[maxlenth - 1 - i][maxwidth - 2] = -1;
		map[0][1] = -1;
		if (map[maxlenth - 2 - i][maxwidth - 2] == -1 || map[maxlenth - 1 - i][maxwidth - 3] == -1)
		{
			break;
		}
		i++;
	}
}


//设置玩家位置
void SetPlayer(int map[MAXLENGTH][MAXWIDTH])
{
	map[0][1] = 2;
}

//打印迷宫
void PrintMaze(int map[MAXLENGTH][MAXWIDTH], int flag)
{
	int i, j, px, py, pl;
	int maxlenth, maxwidth;
	IMAGE img, imga, imgb, imgc;	// 定义 IMAGE 对象

	if (flag == 1)
	{
		maxlenth = MAXLENGTH / 4;
		maxwidth = MAXWIDTH / 4;
		loadimage(&img, _T("mazefile\\mazeeasys.png"));	// 读取图片到 img 对象中
		loadimage(&imga, _T("mazefile\\youriteme.png"));
		loadimage(&imgb, _T("mazefile\\walle.png"));
		loadimage(&imgc, _T("mazefile\\roade.png"));
		pl = 30;
	}
	else if (flag == 2)
	{
		maxlenth = MAXLENGTH;
		maxwidth = MAXWIDTH;
		loadimage(&img, _T("mazefile\\mazehards.png"));	// 读取图片到 img 对象中
		loadimage(&imga, _T("mazefile\\youritemh.png"));
		loadimage(&imgb, _T("mazefile\\wallh.png"));
		loadimage(&imgc, _T("mazefile\\roadh.png"));
		pl = 8;
	}
	putimage(0, 0, &img);
	
	for (i = 0, py = 180; i < maxlenth; i++, py += pl)
	{
		for (j = 0, px = 130; j < maxwidth; j++, px += pl)
		{
			if (map[i][j] == 1)
			{
				putimage(px, py, &imgb);
			}
			else if (map[i][j] == 0)
			{
				putimage(px, py, &imgb);
			}
			else if (map[i][j] == -1)
			{
				putimage(px, py, &imgc);
			}
			else if (map[i][j] == 2)
			{
				putimage(px, py, &imga);
			}
		}
	}
}

int Pause(int map[MAXLENGTH][MAXWIDTH], int flag)
{
	IMAGE img;	// 定义 IMAGE 对象
	MOUSEMSG m;
	
	if (flag == 1)
	{
		loadimage(&img, _T("mazefile\\mazeeasyp.png"));	// 读取图片到 img 对象中
	}
	else if (flag == 2)
	{
		loadimage(&img, _T("mazefile\\mazehardp.png"));	// 读取图片到 img 对象中
	}
	putimage(0, 0, &img);
	while (1)
	{
		m = GetMouseMsg();

		if (m.uMsg == WM_LBUTTONDOWN && m.x > 795 && m.x < 907 && m.y > 533 && m.y < 603)
		{
			PrintMaze(map, flag);
			return 1;
			break;
		}
		else if (m.uMsg == WM_LBUTTONDOWN && m.x > 985 && m.x < 1097 && m.y > 533 && m.y < 603)
		{
			break;
		}
		refreshtime(1);

	}
	return 0;
}


void refreshtime(int flag)
{
	IMAGE img0, img1, img2, img3, img4, img5, img6, img7, img8, img9;
	time_t time0;
	static long int timea, timeb;

	loadimage(&img0, _T("mazefile\\0.png"));
	loadimage(&img1, _T("mazefile\\1.png"));
	loadimage(&img2, _T("mazefile\\2.png"));
	loadimage(&img3, _T("mazefile\\3.png"));
	loadimage(&img4, _T("mazefile\\4.png"));
	loadimage(&img5, _T("mazefile\\5.png"));
	loadimage(&img6, _T("mazefile\\6.png"));
	loadimage(&img7, _T("mazefile\\7.png"));
	loadimage(&img8, _T("mazefile\\8.png"));
	loadimage(&img9, _T("mazefile\\9.png"));
	time0 = time(NULL);
	if (flag == 0)
	{
		timea = time0;
	}
	else
	{
		timeb = time0 - timea;
		switch (timeb / 100)
		{
		case 0:
			putimage(868, 300, &img0);
			break;
		case 1:
			putimage(868, 300, &img1);
			break;
		case 2:
			putimage(868, 300, &img2);
			break;
		case 3:
			putimage(868, 300, &img3);
			break;
		case 4:
			putimage(868, 300, &img4);
			break;
		case 5:
			putimage(868, 300, &img5);
			break;
		case 6:
			putimage(868, 300, &img6);
			break;
		case 7:
			putimage(868, 300, &img7);
			break;
		case 8:
			putimage(868, 300, &img8);
			break;
		case 9:
			putimage(868, 300, &img9);
			break;
		default:
			;
		}
		switch (timeb / 10 % 10)
		{
		case 0:
			putimage(915, 300, &img0);
			break;
		case 1:
			putimage(915, 300, &img1);
			break;
		case 2:
			putimage(915, 300, &img2);
			break;
		case 3:
			putimage(915, 300, &img3);
			break;
		case 4:
			putimage(915, 300, &img4);
			break;
		case 5:
			putimage(915, 300, &img5);
			break;
		case 6:
			putimage(915, 300, &img6);
			break;
		case 7:
			putimage(915, 300, &img7);
			break;
		case 8:
			putimage(915, 300, &img8);
			break;
		case 9:
			putimage(915, 300, &img9);
			break;
		default:
			;
		}
		switch (timeb % 10)
		{
		case 0:
			putimage(962, 300, &img0);
			break;
		case 1:
			putimage(962, 300, &img1);
			break;
		case 2:
			putimage(962, 300, &img2);
			break;
		case 3:
			putimage(962, 300, &img3);
			break;
		case 4:
			putimage(962, 300, &img4);
			break;
		case 5:
			putimage(962, 300, &img5);
			break;
		case 6:
			putimage(962, 300, &img6);
			break;
		case 7:
			putimage(962, 300, &img7);
			break;
		case 8:
			putimage(962, 300, &img8);
			break;
		case 9:
			putimage(962, 300, &img9);
			break;
		default:
			;
		}
	}
}











