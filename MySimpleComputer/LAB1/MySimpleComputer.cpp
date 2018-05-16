#include <stdio.h>
#include <iostream>
#include <fstream>

#include "./MySimpleComputer.h"


using namespace std;

/*
int main(void)
{

	sc_memoryInit();
	sc_regInit();

	int value,command,operand;
	for(int i=0;i<SIZE;i++)
	{
		sc_commandEncode(rand()%60 +10,0+rand()%127,&value);
		sc_memorySet(i,value);
		cout<<MemoryArray[i]<<" ";
		
	}
	
	sc_memorySave((char*)"HDDMemory");
	sc_memoryLoad((char*)"HDDMemory");
	cout<<endl;

	sc_commandDecode(MemoryArray[98],&command,&operand);
	Print();
	cout<<endl;
	sc_memoryGet(10,&value);
	cout<<value;
	return 0;
}
*/
int sc_memoryInit()
{
	
	for(int i=0;i<SIZE;i++)
		sc_memorySet(i,0x00);
		
	
}
int sc_memorySet(int address,int value)
{
	if(address>SIZE || address<0)
	{
		cout<<"Выход за границу памяти."<<endl;
		sc_regSet(M,1);
		return 0;
	}
		
	MemoryArray[address]=value;
	return 1;

}
int sc_memoryGet(int address,int *value)
{
	if(address>SIZE || address<0)
	{
		cout<<"Выход за границу памяти."<<endl;
		sc_regSet(M,1);
	}

	*value = MemoryArray[address];
	return *value;
}

int sc_memorySave(char* filename)
{
	ofstream output(filename,ios::binary);
	for(int i=0;i<SIZE;i++)
		output.write((char*)&MemoryArray[i],sizeof(MemoryArray[i]));
	cout<<endl<<"Бинарный файл успешно записан."<<endl;	
	output.close();
	return 1;
}
int sc_memoryLoad(char* filename)
{
	ifstream input(filename,ios::binary);
	if(!input)
	{
	cout<<"Ошибка файл не может быть прочитан."<<endl;
	return 0;
	}

	for(int i=0;i<SIZE;i++)
		input.read((char*)&MemoryArray[i],sizeof(MemoryArray[i]));
	
	if(input)
	{
		cout<<endl<<"Бинарный файл успешно считан."<<endl;
		input.close();
		return 1;
	}
		
	return 0;
}

int sc_regInit(void) //Инициализирует регистр флагов 0 значением.
{
	
	if(reg == 0)
	{
	cout<<"Флаг уже инициализирован."<<endl;
	return 0;	
	}
		
	sc_regSet(O,1);
	
	return 1;
}
int sc_regSet(int regval,int value)
{
	if(regval>5 || regval<1)
	{
		return 0;
	}
	else
	{
		if(value == 1)
		{
			reg = reg|(1<<(regval-1));
			return 1;
		}
		if(value == 0)
		{
			reg = reg&(~(1<<(regval-1)));
			return 1;
		}
			
	}
	return 0;
}
int sc_regGet(int flag,int *value)
{
	if(flag>5 || flag<1)
	{
		return 0;
	}
	else
	{
		*value = (reg>>(flag-1))&0x1;
		return 1;
	}
return 0;
}
int sc_commandEncode(int command,int operand,int*value)
{
	if(command == 0)
	{
		*value = operand;
		return *value;
	}	
	if(operand > 128 || operand < -128)
	{
		cout<<"Некорректный операнд"<<endl;
		return 0;
	}
	if(command > 76 || command < 10)
	{
		
		cout<<"Некорректная команда"<<endl;
	
		return 0;
	}
	
	*value = ((command << 7) | operand)&(~(1<<15));
	return *value;

}
int sc_commandDecode(int value,int* command,int* operand)
{	
	
	if((value>>15)&0x1 != 0)
	{
		sc_regSet(E,1);
		return 1;
	}
	*command = value >> 7;
	*operand = value & 0x7F;
	sc_regSet(E,0);
	return 1;
}
void Print()
{
	cout<<endl;
	for(int i=0;i<SIZE;i++)
	{
		cout<<MemoryArray[i]<<" ";
		
	}
}
