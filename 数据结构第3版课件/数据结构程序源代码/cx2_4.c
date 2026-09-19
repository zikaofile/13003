#include<stdio.h>
typedef struct node                   /*定义结点的存储结构*/
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

NODE *locate(NODE *head,int x)     /*在已知链表中查找给定的值x*/
{
    NODE *p;
    p=head->next;
    while((p!=NULL)&&(p->data!=x)) /*未到表尾且未找到给定数据*/
        p=p->next;                 /*指向下一个元素*/
    return(p);
}

main()                             /*主程序*/
{
   int y;
   NODE *a,*b;
   a=create();
   printf("Input x: ");
   scanf("%d",&y);
   b=locate(a,y);
   if(b!=NULL)
   {   printf("find:");
       printf("%5d",b->data);      /*查找成功*/
   }
   else
      printf("error");             /*查找失败*/
} 
程序运行结果：
Input the list :1 2 3 4 5?（回车）
Input x: 5（回车）
find:    5