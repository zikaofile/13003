#include <stdio.h>
#define MAXLEN 10
typedef int elementtype;
typedef struct                              /*队列的顺序存储结构定义*/
{
    elementtype element[MAXLEN];            /*存放队列元素的数组*/
    int front,rear;                         /*队列头、尾指针*/
}SeQueue;

SeQueue InitQueue_sq()                      /*建立一个空队列q*/
{   
    /*参考前面入队程序3-6*/
}

int GetFront_sq(SeQueue *q,elementtype *x)  /*取队头元素,若队列q非空,用*x返回其元素*/
{
    /*参考前面入队程序3-6*/
}

int Enqueue_sq(SeQueue *q,elementtype x)    /*入队列操作,若队列q未满，将元素x入队*/
{
    /*参考前面入队程序3-6*/
}

int Delqueue_sq(SeQueue *q,elementtype *x)  /*出队列操作,若队列q非空,将出队元素送*x*/
{
    if(q->front==q->rear)
        return(0);                          /*队列空返回0*/
    else
    {
        q->front++;
        *x=q->element[q->front];
        return(1);
    }
}


int Empty_sq(SeQueue *q)                    /*判断队列q是否为空,空则返回1,非空返回0*/
{
    /*参考前面入队程序3-6*/
}

void print(SeQueue q)                       /*输出队列q元素*/
{
    /*参考前面入队程序3-6*/
}

main()                                       /*主程序*/
{
    SeQueue queue;
    int i;
    elementtype y;
    elementtype z;

    queue=InitQueue_sq();                     /*建立空队列queue*/

    if(Empty_sq(&queue)!=0)                   /*判断队列queue是否为空*/
	printf("\nThe queue is empty!");
    else
	printf("\nThe queue is not empty!");

    printf("\nAdding 5 elements to queue : ");
    for(i=1;i<=5;i++)                         /*入队列5个元素*/
    {
	scanf("%d",&y);
        Enqueue_sq(&queue,y);
    }
    print(queue);                             /*入队列5个元素后输出队列元素*/

    GetFront_sq(&queue,&z);                   /*取队列头部元素,送z*/
    printf("Element of head is : %d ",z);     /*输出队列头部元素z*/

    printf("\nDelete 2 elements from queue : ");
    for(i=1;i<=2;i++)                         /*出队列2个元素*/
    {
	Delqueue_sq(&queue,&z);
        printf("%d ",z);                      /*按出队列次序输出队列元素*/
    }
    printf("\n");    

    print(queue);                             /*再输出队列元素*/

    if(Empty_sq(&queue)!=0)                   /*判断队列queue是否为空*/
	printf("The queue is empty!\n");
    else
	printf("The queue is not empty!\n");
}
程序运行结果：
The queue is empty!
Adding 5 elements to queue : 1 2 3 4 5（回车）
Output elements of queue : 1 2 3 4 5
Element of head is : 1
Delete 2 elements from queue : 1 2
Output elements of queue : 3 4 5
The queue is not empty!
