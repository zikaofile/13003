/*
    Author:     zmofun
    HomePage:   http://zmofun.yeah.net
    CopyRight:  All rights reserved.
    Date:       2000.3

    Before inlcude this file,define type SElemType first.
*/

#include "simuc.h"

#define OVERFLOW -1
#define STACK_INIT_SIZE 1000
#define STACKINCREMENT 10

struct STACK
{
  SElemType *base;
  SElemType *top;
  int stacksize;
};

typedef struct STACK SqStack;
typedef struct STACK *pSqStack;

Status InitStack(SqStack  **S);
Status DestroyStack(SqStack *S);
Status ClearStack(SqStack *S);
Status StackEmpty(SqStack S);
int StackLength(SqStack S);
SElemType GetTop(SqStack S);
Status Push(SqStack *S,SElemType e);
Status Pop(SqStack *S,SElemType *e);
Status StackTraverse(SqStack S,Status (*visit)());

Status InitStack(SqStack **S)
{
  (*S)=(SqStack *)malloc(sizeof(SqStack));
  (*S)->base=(SElemType *)malloc(STACK_INIT_SIZE *sizeof(SElemType));
  if(!(*S)->base)exit(OVERFLOW);
  (*S)->top=(*S)->base;
  (*S)->stacksize=STACK_INIT_SIZE;
  return OK;
}

Status DestroyStack(SqStack *S)
{
 free(S->base);
 free(S);
}

Status ClearStack(SqStack *S)
{
  S->top=S->base;
}

Status StackEmpty(SqStack S)
{
  if(S.top==S.base) return TRUE;
  else
    return FALSE;
}

int StackLength(SqStack S)
{
  int i;
  SElemType *p;
  i=0;
  p=S.top;
  while(p!=S.base)
    {p++;
     i++;
    }
}

SElemType GetTop(SqStack S)
{
  if(S.top==S.base) return ERROR;
  return *(S.top-1);
}

Status Push(SqStack *S,SElemType e)
{
 /*
  if(S->top - S->base>=S->stacksize)
   {

     S->base=(SElemType *) realloc(S->base,
	    (S->stacksize + STACKINCREMENT) * sizeof(SElemType));
     if(!S->base)exit(OVERFLOW);
     S->top=S->base+S->stacksize;
     S->stacksize += STACKINCREMENT;
   }
  */

  *(S->top++)=e;
  return OK;
}

Status Pop(SqStack *S,SElemType *e)
{
  if(S->top==S->base) return ERROR;
  *e=*(--(S->top));
  return OK;
}


Status StackTraverse(SqStack S,Status (*visit)())
{
  while(S.top>S.base)
     visit(--S.top);
}
