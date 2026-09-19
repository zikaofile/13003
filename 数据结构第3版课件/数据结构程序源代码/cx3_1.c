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

int GetTop_sq(SqStack *s,elementtype *x)    /*取栈顶元素,若栈s非空,用*x返回栈顶元素*/
{
    if(s->top==-1)
        return(0);                          /*栈空返回0*/
    else
    {
        *x=s->element[s->top];
        return(1);
    }
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

int Empty_sq(SqStack *s)                    /*判断栈s是否为空,空则返回1,非空返回0*/
{
    return(s->top==-1);
}

void print(SqStack s)                       /*输出栈元素*/
{
    int i;
    if(s.top!=-1)                           /*栈非空,输出栈元素*/
    {
	printf("Output elements of stack : ");
        for(i=0;i<=s.top;i++)
	     printf("%d ",s.element[i]);
    }
    else
	printf("The stack is empty!!!");
    printf("\n");
}

main()                                       /*主程序*/
{
    SqStack stack;
    int i;
    elementtype y;
    elementtype z;

    stack=InitStack_sq();                    /*建立空栈stack*/

    if(Empty_sq(&stack)!=0)                  /*判断栈stack是否为空*/
	printf("\nThe stack is empty!");
    else
	printf("\nThe stack is not empty!");

    printf("\nPush 5 elements to stack : ");
    for(i=1;i<=5;i++)                        /*入栈5个元素*/
    {
	scanf("%d",&y);
        Push_sq(&stack,y);
    }
    print(stack);                            /*入栈5个元素后输出栈元素*/

    GetTop_sq(&stack,&z);                    /*取栈顶元素,送z*/
    printf("Element of top is : %d \n",z);   /*输出栈顶元素z*/

    printf("Pop 3 elements from stack: ");
    for(i=1;i<=3;i++)                        /*出栈3个元素*/
    {
	Pop_sq(&stack,&z);
	printf("%d ",z);                     /*按出栈次序输出栈元素*/
    }
    printf("\n");
    print(stack);                            /*出栈3个元素后输出栈元素*/
    if(Empty_sq(&stack)!=0)                  /*判断栈stack是否为空*/
	printf("The stack is empty!\n");
    else
	printf("The stack is not empty!\n");

    printf("Pop 2 elements from stack: ");
    for(i=1;i<=2;i++)                        /*出栈2个元素*/
    {
	Pop_sq(&stack,&z);
	printf("%d ",z);                     /*按出栈次序输出栈元素*/
    }
    printf("\n");
    print(stack);                            /*出栈2个元素后输出栈元素*/
    if(Empty_sq(&stack)!=0)                  /*判断栈stack是否为空*/
	printf("The stack is empty!\n");
    else
	printf("The stack is not empty!\n");

}
程序运行结果：
The stack is empty!
Push 5 elements to stack : 1 2 3 4 5（回车）
Output elements of stack : 1 2 3 4 5
Element of top is : 5
Pop 3 elements from stack: 5 4 3
Output elements of stack : 1 2
The stack is not empty!
Pop 2 elements from stack: 2 1
The stack is empty!!!
The stack is empty!