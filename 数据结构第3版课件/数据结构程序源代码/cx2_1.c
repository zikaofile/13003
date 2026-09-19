#include <stdio.h>
#define MAXLEN 100               /*MAXLEN要大于实际线性表的长度*/
typedef int elementtype;         /*根据需要，elementtype也可以定义为其它任何类型*/
typedef struct                   /*定义线性表*/
{
    elementtype s[MAXLEN];       /*定义线性表中元素，MAXLEN为线性表的最大容量*/
    int len;                     /*定义线性表的表长*/
}SqList;

int insertsqlist(int i,elementtype x,SqList *sql)
{                                         /*在顺序表(*sql)的第i个元素之前插入一个新元素x*/
    int j;
    if((i<1)||(i>sql->len))               /*i值非法，返回值为0*/
        return(0);
    else
    {
	for(j=sql->len;j>=i;j--)
	    sql->s[j+1]=sql->s[j];        /*向后移动数据，腾出要插入的空位*/
	sql->s[j+1]=x;                    /*修正插入位置为j+1，将新元素插入到s[j+1]位置*/
	(sql->len)++;                     /*表长加1*/
	return(1);                        /*插入成功，返回值为1*/
    }
}

main()                                    /*主程序*/
{
    int b=9,c,k;
    elementtype d=9;
    SqList a={0,1,2,3,4,5,6,7,8};         /*赋线性表各元素初值，为与前概念描述一致，a.s[0]闲置不用*/
    a.len=8;                              /*赋线性表长度值*/
    for(k=1;k<=a.len;k++)
    {
	printf("%3d",a.s[k]);             /*输出插入前结果*/
    }
    printf("\n");
    c=insertsqlist(b,d,&a);               /*调用插入函数*/
    if(c==0)
        printf("error");
    else
    {
	for(k=1;k<=a.len;k++)
	    printf("%3d",a.s[k]);         /*输出插入后结果*/
    }
    printf("\n");
}
程序运行后结果：
   1  2  3  4  5  6  7  8
   1  2  9  3  4  5  6  7  8
