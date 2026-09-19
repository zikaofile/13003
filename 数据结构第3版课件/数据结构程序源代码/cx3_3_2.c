#include<stdio.h>
typedef struct node                /*定义链栈结点*/
{
    int data;                      /*这里以整型数据为例*/
    struct node*next;              /*指针类型,存放下一个结点地址*/
}NODE;
 
NODE *crea_linkstack()             /*建立链栈*/
{
    /*参考前面进栈程序3-2*/
}    

NODE *popstack(NODE *top,int *p)
{
    NODE *q;                      /*定义q结点*/
    if(top!=NULL)                 /*如果栈不空*/
    {
        q=top;
        *p=top->data;             /*将栈顶元素放入*p中*/
        top=top->next;            /*修改top指针*/
        free(q);                  /*释放原栈顶空间*/
    }
    return(top);                  /*返回栈顶指针*/
}

void print(NODE *top)              /*输出链栈中各元素*/
{
    /*参考前面进栈程序3-2*/
}

main()                      /*主程序*/
{
    int y=0;                  /*将入栈的元素*/
    NODE *a; 
    a=crea_linkstack();     /*建立链栈*/
    print(a);                                   /*输出整个链栈*/
    a=popstack(a,&y);                           /*出栈一个元素到y*/
    printf("\nOutput the element of poplinkstack : %d\n",y);
    print(a);                                   /*输出整个链栈*/
}
程序运行结果:
Input number of push linkstack : 5（回车）
Input 5 elements of push linkstack : 1 2 3 4 5（回车）
Output the linkstack : 5 4 3 2 1 
Output the element of poplinkstack : 5
Output the linkstack : 4 3 2 1 