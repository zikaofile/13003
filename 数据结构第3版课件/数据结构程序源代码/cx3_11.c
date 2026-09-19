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

NODE *popqueue(NODE *front,NODE *rear,int *x) /*出队操作*/
{
    NODE *p;
    if(front!=rear)                           /*判断链队列空,若链队列不空*/
    {
        p=front->next;                        /*p指向链队列第一个元素*/
        front->next=p->next;                  /*将p元素出队*/
        if(p->next==NULL)                     /*表示原链队列中只有一个元素*/
             rear=front;                      /*出队后,队空,修改rear指针*/
        *x=p->data;                           /*保存出队后的元素值*/
        free(p);
        return(rear);                         /*返回rear*/
    }
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

main()                                /*主程序*/
{
    int i,x,y=0;                      /*将入链队列的元素x*/
    NODE *front,*rear;                /*定义链队列头、尾指针*/
    front=crea_linkqueue();           /*建立空链队列*/
    rear=front;
    print(front);                     /*输出整个链队列*/
    printf("\nAdding 5 elements to linkqueue : ");
    for(i=1;i<=5;i++)                 /*入链队列5个元素*/
    {
        scanf("%d",&x);
	rear=pushqueue(rear,x);
    }
    print(front);                     /*输出整个链队列*/
    rear=popqueue(front,rear,&y);     /*出链队列一个元素到y*/
    printf("\nDelete the element of linkqueue : %d\n",y);
    print(front);                     /*再输出整个链队列*/
}
程序运行结果：
The linkqueue is empty!!!
Adding 5 elements to linkqueue : 1 2 3 4 5（回车）
Output the linkqueue : 1 2 3 4 5
Delete the element of linkqueue : 1
Output the linkqueue : 2 3 4 5