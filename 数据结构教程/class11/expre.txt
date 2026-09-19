#include<string.h>
#include<stdio.h>
#include<malloc.h>
#include<conio.h>

#define EOFILE '`'

typedef char SElemType;

#include "stack.h"

Status visit(SElemType * e)
{
  printf("%c", *e);
}

char OP[10]={'+','-','*','/','(',')','#'};
int precede[7][7]={
      1,1,2,2,2,1,1,
      1,1,2,2,2,1,1,
      1,1,1,1,2,1,1,
      1,1,1,1,2,1,1,
      2,2,2,2,2,3,0,
      1,1,1,1,0,1,1,
      2,2,2,2,2,0,3};

int In(char c,char *op)
{
  int i=0;
  while(i<7)
     if(c==op[i++])
       return 1;
  return 0;
}

char Precede(char op,char c)
{
  int pos_op;
  int pos_c;
  int i;
  for(i=0;i<7;i++)
    {
      if(op==OP[i]) pos_op=i;
      if(c==OP[i]) pos_c=i;
    }
  switch(precede[pos_op][pos_c])
    {
      case 1:  return '>';
      case 2:  return '<';
      case 3:  return '=';
    }
}

char Operate(int a,char theta,int b)
{
  switch(theta)
    {
      case '+':return a+b-'0';
      case '-':return a-b+'0';
      case '*':return (a-'0')*(b-'0')+'0';
      case '/':return (a-'0')/(b-'0')+'0';
    }
}

char EvaluateExpression()
{
  SqStack *OPND,*OPTR;
  char c,x,theta;
  char a,b;
  InitStack(&OPTR);  Push(OPTR,'#');
  InitStack(&OPND);
  c=getchar();
  while(c!='#'||GetTop(*OPTR)!='#')
    {
      if(!In(c,OP))
	{Push(OPND,c);c=getchar();}
      else
	switch(Precede(GetTop(*OPTR),c))
	  {
	    case '<':
	      Push(OPTR,c);
	      c=getchar();
	      break;
	    case '=':
	      Pop(OPTR,&x);
	      c=getchar();
	      break;
	    case '>':
	      Pop(OPTR,&theta);
	      Pop(OPND,&b);  Pop(OPND,&a);
	      Push(OPND,Operate(a,theta,b));
	      break;
	  }
    }
  c=GetTop(*OPND);
  DestroyStack(OPTR);
  DestroyStack(OPND);
  return c;
}


main()
{
  char i;
  printf("\n\n\n\nOnly within 0..9 evaluation,input a expression end with symbol #:\n");
  i=EvaluateExpression();
  printf("\nThis expression's result is:   ");
  printf("%d\n\n\n\n",i-'0');
  printf("\n\nWelcome to visit http://zmofun.yeah.net !");
}
