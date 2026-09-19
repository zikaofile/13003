//* * * * * * * * * * * * * * * * * * * * * * * *
//*CHAPTER          :7  (7_5)                   *
//*PROGRAM          :简单选择排序               *
//*CONTENT          :简单选择排序               *
//* * * * * * * * * * * * * * * * * * * * * * * *
#include <dos.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20 //排序表的最大容量
typedef struct           //定义排序表的结构
{int  elemword[MAXSIZE]; //数据元素关键字
 int count;            //表中当前元素的个数
}SqList;
void InitialSqList(SqList&);        //初始化排序表
void SelectSort(SqList &);          //简单选择排序
int  SelectMinKey(SqList,int);      //寻找最小关键字的记录
void PrintSqList(SqList);           //显示表中的所有元素
void main()
{SqList L;  //声明表L
 char j='y';
 textbackground(3);  //设定屏幕颜色
 textcolor(15);
 clrscr();
 //-------------------------程序说明-------------------------------
 printf("本程序将演示简单选择排序的操作。\n");
 //----------------------------------------------------------------
 while(j!='n'&&j!='N')
   {InitialSqList(L);    //待排序列初始化
    SelectSort(L);       //简单选择排序
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
 for(i=1;i<=L.count;i++)
   scanf("%d",&L.elemword[i]);
}
void SelectSort(SqList &L)
{//对顺序表L做简单选择排序。
 int i,j,t;
 for(i=1;i<L.count;++i) //选择第i小的记录,并交换到位 
  {j=SelectMinKey(L,i); //在L.elemword[i..L.count]中选择关键字最小的记录
   if(i!=j)             //与第i个记录交换 
     {t=L.elemword[i];
      L.elemword[i]=L.elemword[j];
      L.elemword[j]=t;
     }
  }
}
int SelectMinKey(SqList L,int low)
{//在L.elemword[low..L.count]中寻找关键字最小的记录
 int i,j,t;
 t=L.elemword[low];
 j=low;
 for(i=low+1;i<=L.count;i++)
  if(L.elemword[i]<t)
     {t=L.elemword[i];
      j=i;
     }
 return j;
}
void PrintSqList(SqList L)
{//显示表中所有元素
 int i;
 printf("已排好序的序列如下：\n");
 for(i=1;i<=L.count;i++)
    printf("%4d",L.elemword[i]);
 printf("\n");
}
