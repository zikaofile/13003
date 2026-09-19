#include<stdio.h>
typedef struct node                   /*定义结点的存储结构*/
{
    int data;
    struct node *next;
}NODE;

NODE *create_circular()               /*此函数采用后插入方式建立单向循环链表，并返回一个指向链表表头的指针*/
{
    NODE *head,*q,*p;                 /*定义指针变量*/
    int a,n;
    head=(NODE*)malloc(sizeof(NODE)); /*申请新的存储空间，建立表头结点*/
    q=head;
    printf("\nInput number of the list: ");
    scanf("%d",&n);                          /*输入单向链表结点个数*/
    head->data=n;                            /*表头结点赋值n，即表中结点个数*/
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
    q->next=head;
    return(head);                           /*返回表头指针head*/
}

NODE *prior(NODE *p)
{
   NODE *q;
   q=p->next;
   while(q->next!=p)
       q=q->next;
   return(q);
}

main()                     /*主程序*/
{
   NODE *a,*c,*p;
   int i,j;
   a=create_circular();    /*建立单向循环链表*/
   printf("Input j:");     /*给出单向循环链表中的结点序号，表头结点序号为0*/
   scanf("%d",&j);         /*j的取值为：0～表中的结点个数*/
   p=a;
   for(i=0;i<j;i++)
       p=p->next;          /*按序号确定一个p结点*/
   c=prior(p);
   printf("prior of %d is : %d",p->data,c->data);
}
程序运行结果：/*涉及到和表头结点有关的前趋结点时，注意表头结点的data域的值是表中结点数目*/
Input number of the list: 5（回车）
Input the list : 5 6 7 8 9（回车）
Input j: 4（回车）
prior of 8 is : 7
