#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "func.h"


using namespace std;

//мейн:)
void main ()
{
	HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
	enum keys {ESC=27, LEFT=75, RIGHT=77, UP=72, DOWN=80, SH=254};
	int m=0,x=0,key=0,podmenu=0,menu=1;
	while(true)
	{
		if (menu == 1)
		{
			system("CLS");
			for(int i=0; i<3; i++)
			{
				m=i;
				
					if(i==x)
					{
						SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_INTENSITY);
						cout<<"->";
						SetConsoleTextAttribute(H, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					}
					else
					{cout<<" ";}
			
				switch(m)
				{
				case 0: cout<<" Play game";
					break;
				case 1: cout<<" Instructions";
					break;
				case 2: cout<<" Exit";
				}
				cout<<"\n";
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
				case UP:    x>0 ? x-- : x=2; break;
				case DOWN:  x<2 ? x++ : x=0; break;
				}
			}
			else if(key == 13)
			{
				switch (x)
				{
				case 0: hz(); zap(); fire();
					break;
				case 1: system("CLS"); cout<<"To move across the field use arrows.\nTo Fire press enter.\nPmenyat npravlenie  the ship press space\nTo leave press esc\n"; getch();
					break;
				case 2: exit(0);
					break;
				}
			}
		}
	}
}





