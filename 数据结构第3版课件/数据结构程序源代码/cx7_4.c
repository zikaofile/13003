#include "alloc.h"
#define M 13                  /*M为散列表基本区的长度*/
struct hterm
{
    int key;
    struct hterm *next;
};
struct hterm ht[M];           /*定义表头向量兼散列表基本区*/

void linhash(ht,k)            /*静态链接法散列算法*/
struct hterm ht[M];           /*ht为散列表基本区*/
int k;                        /*k为待查记录的关键字*/
{
    int i;
    struct hterm *p,*q,*r;
    i=k%13;                   /*确定k在基本区的散列地址*/
    if(ht[i].key==0)          /*表中没有关键字为k的记录*/
        ht[i].key=k;          /*将关键字为k的查找记录r插入基本区*/
    else
        if(ht[i].key==k)
            printf("查找成功! %2d,%2d",i,k);  /*查找到显示成功信息等*/
        else
	{
	    r=&ht[i];
	    q=ht[i].next;     /*进入链接区(溢出区)查找(或插入)*/
	    while((q->key!=k)&&(q!=NULL))
            {
		r=q;
                q=q->next;
            }
	    if(q!=NULL)
                printf("查找成功! %2d,%2d",i,k);  /*查找到显示成功信息等*/
            else              /*链接区中没有查到,插入该记录*/
	    {
		p=(struct hterm*)malloc(sizeof(struct hterm));
                p->key=k;     /*插入记录*/
                p->next=NULL;
		r->next=p;
            }
        }
}

main()                                 /*主程序*/
{   int i,j;
     struct hterm *p;
     for(i=0;i<13;i++)                 /*初始化散列表*/
     {
         ht[i].key=0;
         ht[i].next=NULL;
     }
     printf("\n请输入12个待散列的数据 : ");
     for(i=1;i<=12;i++)                /*接收数据*/
     {
         scanf("%d",&j);
         linhash(ht,j);                /*查找或建立散列表*/
     }
     printf("\n");
     printf("输出静态链接法结果 :\n");
     for(i=0;i<13;i++)                 /*输出散列表*/
     {   printf("%d,",ht[i].key);      /*输出链表头中的值*/
         p=ht[i].next;                 /*为查找下面的元素做准备*/
         while(p!=NULL)
         {
             printf("%d,",p->key);     /*输出链表中的其他元素*/
             p=p->next;
         }
         printf("\n");
     }
     printf("请输入1个待散列的数据 : ");
     scanf("%d",&j);
     linhash(ht,j);                    /*查找或建立散列表*/
}
程序运行结果：
请输入12个待散列的数据 : 36 45 85 25 74 86 38 56 27 44 70 12（回车）
输出静态链接法结果 :
0,
27,
0,
0,
56,
44,70,
45,
85,
86,
74,
36,
0,
25,38,12,
请输入1个待散列的数据 : 70（回车）
查找成功! 5,70