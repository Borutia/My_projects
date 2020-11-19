#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>

using namespace std;

int Iam[10][10];
int comp[10][10];
COORD coord;
HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
enum keys {ESC=27, LEFT=75, RIGHT=77, UP=72, DOWN=80, SH=254};
enum line{Vertical = 179, Gorizontal = 196, Cross = 197, LU=218, RU=191, LD=192, RD=217, TL=195, TR=180, TU=194, TD=193};


using namespace std;

//заполняет массивы нулями
void hz()
{
	for (int i=0; i<10; i++)
	{
		for (int j=0; j<10; j++)
		{
			Iam[i][j]=0;
			comp[i][j]=0;
		}
	}
}

//прорисовка сетки
void pole(int who=0)
{
	int row=21, col=21;
	for(int i=0; i<row; i++)
	{
		if(who==1)
		{
			coord.Y=i;
			SetConsoleCursorPosition(H, coord);
		}
		for(int j=0; j<col; j++)
		{
			if(i==0 && j==0)
			{
				cout<<char(LU);
			}
			else if(i==0 && j==col-1)
			{
				cout<<char(RU);
			}
			else if(i==row-1&&j==0)
			{
				cout<<char(LD);
			}
			else if(i==row-1 && j==col-1)
			{
				cout<<char(RD);
			}
			else if(j==0 && i%2==0)
			{
				cout<<char(TL);
			}
			else if(j==col-1 && i%2==0)
			{
				cout<<char(TR);
			}
			else if(i==0 && j%2==0)
			{
				cout<<char(TU);
			}
			else if(i==row-1 && j%2==0)
			{
				cout<<char(TD);
			}
			else if(i%2==0 && j%2==0)
			{
				cout<<char(Cross);
			}
			else if(i%2!=0 && j%2==0)
			{
				cout<<char(Vertical)<<' ';
			}
			else if(i%2==0 && j%2!=0)
			{
				cout<<char(Gorizontal);
			}
			
		}
		cout<<"\n";
	}
}

//вывод моей сетки
void printIam()
{
	pole();
	for (int i=0; i<10; i++)
	{
		for (int j=0; j<10; j++)
		{
			if(Iam[i][j]==1)
			{
				coord.X=j*2+1;
				coord.Y=i*2+1;
				SetConsoleCursorPosition(H,coord);
				cout<<char(SH);
			}
			else if(Iam[i][j]==3)
			{	coord.X=j*2+1;
				coord.Y=i*2+1;
				SetConsoleCursorPosition(H,coord);
				cout<<'*';
			}
			else if(Iam[i][j]==4)
			{
				coord.X=j*2+1;
				coord.Y=i*2+1;
				SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_INTENSITY);
				SetConsoleCursorPosition(H,coord);
				cout<<char(SH);
				SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		}
		
	}
}	

//вывод сетки компа
void printcomp(int cheat=0)
{
	coord.X=30;
	coord.Y=0;
	SetConsoleCursorPosition(H,coord);
	pole(1);

	for (int i=0; i<10; i++)
	{
		for (int j=0; j<10; j++)
		{
			if(cheat==1)
			{
				if(comp[i][j]==1)
				{
					coord.X=(j*2+1)+30;
					coord.Y=(i*2+1);
					SetConsoleCursorPosition(H,coord);
					cout<<char(SH);
				}
				else if(comp[i][j]==3)
				{	coord.X=(j*2+1)+30;
					coord.Y=(i*2+1);
					SetConsoleCursorPosition(H,coord);
					cout<<'*';
				}
				else if(comp[i][j]==4)
				{
					coord.X=(j*2+1)+30;
					coord.Y=(i*2+1);
					SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_INTENSITY);
					SetConsoleCursorPosition(H,coord);
					cout<<char(SH);
					SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				}
			}
			else
			{
				if(comp[i][j]==3)
				{	coord.X=(j*2+1)+30;
					coord.Y=(i*2+1);
					SetConsoleCursorPosition(H,coord);
					cout<<'*';
				}
				else if(comp[i][j]==4)
				{
					coord.X=(j*2+1)+30;
					coord.Y=(i*2+1);
					SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_INTENSITY);
					SetConsoleCursorPosition(H,coord);
					cout<<char(SH);
					SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				}
			}	
		}
	}
}


//обводит поставленные и убитые корабли по горизонтали
void vokryggor(int x, int y, int tip, int who)
{
	if(who==1)
	{
		x=x/2;
		y=y/2;
	}
	//0|0
	if(x==0 && y==0)
	{
		for (int i=0; i<tip; i++)
		{
			//gor
			if(who==3)
			{
				Iam[x+1][y+i]=3;
			}
			else if(who==2)
			{
				comp[x+1][y+i]=3;
			}
			else if(who==1)
			{
				Iam[x+1][y+i]=2;
			}
			else if(who==0)
			{
				comp[x+1][y+i]=2;
				
			}
		}
		for (int i=0; i<2; i++)
		{
			//ver
			if(who==3)
			{
				Iam[x+i][y+tip]=3;
			}
			else if(who==2)
			{
				comp[x+i][y+tip]=3;
			}
			else if(who==1)
			{
				Iam[x+i][y+tip]=2;
			}
			else if(who==0)
			{
				comp[x+i][y+tip]=2;
				
			}
		}
	}
	//9|0
	else if(x==9 && y==0)
	{
			//ver
		if(who==3)
		{
			Iam[x-1][y+tip]=3;
			Iam[x][y+tip]=3;
		}
		else if(who==2)
		{
			comp[x-1][y+tip]=3;
			comp[x][y+tip]=3;
		}
		else if(who==1)
		{
			Iam[x-1][y+tip]=2;
			Iam[x][y+tip]=2;
		}
		else if(who==0)
		{
			comp[x-1][y+tip]=2;
			comp[x][y+tip]=2;
			
		}
		for (int i=0; i<tip; i++)
		{
			//gor
			if(who==3)
			{
				Iam[x-1][y+i]=3;
			}
			else if(who==2)
			{
				comp[x-1][y+i]=3;
			}
			else if(who==1)
			{
				Iam[x-1][y+i]=2;
			}
			else if(who==0)
			{
				comp[x-1][y+i]=2;
				
			}
		}
	}
	//9|9
	else if(x==9 && y==9-tip+1)
	{
		for (int i=0; i<2; i++)
		{
			//ver
			if(who==3)
			{
				Iam[x-i][y-1]=3;
			}
			else if(who==2)
			{
				comp[x-i][y-1]=3;
			}
			else if(who==1)
			{
				Iam[x-i][y-1]=2;
			}
			else if(who==0)
			{
				comp[x-i][y-1]=2;
				
			}
		}
		for (int i=0; i<tip; i++)
		{
			//gor
			if(who==3)
			{
				Iam[x-1][y+i]=3;
			}
			else if(who==2)
			{
				comp[x-1][y+i]=3;
			}
			else if(who==1)
			{
				Iam[x-1][y+i]=2;
			}
			else if(who==0)
			{
				comp[x-1][y+i]=2;
				
			}
		}
	}
	//0|9
	else if(x==0 && y==9-tip+1)
	{
		for (int i=0; i<2; i++)
		{
			//ver
			if(who==3)
			{
				Iam[x+i][y-1]=3;
			}
			else if(who==2)
			{
				comp[x+i][y-1]=3;
			}
			else if(who==1)
			{
				Iam[x+i][y-1]=2;
			}
			else if(who==0)
			{
				comp[x+i][y-1]=2;
				
			}
		}
		for (int i=0; i<tip; i++)
		{
			//gor
			if(who==3)
			{
				Iam[x+1][y+i]=3;
			}
			else if(who==2)
			{
				comp[x+1][y+i]=3;
			}
			else if(who==1)
			{
				Iam[x+1][y+i]=2;
			}
			else if(who==0)
			{
				comp[x+1][y+i]=2;
				
			}
		}
	}
	//verx
	else if(x==0 && y!=0)
	{
		for (int i=0; i<2; i++)
		{
			//ver
			if(who==3)
			{
				Iam[x+i][y-1]=3;
				Iam[x+i][y+tip]=3;
			}
			else if(who==2)
			{
				comp[x+i][y-1]=3;
				comp[x+i][y+tip]=3;
			}
			else if(who==1)
			{
				Iam[x+i][y-1]=2;
				Iam[x+i][y+tip]=2;
			}
			else if(who==0)
			{
				comp[x+i][y-1]=2;
				comp[x+i][y+tip]=2;
				
			}
		}
		for (int i=0; i<tip; i++)
		{
			//gor
			if(who==3)
			{
				Iam[x+1][y+i]=3;
			}
			else if(who==2)
			{
				comp[x+1][y+i]=3;
			}
			else if(who==1)
			{
				Iam[x+1][y+i]=2;
			}
			else if(who==0)
			{
				comp[x+1][y+i]=2;
			}
		}
	}
	//levo
	else if(x!=0 && y==0)
	{
		for (int i=-1; i<2; i++)
		{
			//ver
			if(who==3)
			{
				Iam[x+i][y+tip]=3;
			}
			else if(who==2)
			{
				comp[x+i][y+tip]=3;
			}
			else if(who==1)
			{
				Iam[x+i][y+tip]=2;
			}
			else if(who==0)
			{
				comp[x+i][y+tip]=2;
			}
		}
		for (int i=0; i<tip; i++)
		{
			//gor
			if(who==3)
			{
				Iam[x+1][y+i]=3;
				Iam[x-1][y+i]=3;
			}
			else if(who==2)
			{
				comp[x+1][y+i]=3;
				comp[x-1][y+i]=3;
			}
			else if(who==1)
			{
				Iam[x+1][y+i]=2;
				Iam[x-1][y+i]=2;
			}
			else if(who==0)
			{
				comp[x+1][y+i]=2;
				comp[x-1][y+i]=2;
			}
		}
	}
	
	//niz
	else if(x==9 && y!=9)
	{
		for (int i=0; i>-2; i--)
		{
			//ver
			if(who==3)
			{
				Iam[x+i][y-1]=3;
				Iam[x+i][y+tip]=3;
			}
			else if(who==2)
			{
				comp[x+i][y-1]=3;
				comp[x+i][y+tip]=3;
			}
			else if(who==1)
			{
				Iam[x+i][y-1]=2;
				Iam[x+i][y+tip]=2;
			}
			else if(who==0)
			{
				comp[x+i][y-1]=2;
				comp[x+i][y+tip]=2;
			}
		}
		for (int i=0; i<tip; i++)
		{
			//gor
			if(who==3)
			{
				Iam[x-1][y+i]=3;
			}
			else if(who==2)
			{
				comp[x-1][y+i]=3;
			}
			else if(who==1)
			{
				Iam[x-1][y+i]=2;
			}
			else if(who==0)
			{
				comp[x-1][y+i]=2;
			}
		}
	}
	
	//pravo
	else if(x!=0 && y==9-tip+1)
	{
		for (int i=-1; i<2; i++)
		{
			//ver
			if(who==3)
			{
				Iam[x+i][y-1]=3;
			}
			else if(who==2)
			{
				comp[x+i][y-1]=3;
			}
			else if(who==1)
			{
				Iam[x+i][y-1]=2;
			}
			else if(who==0)
			{
				comp[x+i][y-1]=2;
			}
		}
		for (int i=0; i<tip; i++)
		{
			//gor
			if(who==3)
			{
				Iam[x+1][y+i]=3;
				Iam[x-1][y+i]=3;
			}
			else if(who==2)
			{
				comp[x+1][y+i]=3;
				comp[x-1][y+i]=3;
			}
			else if(who==1)
			{
				Iam[x+1][y+i]=2;
				Iam[x-1][y+i]=2;
			}
			else if(who==0)
			{
				comp[x+1][y+i]=2;
				comp[x-1][y+i]=2;
			}
		}
	}
	
	//pole
	else if(x!=0 && y!=0)
	{
		for (int i=-1; i<2; i++)
		{
			//ver
			if(who==3)
			{
				Iam[x+i][y-1]=3;
				Iam[x+i][y+tip]=3;
			}
			else if(who==2)
			{
				comp[x+i][y-1]=3;
				comp[x+i][y+tip]=3;
			}
			else if(who==1)
			{
				Iam[x+i][y-1]=2;
				Iam[x+i][y+tip]=2;
			}
			else if(who==0)
			{
				comp[x+i][y-1]=2;
				comp[x+i][y+tip]=2;
			}
		}
		for (int i=0; i<tip; i++)
		{
			//gor
			if(who==3)
			{
				Iam[x+1][y+i]=3;
				Iam[x-1][y+i]=3;
			}
			else if(who==2)
			{
				comp[x+1][y+i]=3;
				comp[x-1][y+i]=3;
			}
			else if(who==1)
			{
				Iam[x+1][y+i]=2;
				Iam[x-1][y+i]=2;
			}
			else if(who==0)
			{
				comp[x+1][y+i]=2;
				comp[x-1][y+i]=2;
			}
		}
	}
}

//обводит поставленные и убитые корабли по вертикали
void vokrygver(int x, int y, int tip, int who)
{
	if(who==1)
	{
		x=x/2;
		y=y/2;
	}
	//0|0
	if(x==0 && y==0)
	{
		for (int i=0; i<2; i++)
		{
			//gor
			if(who==3)
			{
				Iam[x+tip][y+i]=3;
			}
			if(who==2)
			{
				comp[x+tip][y+i]=3;
			}
			if(who==1)
			{
				Iam[x+tip][y+i]=2;
			}
			if (who==0)
			{
				comp[x+tip][y+i]=2;
			}
		}
		for (int i=0; i<tip; i++)
		{
			//ver
			if(who==3)
			{
				Iam[x+i][y+1]=3;
			}
			if(who==2)
			{
				comp[x+i][y+1]=3;
			}
			if(who==1)
			{
				Iam[x+i][y+1]=2;
			}
			if (who==0)
			{
				comp[x+i][y+1]=2;
			}
		}
	}
	//9|0
	else if(x==9-tip+1 && y==0)
	{
			//ver
		for (int i=0; i<tip; i++)
		{
			//ver
			if(who==3)
			{
				Iam[x+i][y+1]=3;
			}
			if(who==2)
			{
				comp[x+i][y+1]=3;
			}
			if(who==1)
			{
				Iam[x+i][y+1]=2;
			}
			if (who==0)
			{
				comp[x+i][y+1]=2;
			}
		}
		for (int i=0; i<2; i++)
		{
			//gor
			if(who==3)
			{
				Iam[x-1][y+i]=3;
			}
			if(who==2)
			{
				comp[x-1][y+i]=3;
			}
			if(who==1)
			{
				Iam[x-1][y+i]=2;
			}
			if (who==0)
			{
				comp[x-1][y+i]=2;
			}
		}
	}
	//9|9
	else if(x==9-tip+1 && y==9)
	{
		for (int i=0; i<tip; i++)
		{
			//ver
			if(who==3)
			{
				Iam[x+i][y-1]=3;
			}
			if(who==2)
			{
				comp[x+i][y-1]=3;
			}
			if(who==1)
			{
				Iam[x+i][y-1]=2;
			}
			if (who==0)
			{
				comp[x+i][y-1]=2;
			}
		}
		for (int i=0; i<2; i++)
		{
			//gor
			if(who==3)
			{
				Iam[x-1][y-i]=3;
			}
			if(who==2)
			{
				comp[x-1][y-i]=3;
			}
			if(who==1)
			{
				Iam[x-1][y-i]=2;
			}
			if (who==0)
			{
				comp[x-1][y-i]=2;
			}
		}
	}
	//0|9
	else if(x==0 && y==9)
	{
		for (int i=0; i<tip; i++)
		{
			//ver
			if(who==3)
			{
				Iam[x+i][y-1]=3;
			}
			if(who==2)
			{
				comp[x+i][y-1]=3;
			}
			if(who==1)
			{
				Iam[x+i][y-1]=2;
			}
			if (who==0)
			{
				comp[x+i][y-1]=2;
			}
		}
		for (int i=0; i<2; i++)
		{
			//gor
			if(who==3)
			{
				Iam[x+tip][y-i]=3;
			}
			if(who==2)
			{
				comp[x+tip][y-i]=3;
			}
			if(who==1)
			{
				Iam[x+tip][y-i]=2;
			}
			if (who==0)
			{
				comp[x+tip][y-i]=2;
			}
		}
	}
	//verx
	else if(x==0 && y!=0)
	{
		for (int i=0; i<tip; i++)
		{
			//ver
			if(who==3)
			{
				Iam[x+i][y-1]=3;
				Iam[x+i][y+1]=3;
			}
			if(who==2)
			{
				comp[x+i][y-1]=3;
				comp[x+i][y+1]=3;
			}
			if(who==1)
			{
				Iam[x+i][y-1]=2;
				Iam[x+i][y+1]=2;
			}
			if (who==0)
			{
				comp[x+i][y-1]=2;
				comp[x+i][y+1]=2;
			}
		}
		for (int i=-1; i<2; i++)
		{
			//gor
			if(who==3)
			{
				Iam[x+tip][y+i]=3;
			}
			if(who==2)
			{
				comp[x+tip][y+i]=3;
			}
			if(who==1)
			{
				Iam[x+tip][y+i]=2;
			}
			if (who==0)
			{
				comp[x+tip][y+i]=2;
			}
		}
	}
	//levo
	else if(x!=0 && y==0)
	{
		for (int i=0; i<tip; i++)
		{
			//ver
			if(who==3)
			{
				Iam[x+i][y+1]=3;
			}
			if(who==2)
			{
				comp[x+i][y+1]=3;
			}
			if(who==1)
			{
				Iam[x+i][y+1]=2;
			}
			if (who==0)
			{
				comp[x+i][y+1]=2;
			}
		}
		for (int i=0; i<2; i++)
		{
			//gor
			if(who==3)
			{
				Iam[x-1][y+i]=3;
				Iam[x+tip][y+i]=3;
			}
			if(who==2)
			{
				comp[x-1][y+i]=3;
				comp[x+tip][y+i]=3;
			}
			if(who==1)
			{
				Iam[x-1][y+i]=2;
				Iam[x+tip][y+i]=2;
			}
			if (who==0)
			{
				comp[x-1][y+i]=2;
				comp[x+tip][y+i]=2;
			}
		}
	}
	
	//niz
	else if(x==9-tip+1 && y!=9)
	{
		for (int i=0; i<tip; i++)
		{
			//ver
			if(who==3)
			{
				Iam[x+i][y-1]=3;
				Iam[x+i][y+1]=3;
			}
			if(who==2)
			{
				comp[x+i][y-1]=3;
				comp[x+i][y+1]=3;
			}
			if(who==1)
			{
				Iam[x+i][y-1]=2;
				Iam[x+i][y+1]=2;
			}
			if (who==0)
			{
				comp[x+i][y-1]=2;
				comp[x+i][y+1]=2;
			}
		}
		for (int i=-1; i<2; i++)
		{
			//gor
			if(who==3)
			{
				Iam[x-1][y+i]=3;
			}
			if(who==2)
			{
				comp[x-1][y+i]=3;
			}
			if(who==1)
			{
				Iam[x-1][y+i]=2;
			}
			if (who==0)
			{
				comp[x-1][y+i]=2;
			}
		}
	}
	
	//pravo
	else if(x!=0 && y==9)
	{
		for (int i=0; i<tip; i++)
		{
			//ver
			if(who==3)
			{
				Iam[x+i][y-1]=3;
			}
			if(who==2)
			{
				comp[x+i][y-1]=3;
			}
			if(who==1)
			{
				Iam[x+i][y-1]=2;
			}
			if (who==0)
			{
				comp[x+i][y-1]=2;
			}
		}
		for (int i=0; i<2; i++)
		{
			//gor
			if(who==3)
			{
				Iam[x-1][y-i]=3;
				Iam[x+tip][y-i]=3;
			}
			if(who==2)
			{
				comp[x-1][y-i]=3;
				comp[x+tip][y-i]=3;
			}
			if(who==1)
			{
				Iam[x-1][y-i]=2;
				Iam[x+tip][y-i]=2;
			}
			if (who==0)
			{
				comp[x-1][y-i]=2;
				comp[x+tip][y-i]=2;
			}
		}
	}
	
	//pole
	else if(x!=0 && y!=0)
	{
		for (int i=0; i<tip; i++)
		{
			//ver
			if(who==3)
			{
				Iam[x+i][y-1]=3;
				Iam[x+i][y+1]=3;
			}
			if(who==2)
			{
				comp[x+i][y-1]=3;
				comp[x+i][y+1]=3;
			}
			if(who==1)
			{
				Iam[x+i][y-1]=2;
				Iam[x+i][y+1]=2;
			}
			if (who==0)
			{
				comp[x+i][y-1]=2;
				comp[x+i][y+1]=2;
			}
		}
		for (int i=-1; i<2; i++)
		{
			//gor
			if(who==3)
			{
				Iam[x-1][y+i]=3;
				Iam[x+tip][y+i]=3;
			}
			if(who==2)
			{
				comp[x-1][y+i]=3;
				comp[x+tip][y+i]=3;
			}
			if(who==1)
			{
				Iam[x-1][y+i]=2;
				Iam[x+tip][y+i]=2;
			}
			if (who==0)
			{
				comp[x-1][y+i]=2;
				comp[x+tip][y+i]=2;
			}
		}
	}
}


//ф-ция обводит убитые корабли
void obvodka(int x, int y, int line) 
{
	//обводим корабли компа
	if (line%2 == 1)	
	{
			//четырехпалубный gor
		if(y==0)
		{
			if(comp[x][y]==4 && comp[x][y+1]==4 && comp[x][y+2]==4 && comp[x][y+3]==4)
			{
				if(comp[x][y+4]!=4 && comp[x][y+4]!=1)
				{
					vokryggor(x,y,4,2);
					
				}
			}
		}
		else if(y==1)
		{
			if(comp[x][y]==4 && comp[x][y-1]==4 && comp[x][y+1]==4 && comp[x][y+2]==4)
			{
				if(comp[x][y+3]!=4 && comp[x][y+3]!=1)
				{
					vokryggor(x,y-1,4,2);
					
				}
			}
		}
		else if(y==2)
		{
			if(comp[x][y]==4 && comp[x][y-1]==4 && comp[x][y-2]==4 && comp[x][y+1]==4)
			{
				if(comp[x][y+2]!=4 && comp[x][y+2]!=1)
				{
					vokryggor(x,y-2,4,2);
					
				}
			}
		}
		else if(y==9)
		{
			if(comp[x][y]==4 && comp[x][y-1]==4 && comp[x][y-2]==4 && comp[x][y-3]==4)
			{
				if(comp[x][y-4]!=4 && comp[x][y-4]!=1)
				{
					vokryggor(x,y-3,4,2);
					
				}
			}
		}
		else if(y==8)
		{
			if(comp[x][y]==4 && comp[x][y-1]==4 && comp[x][y-2]==4 && comp[x][y+1]==4)
			{
				if(comp[x][y-3]!=4 && comp[x][y-3]!=1)
				{
					vokryggor(x,y-2,4,2);
					
				}
			}
		}
		else if(y==7)
		{
			if(comp[x][y]==4 && comp[x][y-1]==4 && comp[x][y+1]==4 && comp[x][y+2]==4)
			{
				if(comp[x][y-2]!=4 && comp[x][y-2]!=1)
				{
					vokryggor(x,y-1,4,2);
					
				}
			}
		}
		else
		{
			if(comp[x][y]==4 && comp[x][y+1]==4 && comp[x][y+2]==4 && comp[x][y+3]==4)
			{
				if(comp[x][y-1]!=4 && comp[x][y+4]!=4 && comp[x][y-1]!=1 && comp[x][y+4]!=1)
				{
					vokryggor(x,y,4,2);
					
				}
			}
			else if(comp[x][y]==4 && comp[x][y-1]==4 && comp[x][y-2]==4 && comp[x][y-3]==4)
			{
				if(comp[x][y+1]!=4 && comp[x][y-4]!=4 && comp[x][y+1]!=1 && comp[x][y-4]!=1)
				{
					vokryggor(x,y-3,4,2);
					
				}
			}
			else if(comp[x][y]==4 && comp[x][y-1]==4 && comp[x][y+1]==4 && comp[x][y+2]==4)
			{
				if(comp[x][y-2]!=4 && comp[x][y+3]!=4 && comp[x][y-2]!=1 && comp[x][y+3]!=1)
				{
					vokryggor(x,y-1,4,2);
					
				}
			}
			else if(comp[x][y]==4 && comp[x][y-1]==4 && comp[x][y-2]==4 && comp[x][y+1]==4)
			{
				if(comp[x][y-3]!=4 && comp[x][y+2]!=4 && comp[x][y-3]!=1 && comp[x][y+2]!=1)
				{
					vokryggor(x,y-2,4,2);
					
				}
			}
			
		}
		//ver
		if(x==0)
		{
			if(comp[x][y]==4 && comp[x+1][y]==4 && comp[x+2][y]==4 && comp[x+3][y]==4)
			{
				if(comp[x+4][y]!=4 && comp[x+4][y]!=1)
				{
					vokrygver(x,y,4,2);
					
				}
			}
		}
		else if(x==1)
		{
			if(comp[x][y]==4 && comp[x-1][y]==4 && comp[x+1][y]==4 && comp[x+2][y]==4)
			{
				if(comp[x+3][y]!=4 && comp[x+3][y]!=1)
				{
					vokrygver(x-1,y,4,2);
					
				}
			}
		}
		else if(x==2)
		{
			if(comp[x][y]==4 && comp[x-1][y]==4 && comp[x-2][y]==4 && comp[x+1][y]==4)
			{
				if(comp[x+2][y]!=4 && comp[x+2][y]!=1)
				{
					vokrygver(x-2,y,4,2);
					
				}
			}
		}
		else if(x==9)
		{
			if(comp[x][y]==4 && comp[x-1][y]==4 && comp[x-2][y]==4 && comp[x-3][y]==4)
			{
				if(comp[x-4][y]!=4 && comp[x-4][y]!=1)
				{
					vokrygver(x-3,y,4,2);
					
				}
			}
		}
		else if(x==8)
		{
			if(comp[x][y]==4 && comp[x-1][y]==4 && comp[x-2][y]==4 && comp[x+1][y]==4)
			{
				if(comp[x-3][y]!=4 && comp[x-3][y]!=1)
				{
					vokrygver(x-2,y,4,2);
					
				}
			}
		}
		else if(x==7)
		{
			if(comp[x][y]==4 && comp[x-1][y]==4 && comp[x+1][y]==4 && comp[x+2][y]==4)
			{
				if(comp[x-2][y]!=4 && comp[x-2][y]!=1)
				{
					vokrygver(x-1,y,4,2);
					
				}
			}
		}
		else
		{
			if(comp[x][y]==4 && comp[x+1][y]==4 && comp[x+2][y]==4 && comp[x+3][y]==4)
			{
				if(comp[x-1][y]!=4 && comp[x+4][y]!=4 && comp[x-1][y]!=1 && comp[x+4][y]!=1)
				{
					vokrygver(x,y,4,2);
					
				}
			}
			else if(comp[x][y]==4 && comp[x-1][y]==4 && comp[x+1][y]==4 && comp[x+2][y]==4)
			{
				if(comp[x-2][y]!=4 && comp[x+3][y]!=4 && comp[x-2][y]!=1 && comp[x+3][y]!=1)
				{
					vokrygver(x-1,y,4,2);
					
				}
			}
			else if(comp[x][y]==4 && comp[x-1][y]==4 && comp[x-2][y]==4 && comp[x+1][y]==4)
			{
				if(comp[x-3][y]!=4 && comp[x+2][y]!=4 && comp[x-3][y]!=1 && comp[x+2][y]!=1)
				{
					vokrygver(x-2,y,4,2);
					
				}
			}
			else if(comp[x][y]==4 && comp[x-1][y]==4 && comp[x-2][y]==4 && comp[x-3][y]==4)
			{
				if(comp[x+1][y]!=4 && comp[x-4][y]!=4 && comp[x+1][y]!=1 && comp[x-4][y]!=1)
				{
					vokrygver(x-3,y,4,2);
					
				}
			}
		}
		//трехпалубный gor
		if(y==0)
		{
			if(comp[x][y]==4 && comp[x][y+1]==4 && comp[x][y+2]==4)
			{
				if(comp[x][y+3]!=4 && comp[x][y+3]!=1)
				{
					vokryggor(x,y,3,2);
					
				}
			}
		}
		else if(y==9)
		{
			if(comp[x][y]==4 && comp[x][y-1]==4 && comp[x][y-2]==4)
			{
				if(comp[x][y-3]!=4 && comp[x][y-3]!=1)
				{
					vokryggor(x,y-2,3,2);
					
				}
			}
		}
		else if(y==1)
		{
			if(comp[x][y]==4 && comp[x][y-1]==4 && comp[x][y+1]==4)
			{
				if(comp[x][y+2]!=4 && comp[x][y+2]!=1)
				{
					vokryggor(x,y-1,3,2);
					
				}
			}
		}
		else if(y==8)
		{
			if(comp[x][y]==4 && comp[x][y-1]==4 && comp[x][y+1]==4)
			{
				if(comp[x][y-2]!=4 && comp[x][y-2]!=1)
				{
					vokryggor(x,y-1,3,2);
					
				}
			}
		}
		else
		{
			if(comp[x][y]==4 && comp[x][y+1]==4 && comp[x][y+2]==4)
			{
				if(comp[x][y+3]!=4 && comp[x][y-1]!=4 && comp[x][y+3]!=1 && comp[x][y-1]!=1)
				{
					vokryggor(x,y,3,2);
					
				}
			}
			else if(comp[x][y]==4 && comp[x][y-1]==4 && comp[x][y+1]==4)
			{
				if(comp[x][y-2]!=4 && comp[x][y+2]!=4 && comp[x][y-2]!=1 && comp[x][y+2]!=1)
				{
					vokryggor(x,y-1,3,2);
					
				}
			}
			else if(comp[x][y]==4 && comp[x][y-1]==4 && comp[x][y-2]==4)
			{
				if(comp[x][y-3]!=4 && comp[x][y+1]!=4 && comp[x][y-3]!=1 && comp[x][y+1]!=1)
				{
					vokryggor(x,y-2,3,2);
					
				}
			}
		}
		//ver
		if(x==0)
		{
			if(comp[x][y]==4 && comp[x+1][y]==4 && comp[x+2][y]==4)
			{
				if(comp[x+3][y]!=4 && comp[x+3][y]!=1)
				{
					vokrygver(x,y,3,2);
					
				}
			}
		}
		else if(x==9)
		{
			if(comp[x][y]==4 && comp[x-1][y]==4 && comp[x-2][y]==4)
			{
				if(comp[x-3][y]!=4 && comp[x-3][y]!=1)
				{
					vokrygver(x-2,y,3,2);
					
				}
			}
		}
		else if(x==1)
		{
			if(comp[x][y]==4 && comp[x-1][y]==4 && comp[x+1][y]==4)
			{
				if(comp[x+2][y]!=4 && comp[x+2][y]!=1)
				{
					vokrygver(x-1,y,3,2);
					
				}
			}
		}
		else if(x==8)
		{
			if(comp[x][y]==4 && comp[x-1][y]==4 && comp[x+1][y]==4)
			{
				if(comp[x-2][y]!=4 && comp[x-2][y]!=1)
				{
					vokrygver(x-1,y,3,2);
					
				}
			}
		}
		else
		{
			if(comp[x][y]==4 && comp[x+1][y]==4 && comp[x+2][y]==4)
			{
				if(comp[x+3][y]!=4 && comp[x-1][y]!=4 && comp[x+3][y]!=1 && comp[x-1][y]!=1)
				{
					vokrygver(x,y,3,2);
					
				}
			}
			else if(comp[x][y]==4 && comp[x-1][y]==4 && comp[x+1][y]==4)
			{
				if(comp[x-2][y]!=4 && comp[x+2][y]!=4 && comp[x-2][y]!=1 && comp[x+2][y]!=1)
				{
					vokrygver(x-1,y,3,2);
					
				}
			}
			else if(comp[x][y]==4 && comp[x-1][y]==4 && comp[x-2][y]==4)
			{
				if(comp[x-3][y]!=4 && comp[x+1][y]!=4 && comp[x-3][y]!=1 && comp[x+1][y]!=1)
				{
					vokrygver(x-2,y,3,2);
					
				}
			}
		}
		//двухпалубный gor
		if(y==0)
		{
			if(comp[x][y]==4 && comp[x][y+1]==4)
			{
				if(comp[x][y+2]!=4 && comp[x][y+2]!=1)
				{
					vokryggor(x,y,2,2);
					
				}
			}
		}
		else if(y==9)
		{
			if(comp[x][y]==4 && comp[x][y-1]==4)
			{
				if(comp[x][y-2]!=4 && comp[x][y-2]!=1)
				{
					vokryggor(x,y-1,2,2);
					
				}
			}
		}
		else
		{
			if(comp[x][y]==4 && comp[x][y+1]==4)
			{
				if(comp[x][y-1]!=4 && comp[x][y+2]!=4 && comp[x][y-1]!=1 && comp[x][y+2]!=1)
				{
					vokryggor(x,y,2,2);
					
				}
			}
			else if(comp[x][y]==4 && comp[x][y-1]==4)
			{
				if(comp[x][y+1]!=4 && comp[x][y-2]!=4 && comp[x][y+1]!=1 && comp[x][y-2]!=1)
				{
					vokryggor(x,y-1,2,2);
					
				}
			}
		}
		//ver
		if(x==0)
		{
			if(comp[x][y]==4 && comp[x+1][y]==4)
			{
				if(comp[x+2][y]!=4 && comp[x+2][y]!=1)
				{
					vokrygver(x,y,2,2);
					
				}
			}
		}
		else if(x==9)
		{
			if(comp[x][y]==4 && comp[x-1][y]==4)
			{
				if(comp[x-2][y]!=4 && comp[x-2][y]!=1)
				{
					vokrygver(x-1,y,2,2);
					
				}
			}
		}
		else
		{
			if(comp[x][y]==4 && comp[x+1][y]==4)
			{
				if(comp[x+2][y]!=4 && comp[x+2][y]!=1 && comp[x-1][y]!=4 && comp[x-1][y]!=1)
				{
					vokrygver(x,y,2,2);
					
				}
			}
			else if(comp[x][y]==4 && comp[x-1][y]==4)
			{
				if(comp[x-2][y]!=4 && comp[x-2][y]!=1 && comp[x+1][y]!=4 && comp[x+1][y]!=1)
				{
					vokrygver(x-1,y,2,2);
					
				}
			}
		}
		//однопалубный
		if(comp[x][y]==4)
			
		{
			if(x==0 && y==0)
			{
				if(comp[x+1][y]!=1 && comp[x][y+1]!=1 && comp[x+1][y]!=4 && comp[x][y+1]!=4)
				{
					vokryggor(x,y,1,2);
					
				}
			}
			else if(x==9 && y==9)
			{
				if(comp[x-1][y]!=1 && comp[x][y-1]!=1 && comp[x-1][y]!=4 && comp[x][y-1]!=4)
				{
					vokryggor(x,y,1,2);
					
				}
			}
			else if(x==9 && y==0)
			{
				if(comp[x-1][y]!=1 && comp[x][y+1]!=1 && comp[x-1][y]!=4 && comp[x][y+1]!=4)
				{
					vokryggor(x,y,1,2);
					
				}
			}
			else if(x==0 && y==9)
			{
				if(comp[x+1][y]!=1 && comp[x][y-1]!=1 && comp[x+1][y]!=4 && comp[x][y-1]!=4)
				{
					vokryggor(x,y,1,2);
					
				}
			}
			else if(y==0)
			{
				if(comp[x-1][y]!=1 && comp[x][y+1]!=1 && comp[x+1][y]!=1 && comp[x-1][y]!=4 && comp[x][y+1]!=4 && comp[x+1][y]!=4)
				{
					vokryggor(x,y,1,2);
					
				}
			}
			else if(x==0)
			{
				if(comp[x+1][y]!=1 && comp[x][y-1]!=1 && comp[x][y+1]!=1 && comp[x+1][y]!=4 && comp[x][y-1]!=4 && comp[x][y+1]!=4)
				{
					vokryggor(x,y,1,2);
					
				}
			}
			else if(y==9)
			{
				if(comp[x-1][y]!=1 && comp[x][y-1]!=1 && comp[x+1][y]!=1 && comp[x-1][y]!=1 && comp[x][y-1]!=1 && comp[x+1][y]!=1)
				{
					vokryggor(x,y,1,2);
					
				}
			}
			else if(x==9)
			{
				if(comp[x-1][y]!=1 && comp[x][y-1]!=1 && comp[x][y+1]!=1 && comp[x-1][y]!=4 && comp[x][y-1]!=4 && comp[x][y+1]!=4)
				{
					vokryggor(x,y,1,2);
					
				}
			}
			else
			{
				if(comp[x-1][y]!=1 && comp[x+1][y]!=1 && comp[x][y+1]!=1 && comp[x][y-1]!=1 && comp[x-1][y]!=4 && comp[x+1][y]!=4 && comp[x][y+1]!=4 && comp[x][y-1]!=4)
				{
					vokryggor(x,y,1,2);
					
				}
			}
		}
	}
	//обводим мои корабли
	else if (line%2 == 0)
	{
		//четырехпалубный gor
		if(y==0)
		{
			if(Iam[x][y]==4 && Iam[x][y+1]==4 && Iam[x][y+2]==4 && Iam[x][y+3]==4)
			{
				if(Iam[x][y+4]!=4 && Iam[x][y+4]!=1)
				{
					vokryggor(x,y,4,3);
					
				}
			}
		}
		else if(y==1)
		{
			if(Iam[x][y]==4 && Iam[x][y-1]==4 && Iam[x][y+1]==4 && Iam[x][y+2]==4)
			{
				if(Iam[x][y+3]!=4 && Iam[x][y+3]!=1)
				{
					vokryggor(x,y-1,4,3);
					
				}
			}
		}
		else if(y==2)
		{
			if(Iam[x][y]==4 && Iam[x][y-1]==4 && Iam[x][y-2]==4 && Iam[x][y+1]==4)
			{
				if(Iam[x][y+2]!=4 && Iam[x][y+2]!=1)
				{
					vokryggor(x,y-2,4,3);
					
				}
			}
		}
		else if(y==9)
		{
			if(Iam[x][y]==4 && Iam[x][y-1]==4 && Iam[x][y-2]==4 && Iam[x][y-3]==4)
			{
				if(Iam[x][y-4]!=4 && Iam[x][y-4]!=1)
				{
					vokryggor(x,y-3,4,3);
					
				}
			}
		}
		else if(y==8)
		{
			if(Iam[x][y]==4 && Iam[x][y-1]==4 && Iam[x][y-2]==4 && Iam[x][y+1]==4)
			{
				if(Iam[x][y-3]!=4 && Iam[x][y-3]!=1)
				{
					vokryggor(x,y-2,4,3);
					
				}
			}
		}
		else if(y==7)
		{
			if(Iam[x][y]==4 && Iam[x][y-1]==4 && Iam[x][y+1]==4 && Iam[x][y+2]==4)
			{
				if(Iam[x][y-2]!=4 && Iam[x][y-2]!=1)
				{
					vokryggor(x,y-1,4,3);
					
				}
			}
		}
		else
		{
			if(Iam[x][y]==4 && Iam[x][y+1]==4 && Iam[x][y+2]==4 && Iam[x][y+3]==4)
			{
				if(Iam[x][y-1]!=4 && Iam[x][y+4]!=4 && Iam[x][y-1]!=1 && Iam[x][y+4]!=1)
				{
					vokryggor(x,y,4,3);
					
				}
			}
			else if(Iam[x][y]==4 && Iam[x][y-1]==4 && Iam[x][y+1]==4 && Iam[x][y+2]==4)
			{
				if(Iam[x][y-2]!=4 && Iam[x][y+3]!=4 && Iam[x][y-2]!=1 && Iam[x][y+3]!=1)
				{
					vokryggor(x,y-1,4,3);
					
				}
			}
			else if(Iam[x][y]==4 && Iam[x][y-1]==4 && Iam[x][y-2]==4 && Iam[x][y+1]==4)
			{
				if(Iam[x][y-3]!=4 && Iam[x][y+2]!=4 && Iam[x][y-3]!=1 && Iam[x][y+2]!=1)
				{
					vokryggor(x,y-2,4,3);
					
				}
			}
			else if(Iam[x][y]==4 && Iam[x][y-1]==4 && Iam[x][y-2]==4 && Iam[x][y-3]==4)
			{
				if(Iam[x][y+1]!=4 && Iam[x][y-4]!=4 && Iam[x][y+1]!=1 && Iam[x][y-4]!=1)
				{
					vokryggor(x,y-3,4,3);
					
				}
			}
		}
		//ver
		if(x==0)
		{
			if(Iam[x][y]==4 && Iam[x+1][y]==4 && Iam[x+2][y]==4 && Iam[x+3][y]==4)
			{
				if(Iam[x+4][y]!=4 && Iam[x+4][y]!=1)
				{
					vokrygver(x,y,4,3);
					
				}
			}
		}
		else if(x==1)
		{
			if(Iam[x][y]==4 && Iam[x-1][y]==4 && Iam[x+1][y]==4 && Iam[x+2][y]==4)
			{
				if(Iam[x+3][y]!=4 && Iam[x+3][y]!=1)
				{
					vokrygver(x-1,y,4,3);
					
				}
			}
		}
		else if(x==2)
		{
			if(Iam[x][y]==4 && Iam[x-1][y]==4 && Iam[x-2][y]==4 && Iam[x+1][y]==4)
			{
				if(Iam[x+2][y]!=4 && Iam[x+2][y]!=1)
				{
					vokrygver(x-2,y,4,3);
					
				}
			}
		}
		else if(x==9)
		{
			if(Iam[x][y]==4 && Iam[x-1][y]==4 && Iam[x-2][y]==4 && Iam[x-3][y]==4)
			{
				if(Iam[x-4][y]!=4 && Iam[x-4][y]!=1)
				{
					vokrygver(x-3,y,4,3);
					
				}
			}
		}
		else if(x==8)
		{
			if(Iam[x][y]==4 && Iam[x-1][y]==4 && Iam[x-2][y]==4 && Iam[x+1][y]==4)
			{
				if(Iam[x-3][y]!=4 && Iam[x-3][y]!=1)
				{
					vokrygver(x-2,y,4,3);
					
				}
			}
		}
		else if(x==7)
		{
			if(Iam[x][y]==4 && Iam[x-1][y]==4 && Iam[x+1][y]==4 && Iam[x+2][y]==4)
			{
				if(Iam[x-2][y]!=4 && Iam[x-2][y]!=1)
				{
					vokrygver(x-1,y,4,3);
					
				}
			}
		}
		else
		{
			if(Iam[x][y]==4 && Iam[x+1][y]==4 && Iam[x+2][y]==4 && Iam[x+3][y]==4)
			{
				if(Iam[x-1][y]!=4 && Iam[x+4][y]!=4 && Iam[x-1][y]!=1 && Iam[x+4][y]!=1)
				{
					vokrygver(x,y,4,3);
					
				}
			}
			else if(Iam[x][y]==4 && Iam[x-1][y]==4 && Iam[x+1][y]==4 && Iam[x+2][y]==4)
			{
				if(Iam[x-2][y]!=4 && Iam[x+3][y]!=4 && Iam[x-2][y]!=1 && Iam[x+3][y]!=1)
				{
					vokrygver(x-1,y,4,3);
					
				}
			}
			else if(Iam[x][y]==4 && Iam[x-1][y]==4 && Iam[x-2][y]==4 && Iam[x+1][y]==4)
			{
				if(Iam[x-3][y]!=4 && Iam[x+2][y]!=4 && Iam[x-3][y]!=1 && Iam[x+2][y]!=1)
				{
					vokrygver(x-2,y,4,3);
					
				}
			}
			else if(Iam[x][y]==4 && Iam[x-1][y]==4 && Iam[x-2][y]==4 && Iam[x-3][y]==4)
			{
				if(Iam[x+1][y]!=4 && Iam[x-4][y]!=4 && Iam[x+1][y]!=1 && Iam[x-4][y]!=1)
				{
					vokrygver(x-3,y,4,3);
					
				}
			}
		}
		//трехпалубный gor
		if(y==0)
		{
			if(Iam[x][y]==4 && Iam[x][y+1]==4 && Iam[x][y+2]==4)
			{
				if(Iam[x][y+3]!=4 && Iam[x][y+3]!=1)
				{
					vokryggor(x,y,3,3);
					
				}
			}
		}
		else if(y==9)
		{
			if(Iam[x][y]==4 && Iam[x][y-1]==4 && Iam[x][y-2]==4)
			{
				if(Iam[x][y-3]!=4 && Iam[x][y-3]!=1)
				{
					vokryggor(x,y-2,3,3);
					
				}
			}
		}
		else if(y==1)
		{
			if(Iam[x][y]==4 && Iam[x][y-1]==4 && Iam[x][y+1]==4)
			{
				if(Iam[x][y+2]!=4 && Iam[x][y+2]!=1)
				{
					vokryggor(x,y-1,3,3);
					
				}
			}
		}
		else if(y==8)
		{
			if(Iam[x][y]==4 && Iam[x][y-1]==4 && Iam[x][y+1]==4)
			{
				if(Iam[x][y-2]!=4 && Iam[x][y-2]!=1)
				{
					vokryggor(x,y-1,3,3);
					
				}
			}
		}
		else
		{
			if(Iam[x][y]==4 && Iam[x][y+1]==4 && Iam[x][y+2]==4)
			{
				if(Iam[x][y+3]!=4 && Iam[x][y-1]!=4 && Iam[x][y+3]!=1 && Iam[x][y-1]!=1)
				{
					vokryggor(x,y,3,3);
					
				}
			}
			else if(Iam[x][y]==4 && Iam[x][y-1]==4 && Iam[x][y+1]==4)
			{
				if(Iam[x][y-2]!=4 && Iam[x][y+2]!=4 && Iam[x][y-2]!=1 && Iam[x][y+2]!=1)
				{
					vokryggor(x,y-1,3,3);
					
				}
			}
			else if(Iam[x][y]==4 && Iam[x][y-1]==4 && Iam[x][y-2]==4)
			{
				if(Iam[x][y-3]!=4 && Iam[x][y+1]!=4 && Iam[x][y-3]!=1 && Iam[x][y+1]!=1)
				{
					vokryggor(x,y-2,3,3);
					
				}
			}
		}
		//ver
		if(x==0)
		{
			if(Iam[x][y]==4 && Iam[x+1][y]==4 && Iam[x+2][y]==4)
			{
				if(Iam[x+3][y]!=4 && Iam[x+3][y]!=1)
				{
					vokrygver(x,y,3,3);
					
				}
			}
		}
		else if(x==9)
		{
			if(Iam[x][y]==4 && Iam[x-1][y]==4 && Iam[x-2][y]==4)
			{
				if(Iam[x-3][y]!=4 && Iam[x-3][y]!=1)
				{
					vokrygver(x-2,y,3,3);
					
				}
			}
		}
		else if(x==1)
		{
			if(Iam[x][y]==4 && Iam[x-1][y]==4 && Iam[x+1][y]==4)
			{
				if(Iam[x+2][y]!=4 && Iam[x+2][y]!=1)
				{
					vokrygver(x-1,y,3,3);
					
				}
			}
		}
		else if(x==8)
		{
			if(Iam[x][y]==4 && Iam[x-1][y]==4 && Iam[x+1][y]==4)
			{
				if(Iam[x-2][y]!=4 && Iam[x-2][y]!=1)
				{
					vokrygver(x-1,y,3,3);
					
				}
			}
		}
		else
		{
			if(Iam[x][y]==4 && Iam[x+1][y]==4 && Iam[x+2][y]==4)
			{
				if(Iam[x+3][y]!=4 && Iam[x-1][y]!=4 && Iam[x+3][y]!=1 && Iam[x-1][y]!=1)
				{
					vokrygver(x-2,y,3,3);
					
				}
			}
			else if(Iam[x][y]==4 && Iam[x-1][y]==4 && Iam[x+1][y]==4)
			{
				if(Iam[x-2][y]!=4 && Iam[x+2][y]!=4 && Iam[x-2][y]!=1 && Iam[x+2][y]!=1)
				{
					vokrygver(x-1,y,3,3);
					
				}
			}
			else if(Iam[x][y]==4 && Iam[x-1][y]==4 && Iam[x-2][y]==4)
			{
				if(Iam[x-3][y]!=4 && Iam[x+1][y]!=4 && Iam[x-3][y]!=1 && Iam[x+1][y]!=1)
				{
					vokrygver(x-2,y,3,3);
					
				}
			}
		}
		//двухпалубный gor
		if(y==0)
		{
			if(Iam[x][y]==4 && Iam[x][y+1]==4)
			{
				if(Iam[x][y+2]!=4 && Iam[x][y+2]!=1)
				{
					vokryggor(x,y,2,3);
					
				}
			}
		}
		else if(y==9)
		{
			if(Iam[x][y]==4 && Iam[x][y-1]==4)
			{
				if(Iam[x][y-2]!=4 && Iam[x][y-2]!=1)
				{
					vokryggor(x,y-1,2,3);
					
				}
			}
		}
		else
		{
			if(Iam[x][y]==4 && Iam[x][y+1]==4)
			{
				if(Iam[x][y-1]!=4 && Iam[x][y+2]!=4 && Iam[x][y-1]!=1 && Iam[x][y+2]!=1)
				{
					vokryggor(x,y,2,3);
					
				}
			}
			else if(Iam[x][y]==4 && Iam[x][y-1]==4)
			{
				if(Iam[x][y+1]!=4 && Iam[x][y-2]!=4	&& Iam[x][y+1]!=1 && Iam[x][y-2]!=1)
				{
					vokryggor(x,y-1,2,3);
					
				}
			}
		}
		//ver
		if(x==0)
		{
			if(Iam[x][y]==4 && Iam[x+1][y]==4)
			{
				if(Iam[x+2][y]!=4 && Iam[x+2][y]!=1)
				{
					vokrygver(x,y,2,3);
					
				}
			}
		}
		else if(x==9)
		{
			if(Iam[x][y]==4 && Iam[x-1][y]==4)
			{
				if(Iam[x-2][y]!=4 && Iam[x-2][y]!=1)
				{
					vokrygver(x-1,y,2,3);
					
				}
			}
		}
		else
		{
			if(Iam[x][y]==4 && Iam[x+1][y]==4)
			{
				if(Iam[x+2][y]!=4 && Iam[x+2][y]!=1 && Iam[x-1][y]!=4 && Iam[x-1][y]!=1)
				{
					vokrygver(x-1,y,2,3);
					
				}
			}
			else if(Iam[x][y]==4 && Iam[x-1][y]==4)
			{
				if(Iam[x-2][y]!=4 && Iam[x-2][y]!=1 && Iam[x+1][y]!=4 && Iam[x+1][y]!=1)
				{
					vokrygver(x-1,y,2,3);
					
				}
			}
		}
		//однопалубный
		if(Iam[x][y]==4)
			
		{
			if(x==0 && y==0)
			{
				if(Iam[x+1][y]!=1 && Iam[x][y+1]!=1 && Iam[x+1][y]!=4 && Iam[x][y+1]!=4)
				{
					vokryggor(x,y,1,3);
					
				}
			}
			else if(x==9 && y==9)
			{
				if(Iam[x-1][y]!=1 && Iam[x][y-1]!=1 && Iam[x-1][y]!=4 && Iam[x][y-1]!=4)
				{
					vokryggor(x,y,1,3);
					
				}
			}
			else if(x==9 && y==0)
			{
				if(Iam[x-1][y]!=1 && Iam[x][y+1]!=1 && Iam[x-1][y]!=4 && Iam[x][y+1]!=4)
				{
					vokryggor(x,y,1,3);
					
				}
			}
			else if(x==0 && y==9)
			{
				if(Iam[x+1][y]!=1 && Iam[x][y-1]!=1 && Iam[x+1][y]!=4 && Iam[x][y-1]!=4)
				{
					vokryggor(x,y,1,3);
					
				}
			}
			else if(y==0)
			{
				if(Iam[x-1][y]!=1 && Iam[x][y+1]!=1 && Iam[x+1][y]!=1 && Iam[x-1][y]!=4 && Iam[x][y+1]!=4 && Iam[x+1][y]!=4)
				{
					vokryggor(x,y,1,3);
					
				}
			}
			else if(x==0)
			{
				if(Iam[x+1][y]!=1 && Iam[x][y-1]!=1 && Iam[x][y+1]!=1 && Iam[x+1][y]!=4 && Iam[x][y-1]!=4 && Iam[x][y+1]!=4)
				{
					vokryggor(x,y,1,3);
					
				}
			}
			else if(y==9)
			{
				if(Iam[x-1][y]!=1 && Iam[x][y-1]!=1 && Iam[x+1][y]!=1 && Iam[x-1][y]!=1 && Iam[x][y-1]!=1 && Iam[x+1][y]!=1)
				{
					vokryggor(x,y,1,3);
					
				}
			}
			else if(x==9)
			{
				if(Iam[x-1][y]!=1 && Iam[x][y-1]!=1 && Iam[x][y+1]!=1 && Iam[x-1][y]!=4 && Iam[x][y-1]!=4 && Iam[x][y+1]!=4)
				{
					vokryggor(x,y,1,3);
					
				}
			}
			else
			{
				if(Iam[x-1][y]!=1 && Iam[x+1][y]!=1 && Iam[x][y+1]!=1 && Iam[x][y-1]!=1 && Iam[x-1][y]!=4 && Iam[x+1][y]!=4 && Iam[x][y+1]!=4 && Iam[x][y-1]!=4)
				{
					vokryggor(x,y,1,3);
					
				}
			}
		}
	}
}


void zapver(int& tip, int& flag);
//расстановка моих кораблей горизонтально
void zapgor(int& tip, int& flag)
{
	int key;
	int x=1, y=1, kol=13, k=0;
	for (;;)
	{
		system("CLS");
		printIam();
		printcomp();
		coord.X=y;
		coord.Y=x;
		for(int i=0; i<21; i++)
		{
			for(int j=0; j<21; j++)
			{
				if(i==x && j==y)
				{
					if(flag==1)
					{
						SetConsoleCursorPosition(H,coord);
						SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
						cout<<char(SH)<<char(Vertical)<<char(SH)<<char(Vertical)<<char(SH)<<char(Vertical)<<char(SH);
						SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					}
					else if(flag==2 || flag==3)
					{
						tip=3;
						SetConsoleCursorPosition(H,coord);
						SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
						cout<<char(SH)<<char(Vertical)<<char(SH)<<char(Vertical)<<char(SH);
						SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						
					}
					else if(flag==4 || flag==5 || flag==6)
					{
						tip=2;
						SetConsoleCursorPosition(H,coord);
						SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
						cout<<char(SH)<<char(Vertical)<<char(SH);
						SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						
					}
					else if(flag==7 || flag==8 || flag==9 || flag==10)
					{
						tip=1;
						SetConsoleCursorPosition(H,coord);
						SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
						cout<<char(SH);
						SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						
					}
				}
			}
		}
		if (flag>=11)
			break;
		else if (flag==1)
		{kol=13;}
		else if (flag==2 || flag==3)
		{kol=15;}
		else if (flag==4 || flag==5 || flag==6)
		{kol=17;}
		else if (flag==7 || flag==8 || flag==9 || flag==10)
		{kol=19;}
		
		key = getch();
		if(key == ESC)
		{
			exit(0);
		}
		else if (key==32)
		{
			zapver(tip, flag);
		}
		else if(key == 224)
		{
			key = getch();
			
			switch(key)
			{
			case UP:    x>1 ? x-=2 : x=19; break;
			case DOWN:  x<19 ? x+=2 : x=1; break;
			case LEFT:  y>1 ? y-=2 : y=kol; break;
			case RIGHT: y<kol ? y+=2 : y=1; break;
			}
		}
		
		else if (key == 13)
		{
			if(Iam[x/2][y/2]==0 && Iam[x/2][(y/2)+tip-1]==0)
			{
				//4
				if (flag==1)
				{
					for (int z=0; z<4; z++)
					{
						int l=y/2, l1=x/2;
						k=l+z;
						Iam[l1][k]=1;
						
					}
					vokryggor(x,y,tip,1);
					flag++;
				}
				//3
				else if (flag==2 || flag==3)
				{
					for (int z=0; z<3; z++)
					{
						int l=y/2, l1=x/2;
						k=l+z;
						Iam[l1][k]=1;
						
					}
					vokryggor(x,y,tip,1);
					flag++;	
				}
				//2
				else if (flag==4 || flag==5 || flag==6)
				{
					for (int z=0; z<2; z++)
					{
						int l=y/2, l1=x/2;
						k=l+z;
						Iam[l1][k]=1;
						
					}
					vokryggor(x,y,tip,1);
					flag++;
				}
				//1
				else if (flag==7 || flag==8 || flag==9 || flag==10)
				{
					int l=y/2, l1=x/2;
					Iam[l1][l]=1;
					vokryggor(x,y,tip,1);
					flag++;
				}
			}
		}
		
	}
}

//... вертикально
void zapver(int& tip, int& flag)
{
	int key;
	int x=1, y=1, k=0, x1=0, kol;
	
	for (;;)
	{
		system("CLS");
		printIam();
		printcomp();
		coord.X=y;
		coord.Y=x;
		for(int i=0; i<21; i++)
		{
			for(int j=0; j<21; j++)
			{
				if(i==x && j==y)
				{
					if(flag==1)
					{
						kol=13;
						x1=x;
						for(int s=0; s<4; s++)
						{
							coord.X=y;
							coord.Y=x1+s;
							SetConsoleCursorPosition(H,coord);
							SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							cout<<char(SH);
							SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
							x1++;
						}
					}
					else if(flag==2 || flag==3)
					{
						kol=15;
						tip=3;
						x1=x;
						for(int s=0; s<3; s++)
						{
							coord.X=y;
							coord.Y=x1+s;
							SetConsoleCursorPosition(H,coord);
							SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							cout<<char(SH);
							SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
							x1++;
						}
					}
					else if(flag==4 || flag==5 || flag==6)
					{
						kol=17;
						tip=2;
						x1=x;
						for(int s=0; s<2; s++)
						{
							coord.X=y;
							coord.Y=x1+s;
							SetConsoleCursorPosition(H,coord);
							SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							cout<<char(SH);
							SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
							x1++;
						}
					}
					else if(flag==7 || flag==8 || flag==9 || flag==10)
					{
						kol=19;
						tip=1;
						x1=x;
							coord.X=y;
							coord.Y=x1;
							SetConsoleCursorPosition(H,coord);
							SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							cout<<char(SH);
							SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					}
				}
			}
		}
		key = getch();
		if (flag>=11)
			break;
		else if(key == ESC)
		{
			exit(0);
		}
		else if (key==32)
		{
			zapgor(tip, flag);
		}
		else if(key == 224)
		{
			key = getch();
			
			switch(key)
			{
			case UP:    x>1 ? x-=2 : x=kol; break;
			case DOWN:  x<kol ? x+=2 : x=1; break;
			case LEFT:  y>1 ? y-=2 : y=19; break;
			case RIGHT: y<19 ? y+=2 : y=1; break;
			}
		}
		
		else if (key == 13)
		{
			if(Iam[x/2][y/2]==0 && Iam[x/2+tip-1][y/2]!=2)
			{
				//4
					if (flag==1)
					{
						for (int z=0; z<4; z++)
						{
							int l=y/2;
							Iam[(x/2)+z][l]=1;
							
						}
						vokrygver(x,y,tip,1);
						flag++;
					}
				//3
				else if (flag==2 || flag==3)
				{
					
					for (int z=0; z<3; z++)
					{
						int l=y/2;
						Iam[(x/2)+z][l]=1;
						
					}
					vokrygver(x,y,tip,1);
					flag++;
				}
				//2
				else if (flag==4 || flag==5 || flag==6)
				{
					
					for (int z=0; z<2; z++)
					{
						int l=y/2;
						Iam[(x/2)+z][l]=1;
						
					}
					vokrygver(x,y,tip,1);
					flag++;
				}
				//1
				else if (flag==7 || flag==8 || flag==9 || flag==10)
				{
					
					int l=y/2;
					Iam[x/2][l]=1;
					vokrygver(x,y,tip,1);
					flag++;
				}
			}
		}
	}
}
//расстановка кораблей компа
void zapcomp ()
{
	srand(time(NULL));
	int a=0, flag=1, tip=0;
	int x=0,y=0;
	while (true)
	{
		a=rand()%2;
		if (flag==1)
		{
			tip=4;
			if(a==0)
			{
				y=rand()%7;
				x=rand()%10;
			}
			else if (a==1)
			{
				y=rand()%10;
				x=rand()%7;
			}
		}
		else if (flag==2 || flag==3)
		{
			tip=3;
			if(a==0)
			{
				y=rand()%8;
				x=rand()%10;
			}
			else if (a==1)
			{
				y=rand()%10;
				x=rand()%8;
			}
		}
		else if (flag==4 || flag==5 || flag==6)
		{
			tip=2;
			if(a==0)
			{
				y=rand()%9;
				x=rand()%10;
			}
			else if (a==1)
			{
				y=rand()%10;
				x=rand()%9;
			}
		}
		else if (flag==7 || flag==8 || flag==9 || flag==10)
		{
			tip=1;
			if(a==0)
			{
				y=rand()%10;
				x=rand()%10;
			}
			else if (a==1)
			{
				y=rand()%10;
				x=rand()%10;
			}
		}
		if (flag==11)
		{
			break;
		}
		//gor
		if (a==0)
		{	
			if	(comp[x][y]!=2 && comp[x][y]!=1)
			{
				if( comp[x][y+tip-1]!=1 &&  comp[x][y+tip-1]!=2)
				{
					if (flag==1)
					{
						flag++;				
						for(int i=0; i<4; i++)
						{
							comp[x][y+i]=1;
						}
						vokryggor(x,y,tip,0);
						continue;
					}
					else if (flag==2 || flag==3)
					{
						flag++;					
						for(int i=0; i<3; i++)
						{
							comp[x][y+i]=1;
						}
						vokryggor(x,y,tip,0);
						continue;
					}
					else if (flag==4 || flag==5 || flag==6)
					{
						flag++;				
						for(int i=0; i<2; i++)
						{
							comp[x][y+i]=1;
						}
						vokryggor(x,y,tip,0);
						continue;
					}
					else if (flag==7 || flag==8 || flag==9 || flag==10)
					{
						flag++;					
						comp[x][y]=1;
						vokryggor(x,y,tip,0);
						continue;
					}
				}
			}
			else
				continue;
		}
		//ver
		else if(a==1)
		{
			
			if	(comp[x][y]!=1 && comp[x][y]!=2)
			{
				if (comp[x+tip-1][y]!=1 && comp[x+tip-1][y]!=2)
				{
					if (flag==1)
					{
						flag++;				
						for(int i=0; i<4; i++)
						{
							comp[x+i][y]=1;
						}
						vokrygver(x,y,tip,0);
						continue;
					}
					else if (flag==2 || flag==3)
					{
						flag++;		
						for(int i=0; i<3; i++)
						{
							comp[x+i][y]=1;
						}
						vokrygver(x,y,tip,0);
						continue;
					}
					else if (flag==4 || flag==5 || flag==6)
					{
						flag++;			
						for(int i=0; i<2; i++)
						{
							comp[x+i][y]=1;
						}
						vokrygver(x,y,tip,0);
						continue;
					}
					else if (flag==7 || flag==8 || flag==9 || flag==10)
					{
						flag++;				
						comp[x][y]=1;
						vokrygver(x,y,tip,0);
						continue;
					}
				}
			}
			else
				continue;
		}
	}
}

//функция инициализирует заполнение поля кораблями для меня и компа.затем начинает стрельбу
void zap ()
{
	int a=0;
	int tip=4;
	int flag=1;
	system("CLS");
	cout<<"place your ships\n";
	getch();
	zapgor(tip, flag);
	system("CLS");
	/*cout<<"Wait until comp will place ships\n";
	for(int i=0; i<50; i++)
	{
		a=rand()%75;
		Sleep(a);
		SetConsoleTextAttribute(H,FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout<<char(SH);
	}
	SetConsoleTextAttribute(H,FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);*/
	zapcomp();
	return;
}


//красный крест
void rc(int x, int y, int line=1)
{
	if (line%2==0)
	{
		coord.X=y*2+1;
		coord.Y=x*2+1;
	}
	else
	{
		coord.X=y;
		coord.Y=x;
	}
	SetConsoleCursorPosition(H, coord);
	SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout<<'X';
	Sleep(200);
	SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}



//проверка на победу
void pob()
{
	int flagh=0, flagb=0, key;
	for (int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			if(Iam[i][j]==4)
			{flagb++;}
			if(comp[i][j]==4)
			{flagh++;}
		}
	}
	if(flagh==20)
	{
		system("CLS");
		SetConsoleTextAttribute(H,FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<"You win!!!!!!!!!!!!\n";
	/*	cout<<" ^^      ^^ ^^^^^^   ^^    ^^    ^^     ^^ ^^     ^^   ^^^     ^^^^      ^^  ^^^\n";
		cout<<"  ^^    ^^ ^^    ^^  ^^    ^^     ^^    ^^ ^^    ^^	          ^^ ^^     ^^  ^^^\n";
		cout<<"   ^^  ^^ ^^      ^^ ^^    ^^     ^^   ^^   ^^   ^^    ^^^     ^^  ^^    ^^  ^^^\n";
		cout<<"    ^^^^  ^^      ^^ ^^    ^^      ^^  ^^   ^^  ^^     ^^^     ^^   ^^   ^^  ^^^\n";
		cout<<"     ^^   ^^      ^^ ^^    ^^      ^^ ^^     ^^ ^^     ^^^     ^^    ^^  ^^  ^^^\n";
		cout<<"     ^^    ^^    ^^  ^^    ^^      ^^ ^^     ^^ ^^     ^^^     ^^     ^^ ^^     \n";
		cout<<"     ^^     ^^^^^^   ^^    ^^       ^^^       ^^^      ^^^     ^^      ^^^^  ^^^\n";
		cout<<"     ^^      ^^^^     ^^^^^^         ^         ^       ^^^     ^^        ^^  ^^^\n";*/
		SetConsoleTextAttribute(H,FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		coord.X=0;
		coord.Y=11;
		SetConsoleCursorPosition(H,coord);
		cout<<"Press 'R' to start new game";
		key=getch();
		if(key==114)
		{
			hz();
			zap();
		}
		else
		exit(0);
	}
	else if(flagb==20)
	{
		system("CLS");
		SetConsoleTextAttribute(H,FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<"You loose\n";
		//cout<<" ^^      ^^ ^^^^^^   ^^    ^^      ^^       ^^^^^^      ^^^^^^    ^^^^   ^^^^^^^    ^^^\n";
		//cout<<"  ^^    ^^ ^^    ^^  ^^    ^^      ^^      ^^    ^^    ^^    ^^  ^^  ^^  ^^         ^^^\n";
		//cout<<"   ^^  ^^ ^^      ^^ ^^    ^^      ^^     ^^      ^^  ^^      ^^ ^^      ^^^^^      ^^^\n";
		//cout<<"    ^^^^  ^^      ^^ ^^    ^^      ^^     ^^      ^^  ^^      ^^   ^^    ^^^^^      ^^^\n";
		//cout<<"     ^^   ^^      ^^ ^^    ^^      ^^     ^^      ^^  ^^      ^^     ^^  ^^         ^^^\n";
		//cout<<"     ^^    ^^    ^^  ^^    ^^      ^^      ^^    ^^    ^^    ^^       ^^ ^^            \n";
		//cout<<"     ^^     ^^^^^^   ^^    ^^      ^^       ^^^^^^      ^^^^^^  ^^  ^^   ^^^^^^^    ^^^\n";
		//cout<<"     ^^      ^^^^     ^^^^^^       ^^^^^^^^  ^^^^        ^^^^     ^^     ^^^^^^^    ^^^\n";
		SetConsoleTextAttribute(H,FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		coord.X=0;
		coord.X=0;
		coord.Y=11;
		SetConsoleCursorPosition(H,coord);
		cout<<"Press 'R' to start new game";
		key=getch();
		if(key==114)
		{
			hz();
			zap();
		}
		else
		exit(0);
	}
}

//функция стрельбы
void fire()
{
	int x=1, y=1, x1=0, y1=0, cheat=0;
	int key,line=0,flag=0, tmpx, tmpy;
	while(true)
	{
		line++;
		if(line%2==1)
		{
			while(true)
			{
				system("CLS");
				printIam();
				printcomp(cheat);
				coord.X=y+30;
				coord.Y=x;
				for(int i=0; i<21; i++)
				{
					for(int j=0; j<21; j++)
					{
						if(i==x && j==y)
						{
							SetConsoleCursorPosition(H,coord);
							cout<<'X';
						}
					}
				}
				key = getch();
				if(key == ESC)
				{
					exit(0);
				}
				else if(key == 224)
				{
					key = getch();
					
					switch(key)
					{
					case UP:    x>1 ? x-=2 : x=19; break;
					case DOWN:  x<19 ? x+=2 : x=1; break;
					case LEFT:  y>1 ? y-=2 : y=19; break;
					case RIGHT: y<19 ? y+=2 : y=1; break;
					}
				}
				else if(key==115)//cheat
				{
					if(cheat==0)
						cheat=1;
					else
						cheat=0;
				}
				if(key==114)//remake
					{
						hz();
						zap();
					}
				else if(key==13)
				{
					rc(x,y+30);
					if(comp[x/2][y/2]==3 || comp[x/2][y/2]==4)
						continue;
					else if(comp[x/2][y/2]==1)
					{
						comp[x/2][y/2]=4;
						obvodka(x/2,y/2,line);
						pob();
						continue;
					}
					else if(comp[x/2][y/2]==0 || comp[x/2][y/2]==2)
					{
						comp[x/2][y/2]=3;
						break;
					}
				}
			}
		}
		else if(line%2==0)
		{
			while (true)
			{
					Sleep(300);
					system("CLS");
					printIam();
					printcomp();
				if(flag==0)
				{
					x1=rand()%10;
					y1=rand()%10;
					rc(x1,y1,line);
					pob();
					if(Iam[x1][y1]==3 || Iam[x1][y1]==4)
					{
						continue;
					}
				}
				

				if(flag==0)
				{
					if(Iam[x1][y1]==3 || Iam[x1][y1]==4)
					{
						continue; 
						flag=0;
					}
					rc(x1,y1,line);
					if(Iam[x1][y1]==1)
					{
						
						Iam[x1][y1]=4;
						if(Iam[x1][y1+1]!=1 && Iam[x1][y1-1]!=1 && Iam[x1][y1+1]!=4 && Iam[x1][y1-1]!=4
							&&Iam[x1+1][y1]!=1 && Iam[x1-1][y1]!=1 && Iam[x1+1][y1]!=4 && Iam[x1-1][y1]!=4)
						{
							flag=0; 
							obvodka(x1,y1,line); 
							continue;
						}
						flag=1;
						obvodka(x1,y1,line);
						continue;
					}
					else if(Iam[x1][y1]==0 || Iam[x1][y1]==2)
					{
						Iam[x1][y1]=3;
						break;
					}
					
				}
				else if(flag==1)//стреляем налево
				{
					if(y1!=0)
					{
						if(Iam[x1][y1-1]==1)
						{
							Iam[x1][y1-1]=4;
							obvodka(x1,y1-1,line);					
							rc(x1,y1-1,line);
							if(Iam[x1][y1-2]!=1 && Iam[x1][y1+1]!=1 && Iam[x1][y1-2]!=4 && Iam[x1][y1+1]!=4)
							{
								flag=0; 
								continue;
							}
							if(Iam[x1][y1-2]==1)
							{
								Iam[x1][y1-2]=4;
								obvodka(x1,y1-2,line);
								rc(x1,y1-2,line);
								if(Iam[x1][y1-3]!=1 && Iam[x1][y1+1]!=1 && Iam[x1][y1-3]!=4 && Iam[x1][y1+1]!=4)
								{
									flag=0; 
									continue;
								}
								if(Iam[x1][y1-3]==1)
								{
									Iam[x1][y1-3]=4;
									rc(x1,y1-3,line);
									obvodka(x1,y1-3,line);
									flag=0;
									continue;
								}
								else
								{
									rc(x1,y1-3,line);
									Iam[x1][y1-3]=3;
									
									flag=2;
									break;
								}
							}
							else
							{
								rc(x1,y1-2,line);
								Iam[x1][y1-2]=3;
								flag=2;
								
								break;
							}
						}
						else
						{
							rc(x1,y1-1,line);
							Iam[x1][y1-1]=3;
							flag=2;
							break;
						}
					}
					else if(x==0)
					flag==2;
				}
				else if(flag==2)//стреляем направо
				{
					rc(x1,y1+1,line);
					if(Iam[x1][y1+1]==1)
					{
						Iam[x1][y1+1]=4;
						obvodka(x1,y1+1,line);
						rc(x1,y1+1,line);
						if(Iam[x1][y1+2]!=1 && Iam[x1][y1-1]!=1 && Iam[x1][y1+2]!=4 && Iam[x1][y1-1]!=4)
						{
							flag=0; 
							continue;}
						if(Iam[x1][y1+2]==1)
						{
							Iam[x1][y1+2]=4;
							obvodka(x1,y1+2,line);
							rc(x1,y1+2,line);
							if(Iam[x1][y1+3]!=1 && Iam[x1][y1-1]!=1 && Iam[x1][y1+3]!=4 && Iam[x1][y1-1]!=4)
							{
								flag=0; 
								continue;
							}
							if(Iam[x1][y1+3]==1)
							{
								rc(x1,y1+3,line);
								Iam[x1][y1+3]=4;
								obvodka(x1,y1+3,line);
								flag=0;
								continue;
							}
							else
							{
								rc(x1,y1+3,line);
								Iam[x1][y1+3]=3;
								flag=3;
								break;
							}
						}
						else
						{
							rc(x1,y1+2,line);
							Iam[x1][y1+2]=3;
							flag=3;
							break;
						}
					}
					else
					{
						rc(x1,y1+1,line);
						Iam[x1][y1+1]=3;
						flag=3;
						break;
					}
				}
				else if(flag==3)//стреляем вверх
				{
					if(x!=0)
					{
						rc(x1-1,y1,line);
						if(Iam[x1-1][y1]==1)
						{
							Iam[x1-1][y1]=4;
							obvodka(x1-1,y1,line);
							rc(x1-1,y1,line);
							if(Iam[x1-2][y1]!=1 && Iam[x1+1][y1]!=1 && Iam[x1-2][y1]!=4 && Iam[x1+1][y1]!=4)
							{
								flag=0; 
								continue;
							}
							if(Iam[x1-2][y1]==1)
							{
								Iam[x1-2][y1]=4;
								obvodka(x1-2,y1,line);
								rc(x1-2,y1,line);
								if(Iam[x1-3][y1]!=1 && Iam[x1+1][y1]!=1 && Iam[x1-3][y1]!=4 && Iam[x1+1][y1]!=4)
								{
									flag=0;
									continue;
								}
								if(Iam[x1-3][y1]==1)
								{
									rc(x1-3,y1,line);
									Iam[x1-3][y1]=4;
									obvodka(x1-3,y1,line);
									flag=0;
									continue;
								}
								else
								{
									rc(x1-3,y1,line);
									Iam[x1-3][y1]=3;
									flag=4;
									break;
								}
							}
							else
							{
								rc(x1-2,y1,line);
								Iam[x1-2][y1]=3;
								flag=4;
								break;
							}
						}
						else
						{
							rc(x1-1,y1,line);
							Iam[x1-1][y1]=3;
							flag=4;
							break;
						}
					}
					else if(x==0)
						flag=4;
				}
				else if(flag==4)//стреляем вниз
				{
					rc(x1+1,y1,line);
					if(Iam[x1+1][y1]==1)
					{
						Iam[x1+1][y1]=4;
						obvodka(x1+1,y1,line);
						rc(x1+1,y1,line);
						if(Iam[x1+2][y1]!=1 && Iam[x1-1][y1]!=1 && Iam[x1+2][y1]!=4 && Iam[x1-1][y1]!=4)
						{
							flag=0; 
							continue;
						}
						if(Iam[x1+2][y1]==1)
						{
							Iam[x1+2][y1]=4;
							obvodka(x1+2,y1,line);
							rc(x1+2,y1,line);
							if(Iam[x1+3][y1]!=1 && Iam[x1-1][y1]!=1 && Iam[x1+3][y1]!=4 && Iam[x1-1][y1]!=4)
							{
								flag=0; 
								continue;
							}
							if(Iam[x1+3][y1]==1)
							{
								rc(x1+3,y1,line);
								Iam[x1+3][y1]=4;
								obvodka(x1+3,y1,line);
								flag=0;
								continue;
							}
							else
							{
								rc(x1+3,y1,line);
								Iam[x1+3][y1]=3;
								flag=0;
								break;
							}
						}
						else
						{
							rc(x1+2,y1,line);
							Iam[x1+2][y1]=3;
							flag=0;
							break;
						}
					}
					else
					{
						rc(x1+1,y1,line);
						Iam[x1+1][y1]=3;
						flag=0;
						break;
					}
				}
			}
		}
	}
}
