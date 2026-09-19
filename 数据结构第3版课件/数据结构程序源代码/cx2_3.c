#include<stdio.h>
typedef struct node
{
    int data;
    struct node *next;
}NODE;

NODE *create()                        /*此函数采用后插入方式建立单链表，并返回一个指向链表表头的指针*/
{
    NODE *head,*q,*p;                 /*定义指针变量*/
    char ch;
    int a;
    head=(NODE*)malloc(sizeof(NODE)); /*申请新的存储空间，建立表头结点*/
    q=head;
    ch='*';
    printf("\nInput the list :");
    while(ch!='?')                    /*"ch"为是否建立新结点的标志，若"ch"为"?"则输入结束*/
    {
	scanf("%d",&a);                  /*输入新元素*/
	p=(NODE*)malloc(sizeof(NODE));
        p->data=a;
        q->next=p;
        q=p;
        ch=getchar();                    /*读入输入与否的标志*/
    }
    q->next=NULL;
    return(head);                        /*返回表头指针head*/
}

main()
{
    int i;
    NODE *a;
    a=create();
    printf("output the list:");
    a=a->next;
    while(a!=NULL)
    {
	printf("%d ",a->data);          /*输出链表各元素*/
        a=a->next;
    }
}
程序运行结果：
Input the list :5 6 7 8 9?（回车）
output the list:5 6 7 8 9