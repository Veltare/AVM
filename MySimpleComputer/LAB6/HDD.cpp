#include <iostream>
#include "./HDD.h"

//---------------------------------------------
//-------------------------------------------------------------------//
int g_lba2chs(tLBA arg1,tCHS*arg2)
{
   arg2->s = (arg1%S)+1;
   arg2->h = ((arg1-(arg2->s-1))/S)%H;
   arg2->c = (arg1-(arg2->s-1)-arg2->h*S)/(H*S);
   return 1;
}
//-------------------------------------------------------------------//
int g_lba2large(tLBA arg1,tLARGE*arg2)

{
    int c(0),h(0),s(0);
    c = (arg1-((arg1%S)+1-1)-((arg1-((arg1%S)-1))/S)%H*S)/(H*S);
    h = ((arg1-((arg1%S)+1-1))/S)%H;
    s = (arg1%S)+1;
     arg2->c |= (c & 0xFF) | (c & 0x300);
     arg2->s = (s & 0x3F);  
     arg2->h = h&0xFF;
    
    return 1;
}
//-------------------------------------------------------------------//
int g_lba2idechs(tLBA arg1,tIDECHS*arg2)
{
   
   arg2->s = ((arg1%S)+1)&0xFF;
   arg2->h = (((arg1-(arg2->s-1))/S)%H)&0x0F;
   arg2->c = ((arg1-(arg2->s-1)-arg2->h*S)/(H*S))&0xFFFF; 
   return 1;
}
//-------------------------------------------------------------------//
int g_chs2large(tCHS arg1,tLARGE*arg2)
{
    int c(0),h(0),s(0);
    c = arg1.c;
    h = arg1.h;
    s = arg1.s;
     arg2->c |= (c & 0xFF) | (c & 0x300);
     arg2->s = (s & 0x3F);  
     arg2->h = h&0xFF;

    return 1;
}
//-------------------------------------------------------------------//
int g_chs2lba(tCHS arg1,tLBA*arg2)
{
  *arg2 = (arg1.c*H+arg1.h)*S+arg1.s-1;
  return 1;
}
//-------------------------------------------------------------------//
int g_chs2idechs(tCHS arg1,tIDECHS* arg2)
{
    arg2->c = arg1.c;
    arg2->h = arg1.h & 0x0F;
    arg2->s = arg1.s;
    return 1;
}
//-------------------------------------------------------------------//
int g_large2chs(tLARGE arg1,tCHS* arg2)
{
    arg2->h = arg1.h;
    arg2->c = arg1.c;  
    arg2->s = arg1.s&0x3F;
    return 1;
}
//-------------------------------------------------------------------//
int g_large2idechs(tLARGE arg1,tIDECHS*arg2)
{
    
    arg2->h = arg1.h & 0x0F;
    arg2->c = arg1.c;  
    arg2->s = arg1.s&0x3F;
    return 1;
}
//-------------------------------------------------------------------//
int g_large2lba(tLARGE arg1,tLBA*arg2)
{
    int c(0),h(0),s(0);
    c = arg1.c;
    h = arg1.h & 0x0F;
    s = arg1.s&0x3F;
    *arg2 = (c*H+h)*S+s-1;
    return 1;
}
//-------------------------------------------------------------------//
int g_idechs2chs(tIDECHS arg1,tCHS*arg2)
{
    arg2->c = arg1.c&0x3FF;
    arg2->h = arg1.h;
    arg2->s = arg1.s&0x0F;
    return 1;
}
//-------------------------------------------------------------------//
int g_idechs2large(tIDECHS arg1,tLARGE* arg2)
{
    int c(0),h(0),s(0);
    c = arg1.c;
    h = arg1.h;
    s = arg1.s;
    arg2->c |= (c & 0xFF) | (c & 0x300);
    arg2->s = (s & 0x3F);  
    arg2->h = h&0xFF;
    return 1;
}
//-------------------------------------------------------------------//
int g_idechs2lba(tIDECHS arg1,tLBA* arg2)
{
     *arg2 = (arg1.c*H+arg1.h)*S+arg1.s-1;
    return 1;
}
//-------------------------------------------------------------------//


int a_lba2chs(tCHS geometry,tLBA arg1,tCHS* arg2)
{
    arg2->c = (int)(arg1 / geometry.c / geometry.h);
    arg2->h = (int)(arg1/geometry.s)%geometry.h;
    arg2->s = (int)(arg1%geometry.h+1);
    return 0;
}
int a_lba2large(tLARGE geometry,tLBA arg1,tLARGE* arg2) 
{
  //8 bit Head
     arg2->s = ((arg1 / geometry.c) / geometry.h)&0x3F;
     arg2->h = (arg1 / geometry.s) % geometry.h;
     arg2->c = arg1 % geometry.h + 1;
    return 0;
}
int a_lba2idechs(tIDECHS geometry,tLBA arg1,tIDECHS* arg2)
{
    arg2->s = (int)(arg1/geometry.c)/geometry.h;
    arg2->h = (int)(arg1/geometry.s)%geometry.h;
    arg2->c = (int)(arg1%geometry.h+1);
    return 0;
}
int a_chs2lba(tCHS geometry,tCHS arg1,tLBA* arg2)
{
    *arg2 = (arg1.c*geometry.h+arg1.h)*geometry.s + arg1.s - 1;
    return 0;
}
int a_large2lba(tLARGE geometry,tLARGE arg1,tLBA* arg2)
{
   *arg2 = (arg1.c * geometry.h + arg1.h) *geometry.s + arg1.s - 1;
    return 0;
}
int a_idechs2lba (tIDECHS geometry, tIDECHS arg1, tLBA * arg2)
{
    *arg2 = (arg1.c*geometry.h+arg1.h)*geometry.s+arg1.s - 1;
    return 0;
}
int a_large2chs (tLARGE geometry1, tCHS geometry2, tLARGE arg1, tCHS *arg2)
{
    tLBA tempLBA;
    a_large2lba(geometry1, arg1, &tempLBA);
    a_lba2chs(geometry2, tempLBA, arg2);
    return 0;
}
int a_large2idechs (tLARGE geometry1, tIDECHS geometry2, tLARGE arg1,tIDECHS *arg2)
{
    tLBA tempLBA;
    a_large2lba(geometry1, arg1, &tempLBA);
    a_lba2idechs(geometry2, tempLBA, arg2);
    return 0;
}
int a_chs2large (tCHS geometry1, tLARGE geometry2, tCHS arg1, tLARGE *arg2)
{
    tLBA tempLBA;
    a_chs2lba(geometry1, arg1, &tempLBA);
    a_lba2large(geometry2, tempLBA, arg2);
    return 0;
}
int a_idechs2large (tIDECHS geometry1, tLARGE geometry2, tIDECHS arg1,tLARGE *arg2)
{
     tLBA tempLBA;
     a_idechs2lba(geometry1, arg1, &tempLBA);
     a_lba2large(geometry2, tempLBA, arg2);
     return 0;
}
int a_chs2idechs (tCHS geometry1, tIDECHS geometry2, tCHS arg1, tIDECHS* arg2)
{
    tLBA tempLBA;
    a_chs2lba(geometry1, arg1, &tempLBA);
    a_lba2idechs(geometry2, tempLBA, arg2);
    return 0;
}
int a_idechs2chs (tIDECHS geometry1, tCHS geometry2, tIDECHS arg1, tCHS* arg2)
{
    tLBA tempLBA;
    a_idechs2lba(geometry1, arg1, &tempLBA);
    a_lba2chs(geometry2, tempLBA, arg2);
    return 0;
}