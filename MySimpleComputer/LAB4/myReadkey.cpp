#include <iostream>
#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <fstream>
#include "myReadkey.h"

using namespace std;
static struct termios origin_settings;
/*int main (void)
{
  keys key;
  
  cout<<"robit"<<endl;
  cout<<rk_readkey(&key)<<endl;
 return 0;
 }*/

 int rk_readkey(enum keys* key)
{
   
    char buf[16];
    int num_read;

    if (tcgetattr(0, &origin_settings) != 0)
        return -1;

    if (rk_mytermregime(0, 0, 1, 0, 1) != 0)
        return -1;

    num_read = read(0, buf, 15);
    if (num_read < 0)
        return -1;

    buf[num_read] = '\0';

    if (strcmp(buf, "l") == 0)
        *key = L;
    else
    if (strcmp(buf, "s") == 0)
        *key = S;
    else
    if (strcmp(buf, "r") == 0)
        *key = R;
    else
    if (strcmp(buf, "t") == 0)
        *key = T1;
    else
    if (strcmp(buf, "i") == 0)
        *key = I;
    else
    if (strcmp(buf, "\n") == 0)
        *key = enter;
    else
    if (strcmp(buf, "\E[15~") == 0)
        *key = F5;
    else
    if (strcmp(buf, "\E[17~") == 0)
        *key = F6;
    else
    if (strcmp(buf, "\E[A") == 0)
        *key = up;
    else
    if (strcmp(buf, "\E[B") == 0)
        *key = down;
    else
    if (strcmp(buf, "\E[C") == 0)
        *key = rght;
    else
    if (strcmp(buf, "\E[D") == 0)
        *key = lft;
    else
        *key = other;
    if (tcsetattr(0, TCSANOW, &origin_settings) != 0)
        return -1;

    return 0;
}
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint)
{
        struct termios new_settings;
            
            tcgetattr(0,&origin_settings);
            new_settings = origin_settings;
            if(regime==0)
            {
                new_settings.c_lflag &=(~ICANON);
            }
            else
            {
                if(regime==1)
                {
                    new_settings.c_lflag |= ICANON;
                }

                return -1;
            }
            if(regime==0)
            {
            if(echo==1)
                new_settings.c_lflag |= ECHO;
            else
                new_settings.c_lflag &= (~ECHO);
            if(sigint==1)
                new_settings.c_lflag |= ISIG;
            else
                new_settings.c_lflag &= (~ISIG);
                
                new_settings.c_cc[VTIME] = vtime; 
                new_settings.c_cc[VMIN] = vmin;
            }
         tcsetattr(0,TCSANOW,&new_settings);
         return 0;
}

int rk_mytermrestore (void)
{
    tcsetattr(0,TCSANOW,&origin_settings);
    return 0;
}
int rk_mytermsave (const char* fd)
{
    struct termios options;
    ofstream output(fd,ios::app|ios::out|ios::binary);
    if (tcgetattr(0, &options) != 0)
        return -1;
   
  
    
    output.write((char*)&options,sizeof(options));
	cout<<endl<<"Бинарный файл успешно записан."<<endl;	
	output.close();
}