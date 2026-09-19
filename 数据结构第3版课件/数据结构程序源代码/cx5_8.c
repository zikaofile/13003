#include <stdlib.h>
#include<stdio.h>
typedef struct binode                    /*定义结点数据类型*/
{ 
    int data;
    struct binode *lchild,*rchild;
}BITNODE,*BITREE;
    
BITREE insertbst(BITREE s,BITREE t)                 /*在二叉排序树中插入结点*/
{
    if(t==NULL)
        t=s;                     /*如果二叉排序树为空树,则插入的结点为根结点*/
    else 
        if(s->data<t->data)
            t->lchild=insertbst(s,t->lchild);    /*数据小于根结点,插入左子树*/
        else
            t->rchild=insertbst(s,t->rchild);    /*数据大于根结点,插入右子树*/
    return t;
}

BITREE createordbt()                             /*创建二叉排序树*/
{
    BITREE s,t;
    int x; 
    t=NULL;
    printf("\nInput data please : ");
    scanf("%d",&x);                              /*输入结点数据*/
    while(x!=0)                                  /*输入0表示结束*/
    {
       s=(BITREE)malloc(sizeof(BITNODE));        /*为结点分配空间*/
       s->data=x;                                /*为生成的结点赋值*/
       s->lchild=NULL;
       s->rchild=NULL; 
       t=insertbst(s,t);                         /*调用插入结点函数*/
       scanf("%d",&x);
    }
    return t;
}

inorder(BITREE t)                                /*中序遍历二叉排序树*/
{
    if(t!=NULL)
    {
        inorder(t->lchild);
        printf("%d ",t->data);                   /*输出结点数据*/
        inorder(t->rchild);
    }
}

main()                               /*主程序*/
{
    BITREE root;                     /*定义二叉排序树的根结点*/
    printf("\n");
    root=createordbt();              /*创建二叉排序树*/
    printf("\nThe inorder is : "); 
    inorder(root);                   /*中序遍历二叉排序树*/
}
程序运行结果：
Input data please : 3 5 6 2 8 5 0（回车）
The inorder is : 2 3 5 5 6 8
程序运行时，输入数据的次序可以打乱，如 2 8 5 3 5 6 0（回车），函数createordbt()会产生不同的
二叉排序树，但只要输入数据不变，中序遍历二叉排序树的结果是一样的，总是：2 3 5 5 6 8 。