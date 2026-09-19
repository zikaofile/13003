#include <stdio.h>
#include <alloc.h>
typedef struct dupnode            /*定义双向链表结点类型*/
{
   int data;
   struct dupnode *prior,*next;   /*定义双向链表结点的直接前驱和后继的指针*/
}DUPNODE;

DUPNODE *create_dlist(int *array,int len) /*双向链表建立函数*/
{                      /*array[]为加入链表的数组,len数组长度*/
   DUPNODE *head,*p,*q;
   int i;
   head=(DUPNODE*)malloc(sizeof(DUPNODE));      /*新结点申请内存单元*/
   head->data=array[0];         /*将数组第一个元素赋给链表第一个元素*/
   head->prior=NULL;
   head->next =NULL;
   p=head;
   for(i=1;i<len;i++)                   /*使用循环来建立链表其他结点*/
   {                                    /*采用后插入方式插入结点*/
      q=( DUPNODE*)malloc(sizeof(DUPNODE));
      q->data=array[i];
      q->next=NULL;
      q->prior=p;
      p->next=q;
      p=q;
   }
   return(head);                   /*返回head*/
}

DUPNODE *insert_node(DUPNODE *head,int l,int value,int *len)   /*插入结点函数*/
{  /*head链表头指针,l插入位置,value待插入值,*n链表长度*/
   int i;
   DUPNODE *q,*p;
   q=( DUPNODE*)malloc(sizeof(DUPNODE));     /*申请新结点空间q*/
   q->data=value;                              /*初始化新结点q*/
   q->prior=NULL;
   q->next=NULL;
   if(l==0)                         /*情况1,插在第一个结点前面*/
   {
      q->next=head;
      head->prior=q;
      head=q;
   }
   else                     /*插在第1或第2或..或第13个结点后面*/
   {  if(l==*len)
      {                           /*情况2,插在最后一个结点后面*/
	 p=head;
	 for(i=1;i<l;i++)
	    p=p->next;
	 q->prior=p;
	 p->next=q;
      }
      else
      {                        /*情况3,插在第1和第13个结点之间*/
	 p=head;
	 for(i=1;i<l;i++)
	    p=p->next;
	 q->prior=p;
	 q->next=p->next;
	 (p->next)->prior=q;
	 p->next=q;
      }
   }
   (*len)++;                     /*链表长度加1*/
   return(head);                 /*返回双向链表头指针*/
}


DUPNODE *delete_node(DUPNODE *head,int l,int *temp,int *len)  /*删除双向链表结点函数*/
{  /*head链表头指针,l删除位置,temp返回删除元素值,*n链表长度*/
   int i;
   DUPNODE *q,*p;
   if(l==1)                              /*情况1,删除第一个结点*/
   {
      p=head;
      head=head->next;
      head->prior=NULL;
   }
   else
   {
      if(l==*len)
      {                                  /*情况2,删除最后一个结点*/
         p=head;
         for(i=1;i<l;i++)
         {
            q=p;
      	    p=p->next;
	 }
	 q->next=NULL;
      }
      else
      {                               /*情况3,删除第2和第13个结点*/
         p=head;
         for(i=1;i<l;i++)
         {
            q=p;
      	    p=p->next;
         }
         q->next=p->next;
         (p->next)->prior=q;       /*或(p->next)->prior=p->prior;*/
      }
   }
   (*len)--;                          /*链表长度减1*/
   *temp=p->data;                     /*返回被删结点元素值*/
   free(p);                           /*释放被删除结点*/
   return(head);                      /*返回双向链表头指针*/
}

void print(head)                      /*输出双向链表各元素*/
DUPNODE *head;
{
   DUPNODE *p;
   p=head;
   while(p!=NULL)
   {
      printf("%d ",p->data);
      p=p->next;
   }
}

main()           /*主程序*/
{
   int i;        /*表示插入链表位置,可以是(0,1,2,…13),0表示插在第1个结点*/
                 /*前面,其它表示插在某结点后面,如1表示插在第1个结点后面等*/
   int j;        /*表示删除结点在链表中位置,可以是(1,2,…14),表示删除第1个*/
                 /*或第2个...或第14个结点*/
   int k;        /*插入链表的新元素值或返回删除元素值*/
   int a[13]={1,2,3,4,5,6,7,8,9,10,11,12,13};                   /*13个元素*/
   int n=13;                                                    /*数组长度*/
   DUPNODE *h;
   h=create_dlist(&a,n);                                    /*调用建表函数*/
   printf("\n");
   print(h);                                      /*输出双向链表各结点元素*/
   printf("\n输入新元素插在链表中的位置(0,1..13)和新元素值 ：");
   scanf("%d%d",&i,&k);
   h=insert_node(h,i,k,&n);                                 /*调用插入函数*/
   print(h);                     /*插入一个结点后,再输出双向链表各结点元素*/
   printf("\n输入删除元素在链表中的位置(1,2..14) ：");
   scanf("%d",&j);
   h=delete_node(h,j,&k,&n);                                /*调用删除函数*/
   printf("删除元素值为：%d\n",k);
   print(h);                     /*删除一个结点后,再输出双向链表各结点元素*/
}
程序运行结果：
1 2 3 4 5 6 7 8 9 10 11 12 13
输入新元素插在链表中的位置(0,1..13)和新元素值 ：13 66（回车）
1 2 3 4 5 6 7 8 9 10 11 12 13 66
输入删除元素在链表中的位置(1,2..14) ：13（回车）
1 2 3 4 5 6 7 8 9 10 11 12 66