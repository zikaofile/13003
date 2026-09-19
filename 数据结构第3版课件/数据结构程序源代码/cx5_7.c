#include<stdio.h>
#define QUEUESIZE 20
typedef struct node
{   int data;
    int ltag,rtag;              /*线索标志域，取值为0或1*/
    struct node *lchild;
    struct node *rchild;
}BINTNODE, *BINTREE;            /*定义二叉链表指针类型*/
BINTREE pre=NULL;               /*全局变量,用于二叉树线索化*/

createbintree(BINTREE *t)       /*建立二叉树，且每个结点的线索标志域均为1*/
{    
    /*参考中序线索二叉树算法的程序5-6*/
}

void inthread(BINTREE ptr)                   /*中序线索化二叉树*/
{
     /*参考中序线索二叉树算法的程序5-6*/
}

void inorder(BINTREE t)                      /*线索二叉树中序遍历输出*/
{   BINTREE ptr;
    ptr=t;                                   /*指向根结点*/
    if(ptr!=NULL)
    {
        while(ptr->ltag==0)
            ptr=ptr->lchild;                 /*找到根结点的最左端结点*/
        do
        {
	    printf("%d ",ptr->data);         /*输出结点内容*/
	    if(ptr->rtag==1)                 /*右子树结点是否是线索*/
            {
                ptr=ptr->rchild;             /*往右子树走*/
            }
            else
            {
                ptr=ptr->rchild;             /*先到右子树结点*/
                while(ptr->ltag==0)          /*当右子树结点有左儿子*/
                   ptr=ptr->lchild;          /*找到右子树的最左端结点*/
            }
	}while(ptr!=NULL);
    }
}

main() /*主函数*/
{   BINTREE t=NULL;
    printf("\nplease input nodes of BINTREE : ");
    createbintree(&t);                            /*建立二叉树*/
    inthread(t);                                  /*中序线索化二叉树*/
    printf("the thinorder is : ");
    inorder(t);                                   /*线索二叉树中序遍历*/
}
程序运行结果（以图5.14二叉树为例）：
please input nodes of BINTREE : 1 2 4 0 0 5 0 0 3 0 6 0 0（回车）
the thinorder is : 4 2 5 1 3 6