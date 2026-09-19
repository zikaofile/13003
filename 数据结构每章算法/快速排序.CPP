//* * * * * * * * * * * * * * * * * * * * * * * *
//*CHAPTER          :7  (7_4)                   *
//*PROGRAM          :快速排序                   *
//*CONTENT          :快速排序                   *
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
void QuickSort(SqList &);           //快速排序
void QSort(SqList &,int,int);       //子序列快速排序
int  Partition(SqList &,int,int);   //一趟快速排序
void PrintSqList(SqList);           //显示表中的所有元素
void main()
{SqList L;  //声明表L
 char j='y';
 textbackground(3);  //设定屏幕颜色
 textcolor(15);
 clrscr();
 //-------------------------程序说明-------------------------------
 printf("本程序将演示快速排序的操作。\n");
 //----------------------------------------------------------------
 while(j!='n'&&j!='N')
   {InitialSqList(L);    //待排序列初始化
    QuickSort(L);        //快速排序
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
void QuickSort(SqList &L)
{//对顺序表L做快速排序。
 QSort(L,1,L.count);
}
void QSort(SqList &L,int low,int high)
{//对顺序表中的子序列L.r[low..high]作快速排序
 int pivotloc;
 if(low<high)         //长度大于1
   {pivotloc=Partition(L,low,high); //将L.elemword[low..high]一分为二
    QSort(L,low,pivotloc-1);        //对低子表递归排序,pivotloc是枢轴位置
    QSort(L,pivotloc+1,high);       //对高子表递归排序
   }
}
int Partition(SqList &L,int low,int high)
{//交换顺序表L中子表r[low..high]的记录，枢轴记录到位，并返回其所在位置，此时
 //在它之前(后)的记录均不大(小)于它
 int pivotkey;          
 pivotkey=L.elemword[low]; //用子表的第一个记录作枢轴记录
 while(low<high)      //从表的两端交替地向中间扫描 
   {while(low<high&&L.elemword[high]>=pivotkey)
       --high;
    L.elemword[low]=L.elemword[high];//将比枢轴记录小的记录移到低端
    while(low<high&&L.elemword[low]<=pivotkey)
       ++low;
    L.elemword[high]=L.elemword[low]; //将比枢轴记录大的记录移到高端
   }
 L.elemword[low]=pivotkey;  //枢轴记录到位
 return low;                //返回枢轴记录
}
void PrintSqList(SqList L)
{//显示表中所有元素
 int i;
 printf("已排好序的序列如下：\n");
 for(i=1;i<=L.count;i++)
    printf("%4d",L.elemword[i]);
 printf("\n");
}
