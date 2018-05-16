#include <stdio.h>
#include <fstream>
#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "./myTerm.h"
using namespace std;

/*
int main(void)
{
	int x,y;
	int buffer;
	colors color;
	cout<<"Введите значения для положения курсора."<<endl;
	cout<<"Введите x"<<endl;
	cin>>x;
	cout<<"Введите y"<<endl;
	cin>>y;
	mt_clrscr();
	mt_gotoXY(x,y);
	cout<<"Введите цвет текста от 1 до 8"<<endl;
	cin>>buffer;
	color = static_cast<colors>(buffer);
	mt_setfgcolor(color);
	cout<<"Введите цвет фона от 1 до 8"<<endl;
	cin>>buffer;
	color = static_cast<colors>(buffer);
	mt_setbgcolor(color);
	cout<<"УРА!ОНО РАБОТАЕТ!"<<endl;

	return 0;
}
*/
int mt_clrscr(void)
{
	
	printf("\E[H\E[2J");
	return 0;
}

int mt_getscreensize(int*rows,int*cols)
{

	struct winsize ws;
 if (!ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws)){
 	//cout<< "Получен размер экрана.\n";
	//cout<<*rows<<"|"<<*cols<<endl;
 	*rows = ws.ws_row;
	*cols = ws.ws_col;

	return 0;
 	} 
 	else {
		 
 	fprintf (stderr, "Ошибка получения размера экрана.\n");
	return -1;
	 }
}
int mt_gotoXY(int x,int y)
{
	int rows,cols;
	mt_getscreensize(&rows,&cols);
	
	if ((x >= 0) && (x < cols) && (y < rows) && (y >= 0)) 
	{
		printf("\E[%d;%dH",y,x);
		
	}
	else
	{	

		cout<<"Некорректно введенные размеры"<<endl;
		cout<<"x: "<<x<<" "<<"y: "<<y<<endl;
		return -1;
	}
}
int mt_setfgcolor(const enum colors color)
{
	switch(color)
	{
		case BLACK:
		{
			cout<<"\E["<<BLACK+29<<"m"<<endl;
				
			break;
		}
		case RED:
		{
			cout<<"\E["<<RED+29<<"m"<<endl;
			break;
		}
		case GREEN:
		{
			cout<<"\E["<<GREEN+29<<"m"<<endl;
			break;
		}
		case YELLOW:
		{
				
			printf("\E[%dm",YELLOW+29);
			break;
		}
		case BLUE:
		{
			cout<<"\E["<<BLUE+29<<"m"<<endl;
			break;
		}
		case MAGENTA:
		{
			cout<<"\E["<<MAGENTA+29<<"m"<<endl;
			break;
		}
		case WHITE:
		{
			cout<<"\E["<< WHITE+29<<"m"<<endl;
			break;
		}
		case DEFAULT:
		{
			
			printf("\E[%dm",DEFAULT+29);
			break;
		}
		default:
		{
			cout<<"Такого цвета не существует!!!Введите от 1 до 10"<<endl;
			return -1;
			
		}
	}
	

}
int mt_setbgcolor(const enum colors color)
{

	switch(color)
	{
		case BLACK:
		{
			cout<<"\E["<<BLACK+39<<"m"<<endl;
			break;
		}
		case RED:
		{
			cout<<"\E["<<RED+39<<"m"<<endl;
			break;
		}
		case GREEN:
		{
			cout<<"\E["<<GREEN+39<<"m"<<endl;
			break;
		}
		case YELLOW:
		{
			
			printf("\E[%dm",YELLOW+39);
			break;
		}
		case BLUE:
		{
			cout<<"\E["<<BLUE+39<<"m"<<endl;
			break;
		}
		case MAGENTA:
		{
			cout<<"\E["<<MAGENTA+39<<"m"<<endl;
			break;
		}
		case WHITE:
		{
			cout<<"\E["<<WHITE+39<<"m"<<endl;
			break;
		}
		case DEFAULT:
		{
			printf("\E[49m");
			break;
		}
		default:
		{
			cout<<"Такого цвета не существует!!!Введите от 1 до 10"<<endl;
			return -1;
			
		}
	}
}
