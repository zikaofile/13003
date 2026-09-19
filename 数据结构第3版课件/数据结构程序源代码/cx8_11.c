#include <stdio.h>
#include <alloc.h>
typedef struct jlnode     /*定义单链表结点的存储结构*/
{
   int key;               /*记录关键字*/
   struct jlnode *next; 
}RANODE;

RANODE *create()    /*采用后插入方式建立单链表,并返回指向链表表头的指针*/
{
    RANODE *head,*q,*p;                       /*定义指针变量*/
    int a,n;
    head=(RANODE*)malloc(sizeof(RANODE));     /*建立表头结点*/
    q=head; 
    printf("\nInput number of the record : ");
    scanf("%d",&n);                           /*输入记录个数*/   
    if(n>0)                             /*若n<=0,建立仅含表头结点的空表*/
    {
	printf("Input the records :");
        while(n>0)
        {
	    scanf("%d",&a);                   /*输入记录关键字*/
            p=(RANODE*)malloc(sizeof(RANODE));
            p->key=a;
            q->next=p;
            q=p;
            n--;
        }
    }
    q->next=NULL;
    return(head);                           /*返回表头指针head*/
}

RANODE *radixsort(RANODE *h,int d,int R)    /*链式基数排序算法*/
{  /*h为单链表指针,d为单链表中记录关键字位数,R为基数,如为十进制,R=10*/
   int  i,j,s,k,m;
   RANODE *f[10],*r[10],*p,*q;  /*f和*r分别为队头指针数组和队尾指针数组*/
   s=1;
   m=R;                      /*将十进制基数R赋m*/
   p=h->next;                /*取链队第一个记录*/
   for(i=1;i<=d; i++)        /*分配、收集d次*/
   {
      for(j=0;j<R;j++)       /*对R个队列头尾指针赋初值*/
      {
         f[j]=NULL;
         r[j]=NULL;
      }
      q=p;
      while(q!=NULL)         /*分配*/
      {
         k=(q->key%m)/s;     /*先后分离出3位数的个、十、百位数字*/
         if(f[k]==NULL)      /*根据q->key分离的数字,送入相应队列*/
            f[k]=q;          /*队列空,直接加入*/ 
         else
            r[k]->next=q;    /*队列非空,加到队尾*/
         r[k]=q;
         q=q->next;          /*取单链表的下一个记录*/
      }
      p=NULL;
      for(j=R-1;j>=0;j--)    /*从R个队列最后一个队列向前收集*/
         if(f[j]!=NULL)
         { 
            r[j]->next=p;
            p=f[j];
         }
      m=m*10;                /*为分离高一位数字做准备*/
      s=s*10;                /*为分离高一位数字做准备*/
   }
   h->next=p;
   return(h);
}

main()                             /*主程序*/
{
   int d=3;
   int R=10;
   RANODE *a,*b;
   a=create();                     /*建立待排序的各记录链表*/
   b=radixsort(a,d,R);             /*调用链式基数排序算法*/
   b=b->next;
   printf("Output the radixsort list : ");
   while(b!=NULL)
   {
       printf("%4d",b->key);       /*输出已进行基数排序的有序表*/
       b=b->next;
   }
}
程序运行结果：
Input number of the record : 10（回车）
Input the records : 387 456 592 625 076 471 050 396 557 522（回车）
Output the radixsort list :  50  76 387 396 456 471 552 557 592 625
