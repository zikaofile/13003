/*
    Author:     zmofun      
    HomePage:   http://zmofun.yeah.net
    CopyRight:  All rights reserved.
    Date:       2000.3
    
    
    Before include this file,you must define this type:SequListElemType ;
*/


#include "simuc.h"
#include<stdio.h>
#include<malloc.h>
#include<conio.h>

struct SequLIST
{
  SequListElemType *elem;
  int length;
};

typedef struct SequLIST SequList;


int SequListInit(SequList **L,int itemnum)
{
  *L=(SequList *)malloc(sizeof(SequList));
  (*L)->elem=(SequListElemType *)malloc(itemnum*sizeof(SequListElemType));
  (*L)->length=0;
}

int SequListDestroy(SequList *L)
{
  free(L->elem);
  free(L);
}
int SequListLength(SequList *L)
{
  return L->length;
}

void GetElem(SequList L,int i,SequListElemType *e)
{
  *e=L.elem[i];
}

void UnionSequList(SequList *La, SequList *Lb,int LocateElem())
{
  int La_len,Lb_len;
  int i;
  SequListElemType e;

  La_len=SequListLength(La);  Lb_len=SequListLength(Lb);
  for(i=0;i<Lb_len;i++)
    {
      GetElem(*Lb,i,&e);
      if(!LocateElem(La,e,EQUAL))
	SequListInsert(La,++La_len,e);
    }

}


int SequListInsert(SequList *L,int i,SequListElemType e)
{
  SequListElemType *p,*q;
  if (i<1||i>L->length+1) return ERROR;
  q=&(L->elem[i-1]);
  for(p=&L->elem[L->length-1];p>=q;--p)
    *(p+1)=*p;
  *q=e;
  ++L->length;
  return OK;
}/*SequListInsert Before i */

SequListDelete(SequList *L,int i)
{
  SequListElemType *p,*q;
  if (i<1||i>L->length) return ERROR;
  q=&(L->elem[L->length-1]);
  free(L->elem[i-1].base);
  for(p=&(L->elem[i-1]);p<=q;p++)
    *p=*(p+1);
  L->length--;

}

