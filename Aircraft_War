#include <time.h>
#include <conio.h>
#include <windows.h>

#define MAX_X	60
#define MAX_Y	35

#define LIFE	6
#define BULLET	500

typedef struct _aircraft_information{
	int score;
	int speed;
	int bpspeed;
	int life;
	int bullet;
	struct _head_position{
		int x;
		int y;
	} hep;
} aci;

typedef struct _position{
	int x;
	int y;
} *pos;

#define LIST_TYPE pos
#include "list.h"

aci *aci_init();
int map_init();
void init_window();
void refresh_score(aci *aci);
void refresh_life(aci *aci);
void aci_dir(aci *aci);
void aci_move(aci *aci, list *bp, list *ap);
void bp_move(aci *aci, list *bp, list *ap);
void ap_move(list *ap);
void sp_move(list *sp, list *ap);
void gotoxy(int x,int y);
void help();

int main()
{
	init_window();
	srand((unsigned) time(NULL));
	map_init();
	help();
	list *bp = list_init();
	list *ap = list_init();
	list *sp = list_init();
	aci *aci = aci_init();
	gotoxy(MAX_X+4,9);
	printf("Bullets:");
	refresh_score(aci);
	refresh_life(aci);
	int xs = aci->bpspeed;
	int last_score = 0;
	while("Enjoy :)")
	{
		aci_move(aci,bp, ap);
		bp_move(aci, bp, ap);
		xs--;
		if(!xs)
			ap_move(ap);
		if(xs<=0)xs = aci->bpspeed;
		if(last_score != aci->score)
		{
			refresh_score(aci);
			last_score = aci->score;
		}
		sp_move(sp, ap);
		if(aci->score>=999)
		{
			gotoxy(MAX_X/2-5,MAX_Y/2);
			printf("You Win!");
			Sleep(3000);
			break;
		}
		Sleep(aci->speed);
	}
	getch();
	return 0;
}

void init_window()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); 

	//设置窗口大小
	SMALL_RECT rc = {0,0,80-1,39-1};
	SetConsoleWindowInfo(hOut, TRUE,&rc);

	// 设置缓冲区大小
	COORD size = {80, 39};
	SetConsoleScreenBufferSize(hOut,size);

	//设置字体
	CONSOLE_FONT_INFOEX info = {0};
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = 24;
	info.FontWeight = FW_NORMAL;
	wcscpy(info.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &info);

	//最大化
	HWND hWnd = GetConsoleWindow();
	PostMessage(hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);

	//隐藏光标
	CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
	SetConsoleCursorInfo(hOut, &cursor_info);

	//设置窗口名称
	SetConsoleTitle("Aircraft War");
}

aci *aci_init()
{
	aci *paci = (aci*)malloc(sizeof(aci));
	paci->score = 0;
	paci->speed = 5;		//整体速度
	paci->bpspeed = 3;		//敌机速度
	paci->life = LIFE;		//生命值
	paci->bullet = BULLET;	//子弹数
	paci->hep.x = MAX_X/2;		//起始位置
	paci->hep.y = MAX_Y-3;
	return paci;
}

//初始化地图
int map_init()
{
	for(int i=0;i<MAX_Y+2;i++)
	{
		for(int j=0;j<MAX_X/2+2;j++)
		{
			if(i==0)
			{
				if(j==0)printf("*-");
				else if(j==MAX_X/2+1)printf("-*");
				else printf("--");
			}
			else if(i==MAX_Y+1)
			{
				if(j==0)printf("*-");
				else if(j==MAX_X/2+1)printf("-*");
				else printf("--");
			}
			else
			{
				if(j==0) printf("| ");
				else if(j==MAX_X/2+1) printf(" |");
				else printf("  ");
			}
		}
		printf("\n");
	}
	gotoxy(MAX_X+4,3);
	printf("###############");
	gotoxy(MAX_X+4,4);
	printf("#  Score:     #");
	gotoxy(MAX_X+4,5);
	printf("###############");
	return 1;
}

void refresh_score(aci *aci)
{
	gotoxy(MAX_X+13,4);
	printf("%3d",aci->score);
}

void refresh_life(aci *aci)
{
	gotoxy(MAX_X+4,7);
	printf("HP:");
	for(int i=0;i<LIFE;i++)
		printf("  ");
	gotoxy(MAX_X+7,7);
	for(int i=0;i<aci->life;i++)
		printf("[]");
}

int reloadflag;
void aci_move(aci *aci, list *bp, list *ap)
{
	if(kbhit())
	{
		gotoxy(aci->hep.x,aci->hep.y);
		printf("  ");
		gotoxy(aci->hep.x-1,aci->hep.y+1);
		printf("    ");
		if(GetKeyState(87)<0 && aci->hep.y>=3)
			aci->hep.y--;
		if(GetKeyState(83)<0 && aci->hep.y<=MAX_Y-2)
			aci->hep.y++;
		if(GetKeyState(65)<0 && aci->hep.x>=3)
			aci->hep.x--;
		if(GetKeyState(68)<0 && aci->hep.x<=MAX_X-1)
			aci->hep.x++;
		//if(GetKeyState(82)<0)
		reloadflag = 1;
		if(GetKeyState(VK_SPACE)<0 && aci->bullet>=0)
		{
			reloadflag = 0;
			if(aci->bullet == 0)
				goto endkbhit;
			pos p = (pos)malloc(sizeof(struct _position));
			p->x = aci->hep.x;
			p->y = aci->hep.y-1;
			list_push_back(bp,p);
			aci->bullet--;
			gotoxy(MAX_X+12,9);
			printf("%3d",aci->bullet);
		}
	}
endkbhit:
	if(reloadflag)
	{
		if(aci->bullet>=BULLET)
			reloadflag = 0;
		else
			aci->bullet++;
		gotoxy(MAX_X+12,9);
		printf("%3d",aci->bullet);
	}
	pos atmp;
	for(int j=0;j<ap->size;j++)
	{
		atmp = list_var(ap,j);
		if((atmp->x == aci->hep.x
					||atmp->x == aci->hep.x+1
					||atmp->x == aci->hep.x-1)
				&& atmp->y == aci->hep.y)
		{
			list_erase(ap,1,j);
			gotoxy(atmp->x,atmp->y);
			printf("  ");
			aci->life--;
			refresh_life(aci);
			if(aci->life == 0)
			{
				gotoxy(MAX_X/2-5,MAX_Y/2);
				printf("You Lose!");
				Sleep(3000);
				exit(0);
			}
		}
	}
	gotoxy(aci->hep.x,aci->hep.y);
	printf("^^");
	gotoxy(aci->hep.x-1,aci->hep.y+1);
	printf("=##=");
}

void bp_move(aci *aci, list *bp, list *ap)
{
	pos tmp;
	if(bp->size>=55)
		list_erase(bp,20,0);
	for(int i=0;i<bp->size;i++)
	{
		tmp = list_var(bp,i);
		gotoxy(tmp->x,tmp->y);
		printf("  ");
		if(tmp->y <= 1)
			continue;
		tmp->y--;
		gotoxy(tmp->x,tmp->y);
		printf("||");
		pos atmp;
		for(int j=0;j<ap->size;j++)
		{
			atmp = list_var(ap,j);
			if((atmp->x == tmp->x
						||atmp->x == tmp->x+1
						||atmp->x == tmp->x-1)
					&& atmp->y == tmp->y)
			{
				list_erase(ap,1,j);
				list_erase(bp,1,i);
				gotoxy(tmp->x,tmp->y);
				printf("  ");
				gotoxy(atmp->x,atmp->y);
				printf("  ");
				aci->score++;
				break;
			}
		}
	}
}

void ap_move(list *ap)
{
	static int ap_f = 1;
	if(ap->size>=40)
		list_erase(ap,19,0);
	ap_f--;
	if(!ap_f)
	{
		pos p = (pos)malloc(sizeof(struct _position));
		p->x = rand()%(MAX_X-1)+3;
		p->y = 1;
		list_push_back(ap,p);
	}
	if(ap_f<0)ap_f = 1;
	pos tmp;
	for(int i=0;i<ap->size;i++)
	{
		tmp = list_var(ap,i);
		gotoxy(tmp->x,tmp->y);
		printf("  ");
		if(tmp->y >= MAX_Y-1)
		{
			tmp->y = MAX_Y+3;
			continue;
		}
		tmp->y++;
		gotoxy(tmp->x,tmp->y);
		printf("##");
	}
}

void sp_move(list *sp, list *ap)
{
	if(sp->size>=70)
		list_erase(sp,30,0);
	pos p = (pos)malloc(sizeof(struct _position));
	p->x = rand()%(MAX_X-1)+3;
	p->y = 1;
	list_push_back(sp,p);
	pos tmp;
	pos atmp;
	for(int i=0;i<sp->size;i++)
	{
		tmp = list_var(sp,i);
		for(int j=0;j<ap->size;j++)
		{
			atmp = list_var(ap,j);
			if((atmp->x == tmp->x && atmp->y == tmp->y)
					||(atmp->x+1 == tmp->x && atmp->y == tmp->y))
				goto CON;
		}
		gotoxy(tmp->x,tmp->y);
		printf(" ");
		if(tmp->y >= MAX_Y-1)
			CON:continue;
		tmp->y++;
		gotoxy(tmp->x,tmp->y);
		for(int j=0;j<ap->size;j++)
		{
			atmp = list_var(ap,j);
			if((atmp->x == tmp->x && atmp->y == tmp->y)
					||(atmp->x+1 == tmp->x && atmp->y == tmp->y))
				goto CON;
		}
		printf(".");
	}
}

void gotoxy(int x,int y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}

void help()
{
	gotoxy(MAX_X+4,11);
	printf("Control key:");
	gotoxy(MAX_X+9,12);
	printf("w");
	gotoxy(MAX_X+7,13);
	printf("a s d");
	gotoxy(MAX_X+4,15);
	printf("Fire:");
	gotoxy(MAX_X+7,16);
	printf("Space key");
}
