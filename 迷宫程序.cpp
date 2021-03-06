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
	IMAGE img;	// ���� IMAGE ����
	loadimage(&img, _T("mazefile\\start.png"));	// ��ȡͼƬ�� img ������
	putimage(0, 0, &img);
	
	while(1)
	{
		// ��ȡһ�������Ϣ
		m = GetMouseMsg();

		if (m.uMsg == WM_LBUTTONDOWN && m.x > 177 && m.x < 494 && m.y > 239 && m.y < 344)// ����ƶ���ʱ�򻭺�ɫ��С��
		{
			return 1;
		}
		if (m.uMsg == WM_LBUTTONDOWN && m.x > 177 && m.x < 494 && m.y > 373 && m.y < 478)// ����ƶ���ʱ�򻭺�ɫ��С��
		{
			return 2;
		}
		if (m.uMsg == WM_LBUTTONDOWN && m.x > 177 && m.x < 494 && m.y > 506 && m.y < 611)// ����ƶ���ʱ�򻭺�ɫ��С��
		{
			return 3;
		}
	}
}

void Teaching(void)
{
	MOUSEMSG m;
	IMAGE img;	// ���� IMAGE ����

	loadimage(&img, _T("mazefile\\teaching.png"));	// ��ȡͼƬ�� img ������
	putimage(0, 0, &img);
	while(1)
	{
		// ��ȡһ�������Ϣ
		m = GetMouseMsg();

		if (m.uMsg == WM_LBUTTONDOWN)
		{
			break ;
		}
	}
}

//ѡ���Ѷ�
int ChoosingDifficulty(void)
{
	MOUSEMSG m;
	IMAGE img;	// ���� IMAGE ����

	loadimage(&img, _T("mazefile\\chodif.png"));	// ��ȡͼƬ�� img ������
	putimage(0, 0, &img);
	while(1)
	{
		// ��ȡһ�������Ϣ
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

//����
int ControlGame(int flag)
{
	int map[MAXLENGTH][MAXWIDTH], x = 0, y = 1, px, py, pl, maxlenth, maxwidth, flag0;
	IMAGE imga, imgb, imgc;	// ���� IMAGE ����
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
		//��ȡ��������w�����Ϸ���·������
        if ((GetAsyncKeyState(VK_UP) || GetAsyncKeyState(87)) && map[x - 1][y] == RouteMark && x > 0)
        {
            map[x][y] = RouteMark;
			putimage(px, py, &imgb);
			x--;
			py -= pl;
			putimage(px, py, &imga);
			map[x][y] = PlayerMark;
        }
		//��ȡ��������s�����·���·������
        else if ((GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(83)) && map[x + 1][y] == RouteMark && x < maxlenth - 1)
        {
            map[x][y] = RouteMark;
			putimage(px, py, &imgb);
			x++;
			py += pl;
			putimage(px, py, &imga);
			map[x][y] = PlayerMark;
        }
		//��ȡ��������a��������·������
        else if ((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(65)) && map[x][y - 1] == RouteMark && y > 0)
        {
            map[x][y] = RouteMark;
			putimage(px, py, &imgb);
			y--;
			px -= pl;
			putimage(px, py, &imga);
			map[x][y] = PlayerMark;
        }
		//��ȡ��������d�����ҷ���·������
        else if ((GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(68)) && map[x][y + 1] == RouteMark && y < maxwidth - 1)
        {
            map[x][y] = RouteMark;
			putimage(px, py, &imgb);
			y++;
			px += pl;
			putimage(px, py, &imga);
			map[x][y] = PlayerMark;
        }
		//��ȡ����Esc��
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
				// ��ȡһ�������Ϣ
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

//���ɵ�ͼ
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

//��·
void FindRoute(int map[MAXLENGTH][MAXWIDTH], int x, int y, int flag)//��x y������λ�ÿ�ʼ�ڣ�������Ĭ�ϴӣ�1,1���ڣ�flagΪ�Ѷȵ��жϱ��
{
	int Direction[4] = {0, 0, 0, 0};//����¼�ĸ������Ƿ��жϹ����ֱ����������ң�������жϹ����Ϊ1
	int i, c = 0;//i����� c���ж��Ƿ��ڹ�·
	int maxlenth, maxwidth;//��ͼ�ĳ��Ϳ�

	if (flag == 1)//��ģʽ���Ϳ���С�ı�
	{
		maxlenth = MAXLENGTH / 4;
		maxwidth = MAXWIDTH / 4;
	}
	else if(flag == 2)//����ģʽ����
	{
		maxlenth = MAXLENGTH;
		maxwidth = MAXWIDTH;
	}

	map[x][y] = -1;//�ѵ�ǰ�ĵ�λ�ڳ�·

	while (Direction[0] != 1 || Direction[1] != 1 || Direction[2] != 1 || Direction[3] != 1)//ֻҪ�ĸ�������һ��û�жϹ���ִ��ѭ��
	{
		i = rand() % 4;//���һ������
		if (Direction[i] != 1)//���˷����¼Ϊ�жϹ�
		{
			Direction[i] = 1;
		}
		if (i == 0)/*��*/
		{
			//������ϲ������
			if (x - 1 > 0)
			{
				//��������ڵ�һ������Χ����ǽ
				if (map[x - 2][y] != RouteMark && map[x - 1][y] == WallMark && map[x - 1][y - 1] != RouteMark && map[x - 1][y + 1] != RouteMark)
				{
					x--;//����������һ��
					c = 1;//·�ڳɹ����жϱ��
				}
			}
		}
		else if (i == 1)/*��*/
		{
			//������²������
			if (x + 1 < maxlenth - 1)
			{
				//��������ڵ�һ������Χ����ǽ
				if (map[x + 2][y] != RouteMark && map[x + 1][y] == WallMark && map[x + 1][y - 1] != RouteMark && map[x + 1][y + 1] != RouteMark)
				{
					x++;//����������һ��
					c = 1;//·�ڳɹ����жϱ��
				}
			}
		}
		else if (i == 2)/*��*/
		{
			//������󲻻����
			if (y - 1 > 0)
			{
				//��������ڵ�һ������Χ����ǽ
				if (map[x][y - 2] != RouteMark && map[x][y - 1] == WallMark && map[x - 1][y - 1] != RouteMark && map[x + 1][y - 1] != RouteMark)
				{
					y--;//����������һ��
					c = 1;//·�ڳɹ����жϱ��
				}
			}
		}
		else if (i == 3)/*��*/
		{
			//������Ҳ������
			if (y + 1 < maxwidth - 1)
			{
				//��������ڵ�һ������Χ����ǽ
				if (map[x][y + 2] != RouteMark && map[x][y + 1] == WallMark && map[x - 1][y + 1] != RouteMark && map[x + 1][y + 1] != RouteMark)
				{
					y++;//����������һ��
					c = 1;//·�ڳɹ����жϱ��
				}
			}
		}
		//���·�ڳɹ���
		if (c == 1)
		{
			FindRoute(map, x, y, flag);//ʹ���µ����������· ��������Ƕ��
		}
		c = 0;
	}
}

//���ó����
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


//�������λ��
void SetPlayer(int map[MAXLENGTH][MAXWIDTH])
{
	map[0][1] = 2;
}

//��ӡ�Թ�
void PrintMaze(int map[MAXLENGTH][MAXWIDTH], int flag)
{
	int i, j, px, py, pl;
	int maxlenth, maxwidth;
	IMAGE img, imga, imgb, imgc;	// ���� IMAGE ����

	if (flag == 1)
	{
		maxlenth = MAXLENGTH / 4;
		maxwidth = MAXWIDTH / 4;
		loadimage(&img, _T("mazefile\\mazeeasys.png"));	// ��ȡͼƬ�� img ������
		loadimage(&imga, _T("mazefile\\youriteme.png"));
		loadimage(&imgb, _T("mazefile\\walle.png"));
		loadimage(&imgc, _T("mazefile\\roade.png"));
		pl = 30;
	}
	else if (flag == 2)
	{
		maxlenth = MAXLENGTH;
		maxwidth = MAXWIDTH;
		loadimage(&img, _T("mazefile\\mazehards.png"));	// ��ȡͼƬ�� img ������
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
	IMAGE img;	// ���� IMAGE ����
	MOUSEMSG m;
	
	if (flag == 1)
	{
		loadimage(&img, _T("mazefile\\mazeeasyp.png"));	// ��ȡͼƬ�� img ������
	}
	else if (flag == 2)
	{
		loadimage(&img, _T("mazefile\\mazehardp.png"));	// ��ȡͼƬ�� img ������
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











