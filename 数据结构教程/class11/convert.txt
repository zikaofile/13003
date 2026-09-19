#include<stdio.h>
#include<malloc.h>
#include<conio.h>

typedef int SElemType;

#include "stack.h"

Status visit(SElemType * e)
{
  printf(" %d  ", *e);
}

void conversion()
{
 pSqStack S;
 SElemType e;

 int n;
 InitStack(&S);
 printf("Input a number to convert to OCT:\n");
 scanf("%d",&n);

 if(n<0)
   {
     printf("\nThe number must be over 0.");
     return;
   }
 if(!n) Push(S,0);

 while(n){
   Push(S,n%8);
   n=n/8;
 }

 printf("the result is:        ");
 while(!StackEmpty(*S)){
   Pop(S,&e);
   printf("%d",e);
 }
}

main()
{
  printf("\n\n\n\n");
  conversion();
  getch();
  printf("\n\nWelcome to visit http://zmofun.yeah.net !");
}
