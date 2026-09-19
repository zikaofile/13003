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

void print(NODE *head)          /*输出单向链表各元素，第3章中也用到此函数*/
{
    NODE *p;
    p=head->next;
    printf("Output the list:");
    while(p!=NULL)
    {
	printf("%3d",p->data);
        p=p->next;
    }
}

main()
{
   NODE *a;
   a=create();
   print(a);
}
程序运行结果：
Input number of the list: 5（回车）
Input the list : 1 2 3 4 5（回车）
Output the list:  1  2  3  4  5