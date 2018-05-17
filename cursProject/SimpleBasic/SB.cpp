#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <sstream>
#include <locale>  

//#include ".../MySimpleComputer/LAB1/MySimpleComputer.h"
//#include "./ASM.h"



using namespace std;

bool IsFirst = true;
bool PriorityOperation = true;
struct Variable
{
    string name;
    string mem_address;
    int value;
};
int numericMemory(0);
vector<Variable> GlobalVariable;
vector<string> GlobalString;

int analysisLine(string line);
string analysisCommand(string line,vector<string> &lineArray);
bool isValue(string value);
vector<string>stringSplit(string line);
int existenceVariable(string A);
int FindVariable(string A);
int OperationProcess(string operation,int index1,int index2,int index3,string cell,string &value,string&command);
vector<string> ReverseRecordingCreation(vector<string> line);
int OperationPriority(string operation);
bool IsOperation(string operation);
void ResolutionProcess(vector<string> lineA,string &value,string&command);

main(int argc, char* argv[])
{

ifstream fin;
ofstream out;
int temp;
string line;

if(argc !=3)
    {
        cerr<<"Ошибка!Неверное количество аргументов!"<<endl;
        exit(1);
    }
 
if ((strcmp(argv[1], ".sb") == 0) || (strcmp(argv[2], ".sa") == 0))
		{
            cout<<argv[1]<<endl;
            cout<<argv[2]<<endl;
            cerr<<"Ошибка!Неверный название или путь к файлам!"<<endl;
            exit(1);
        }  
       
    fin.open(argv[1],ifstream::in);
    out.open(argv[2],ofstream::out);
   
if(fin.good())
    {
       
        while(getline(fin,line))
        {
            
            analysisLine(line);
        }
    }
if(out.good())
{
    for(int i=0;i<GlobalString.size();i++)
    {
        cout<<GlobalString[i]<<endl;
		out << GlobalString[i] <<endl;

    }
}
return 0;
}

int analysisLine(string line)
{
    string Command;
   
    
    vector<string> arrayLine;
    arrayLine = stringSplit(line);
    if(arrayLine[1] == "END")
    {  
         Command = "HALT";
        string value = "0";   
        string cell = to_string(numericMemory);
        string compliteString=cell+" "+Command+" "+value;
        GlobalString.push_back(compliteString);
        numericMemory++;
            
       
    }  
    if(arrayLine.size() >= 3)
    {        
        Command = analysisCommand(arrayLine[1],arrayLine);
        if(Command!="-1")
            GlobalString.push_back(Command);
            
       
    }   
    else
        return -1;
   
  return 0;
}
vector<string>stringSplit(string line)
{
    
    vector<string> arrayLine1;
    istringstream is(line);
    string buffer;
    while(getline(is,buffer,' '))
        arrayLine1.push_back(buffer);

     
    
 return arrayLine1;
}
string analysisCommand(string line,vector<string> &lineArray)
{
    string compliteString;
    
    string command;
    string operand;
    string value = to_string(numericMemory+1);
    string cell = to_string(numericMemory);
    
    
    //cout<<"R2"<<endl;
    
    if(!isValue(lineArray[2]))
            return "-1";
    /*if(existenceVariable(lineArray[2])==-1)
    {
                
            Variable *temp = new Variable;
            temp->name = lineArray[2];
            temp->mem_address = cell;
            temp->value = 0;
            GlobalVariable.push_back(*temp);
            operand = lineArray[2];
            value = "0";
           
            
    }*/
    
    for(int i = 0;i < lineArray.size();i++)
        {
            if((existenceVariable(lineArray[i])==-1))
               {
                  if(isValue(lineArray[i])==true)
                  {
                    Variable *temp = new Variable;
                   
                    
                    cell = to_string(numericMemory);
                    numericMemory++;
                   
                    temp->mem_address = cell;
                   
                    temp->value = 0;
                    operand = lineArray[i];
                    temp->name = operand;
                    GlobalVariable.push_back(*temp);
                    
                    value = "0";
                  }
                  else
                  {
                      
                  }
               
               }
        }    
    if(line == "REM")
    {
      return "-1"; 
    }     
    else    
    if(line == "INPUT") //--> READ
    {
        
        
        if(existenceVariable(lineArray[2])!=-1)
        {
            
            
            operand = lineArray[2];
            command = "READ";
            value =  GlobalVariable[existenceVariable(lineArray[2])].mem_address;
            
        }
        else
            command = "READ";

        compliteString=cell+" "+command+" "+value;
        //numericMemory++;
    
        return compliteString;      
    }
        
    else    
    if(line == "PRINT")//--> WRITE
       {
        if(existenceVariable(lineArray[2])!=-1)
        {
            
            
            operand = lineArray[2];
            command = "WRITE";
            value =  GlobalVariable[existenceVariable(lineArray[2])].mem_address;
        }
        else
           command = "WRITE"; 

        compliteString=cell+" "+command+" "+value;
        numericMemory++;
   
        return compliteString;    
       }
    else
    if(line == "LET")
        {
             vector<string> T = lineArray;
             while(T[0]!= "LET")
             {
                 T.erase(T.begin());
             }
             T.erase(T.begin());
             T = ReverseRecordingCreation(T);
             for(int z = 0;z<T.size();z++)
             {
                 cout<<T[z];
             }
             cout<<endl;
             ResolutionProcess(T,value,command);   
                 return "-1";
        }
                
    else  
    if(line == "GOTO")
        {
             
            cout<<"ZAHOD3"<<endl;
            command = "JUMP";
            if(existenceVariable(lineArray[2])!=-1)
                {

                    operand = lineArray[2];
                    value =  GlobalVariable[existenceVariable(lineArray[2])].mem_address;
                    compliteString=cell+" "+command+" "+value;
                    numericMemory++;
   
                    return compliteString; 
                }
              
            
        }
    else
            
    if(line == "IF")
        {
            
            command = "LOAD";
            if(existenceVariable(lineArray[2])!=-1)
                {
                    value =  GlobalVariable[existenceVariable(lineArray[2])].mem_address;
                    compliteString=cell+" "+command+" "+value;
                    GlobalString.push_back(compliteString);
                    numericMemory++;
                    operand = lineArray[2];
                    if(lineArray[5] == "GOTO")
                    {
                       
                        cell = to_string(numericMemory);
                        value = to_string(stoi( lineArray[6],nullptr,10)/10);
                        command = "JNEG";    
                    }
                    compliteString=cell+" "+command+" "+value;
                    numericMemory++;
                    return compliteString; 
                }
                else
                {
                    
                    compliteString=cell+" "+command+" "+value;
                    
                    GlobalString.push_back(compliteString);
                    numericMemory++;
                    if(lineArray[5] == "GOTO")
                    {
                        
                        cell = to_string(numericMemory);
                        value = to_string(stoi( lineArray[6],nullptr,10)/10);
                        command = "JNEG";    
                    }
                    compliteString=cell+" "+command+" "+value;
                    numericMemory++;
                    return compliteString; 
                }
        }
      return "-1";       
}

bool isValue(string value)
{
    
    if(value.size()>1)
        return false;
    if(value >="A" && value <="Z")
        return true;
    else
        return false;    
}

int existenceVariable(string A)
{
    for(int i = 0;i<GlobalVariable.size();i++)
    {
        if(GlobalVariable[i].name == A)
            return i;
    }
   return -1;
}
int OperationProcess(string operation,Variable V1,Variable V2,Variable V3,string cell,string &value,string&command)
{

 
    string compliteString;
   
    string operand;
    if(operation == "=")
    {
        command = "LOAD";
        value =  V1.mem_address;
        cell = to_string(numericMemory);
        compliteString=cell+" "+command+" "+value;
        GlobalString.push_back(compliteString);
        numericMemory++;
        IsFirst = false;    
        command = "STORE";
        value =  V2.mem_address;
        cell = to_string(numericMemory);
        compliteString=cell+" "+command+" "+value;
        GlobalString.push_back(compliteString);
        numericMemory++;
    return 0;
    
    }
        command = "LOAD";
        value =  V1.mem_address;
        cell = to_string(numericMemory);
        compliteString=cell+" "+command+" "+value;
        GlobalString.push_back(compliteString);
        numericMemory++;
        IsFirst = false;
    
  
    if(operation == "-")
    {
    
    command = "SUB";
    value =  V2.mem_address;
    cell = to_string(numericMemory);
    compliteString=cell+" "+command+" "+value;
    GlobalString.push_back(compliteString);
    numericMemory++;
  
    }
    if(operation == "+")
    {
    command = "ADD";
    value =  V2.mem_address;
    cell = to_string(numericMemory);
    compliteString=cell+" "+command+" "+value;
    GlobalString.push_back(compliteString);
    numericMemory++;
    
    
    }
    if(operation == "*")
    {
    command = "MUL";
    value =  V2.mem_address;
    cell = to_string(numericMemory);
    compliteString=cell+" "+command+" "+value;
    GlobalString.push_back(compliteString);
    numericMemory++;
   
    }
    if(operation == "/")
    {
  
    command = "DIVIDE";
    value =  V2.mem_address;
    cell = to_string(numericMemory);
    compliteString=cell+" "+command+" "+value;
    GlobalString.push_back(compliteString);
    numericMemory++;
   
    
    }
    
    if(PriorityOperation == true)
    {
         
                   
        Variable *temp = new Variable;
        cell = to_string(numericMemory);
        numericMemory++;
                   
        temp->mem_address = cell;
                   
        temp->value = 0;
        operand = V3.name+cell;
        temp->name = operand;
        GlobalVariable.push_back(*temp);
         
        command = "STORE";
        value =  temp->mem_address;
        cell = to_string(numericMemory);
        compliteString=cell+" "+command+" "+value;
        GlobalString.push_back(compliteString);
        numericMemory++;
        PriorityOperation = true;
        IsFirst = true;
    }
    return 0;
}

vector<string> ReverseRecordingCreation(vector<string> line)
{
    vector<string> input;
    vector<string> operation;
    for(int i = 0; i < line.size();i++)
        {
            if(line[i] == "(")
            {
                operation.push_back(line[i]);
                continue;
            }
            if(line[i] == ")")
                {
                    
                    for(int k = 0;k<operation.size();k++)
                    {
                        if(operation[k] == "(")
                        {   operation.erase(operation.begin() + k);
                            
                            
                            for(int m = operation.size()-1;m>=k;m--)
                            {
                                //cout<<operation[m]<<endl;  
                                input.push_back(operation[m]);
                                if(k + 1 < operation.size())
                                    operation.erase(operation.begin() + k+1);
                                else    
                                if(k < operation.size())
                                    operation.erase(operation.begin() + k);
                            }
                            continue;
                        }
                    }
                    continue;
                } 
            if(IsOperation(line[i]))
            {
                
                
                if(operation.size() > 0)
                    if(OperationPriority(operation[operation.size() - 1]) >= OperationPriority(line[i]) && operation[operation.size() - 1] != "(")
                    {
                        /*cout<<"COMPLITE"<<endl;
                        cout<<OperationPriority(operation[operation.size() - 1]) << ">="<<OperationPriority(line[i])<<endl;
                        cout<<"DO"<<endl;
                        cout<<"value"<<line[i]<<endl;
                        for(int i = 0; i < operation.size();i++)
                                cout<<operation[i];
                                cout<<endl;*/
                        input.push_back(operation[operation.size() - 1]);
                        operation.erase(operation.begin() + (operation.size() - 1));
                        //cout<<"POSLE"<<endl;
                        
                        operation.push_back(line[i]);
                        /*for(int i = 0; i < operation.size();i++)
                                cout<<operation[i];
                                cout<<endl;*/
                        continue;
                    }
            
            operation.push_back(line[i]);
            }
            else
            {
                
                input.push_back(line[i]);
            }
        }
       
         for(int i = operation.size()-1; i >= 0;i--)
            input.push_back(operation[i]);
        
        return input;    
}
int OperationPriority(string operation)
{
    if(operation == "+" || operation == "-" )
        return 2;
    if(operation == "/" || operation == "*" )
        return 3;
    if(operation == "(" || operation == ")" )
        return 1; 
    if(operation == "=")
        return 0;
    return -1;    
}
bool IsOperation(string operation)
{
    
    if(operation == "+" || operation == "-" || operation == "/" || operation == "*" || operation == "=")
        return true;
    else 
        return false;    
}
void ResolutionProcess(vector<string> lineA,string &value,string&command)
{
    vector<Variable> V;
  
    string cell;
    
    value = to_string(numericMemory+1);
    cell = to_string(numericMemory);
    for(int i = 0;i<lineA.size();i++)
    {
         if(!IsOperation(lineA[i]))
         {
             if(existenceVariable(lineA[i])!=-1)
             {
                 
                 V.push_back(GlobalVariable[existenceVariable(lineA[i])]);
             }
         }
         else
         {
             if(V.size() > 1)
             {
                 OperationProcess(lineA[i],V[V.size() - 2],V[V.size() - 1],
                            V[V.size() - 2],cell,value,command);
                 V.erase(V.end());
                 V.erase(V.end());           
                 V.push_back(GlobalVariable[GlobalVariable.size()-1]);           
             }
         }
    }
    
}