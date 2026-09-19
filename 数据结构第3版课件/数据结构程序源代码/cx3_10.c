#include<stdio.h>
typedef struct node                     /*定义链队列结点*/
{
    int data;                           /*以整型数据为例*/
    struct node*next;                   /*指针类型,存放下一个结点地址*/
}NODE;

NODE *crea_linkqueue()                  /*建立空链队列*/
{
    NODE *front,*rear;                  /*定义链队列头指针front*/
    front=(NODE*)malloc(sizeof(NODE));  /*建立表头结点*/
    front->next=NULL;
    return(front);                      /*返回链队列指针front*/
}

NODE *pushqueue(NODE *rear,int x)       /*入队操作*/
{
    NODE *p;
    p=(NODE*)malloc(sizeof(NODE));
    p->data=x;                          /*将要插入的数据x存储到结点p的数据域中*/
    p->next=NULL;
    rear->next=p;                       /*将p插入链队列尾部*/
    rear=p;
    return(rear);
}

void print(NODE *front)                 /*输出链队列中各元素*/
{
    NODE *p;
    p=front->next;
    if(p!=NULL)
    {
        printf("Output the linkqueue : ");
        while(p!=NULL)
        {
	    printf("%2d",p->data);
            p=p->next;
        }
    }
    else
        printf("\nThe linkqueue is empty!!!");
}

main()                           /*主程序*/
{
    int i,y=0;                   /*将入链队列的元素y*/
    NODE *front,*rear;           /*定义链队列头、尾指针*/
    front=crea_linkqueue();      /*建立空链队列*/
    rear=front;
    print(front);                /*输出整个链队列*/
    printf("\nAdding 5 elements to linkqueue : ");
    for(i=1;i<=5;i++)            /*入链队列5个元素*/
    {
        scanf("%d",&y);
	rear=pushqueue(rear,y);
    }
    print(front);                /*再输出整个链队列*/
}
程序运行结果：
The linkqueue is empty!!!
Adding 5 elements to linkqueue : 1 2 3 4 5（回车）
Output the linkqueue : 1 2 3 4 5
