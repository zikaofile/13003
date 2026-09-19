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
{    int a;
     scanf("%d",&a);
     if(a==0)
         *t=NULL;
     else
     {   *t=(BINTNODE*)malloc(sizeof(BINTNODE));
	 (*t)->data=a;
         (*t)->ltag=1;
         (*t)->rtag=1;
         createbintree(&(*t)->lchild);
         createbintree(&(*t)->rchild);
     }
}

void inthread(BINTREE ptr)                    /*中序线索化二叉树*/
{
    if(ptr!=NULL)                             /*对非空树进行中序线索化*/
    {
	inthread(ptr->lchild);                /*左子树线索化*/
	if(ptr->lchild==NULL)                 /*建立前驱线索*/
            ptr->lchild=pre;
        else
	    ptr->ltag=0;
        if((pre->rchild==NULL)&&(pre!=NULL))  /*建立后继线索*/
            pre->rchild=ptr;
        else
	    if(pre!=NULL)
	       pre->rtag=0;
	pre=ptr;
	inthread(ptr->rchild);                /*右子树线索化*/
    }
}

main()                                            /*主函数*/
{   BINTREE t=NULL;
    printf("\nplease input nodes of BINTREE : ");
    createbintree(&t);                            /*建立二叉树*/
    inthread(t);                                  /*中序线索化二叉树*/
}
程序运行结果（以图5.14二叉树为例）：
please input nodes of BINTREE : 1 2 4 0 0 5 0 0 3 0 6 0 0（回车）
程序运行以后，所建二叉树已经中序线索化，但此程序看不到结果，在后继《程序5-7》的
中序线索二叉树遍历算法中能看到结果。
