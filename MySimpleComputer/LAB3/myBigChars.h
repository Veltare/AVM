 #ifndef H_MYBIGCHARS
 #define H_MYBIGCHARS


#define REC 'a'
#define BR "j"
#define BL "m"
#define TR "k"
#define TL "l"
#define VERT "x"
#define HOR "q"

int bc_printA(const char *str);
int bc_box(int x1,int y1,int x2,int y2);
int bc_setbigcharpos(int *big,int x,int y,int value);
int bc_getbigcharpos(int* big,int x,int y,int *value);
int bc_bigcharwrite(int fd,int* big,int count);
int bc_bigcharread(int fd,int *big,int need_count,int *count);
int bc_bigcharwrite(const char* fd,int* big,int count);
int bc_bigcharread(const char* fd,int *big,int need_count,int *count);
int bc_printbigchar(int* array,int x,int y,enum colors fg,enum colors bg);

 #endif
