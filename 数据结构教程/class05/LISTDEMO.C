#include<stdio.h>
#include<malloc.h>
#include<conio.h>

#define ERROR 0
#define OK 1
#define EQUAL 1

struct STU{
  char name[20];
  char stuno[10];
  int age;
  int score;
}stu[50];
typedef struct STU ElemType;

struct LIST
{
  ElemType elem[50];
  int length;
};
typedef struct LIST List;


int init(List **L)
{
  *L=(List *)malloc(sizeof(List));
  (*L)->length=0;
}

int ListLength(List *L)
{
  return L->length;
}

void GetElem(List L,int i,ElemType *e)
{
  *e=L.elem[i];
}
int EqualList(ElemType *e1,ElemType *e2)
{
  if (strcmp(e1->name,e2->name))
    return 0;
  if (strcmp(e1->stuno,e2->stuno))
    return 0;
  if (e1->age!=e2->age)
    return 0;
  if (e1->score!=e2->score)
    return 0;
  return 1;
}
int LocateElem(List *La,ElemType e,int type)
{
  int i;
  switch (type)
    {
      case EQUAL:
	for(i=0;i<La->length;i++)
	  if(EqualList(&La->elem[i],&e))
	    return 1;
	break;
      default:
	break;
    }
  return 0;
}
void UnionList(List *La, List *Lb)
{
  int La_len,Lb_len;
  int i;
  ElemType e;

  La_len=ListLength(La);  Lb_len=ListLength(Lb);
  for(i=0;i<Lb_len;i++)
    {
      GetElem(*Lb,i,&e);
      if(!LocateElem(La,e,EQUAL))
	ListInsert(La,++La_len,e);
    }

}

int printlist(List L)
{
  int i;
  printf("name       stuno        age     score\n");
  for(i=0;i<L.length;i++)
      printf("%-10s %s\t%d\t%d\n",  L.elem[i].name,  L.elem[i].stuno,
	  L.elem[i].age,  L.elem[i].score);
  printf("\n");
}

int ListInsert(List *L,int i,struct STU e)
{
  struct STU *p,*q;
  if (i<1||i>L->length+1) return ERROR;
  q=&(L->elem[i-1]);
  for(p=&L->elem[L->length-1];p>=q;--p)
    *(p+1)=*p;
  *q=e;
  ++L->length;
  return OK;
}/*ListInsert Before i */


main()
{
  struct STU e;
  List *La,*Lb;

  clrscr();

  printf("\n\n-------------------List Demo is running...----------------\n\n");
  printf("First is InsertList function.\n");
  init(&La);

  strcpy(e.name,"stu1");
  strcpy(e.stuno,"100001");
  e.age=80;
  e.score=1000;
  ListInsert(La,1,e);
  strcpy(e.name,"stu2");
  strcpy(e.stuno,"100002");
  e.age=80;
  e.score=1000;
  ListInsert(La,2,e);

  printlist(*La);
  printf("List A length now is  %d.\n\n",La->length);
  getch();

  strcpy(e.name,"stu3");
  strcpy(e.stuno,"100003");
  e.age=80;
  e.score=1000;
  ListInsert(La,3,e);

  printlist(*La);
  printf("List A length now is  %d.\n\n",La->length);
  getch();

  init(&Lb);

  strcpy(e.name,"zmofun");
  strcpy(e.stuno,"100001");
  e.age=80;
  e.score=1000;
  ListInsert(Lb,1,e);
  strcpy(e.name,"bobjin");
  strcpy(e.stuno,"100002");
  e.age=80;
  e.score=1000;
  ListInsert(Lb,2,e);

  strcpy(e.name,"stu1");
  strcpy(e.stuno,"100001");
  e.age=80;
  e.score=1000;
  ListInsert(Lb,3,e);

  printlist(*Lb);
  printf("List B length now is  %d.\n\n",Lb->length);
  getch();

  printf("Second is UnionList function.\n");
  printf("Now union List A and List B.....\n");
  UnionList(La,Lb);
  printlist(*La);
  printf("List A length now is  %d.\n\n",La->length);
  getch();
  clrscr();
  printf("\n\n\n\n\n\nWelcome to visit http://zmofun.heha.net !\n\n\n\n\n\n\n");

}

