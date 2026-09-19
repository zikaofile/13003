#include<stdio.h>
#define QUEUESIZE 20
typedef struct node
{   int data1;
    struct node *lchild;
    struct node *rchild;
}BINTNODE, *BINTREE;            /*定义二叉链表指针类型*/
typedef struct cirqueue
{
    int count,front,rear;
    BINTNODE *data[QUEUESIZE];
}CIRQUEUE;

createbintree(BINTREE *t)
{    int a;
     scanf("%d",&a);
     if(a==0)
         *t=NULL;
     else
     {   *t=(BINTNODE*)malloc(sizeof(BINTNODE));
	 (*t)->data1=a;
         createbintree(&(*t)->lchild);
         createbintree(&(*t)->rchild);
     }
}

leverorder(BINTREE t)
{   CIRQUEUE *q;
    BINTREE p;
    q=(CIRQUEUE*)malloc(sizeof(CIRQUEUE));        /*申请循环队列空间*/
    q->rear=q->front=q->count=0;                  /*将循环队列初始化为空*/
    q->data[q->rear]=t;                           /*将根结点入队*/
    q->count++;
    q->rear=(q->rear+1)%QUEUESIZE;
    while(q->count)                               /*若队列不为空，做以下操作*/
        if(q->data[q->front])                     /*若队首元素不为空指针，做以下操作*/
        {
            p=q->data[q->front];                  /*取队首元素*p*/
	    printf("%d ",p->data1);               /*打印*p结点的数据域信息*/
            q->front=(q->front+1)%QUEUESIZE;
            q->count--;                           /*队首元素出队*/
            if(q->count==QUEUESIZE)               /*若队列为队满，则打印队满信息，退出程序的执行*/
		 printf("the queue full!");
            else                                  /*若队列不满，将*p结点的左孩子指针入队*/
            {
                 q->count++;
                 q->data[q->rear]=p->lchild;
                 q->rear=(q->rear+1)%QUEUESIZE;
            }                                     /*enf of if*/
            if(q->count==QUEUESIZE)               /*若队列为队满，则打印队满信息，退出程序的执行*/
		 printf("the queue full!");
            else                                  /*若队列不满，将*p结点的右孩子指针入队*/
            {
                 q->count++;
                 q->data[q->rear]=p->rchild;
                 q->rear=(q->rear+1)%QUEUESIZE;
            }                                     /*end of if*/
        } /*end of if*/
        else
        {                                         /*当队首元素为空指针，将空指针出队*/
            q->front=(q->front+1)%QUEUESIZE;
            q->count--;
        }
}                                                 /*end of leverorder*/

main() /*主函数*/
{   BINTREE t=NULL;
    printf("\nPlease input nodes of BINTREE : ");
    createbintree(&t);
    printf("The levelord is : ");
    leverorder(t);
}
程序运行结果（以图5.14二叉树为例）：
Please input nodes of BINTREE : 1 2 4 0 0 5 0 0 3 0 6 0 0（回车）
The levelord is : 1 2 3 4 5 6