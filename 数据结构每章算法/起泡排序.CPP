//* * * * * * * * * * * * * * * * * * * * * * * *
//*CHAPTER          :7  (7_3)                   *
//*PROGRAM          :起泡排序                   *
//*CONTENT          :起泡排序                   *
//* * * * * * * * * * * * * * * * * * * * * * * *
#include <dos.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20 //排序表的最大容量
enum BOOL{False,True};
typedef struct           //定义排序表的结构
{int  elemword[MAXSIZE]; //数据元素关键字
 int count;            //表中当前元素的个数
}SqList;
void InitialSqList(SqList&);        //初始化排序表
void BubbleSort(SqList &);          //起泡排序
void PrintSqList(SqList);           //显示表中的所有元素
void main()
{SqList L;  //声明表L
 char j='y';
 textbackground(3);  //设定屏幕颜色
 textcolor(15);
 clrscr();
 //-------------------------程序说明-------------------------------
 printf("本程序将演示起泡排序的操作。\n");
 //----------------------------------------------------------------
 while(j!='n'&&j!='N')
   {InitialSqList(L);    //待排序列初始化
    BubbleSort(L);       //起泡排序
    PrintSqList(L);      //显示排序结果
    printf("继续进行下一次排序吗?(Y/N)");
    scanf(" %c",&j);
   }
 printf("程序运行结束!\n按任意键关闭窗口!\n");
 getchar();getchar();
}
void InitialSqList(SqList &L)
{//表初始化
 int i;
 printf("请输入待排序的记录的个数:");
 scanf("%d",&L.count);
 printf("请输入待排序的记录的关键字(整型数):\n");
 for(i=0;i<L.count;i++)
   scanf("%d",&L.elemword[i]);
}
void BubbleSort(SqList &L)
{//对顺序表L做起泡排序。
 int i,j,t;
 BOOL change;
 for(i=L.count-1,change=True;i>0&&change;--i)
    {change=False;
     for(j=0;j<i;j++)
       if(L.elemword[j]>L.elemword[j+1])
	 {t=L.elemword[j];
	  L.elemword[j]=L.elemword[j+1];
	  L.elemword[j+1]=t;
	  change=True;
	 }
    }
}
void PrintSqList(SqList L)
{//显示表中所有元素 
 int i;
 printf("已排好序的序列如下：\n");
 for(i=0;i<L.count;i++)
    printf("%4d",L.elemword[i]);
 printf("\n");
}
