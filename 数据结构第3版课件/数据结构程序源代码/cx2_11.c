#include<stdio.h>
typedef struct node                   /*定义多项式结点的存储结构*/
{
    int coef;                         /*多项式系数*/
    int exp;                          /*多项式指数*/
    struct node *next;
}PNODE;

PNODE *create_polyn()                   /*此函数采用后插入方式建立一元多项式，并返回一个指向多项式表表头的指针*/
{
    PNODE *head,*q,*p;                  /*定义指针变量*/
    int c,e,n;
    head=(PNODE*)malloc(sizeof(PNODE)); /*申请新的存储空间，建立多项式表头结点*/
    q=head;
    printf("Input number of the polyn_list: ");
    scanf("%d",&n);                          /*输入多项式项数*/
    if(n>0)                                  /*若n<=0，建立仅含表头结点的空表,即空多项式*/
    {
	printf("Input the list : ");
        while(n>0)
        {
	    p=(PNODE*)malloc(sizeof(PNODE));
            scanf("%d",&c);                  /*输入多项式系数*/
            scanf("%d",&e);                  /*输入多项式指数*/
            p->coef=c;
            p->exp=e;
            q->next=p;
            q=p;
            n--;
        }
    }
    q->next=NULL;
    return(head);                           /*返回多项式表头指针head*/
}

void padd(PNODE *heada,PNODE *headb)
{   /*多项式A(x)+B(x)。heada和headb分别为多项式A(x)和B(x)的表头指针*/
    PNODE *p,*q,*u,*s;
    int x;                                 /*假设多项式系数为整数*/
    p=heada->next;                         /*p指向heada链表中的第一个结点,即多项式的第一项*/
    q=headb->next;                         /*q指向headb链表中的第一个结点,即多项式的第一项*/
    s=heada;                               /*s与p配合,s暂存heada指针*/
    while((p!=NULL)&&(q!=NULL))            /*在heada和headb链表都未到表尾结点时*/
    {  
        if(p->exp==q->exp)                 /*当两个多项式中的某项指数相等时*/
        {
            x=p->coef+q->coef;             /*系数相加,值存放在临时单元x中*/
            if(x!=0)                       /*当系数相加后,系数值不为0时*/
            {
                p->coef=x;                 /*在heada链表中存放系数相加后的值*/
                s=p;                       /*s暂存p指针*/
            }
            else                           /*当系数相加后,系数值为0时*/
            { 
                s->next=p->next;           /*将p->next临时存放在s->next指针中*/
                free(p);                   /*释放p结点*/
            }
            p=s->next;                     /*将p重新赋值为s->next，即释放前的p->next指针*/
            u=q;                           /*u与q配合,u暂存q指针*/
            q=q->next;                     /*q指向下一结点*/
            free(u);                       /*释放u结点*/
        }
        else                               /*当两个多项式中的某项指数不相等时*/
            if(p->exp>q->exp)              /*如果p的指数大于q的指数,在p之前插入q*/
            {
                u=q->next;                 /*将u指向q结点的直接后继结点*/
                q->next=p;                 /*将p结点成为q结点的直接后继结点*/
                s->next=q;                 /*将q结点成为s结点的直接后继结点,即q结点插入到s和p结点之间*/
                s=q;                       /*置s指向p结点的直接前趋结点*/
                q=u;                       /*完成q结点的插入,q重新赋值为u指针*/
            }
            else                           /*如果p的指数小于q的指数*/
            { 
                s=p;                       /*s跟上p*/
                p=p->next;                 /*p结点前进到下一个结点*/
            }
    }
    if(q!=NULL)   /*当heada和headb中某一链表到表尾结点时,如果p已是尾结点,而q未到尾结点*/
                  /*就将q链接到p的尾结点上;如果q已到尾结点,则不再需要改变p结点了。*/
        s->next=q;
    free(headb);                           /*释放headb结点空间*/
}

void print(PNODE *head)                    /*输出多项式*/
{
    PNODE *p;
    p=head->next;
    printf("Output the polyn_list: ");
    while(p!=NULL)
    {
       printf("%dx^%d,   ",p->coef,p->exp);
       p=p->next;
    }
    printf("\n");

}



main()                  /*主程序*/
{
   PNODE *a,*b;
   a=create_polyn();    /*此函数采用后插入方式建立一元多项式A(x)*/
   b=create_polyn();    /*此函数采用后插入方式建立一元多项式B(x)*/
   print(a);            /*输出多项式A(x)*/
   print(b);            /*输出多项式B(x)*/
   padd(a,b);
   print(a);            /*输出多项式A(x)+B(X)*/
}
程序运行结果：
Input number of the polyn_list: 3（回车）
Input the list : 1 0 2 1 4 3（回车）
Input number of the polyn_list: 3（回车）
Input the list : 2 0 -2 1 3 2（回车）
Output the polyn_list: 1x^0,  2x^1,  4x^3,
Output the polyn_list: 2x^0,  -2x^1,  3x^2
Output the polyn_list: 3x^0,  3x^2,  4x^3