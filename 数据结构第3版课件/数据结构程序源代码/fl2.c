#include <stdio.h>
#define MAXLEN 10
typedef int elementtype;
typedef struct                              /*栈的顺序存储结构定义*/
{
    elementtype element[MAXLEN];            /*存放栈元素的数组*/
    int top;                                /*栈指针*/
}SqStack;

SqStack InitStack_sq()                      /*建立一个空栈s*/
{   
    SqStack s;
    s.top=-1;
    return(s);
}

int Push_sq(SqStack *s,elementtype x)       /*进栈操作,若栈s未满，将元素x进栈*/
{
    if(s->top==MAXLEN-1)
        return(0);                          /*栈满返回0*/
    s->top++;
    s->element[s->top]=x;
    return(1);
}

int Pop_sq(SqStack *s,elementtype *x)       /*出栈操作,若栈s非空,删除s的栈顶元素,并用*x返回栈顶元素*/
{
    if(s->top==-1)
        return(0);                          /*栈空返回0*/
    *x=s->element[s->top];
    s->top--;
    return(1);
}

void Empty_sq(SqStack *s)                   /*判断栈空函数*/
{
   if(s->top==-1)                           /*栈空*/
      printf("The stack is empty!\n");
   else                                     /*栈不空*/
      printf("The stack is not empty!\n");
   return;
}

void print(SqStack s)                       /*输出栈元素*/
{
    int i;
    if(s.top!=-1)                           /*栈非空,输出栈元素*/
    {
	printf("\nOutput elements of stack : ");
        for(i=0;i<=s.top;i++)
	     printf("%d ",s.element[i]);
    }
    else
	printf("The stack is empty!!!");
    printf("\n");
}

main()                                         /*主程序*/
{
    SqStack stack;
    int i;
    elementtype z;
    stack=InitStack_sq();                      /*建立空栈stack*/
    printf("\nPush 1 to 9 elements to stack !");
    for(i=1;i<=9;i++)                          /*入栈1～9*/
        Push_sq(&stack,i);                     /*进栈操作*/
    print(stack);                              /*入栈9个元素后输出栈元素*/

    printf("Pop 4 elements from stack:");
    for(i=1;i<=4;i++)                          /*出栈4个元素*/
    {
	Pop_sq(&stack,&z);                     /*出栈操作*/
	printf("% d",z);                       /*按出栈次序输出栈元素*/
    }
    print(stack);                              /*出栈4个元素后输出栈元素*/
    Empty_sq(&stack);                          /*调用判断栈空函数*/
}
程序运行结果：
Push 1 to 9 elements to stack !
Output elements of stack : 1 2 3 4 5 6 7 8 9
Pop 4 elements from stack: 9 8 7 6
Output elements of stack : 1 2 3 4 5 
The stack is not empty!