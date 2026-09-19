#include <stdio.h>
#define MAXLEN 100               /*MAXLEN要大于实际线性表的长度*/
typedef int elementtype;         /*根据需要，elementtype也可以定义为其它任何类型*/
typedef struct                   /*定义线性表*/
{
    elementtype s[MAXLEN];       /*定义线性表中元素，MAXLEN为线性表的最大容量*/
    int len;                     /*定义线性表的表长*/
}SqList;

int delsqlist(int i,SqList *sql) /*删除顺序表(*sql)的第i个元素*/
{
    int j;
    if((i<1)||(i>sql->len))      /*i值非法，返回值为0*/
         return(0);
    else
    {
	 for(j=i+1;j<=sql->len;j++)
             sql->s[j-1]=sql->s[j];   /*向前移动数据，覆盖前一数据*/
         (sql->len)--;                /*表长度减1*/
         return(1);                   /*删除成功，返回值为1*/
    }
}

main()                                /*主程序*/
{
    int b=4,c,k;
    SqList a={0,1,2,3,4,5,6,7,8};     /*赋线性表各元素初值，为与前概念描述一致，a.s[0]闲置不用*/
    a.len=8;                          /*赋线性表长度值*/
    for(k=1;k<=a.len;k++)
    {
	printf("%3d",a.s[k]);         /*输出删除前结果*/
    }
    printf("\n");
    c=delsqlist(b,&a);                /*调用删除函数*/
    if(c==0)
        printf("error\n");
    else
    {
	for(k=1;k<=a.len;k++)
	    printf("%3d",a.s[k]);     /*输出删除后结果*/
    }
    printf("\n");
}
程序运行后结果：
   1  2  3  4  5  6  7  8
   1  2  3  5  6  7  8
