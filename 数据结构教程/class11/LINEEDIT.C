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

void LineEdit()
{
  pSqStack S,T;
  char str[1000];
  int strlen=0;
  char e;
  char ch;

  InitStack(&S);
  InitStack(&T);

  ch=getchar();
  while(ch!=EOFILE)
   {
    while(ch!=EOFILE&&ch!='\n')
     {
       switch(ch){
	case '#':
	  Pop(S,&ch);
	  break;
	case '@':
	  ClearStack(S);
	  break;
	default:
	  Push(S,ch);
	  break;
	}
       ch=getchar();
     }
    if(ch=='\n')
      Push(S,ch);
      while(!StackEmpty(*S))
       {
	 Pop(S,&e);
	 Push(T,e);
       }
      while(!StackEmpty(*T))
       {
	 Pop(T,&e);
	 str[strlen++]=e;
       }
    if(ch!=EOFILE) ch=getchar();
  }
  str[strlen]='\0';
  printf("\n%s",str);

  DestroyStack(S);
  DestroyStack(T);
}

main()
{
  printf("\n\n\n\n");
  LineEdit();
  printf("\n\nWelcome to visit http://zmofun.yeah.net !");
}
