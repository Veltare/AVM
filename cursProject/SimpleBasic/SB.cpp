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
const int SIZE = 100;
int current_step(0);
bool IsFirst = true;
bool PriorityOperation = true;
struct Variable
{
    string name;
    string mem_address;
    int value;
};
struct UnresolvedReferences
{
    string name;
    string mem_address;
};
int numericMemory(1);

vector<Variable> GlobalVariable;
vector<string> GlobalString;
vector<UnresolvedReferences>References;

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
bool isVariable(string value);
void SolutionUnresolved();
int existenceReferences(string A);
void SolutionVariable();
int CounterUnresolved(vector<string> line);
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
        fin.clear();
        IsFirst = false;
        //SolutionUnresolved();
        SolutionVariable();
        fin.seekg(0);
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
    if(IsFirst)
    {
        
        UnresolvedReferences *elem = new UnresolvedReferences;
        elem->name = arrayLine[0];
        if(References.size() > 0)
        {
            
            if(numericMemory == 0)
                numericMemory+=1;
            elem->mem_address = to_string(stoi(References[References.size()-1].mem_address,nullptr,10)+numericMemory);
            cout<<"]]"<<elem->mem_address<<endl;
            numericMemory = CounterUnresolved(arrayLine);
        }
        else
        {
            elem->mem_address = "0"; 
        }    
        numericMemory =  CounterUnresolved(arrayLine);
        References.push_back(*elem);
        for(int i = 0;i < arrayLine.size();i++)
        {
            if((existenceVariable(arrayLine[i])==-1))
               {
                  if(isValue(arrayLine[i])==true || isVariable(arrayLine[i]))
                  {
                    Variable *temp = new Variable;
                    temp->value = 0;
                    temp->name = arrayLine[i];
                    GlobalVariable.push_back(*temp);
                    
                  }
                  else
                  {
                      
                  }
               
               }
        }    
        return 0;
    }
    
    if(arrayLine.size() >= 2)
    {   
        cout<< arrayLine[1] <<endl;    
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
    string cell;
    string command;
    string value;
    
    
    
    
    //cout<<"R2"<<endl;
    cout<<line<<endl;
    //cout<<(existenceReferences(lineArray[2])==-1)<<endl;
    ///cout<<lineArray[2]<<endl;  

    
    if(line == "END")
        {  
            cout<<"TEST"<<endl;
            cell = to_string(current_step);  
            command = "HALT";
            string value = "0";
            if(existenceReferences(lineArray[0])!=-1)
            {
                cell = References[existenceReferences(lineArray[0])].mem_address;
                string compliteString=cell+" "+command+" "+value;
                GlobalString.push_back(compliteString);
                return "-1";
            }   
        
            
       
        }  

    if((!isValue(lineArray[2]) || isVariable(lineArray[2])) && existenceReferences(lineArray[2])==-1)
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
    
   
    if(line == "REM")
    {
      return "-1"; 
    }     
    else    
    if(line == "INPUT") //--> READ
    {
        cell = References[existenceReferences(lineArray[0])].mem_address;
       
        if(existenceVariable(lineArray[2])!=-1 && existenceReferences(lineArray[0])!=-1)
        {
            
            
            
            command = "READ";
            value =  GlobalVariable[existenceVariable(lineArray[2])].mem_address;
            
        }
        else
         {
             if(isVariable(lineArray[2]))
             {
                 command = "READ";
                 value = lineArray[2];
             }


         }   
        compliteString=cell+" "+command+" "+value;
        current_step++;

        return compliteString;      
    }
        
    else    
    if(line == "PRINT")//--> WRITE
       {
        cell = References[existenceReferences(lineArray[0])].mem_address;  
        if(existenceVariable(lineArray[2])!=-1 && existenceReferences(lineArray[0])!=-1)
        {
            
            
            
            command = "WRITE";
            value =  GlobalVariable[existenceVariable(lineArray[2])].mem_address;
        }
        else
         {
             if(isVariable(lineArray[2]))
             {
                 command = "WRITE";
                 value = lineArray[2];
             }


         }   

        compliteString=cell+" "+command+" "+value;
        current_step++;
   
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
 
            cell = to_string(current_step);
              
            command = "JUMP";
            if(existenceVariable(lineArray[2])!=-1 )
                {

                    value =  GlobalVariable[existenceVariable(lineArray[2])].mem_address;
                     
                    compliteString=cell+" "+command+" "+value;
                    current_step++;
                    return compliteString; 
                }
                else
                    if(existenceReferences(lineArray[0])!=-1 && existenceReferences(lineArray[2])!=-1)
                    {
                        cell = References[existenceReferences(lineArray[0])].mem_address;
                        value =  References[existenceReferences(lineArray[2])].mem_address;
                        
                        compliteString=cell+" "+command+" "+value;
                        
                        current_step++;
                        return compliteString; 
                    }    
              
            
        }
    else
            
    if(line == "IF")
        {
            
            command = "LOAD";
            if(existenceVariable(lineArray[2])!=-1)
                {
                   cell = References[existenceReferences(lineArray[0])].mem_address;
                    value =  GlobalVariable[existenceVariable(lineArray[2])].mem_address;
                    compliteString=cell+" "+command+" "+value;
                    GlobalString.push_back(compliteString);
                    current_step++;
                    
                    if(lineArray[5] == "GOTO" && existenceReferences(lineArray[6])!=-1)
                    {
                        
                        cell = to_string(current_step);
                        value = References[existenceReferences(lineArray[6])].mem_address;
                        command = "JNEG";
                        current_step++;    
                    }
                    else
                        return "-1";
                    compliteString=cell+" "+command+" "+value;
                    return compliteString; 
                }
                else
                {
                   return "-1";
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
bool isVariable(string value)
{
    locale loc;
    if(value.size()>1)
        return false;
    for(int i = 0;i<value.size();i++)
        {
            if(!isdigit(value[i],loc))
                return false;
        }
    if(isdigit(value[0],loc))
        return true;
     
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
int existenceReferences(string A)
{
    for(int i = 0;i<References.size();i++)
    {
        if(References[i].name == A)
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
        cell = to_string(current_step);
        compliteString=cell+" "+command+" "+value;
        GlobalString.push_back(compliteString);
        current_step++;
       
        command = "STORE";
        value =  V2.mem_address;
        cell = to_string(current_step);
        compliteString=cell+" "+command+" "+value;
        GlobalString.push_back(compliteString);
        current_step++;
    return 0;
    
    }
        command = "LOAD";
        value =  V1.mem_address;
        cell = to_string(current_step);
        compliteString=cell+" "+command+" "+value;
        GlobalString.push_back(compliteString);
        current_step++;
        
    
  
    if(operation == "-")
    {
    
    command = "SUB";
    value =  V2.mem_address;
    cell = to_string(current_step);
    compliteString=cell+" "+command+" "+value;
    GlobalString.push_back(compliteString);
    current_step++;
  
    }
    if(operation == "+")
    {
    command = "ADD";
    value =  V2.mem_address;
    cell = to_string(current_step);
    compliteString=cell+" "+command+" "+value;
    GlobalString.push_back(compliteString);
    current_step++;
    
    
    }
    if(operation == "*")
    {
    command = "MUL";
    value =  V2.mem_address;
    cell = to_string(current_step);
    compliteString=cell+" "+command+" "+value;
    GlobalString.push_back(compliteString);
    current_step++;
   
    }
    if(operation == "/")
    {
  
    command = "DIVIDE";
    value =  V2.mem_address;
    cell = to_string(current_step);
    compliteString=cell+" "+command+" "+value;
    GlobalString.push_back(compliteString);
    current_step++;
   
    
    }
    
    if(PriorityOperation == true)
    {
        
        int buffer = stoi(GlobalVariable[GlobalVariable.size()-1].mem_address,nullptr,10);           
        Variable *temp = new Variable;
        
        cell = to_string(buffer-1);
        //current_step++;
                   
        temp->mem_address = cell;
                   
        temp->value = 0;
        operand = V3.name+cell;
        temp->name = operand;
        GlobalVariable.push_back(*temp);
         
        command = "STORE";
        value =  temp->mem_address;
        cell = to_string(current_step);
        compliteString=cell+" "+command+" "+value;
        GlobalString.push_back(compliteString);
        current_step++;
        PriorityOperation = true;
        
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
void SolutionUnresolved()
{
    for(int i = 0;i < References.size();i++)
    {
        References[i].mem_address = to_string(i);
        cout<<"]]"<<References[i].mem_address<<endl;
    }
    
}
void SolutionVariable()
{
    int cell = SIZE - 1;
    int k = 0;
    for(int i = cell;i > SIZE - GlobalVariable.size()-1;i--)
    {
        GlobalVariable[k].mem_address = to_string(i);
        //cout<<GlobalVariable[k].mem_address<<endl;
        k++;
    }
    
}
int CounterUnresolved(vector<string> line)
{
    int counter(0);
    for(int i = 0;i < line.size();i++)
    {
               //cout<<line[i]<<"-> "; 
              // cout<<IsOperation(line[i]);
    }
              //  cout<<endl; 
    for(int i = 0;i < line.size();i++)
    {
       
        if(IsOperation(line[i]) && line[i].compare("=") < 0)
        {
           //cout<<"ZAHOD"<<endl; 
           counter+=3;
           continue;     
        }
        else
        if(IsOperation(line[i]) && line[i].compare("=") == 0)
        {
            //cout<<"ZAHOD2"<<endl; 
            counter+=2;
            continue;
        }
        if(line[i].compare("IF") == 0)
        {
            counter+=2;
            continue;
        }

       
    }
    cout<<"C: "<<counter<<endl;
    return counter;
}