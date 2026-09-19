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

NODE *connect(NODE *head1,NODE *head2)
{   /*把循环链表A和B合并成一个循环链表。head1和head2分别为两个循环链表的头指针*/
    NODE *p,*q;
    p=head1->next;
    while(p->next!=head1)                   /*找head1的最后一个结点*/
        p=p->next; 
    q=head2->next;
    while(q->next!=head2)                   /*找head2的最后一个结点*/
        q=q->next;
    p->next=head2->next;                    /*A,B两表链接*/
    q->next=head1;
    free(head2);                            /*释放B表表头结点*/ 
    return(head1);
}

main()                              /*主程序*/
{
    NODE *a,*b,*c,*d;
    a=create_circular();            /*调用create_circular()函数，建立单向循环链表A*/
    b=create_circular();            /*调用create_circular()函数，建立单向循环链表B*/
    c=connect(a,b);                 /*调用connect函数,将循环链表A和B合并成一个循环链表*/
    d=c; 
    printf("\nOutput the list: ");  /*输出链接后的整个链表*/  
    while(d->next!=c) 
    {
        d=d->next;
        printf("%3d",d->data);
    }
}
程序运行结果：（首先建立A,B单向循环链表,然后输出合并后的单向循环链表）
Input number of the list: 3（回车）
Input the list : 11 22 33（回车）

Input number of the list: 4（回车）
Input the list : 44 55 66 77（回车）

Output the list: 11 22 33 44 55 66 77