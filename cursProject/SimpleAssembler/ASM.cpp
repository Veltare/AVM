#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "../../MySimpleComputer/LAB1/MySimpleComputer.h"
#include "ASM.h"

main(int argc, char* argv[])
{

    ifstream fin;
    ofstream out;
    string line;

if(argc !=3)
    {
        cerr<<"Ошибка!Неверное количество аргументов!"<<endl;
        exit(1);
    }
if((strcmp(argv[1], ".sa") == 0) && (strcmp(argv[2], ".o") == 0))
		{
            cout<<argv[1]<<endl;
            cout<<argv[2]<<endl;
            cerr<<"Ошибка!Неверный название или путь к файлам!"<<endl;
            exit(1);
        }  

fin.open(argv[1],ifstream::in);
out.open(argv[2],ofstream::binary);

if(fin.good())
{
    
    while(getline(fin,line))
    {
        analysisLine(line);
    }
}
if(out.good())
{
    for(int i=0;i<SIZE;i++)
		out.write((char*)&MemoryArray[i],sizeof(MemoryArray[i]));
}
return 0;
}

int analysisLine(string line)
{
    int cell(0);
    int command(0);
    int argument(0);
    int code(0);
    
    string Comment;
    string SymbolComment = ";";
 
    vector<string> arrayLine;
    arrayLine = stringSplit(line);
    if(arrayLine.size() >= 3)
    {
       
        cell = stoi( arrayLine[0],nullptr,10);
        argument = stoi( arrayLine[2],nullptr,10);
        if(cell < 0x00 || cell > 0x63)
            return -1;
        analysisOperation(arrayLine);
         
        if(analysisCommand(arrayLine[1],command)==-1)
            return -1;

        
         if(argument < 0x00 || argument > 0x270F)
            return -1;    
         
        Comment = analysisComment(arrayLine,SymbolComment);
       
        if(sc_commandEncode(command,argument,&code))
        {
            sc_memorySet(cell,code); 
        }
       
    }   
    else
        return -1;
   
}
vector<string>stringSplit(string line)
{
    vector<string> arrayLine;
    istringstream is(line);
    string buffer;
    
    while(getline(is,buffer,' '))
        arrayLine.push_back(buffer);

 return arrayLine;
}
int analysisCommand(string line,int &command)
{
    if(line == "READ")
        command = 0x0A;
    else    
    if(line == "WRITE")
        command = 0x0B;
    else
    if(line == "LOAD")
        command = 0x14;
    else    
    if(line == "STORE")
        command = 0x15;
    else    
    if(line == "ADD")
        command = 0x1E;
    else    
    if(line == "SUB")
        command = 0x1F;
    else    
    if(line == "DIVIDE")
        command = 0x20;
    else    
    if(line == "MUL")
        command = 0x21;
    else    
    if(line == "JUMP")
        command = 0x28;
    else    
    if(line == "JNEG")
        command = 0x29;
    else    
    if(line == "JZ")
        command = 0x2A;
    else    
    if(line == "HALT")
        command = 0x2B;
    else
    if(line == "RCCR")
        command = 0x46;
    else
    if(line == "=")
        command = 0;
    else    
    return -1;

    return 0;          
}
string analysisComment(vector<string> arrayLine,string SymbolComment)
{
    string Comment;
    for(int i = 0;i<arrayLine.size();i++)
    {    
            if(arrayLine[i] == SymbolComment)
            {
                
                for(int k = i+1;k<arrayLine.size();k++)
                {
                    Comment+=arrayLine[i];
                    Comment+=" ";
                }
                return Comment;
            }
    }    
    return Comment;
}
int analysisOperation(vector<string> arrayLine)
{
    for(int i = 0;i<arrayLine.size();i++)
    {
            if(arrayLine[i] == "=" && i+1 < arrayLine.size())
            {
               string temp = arrayLine[i+1];
               
               if(temp[0]=='+')
               {
                  
                   arrayLine[i+1].erase(0,1);
               } 
               sc_memorySet(stoi( arrayLine[i-1],nullptr,10),stoi( arrayLine[i+1],nullptr,10));
               return 0;
            }
    }    
    return -1;
}