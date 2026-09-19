#include <stdio.h>
#define MAXLEN 10
typedef int elementtype;
typedef struct                              /*循环队列的存储结构定义*/
{
    elementtype element[MAXLEN];            /*存放循环队列元素的数组*/
    int front,rear;                         /*循环队列头、尾指针*/
}CQueue;

CQueue InitCQueue()                         /*建立一个空循环队列cq*/
{
    CQueue cq;
    cq.front=0;
    cq.rear=0;
    return(cq);
}

int EnCqueue(CQueue *cq,elementtype x)      /*入循环队列操作,若循环队列cq未满,将元素x入队*/
{
    if((cq->rear+1)%MAXLEN==cq->front)
        return(0);                          /*循环队列满返回0*/
    else
    {
        cq->rear=(cq->rear+1)%MAXLEN;
        cq->element[cq->rear]=x;
        return(1);
    }
}

void print(CQueue cq)                       /*输出循环队列cq元素*/
{
    int i;
    if(cq.front!=cq.rear)                   /*循环队列非空,输出循环队列元素*/
    {
	printf("Output elements of cqueue : ");
	i=cq.front;
	do
	{
	     i=(i+1)%MAXLEN;
	     printf("%d ",cq.element[i]);
	}while(i!=cq.rear);
    }
    else
	printf("The cqueue is empty!!!");
}

main()                                          /*主程序*/
{
    CQueue cqueue;
    int i;
    elementtype y;

    cqueue=InitCQueue();                        /*建立空循环队列cqueue*/

    printf("\nAdding 5 elements to cqueue : ");
    for(i=1;i<=5;i++)                           /*入循环队列5个元素*/
    {
	scanf("%d",&y);
	EnCqueue(&cqueue,y);
    }
    print(cqueue);                              /*输出循环队列元素*/
    printf("\nAdding 1 element to cqueue : ");
    scanf("%d",&y);                             /*再入循环队列1个元素*/
    EnCqueue(&cqueue,y);

    print(cqueue);                              /*再输出循环队列元素*/
}
程序运行结果：
Adding 5 elements to cqueue : 1 2 3 4 5（回车）
Output elements of cqueue : 1 2 3 4 5
Adding 1 element to cqueue : 6（回车）
Output elements of cqueue : 1 2 3 4 5 6