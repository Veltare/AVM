#include <iostream>
#include "./HDD.h"
#include <string>
#include <vector>     
#include <iterator> 
#include "../LAB2/myTerm.h"
#include "../LAB3/myBigChars.h"

using namespace std;

struct HDDCELL
{
    double size;
    string TypeCell;
    unsigned int active;


};

void HDD_work();
void Print_HDD(vector<HDDCELL> table);
//-------------------------------------------------------------------//
int main()
{

    HDD_work();
    return 0;
} 

void HDD_work()
{
    double amountHDD(0);
    double sizeCELL(0);
    unsigned int buffer(0);
    vector<HDDCELL> table;
    HDDCELL cell;
    string text;

    tIDECHS geometry;
    tCHS chs;
   


    cout<<"----Введите tIDECHS геометрию----"<<endl;
    do
    {
    cout<<"Введите С"<<endl;
    cin >> buffer;
    }
    while((buffer>>16)&0x1 == 1);

    do
    {
    cout<<"Введите H"<<endl;
    cin >> buffer;
    }
    while((buffer>>4)&0x1 == 1);

    do
    {
    cout<<"Введите S"<<endl;
    cin >> buffer;
    }
    while((buffer>>8)&0x1 == 1);

    g_idechs2chs(geometry, &chs);
    amountHDD = chs.c*chs.h*chs.s;
    amountHDD/=(1024*1024);
    
    while(true)
    {
        
        cout<<"Размер HDD - "<<amountHDD<<"GB"<<endl;
        text.clear();
        while(text.empty())
        {
            cout<<"Введите размер тома в MB"<<endl;
            cin >> text;
            sizeCELL = stod(text)/1024;    
            if(sizeCELL > amountHDD)
            {
                cout<<"Некорректный размер"<<endl;
                text.clear();
            }
        }
        cell.size = sizeCELL;
        text.clear();
        
        do{
            cout<<"Выберите формат раздела NTFS - 0 / FAT16 - 1 / FAT32 - 2 / LinuxSwap - 3"<<endl;
            cin >> buffer;
            switch (buffer)
            {
                case 0:
                {
                    cell.TypeCell = "NTFS";
                    break;
                }
                case 1:
                {
                    cell.TypeCell = "FAT16";
                    break;
                }
                case 2:
                {
                    cell.TypeCell = "FAT32";
                    break;
                }

                case 3:
                {
                    cell.TypeCell = "LinuxSwap";
                    break;
                }
            default:
                break;
            }
        }
        while(buffer > 3 || buffer < 0);

        while(text.empty())
        {
            cout<<"Том Активен?! y / n"<<endl;
            cin>>text;
            if(text=="y")
            {
                cell.active = 128;
                break;
            }
            if(text=="n")
            {
                cell.active = 0;
                break;
            }
            text.clear();
        }

        if(amountHDD-sizeCELL < 0)
        {
            cout<<"Память переполнена!"<<endl;
            break;
        }
        else
        {
            table.push_back(cell);
            amountHDD-=sizeCELL;
        }
        cout<<"Если хотите закончить введите 0!"<<endl;
        cin >> text;
        if(text=="0")
            {
                break;
            }
    }
 Print_HDD(table);
}


void Print_HDD(vector<HDDCELL> table)
{
    int x(4),y(4);
    mt_clrscr();
    for(int i = 0;i<table.size();i++)
    {
    mt_gotoXY(x,y);
    bc_box(x,y,x+10,y+4);
    bc_box(x,y+10,x+10,y+4);
    bc_box(x,y+20,x+10,y+4);
    mt_gotoXY(x+1,y+1);
    cout<<"Раздел"<<endl;
    mt_gotoXY(x+12,y+1);
    cout<<"Активно"<<endl;
    mt_gotoXY(x+22,y+1);
    cout<<"Размер"<<endl;
    mt_gotoXY(x+1,y+3);
    cout<<table[i].TypeCell<<endl;
    mt_gotoXY(x+12,y+3);
    cout<<table[i].active<<endl;
    mt_gotoXY(x+22,y+3);
    cout<<table[i].size<<endl;
    y+=4;
    
    }
    mt_gotoXY(2,40);
}