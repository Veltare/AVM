 #ifndef H_MYTERM
 #define H_MYTERM

enum colors{
	BLACK = 1,
	RED,GREEN,YELLOW,
	BLUE,MAGENTA,Cyan,
	WHITE,DEFAULT=10
};
int mt_clrscr(void);
int mt_gotoXY(int,int);
int mt_getscreensize(int*row,int*cols);
int mt_setfgcolor(enum colors);
int mt_setbgcolor(enum colors);

 #endif
