//* * * * * * * * * * * * * * * * * * * * * * * *
//*CHAPTER          :7  (7_6)                   *
//*PROGRAM          :堆排序                     *
//*CONTENT          :堆排序                     *
//* * * * * * * * * * * * * * * * * * * * * * * *
#include <dos.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20 //排序表的最大容量
typedef struct           //定义排序表的结构
{int  elemword[MAXSIZE]; //数据元素关键字
 int length;            //表中当前元素的个数
}SqList;
void InitialSqList(SqList&);       //初始化排序表
void HeapSort(SqList &);           //堆排序
void HeapAdjust(SqList &,int,int); //堆调整
void PrintSqList(SqList);          //显示表中的所有元素
void main()
{SqList L;  //声明表L
 char j='y';
// textbackground(3);  //设定屏幕颜色
// textcolor(15);
 //clrscr();
 //-------------------------程序说明-------------------------------
 printf("本程序将演示堆排序的操作。\n");
 //----------------------------------------------------------------
 while(j!='n'&&j!='N')
   {InitialSqList(L);    //待排序列初始化
    HeapSort(L);         //堆排序
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
 scanf("%d",&L.length);
 printf("请输入待排序的记录的关键字(整型数):\n");
 for(i=1;i<=L.length;i++)
   scanf("%d",&L.elemword[i]);
}
void HeapSort(SqList &L)
{//对顺序表L做堆排序。
 int i,j,t;
 for(i=L.length/2;i>0;--i)   //把L.elemword[1..L.length]建成大顶堆
   HeapAdjust(L,i,L.length);
 for(i=L.length;i>1;--i)
    {t=L.elemword[1];             //将堆顶记录和当前未经排序子序列L.elemword[1..i]    
     L.elemword[1]=L.elemword[i]; //中的最后一个记录相互交换
     L.elemword[i]=t;
     HeapAdjust(L,1,i-1);         //将L.r[1..i-1]重新调整为大顶堆
    }
}
void HeapAdjust(SqList &H,int s,int m)
{//已知H.elemword[s..m]中除H.elemword[s]之外均满足堆的定义,本函数调整H.elemword[s]
 //使H.elemword[s..m]成为一个大顶堆
 int j,rc;
 rc=H.elemword[s];
 for(j=2*s;j<=m;j*=2)     //沿关键字叫大的结点向下筛选
   {if(j<m&&H.elemword[j]<H.elemword[j+1]) ++j; //j为关键字较大的记录的下标
    if(rc>=H.elemword[j]) break;    //rc应插入在位置s上
    H.elemword[s]=H.elemword[j];
    s=j;
   }
 H.elemword[s]=rc;  //插入
}
void PrintSqList(SqList L)
{//显示表中所有元素
 int i;
 printf("已排好序的序列如下：\n");
 for(i=1;i<=L.length;i++)
    printf("%4d",L.elemword[i]);
 printf("\n");
}
