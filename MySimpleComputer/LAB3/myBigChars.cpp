//#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include "../LAB2/myTerm.h"
#include "myBigChars.h"
#include <cstdlib>
#include <string>
using namespace std;

int main()
{
  int big[2];
  int count(0);
  big[0] = 3234070272;
  big[1] = 3233857788;
  for(int i = 0;i<16;i++)
  {
   bc_bigcharread(i,big,1,&count);
    //bc_printbigchar(big,10,10,BLUE,WHITE);
   bc_bigcharwrite((char*)"NUM2",big,i);
   

  }
  bc_bigcharwrite(15,big,1);
  //bc_printbigchar(big,10,10,BLUE,WHITE);
  //bc_bigcharwrite((char*)"NUM",big,i);

  return 0;
}


int bc_printA(const char *str)
{
  if(str==NULL)
    return -1;
  cout<<"\E(0"<<*str<<"\E(B";

 return 0;
}
int bc_box(int x1,int y1,int x2,int y2)
{
  int max_y(0),max_x(0);
  int i,j;
  mt_getscreensize(&max_y,&max_x);
  if(x1<0 || y1<0 || x2>max_x || y2>max_y || (x2-x1<2) ||(y2-y1<2))
    return -1;
 
  
  mt_gotoXY(x1,y1);
  bc_printA(TL);
  for(i=x1+1;i<x2;i++)
  {
     bc_printA(HOR);
  }
  bc_printA(TR);
  mt_gotoXY(x1,y2);
  bc_printA(BL); 
  for(i=x1+1;i<x2;i++)
  {
    
     bc_printA(HOR);
     
  }
  
  bc_printA(BR); 
   
  mt_gotoXY(x1,y1);
  for(j=y1+1;j<y2;j++)
  {
    mt_gotoXY(x1,j);
     bc_printA(VERT);
     mt_gotoXY(i,j);
     bc_printA(VERT);
     
  }
   mt_gotoXY(0,j+2);
}
int bc_printbigchar(int* array,int x,int y,enum colors fg,enum colors bg)
{
  int max_y(0),max_x(0);
  int number_bit,temp_number;
  int bit;
  int buffer;
  int count(0);
  char *result_string = new char[9];
  mt_getscreensize(&max_y,&max_x);
 // if ((x < 0) || (y < 0) || (x + 8 > max_x) || (y + 8 > max_y))
	//	return -1;
  mt_setfgcolor(fg);
	mt_setbgcolor(bg);
  result_string[8] = '\0';
 
  for(int i = 0;i<2;i++)
  {
    temp_number = array[i];
    for(int j = 0;j<4;j++)
    {
      number_bit = (temp_number & 0xFF);
      temp_number = temp_number>>8;
      for(int k = 0;k<8;k++)
      {
        if((8-k-1)>=0)
        {
           bit = (number_bit>>(8-k-1))&0x1;
          if(bit==0)
           result_string[k] = ' ';
          if(bit==1) 
           result_string[k] = REC; 
        }
        else
        {
          continue;
        }    
      
      
      }
       
      mt_gotoXY(x,y + count);
      
     for(int k = 0;k<8;k++)
        bc_printA(&result_string[k]);
      count++;
    }
  }
  mt_setfgcolor(DEFAULT);
	mt_setbgcolor(DEFAULT);
  cout<<endl;
  
	return 0;
}
int bc_setbigcharpos(int *big,int x,int y,int value)
{
  
  if(x<0 || y<0 || x>7 || y>7)
    return -1;
  if(value < 0 || value > 1)
    return -1;
  if(y < 3)
  {
    y = y % 4;
    if(value == 1)
    {
     
      big[0] = big[0] | (1<<(x+8*y));
      
    }
     
    if(value == 0)
      big[0]&= (~(1<<(x+8*y)));
   
      return 0;
  }
  else
  {
    y = y % 4;
    if(value == 1)
      big[1]|=(1<<(x+8*y));
    if(value == 0)
      big[1]&= (~(1<<(x+8*y)));
      return 0;
  }
  return -1;
}
int bc_getbigcharpos(int* big,int x,int y,int *value)
{
  int buffer;
  if(x<0 || y<0 || x>7 || y>7)
    return -1;
 
  if(y<3)
  {
   
      *value = (big[0]>>(x+8*y) & 0x1);  
      
  }
  else
  {
 
      *value = (big[1]>>(8*y+x) & 0x1); 
     
  }
  return 0;
}
int bc_bigcharwrite(int fd,int* big,int count)
{
   string s = to_string(fd);
  char const *pchar = s.c_str();
  
  ofstream output(pchar,ios::app|ios::out|ios::binary);
  output.write((char*)&count,sizeof(count));
	for(int i=0;i<2;i++)
		output.write((char*)&big[i],sizeof(big[i]));
	cout<<endl<<"Бинарный файл успешно записан."<<endl;	
	output.close();
		

return 0;
}
int bc_bigcharwrite(const char* fd,int* big,int count)
{
  
  ofstream output(fd,ios::app|ios::out|ios::binary);
  output.write((char*)&count,sizeof(count));
	for(int i=0;i<2;i++)
		output.write((char*)&big[i],sizeof(big[i]));
	cout<<endl<<"Бинарный файл успешно записан."<<endl;	
	output.close();
		

return 0;
}
int bc_bigcharread(int fd,int *big,int need_count,int *count)
{
  string s = to_string(fd);
  char const *pchar = s.c_str();
  
  ifstream input;
  input.open(pchar,ios::in|ios::binary);
	if(!input)
	{
	cout<<"Ошибка файл не может быть прочитан."<<endl;
	return -1;
	}
  while(!input.eof())
  {
    
      
    input.read((char*)&*count,sizeof(*count));
    if(*count==need_count)
    {
      for(int i=0;i<2;i++)
      input.read((char*)&big[i],sizeof(big[i]));
      
      //cout<<"Необходимый файл считан."<<endl;
      return 0;
   }
    
  }
     
	
	if(input)
	{
		cout<<endl<<"Бинарный файл успешно считан."<<endl;
		input.close();
		return -1;
	}
		
	return -1;
}
int bc_bigcharread(const char* fd,int *big,int need_count,int *count)
{
  
  
  ifstream input;
  input.open(fd,ios::in|ios::binary);
	if(!input)
	{
	cout<<"Ошибка файл не может быть прочитан."<<endl;
	return -1;
	}
  while(!input.eof())
  {
     input.read((char*)&*count,sizeof(*count));
    if(*count==need_count)
    {
      for(int i=0;i<2;i++)
      {
      input.read((char*)&big[i],sizeof(big[i]));
      
      
      }
      //cout<<"Необходимый файл считан."<<endl;
      return 0;
    }
      
   
  
  }
     
	
	if(input)
	{
		cout<<endl<<"Бинарный файл успешно считан."<<endl;
		input.close();
		return -1;
	}
		
	return -1;
}
