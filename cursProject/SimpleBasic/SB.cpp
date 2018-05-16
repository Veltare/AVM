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
             
             if(existenceVariable(lineArray[2])!=-1)
                {
                   
                   for(int i = 0;i < lineArray.size()-1;i++)
                   {
                       
                       if(lineArray[i] == "(")
                       {
                          vector <string> temp;
                           int m = i+1;
                           
                           while(lineArray[m]!=")")
                           {
                               if(m > lineArray.size()-1)
                                  return "-1";
                                temp.push_back(lineArray[m]);
                                m++;
                           }
                           if(analysisCommand(line,temp)=="-1")
                           {
                                //for(int i = 0;i < temp.size();i++)
                                  //             cout<<temp[i]<<endl;
                               cout<<"ZAHOD"<<endl;
                               int c = i+1;
                               
                               while(c!=m)
                               {
                                   lineArray.erase(lineArray.begin()+i+1);
                                   c++;
                               }
                               for(int k = 0;k < temp.size();k++)
                                lineArray.insert(lineArray.begin()+i+1,temp[k]);
                                lineArray.erase(lineArray.begin()+i); 
                                lineArray.erase(lineArray.begin()+i+1);    
                                for(int i = 0;i < lineArray.size();i++)
                                    cout<<lineArray[i];
                               cout<<endl;  
                           }
                           
                           
                       }
                   }
                   for(int i = lineArray.size()-1;i >= 0;i--)
                   {
                    if(i-1 >= 0 && i+1 < lineArray.size())
                       if(existenceVariable(lineArray[i-1])!=-1 && existenceVariable(lineArray[i+1])!=-1 )
                       {
                          
                           if(lineArray[i] == "*" || lineArray[i] == "/")
                           {
                              
                            OperationProcess(lineArray[i],existenceVariable(lineArray[i-1]),existenceVariable(lineArray[i+1]),
                            existenceVariable(lineArray[i-1]),cell,value,command);
                            lineArray.erase(lineArray.begin()+i);
                            lineArray.erase(lineArray.begin()+i);
                            lineArray[i-1] = GlobalVariable[GlobalVariable.size()-1].name;
                            
                                     
                           }
                           else
                           {
                               PriorityOperation = true;
                           }
                        
                           
                       }
                   }
                   for(int i = 0;i < lineArray.size();i++)
                                    cout<<lineArray[i];
                               cout<<endl; 
                   for(int i = lineArray.size()-1;i >= 0;i--)
                   {
                       
                    if(i-1 >= 0 && i+1 < lineArray.size())
                       if(existenceVariable(lineArray[i-1])!=-1 && existenceVariable(lineArray[i+1])!=-1 )
                       {
                           
                            
                           if(lineArray[i] == "+" || lineArray[i] == "-")
                           {
                             
                            OperationProcess(lineArray[i],existenceVariable(lineArray[i-1]),existenceVariable(lineArray[i+1]),
                            existenceVariable(lineArray[i-1]),cell,value,command);
                            lineArray.erase(lineArray.begin()+i);
                            lineArray.erase(lineArray.begin()+i);
                           
                            lineArray[i-1] = GlobalVariable[GlobalVariable.size()-1].name;
                                        
                           }
                           else
                           {
                               PriorityOperation = true;
                           }
                          
                       }
                   }
                   for(int i = 0;i < lineArray.size();i++)
                                    cout<<lineArray[i];
                               cout<<endl; 
                   for(int i = 0;i < lineArray.size();i++)
                   {
                        if(lineArray[i] == "=")
                           {
                            
                            
                            command = "LOAD";
                            value =  GlobalVariable[existenceVariable(lineArray[i+1])].mem_address;
                            cell = to_string(numericMemory);
                            compliteString=cell+" "+command+" "+value;
                            GlobalString.push_back(compliteString);
                            numericMemory++;

                            command = "STORE";
                            value =  GlobalVariable[existenceVariable(lineArray[2])].mem_address;
                            cell = to_string(numericMemory);
                            compliteString=cell+" "+command+" "+value;
                            GlobalString.push_back(compliteString);
                            numericMemory++;   

                           }
                   }
                   
                }
                
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
int OperationProcess(string operation,int index1,int index2,int index3,string cell,string &value,string&command)
{

 
    string compliteString;
   
    string operand;
    if(IsFirst)
    {
        command = "LOAD";
        value =  GlobalVariable[index1].mem_address;
        cell = to_string(numericMemory);
        compliteString=cell+" "+command+" "+value;
        GlobalString.push_back(compliteString);
        numericMemory++;
        IsFirst = false;
    }
  
    if(operation == "-")
    {
    
    command = "SUB";
    value =  GlobalVariable[index2].mem_address;
    cell = to_string(numericMemory);
    compliteString=cell+" "+command+" "+value;
    GlobalString.push_back(compliteString);
    numericMemory++;
  
    }
    if(operation == "+")
    {
    command = "ADD";
    value =  GlobalVariable[index2].mem_address;
    cell = to_string(numericMemory);
    compliteString=cell+" "+command+" "+value;
    GlobalString.push_back(compliteString);
    numericMemory++;
    
    
    }
    if(operation == "*")
    {
    command = "MUL";
    value =  GlobalVariable[index2].mem_address;
    cell = to_string(numericMemory);
    compliteString=cell+" "+command+" "+value;
    GlobalString.push_back(compliteString);
    numericMemory++;
   
    }
    if(operation == "/")
    {
  
    command = "DIVIDE";
    value =  GlobalVariable[index2].mem_address;
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
        operand = GlobalVariable[index3].name+cell;
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

