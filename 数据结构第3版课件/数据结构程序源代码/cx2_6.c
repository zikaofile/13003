#include<stdio.h>
typedef struct node                   /*定义结点的存储结构*/
{
    int data;
    struct node *next;
}NODE;

NODE *create()                        /*此函数采用后插入方式建立单链表，并返回一个指向链表表头的指针*/
{
    NODE *head,*q,*p;                 /*定义指针变量*/
    int a,n;
    head=(NODE*)malloc(sizeof(NODE)); /*申请新的存储空间，建立表头结点*/
    q=head;
    printf("\nInput number of the list: ");
    scanf("%d",&n);                          /*输入单向链表结点个数*/
    if(n>0)                                  /*若n<=0，建立仅含表头结点的空表*/
    {
	printf("Input the list :");
        while(n>0)
        {
	    scanf("%d",&a);                  /*输入新元素*/
            p=(NODE*)malloc(sizeof(NODE));
            p->data=a;
            q->next=p;
            q=p;
            n--;
        }
    }
    q->next=NULL;
    return(head);                           /*返回表头指针head*/
}

void insert(NODE *p,int x) /*在链表的p结点位置后插入给定元素x*/
{
    NODE *q;
    q=(NODE*)malloc(sizeof(NODE));    /*申请新的存储空间*/
    q->data=x;
    q->next=p->next;                  /*实现图2.9(b)的①*/
    p->next=q;                        /*实现图2.9(b)的②，将新结点q链接到p结点之后*/
}

main()                  /*主程序*/
{
   int x,position;      /*x为将插入的元素，position为插入位置的序号*/
   int i=0,j=0;
   NODE *c,*d;
   c=create();          /*建立单向链表*/
   d=c->next;
   while(d!=NULL)       /*统计单向链表中结点数，置j中*/
   {
       d=d->next;
       j++;
   }
   d=c;
   do
   {
       printf("Input position (again):");
       scanf("%d",&position);           /*position可为0，表示表头结点*/
   }while((position>j)||position<0);    /*position值超过单向链表结点数，重新输入*/
   printf("Input x:");
   scanf("%d",&x);
   while(i!=position)                   /*由position值确定其在单向链表中的位置d*/
   {
       d=d->next;
       i++;
   }
   insert(d,x);
   printf("Output the list:");
   while(c->next!=NULL)                 /*输出插入x后的单向链表各元素*/
   {
       c=c->next;
       printf("%5d",c->data);
   }
   printf("  ok");
}
程序运行结果：
Input number of the list: 5（回车）
Input the list : 5 6 7 8 9（回车）
Input position: 3（回车）
Input x: 33（回车）
Output the list:  5  6  7  33  8  9  ok