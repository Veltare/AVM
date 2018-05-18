#include <stdio.h>
#include <iostream>
#include <string>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <sys/time.h>
#include <iomanip> 

#include "../LAB1/MySimpleComputer.h"
#include "../LAB2/myTerm.h"
#include "../LAB3/myBigChars.h"
#include "../LAB4/myReadkey.h"


using namespace std;

ios_base::fmtflags oldFlags = cout.flags();
    streamsize         oldPrec  = cout.precision();
    char               oldFill  = cout.fill();

struct itimerval nval, oval;

void PrintMemory(int z,int k,bool enter_mode);
void PrintInterface(void);
void PrintFlag();
void PrintBigNumber(int value,int x,int y,enum colors fg,enum colors bg);
void Control();
void Reset();
void Timer();
void IOT(int *value,int command,int operand);
void PrintC(int value);
void CU();
int ALU(int command,int operand);
void PrintCell(int value);

int IncCounter(0);
int Accumulator(0);
int Operation(0);
int x(2),y(2);



bool CounterMode(false);
void signalhandler(int sign)
{
    int value;
    sc_regGet(T,&value);
    if(!value)
    {
        sc_regSet(T,0);
        
    }
    else
    {
        if(IncCounter<100)
        {
           CU();    
        }
        else
        {
            sc_regSet(M,1);

        }
        
       // alarm(0);
    }
}
int main()
{

    signal(SIGALRM,signalhandler);
   // signal(SIGUSR1,Reset);
    nval.it_interval.tv_sec  = 1;
    nval.it_interval.tv_usec = 0;
    nval.it_value.tv_sec  = 1;
    nval.it_value.tv_usec = 0;	
    //sc_memoryInit();
    mt_clrscr();
    PrintMemory(2,2,false);
    PrintInterface();
    Control();
  return 0;
}



void PrintInterface()
{
    
    int x1(1),y1(1),x2(62),y2(12);
    mt_gotoXY(x1,y1);
    bc_box(x1,y1,x2,y2);
    mt_gotoXY(x2/2,y1);
    cout<<"Memory"<<endl;
    for(int i = 0;i<4;i++)
    {
       
            
        bc_box(x2+2,y1,x2+22,y1+2);
         if(i == 0)
        {
            
            mt_gotoXY(x2+22/3,y1);
            cout<<"Accumulator"<<endl;    
            mt_gotoXY(x2+22/3,y1+1);
            PrintC(Accumulator);
          
        }
        if(i == 1)
        {
            mt_gotoXY(x2+22/5.3,y1);
            cout<<"instructionCounter"<<endl;    
            mt_gotoXY(x2+22/5+3.3,y1+1);
            PrintC(IncCounter);
           
        }
        if(i == 2)
        {
            int command(0),operand(0);
            mt_gotoXY(x2+22/3.5,y1);
            cout<<"Operation"<<endl; 
             mt_gotoXY(x2+22/3+1.5,y1+1);
             sc_commandDecode(Operation,&command,&operand);
            cout<<command<<" : "<<operand<<endl;  
        }
        if(i == 3)
        {
            mt_gotoXY(x2+22/3,y1);
            cout<<"Flags"<<endl;    
        }
        y1+=3;
    }
    mt_gotoXY(x2+8,y1-2);
    PrintFlag();
    bc_box(1,y1+1,x1+45,y2+11);
    
    y1+=1;
    x1+=45;
    y2+=11;
    
    bc_box(x1+2,y1,x2+22,y2);
    mt_gotoXY(50,14);
    cout<<"Keys:"<<endl;  
    mt_gotoXY(51,16);
    cout<<"l - load"<<endl;
     mt_gotoXY(51,17);
    cout<<"s - save"<<endl;
     mt_gotoXY(51,18);
    cout<<"r - run"<<endl;
     mt_gotoXY(51,19);
    cout<<"t - step"<<endl;
     mt_gotoXY(51,20);
    cout<<"i - reset"<<endl;
     mt_gotoXY(51,21);
    cout<<"F5 - accumulator"<<endl;
     mt_gotoXY(51,22);
    cout<<"F6 - instructionCounter"<<endl;
    //PrintMemory();
  
    mt_setbgcolor(DEFAULT);
    mt_gotoXY(0,28);
    

}
void PrintFlag()
{
    int value;
    int flag;
    if(sc_regGet(P,&value))
    {
        if(value == 1)
        cout<<"P"<<" ";
    }
    if(sc_regGet(O,&value))
    {
        if(value == 1)
        cout<<"O"<<" ";
    }
    if(sc_regGet(M,&value))
    {
        if(value == 1)
        cout<<"M"<<" ";
    }
    if(sc_regGet(T,&value))
    {
        if(value == 1)
        cout<<"T"<<" ";
    }
     if(sc_regGet(E,&value))
    {
        if(value == 1)
        cout<<"E"<<" ";
    }


}
void PrintBigNumber(int value,int x,int y,enum colors fg,enum colors bg)
{
    int command(0),operand(0);
    int *array = new int[2];
    mt_setbgcolor(DEFAULT);
    int count;

        bc_bigcharread(10,array,1,&count);
        bc_printbigchar(array,x,y,fg,bg);
        
        sc_commandDecode(value,&command,&operand);
        if(command > 15)
        {
             if(operand < 15)
             {
                    bc_bigcharread((char*)"NUM2",array,(int)command/16,&count);
                    bc_printbigchar(array,x+9,y,fg,bg);
                    bc_bigcharread((char*)"NUM2",array,(int)command%16,&count);
                    bc_printbigchar(array,x+18,y,fg,bg);
                    bc_bigcharread((char*)"NUM2",array,(int)0,&count);
                    bc_printbigchar(array,x+27,y,fg,bg);
                    bc_bigcharread((char*)"NUM2",array,(int)operand,&count);
                    bc_printbigchar(array,x+36,y,fg,bg);
             }
             else
             {
                    bc_bigcharread((char*)"NUM2",array,(int)command/16,&count);
                    bc_printbigchar(array,x+9,y,fg,bg);
                    bc_bigcharread((char*)"NUM2",array,(int)command%16,&count);
                    bc_printbigchar(array,x+18,y,fg,bg);
                    bc_bigcharread((char*)"NUM2",array,(int)operand/16,&count);
                    bc_printbigchar(array,x+27,y,fg,bg);
                    bc_bigcharread((char*)"NUM2",array,(int)operand%16,&count);
                    bc_printbigchar(array,x+36,y,fg,bg);
             }
       
        }
        else
        {
            if(operand < 15)
             {
                    bc_bigcharread((char*)"NUM2",array,(int)0,&count);
                    bc_printbigchar(array,x+9,y,fg,bg);
                    bc_bigcharread((char*)"NUM2",array,(int)command,&count);
                    bc_printbigchar(array,x+18,y,fg,bg);
                    bc_bigcharread((char*)"NUM2",array,(int)0,&count);
                    bc_printbigchar(array,x+27,y,fg,bg);
                    bc_bigcharread((char*)"NUM2",array,(int)operand,&count);
                    bc_printbigchar(array,x+36,y,fg,bg);
             }
             else
             {
                    bc_bigcharread((char*)"NUM2",array,(int)0,&count);
                    bc_printbigchar(array,x+9,y,fg,bg);
                    bc_bigcharread((char*)"NUM2",array,(int)command,&count);
                    bc_printbigchar(array,x+18,y,fg,bg);
                    bc_bigcharread((char*)"NUM2",array,(int)operand/16,&count);
                    bc_printbigchar(array,x+27,y,fg,bg);
                    bc_bigcharread((char*)"NUM2",array,(int)operand%16,&count);
                    bc_printbigchar(array,x+36,y,fg,bg);
             }
       
        }
}
void Control()
{
    keys key;
    int temp;
    
    int value(0);
    while(true)
    {
        
        mt_gotoXY(0,28);
        rk_readkey(&key);
        sc_regGet(T,&value);
        
        if(key == R ||  value == 1)
        {
            mt_clrscr();
            sc_regSet(T,1);
            PrintInterface();
            PrintMemory(x,y,false);

            Timer();

          
        }  
        if(key == T1)
        {
            if(IncCounter > 100)
                IncCounter = 0;
            sc_regSet(T,0);
            CU();
            x = (int)2 + (IncCounter%10*6);
            y = (int)2 + (IncCounter/10);
            mt_clrscr();
            PrintInterface();
            PrintMemory(x,y,false);
            sc_regSet(T,0);

        }
        
        if(value == 0)  
        switch(key)
        {
            case up:
            {
               
                if(y-1>=2 && y-1<12)
                {
                    mt_clrscr();
                    y-=1;
                    PrintMemory(x,y,false);
                    PrintInterface();
                    
                    

                }
                else
                {
                    PrintInterface();
                    PrintMemory(x,y,false);
                }

                key = other;    
                break;
            }
            case down:
            {
                
                if(y+1>=2 && y+1<12)
                {
                    mt_clrscr();
                    y+=1;
                    
                    PrintMemory(x,y,false);
                    PrintInterface();
                    
                }
                else
                {
                    PrintInterface();
                    PrintMemory(x,y,false);
                }
                    
                key = other;   
                break;
            }
            case rght:
            {
              
                if(x+6>=2 && x+6<60)
                {
                    mt_clrscr();
                    x+=6;
                    PrintMemory(x,y,false);
                    PrintInterface();
                   

                }
                else
                {
                    PrintInterface();
                     PrintMemory(x,y,false);
                }
                    

                key = other;   
                break;
            }
            case lft:
            {
               
                if(x-6>=2 && x-6<60)
                {
                    mt_clrscr();
                    x-=6;
                    PrintMemory(x,y,false);
                    PrintInterface();
                    

                }
                else
                {
                    PrintInterface();
                     PrintMemory(x,y,false);
                }
                    

                key = other;   
                break;
            }
            case enter:
            {
                
                PrintMemory(x,y,true);
                PrintInterface();
                break;
                
            }
            case S:
            {
                sc_memorySave((char*)"RAM");
                
                mt_gotoXY(1,32);
                break;
            }
            case L:
            {
                cout<<"ROBIT"<<endl;
                sc_memoryLoad((char*)"memory.o");
                mt_clrscr();
                PrintInterface();
                PrintMemory(x,y,false);
                mt_gotoXY(1,32);
                break;
            }
            case I:
            {
                Reset();
                break;
            }
            case F5:
            {
                int command(0),operand(0),value(0);
                
                mt_gotoXY(1,32);
                cout<<"Введите Accumulator"<<endl;
                cin>>Accumulator;

                IOT(&value,operand,value);
                Accumulator = value;
                mt_clrscr();
                PrintInterface();
                PrintMemory(x,y,false);
                break;
            }
            case F6:
            {
                mt_gotoXY(1,32);
            
                cout<<"Введите Counter"<<endl;
                cin>>IncCounter;
                if(IncCounter > 99)
                    {
                        cout<<"Ошибка неверный Counter"<<endl;
                        break;
                    }
                x = (int)2 + (IncCounter%10*6);
                y = (int)2 + (IncCounter/10);
                cout<<x<<":"<<y<<endl;
                mt_clrscr();
                PrintInterface();
                PrintMemory(x,y,false);
                break;
            }
            default:
            {
                break;
            }
        }
    }
  
}
void PrintMemory(int z,int k,bool enter_mode)
{
    int count(0);
    int value(0);
    int size_x(0),size_y(0);
    int command,operand;
    int bcommand,boperand,bvalue;
    int x1(2),y1(2);
    mt_getscreensize(&size_y,&size_x);
    if(enter_mode)
    {
        IOT(&value,command,operand);
    }
    for(int i = 0;i<SIZE;i++)
    {
            int buffer;
            if(x1>=size_x || count >= 10)
            {
                x1 = 2;
                y1+=1;
                count = 0;
                
            }
            
            if(sc_commandDecode(MemoryArray[i],&command,&operand))
            {
                   
                
                
                if(x1==z && y1==k)
                {
                    
                    if(enter_mode)
                    {
                            mt_gotoXY(1,28);
                            
                        	MemoryArray[i] = value;

                            
                            sc_commandDecode(value,&command,&operand);  
                            cout<<endl<<i<<"<  "<< command <<operand;
                            sc_commandDecode(MemoryArray[i],&command,&operand);
                            cout<<endl<<i<<">  "<<command<<operand;
                        	enter_mode = false;
                        
                    }
                    mt_gotoXY(1,28);

                    mt_setbgcolor(YELLOW);
                    bvalue = MemoryArray[i];
                   
                    Operation = MemoryArray[i];
                    IncCounter = i;

                }
                else
                {
                    
                }
                 
                mt_gotoXY(x1,y1);
                PrintCell(MemoryArray[i]);
                x1+=6;
                count++;
                 
                mt_setbgcolor(DEFAULT);
                     
            }
    
    }
    PrintBigNumber(bvalue,2,15,WHITE,BLACK);
    mt_gotoXY(0,0);
}

void Reset()
{
    IncCounter = 0;
    Accumulator = 0;
    sc_memoryInit();
    sc_regInit();
    mt_clrscr();
    PrintMemory(2,2,false);
    PrintInterface();
    
}
void Timer()
{
    setitimer (ITIMER_REAL, &nval, &oval);
}
void IOT(int *value,int command,int operand)
{
    string str;
    do
	{
            cout<<"Output/Input"<<endl;
	        cin>>str;

            if(str.size()>6)
                continue;
            if(str[0]!='+')
                continue;

            *value = stoi(str,nullptr,0);  
            command = ((int)(*value/1000)*10)+((int)(*value/100)%10);
            operand = ((int)((*value%100)/10))*10+((int)(*value%10));
            
            sc_commandEncode(command,operand,value);
	    	
            break;
	}while(true); 
   
}
void PrintC(int value)
{
    int buffer;
               
                if(value < 0)  
                {
                    cout<<dec;
                    buffer = value/100;
                    cout<<"+"<<(int)(-1)*buffer;
                    buffer = (value/100)%10;
                    cout<<(int)(-1)*buffer;
                    buffer = (value%100)/10;
                    cout<<(int)(-1)*buffer;
                    buffer = (value%10);
                    cout<<(int)(-1)*buffer;
                }
                else
                {
                    cout<<dec;
                    buffer = value/1000;
                    cout<<"+"<<(int)buffer;
                    buffer = (value/100)%10;
                    cout<<(int)buffer;
                    buffer = (value%100)/10;
                    cout<<(int)buffer;
                    buffer = (value%10);
                    cout<<(int)buffer;
                }
}
void PrintCell(int value)
{
    
    int command(0),operand(0);
    sc_commandDecode(value,&command,&operand);
    if(command > 0x0F)
    {   
        if(operand > 0x0F)
            cout<<uppercase<<right<<"+"<<hex<<setfill('0') << setw(2)<<command<<operand;
        else
            cout<<uppercase<<right<<"+"<<hex<<setfill('0') << setw(1)<<command<<setw(2)<<operand;    
    }
    else
    if(command < 0x0F)
    {
         if(operand > 0x0F)
            cout<<uppercase<<right<<"+"<<hex<<setfill('0') << setw(2)<<command<<setw(1)<<operand; 
        else
            cout<<uppercase<<right<<"+"<<hex<<setfill('0') << setw(2)<<command<<setw(2)<<operand;    
    }
           
}
void CU()
{
    int value(0);
    string str;
    int command(0),operand(0);
             x = (int)2 + (IncCounter%10*6);
             y = (int)2 + (IncCounter/10);

             mt_clrscr();
             PrintMemory(x,y,false);
             PrintInterface();

 if(sc_commandDecode(MemoryArray[IncCounter],&command,&operand))
  {
    
    if(command >= 0x1E && command <=0x21)
    {
        
        if(ALU(command,operand) == -1)
        {
            cout<< command <<endl; 
            return;
        }
    }
    else  
    switch(command)
    {
        
        case READ:
        {
            
            int buf_o(0),buf_c(0);
            cout<<"Output"<<endl;
	        cin>>str;

            if(str.size()>5)
            {
                
                sc_regSet(P,1);
                break;
            }
            value = stoi(str,nullptr,0);  
            buf_c = ((int)(value/1000)*10)+((int)(value/100)%10);
            buf_o = ((int)((value%100)/10))*10+((int)(value%10));
            
            sc_commandEncode(buf_c,buf_o,&value);
            sc_memorySet(operand,value);
            break;
        }
         case WRITE:
        {
            int buffer(0);
            sc_memoryGet(operand,&value);
            sc_commandDecode(value,&value,&buffer);
            cout<<"VALUE:"<<buffer<<endl;
            break;
        }
         case LOAD:
        {
            int buffer(0);
            sc_memoryGet(operand,&value);
            if(value > 0)
            {
                sc_commandDecode(value,&value,&buffer);
                Accumulator = buffer;
            }
            else
            {
                Accumulator = value;
            }    
            break;
        }
         case STORE:
        {
            
            sc_memorySet(operand,Accumulator);
            break;
        }
         
         case JUMP:
        {
             if(operand > 99)
             {
                 sc_regSet(M,1);
                 break;
             }
                
             x = (int)2 + (operand%10*6);
             y = (int)2 + (operand/10);
             IncCounter = operand;
             mt_clrscr();
             PrintMemory(x,y,false);
             PrintInterface();
            break;
        }
         case JNEG:
        {
            if(Accumulator < 0)
            {
            if(operand > 99)
             {
                 sc_regSet(M,1);
                 return;
             }
                
             x = (int)2 + (operand-1%10*6);
             y = (int)2 + (operand-1/10);
             IncCounter = operand-1;   
             mt_clrscr();
             PrintMemory(x,y,false);
             PrintInterface();
            }
            break;
        }
         case JZ:
        {
            if(Accumulator == 0)
            {
            if(operand > 99)
             {
                 sc_regSet(M,1);
                 return;
             }
                
             x = (int)2 + (operand%10*6);
             y = (int)2 + (operand/10);
             IncCounter = operand;
             mt_clrscr();
             PrintMemory(x,y,false);
             PrintInterface();
            }
            
            break;
        }
         case HALT:
        {
            sc_regSet(T,0);
            return;
        }
        case RCCR:
        {
            sc_memoryGet(operand,&value);
            for(int i=0;i<Accumulator;i++)
            {
                value = value>>1;
            }
            Accumulator = value;
            break;
        }
        case 0: //Для пропуска нулевых команд
        {
            break;
        }
        default:
        {
            sc_regSet(E,1);
            return;
        }
    } 
    if ((Accumulator > 0x7FFF)) {
		Accumulator = 9999;
		sc_regSet(P, 1);
	}
	else
		sc_regSet(M, 0);

     IncCounter++;
     sc_regSet(T,1);    
 }
 
}
int ALU(int command,int operand)
{
    int value(0);
    switch(command)
    {
        
        case ADD:
        {

            int buffer(0);
            sc_memoryGet(operand,&value);
            sc_commandDecode(value,&value,&buffer);
            
            if((Accumulator + buffer)>10000)
            {
                sc_regSet(P,1);
                
                break;
            }
                
            Accumulator+=buffer;    
            break;
        }
        case SUB:
        {
           int buffer(0);
           sc_memoryGet(operand,&value);
           sc_commandDecode(value,&value,&buffer);
            
            if((Accumulator - buffer)>10000)
            {
                sc_regSet(P,1);
                
                break;
            }
                
            Accumulator-=buffer;    
            break;
        }
        case DIVIDE:
        {
            int buffer(0);
            sc_memoryGet(operand,&value);
            sc_commandDecode(value,&value,&buffer);
            
            if(buffer==0)
            {
                sc_regSet(O,1);
                //return -1;
            }
             if((Accumulator / buffer)>10000)
            {
                sc_regSet(P,1);
                break;
            }    
            Accumulator = (int)(Accumulator / buffer);    
            
            break;
        }
        case MUL:
        {
            int buffer(0);
            sc_memoryGet(operand,&value);
            sc_commandDecode(value,&value,&buffer);
            
             if((Accumulator * buffer)>10000)
            {
                sc_regSet(P,1);
               
                break;
            }    
            Accumulator = (int)(Accumulator * buffer);    
            
            break;
        }
        case 0: //Для пропуска нулевых команд
        {
            break;
        }
        default:
        {
            //sc_regSet(E,1);
            return 0;
        }
    } 
    if ((Accumulator > 0x7FFF)) {
        
		Accumulator = 9999;
         
		sc_regSet(P, 1);
	}
	else
		sc_regSet(P, 0);

    return 0;    
}
