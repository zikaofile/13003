//* * * * * * * * * * * * * * * * * * * * * * * *
//*CHAPTER          :7  (7_7)                   *
//*PROGRAM          :归并排序                     *
//*CONTENT          :归并排序                     *
//* * * * * * * * * * * * * * * * * * * * * * * *
#include <dos.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 30 //排序表的最大容量
typedef struct           //定义排序表的结构
{int  elemword[MAXSIZE]; //数据元素关键字
 int length;            //表中当前元素的个数
}SqList;
void InitialSqList(SqList&);       //初始化排序表
void MergeSort(SqList &);          //归并排序
void MSort(int [],int [],int,int); //归并排序递归子程序
void Merge(int [],int [],int,int,int); //两个子序列归并
void PrintSqList(SqList);          //显示表中的所有元素
void main()
{SqList L;  //声明表L
 char j='y';
 textbackground(3);  //设定屏幕颜色
 textcolor(15);
 clrscr();
 //-------------------------程序说明-------------------------------
 printf("本程序将演示归并排序的操作。\n");
 //----------------------------------------------------------------
 while(j!='n'&&j!='N')
   {InitialSqList(L);    //待排序列初始化
    MergeSort(L);         //归并排序
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
void MergeSort(SqList &L)
{//对顺序表L做归并排序。
 MSort(L.elemword,L.elemword,1,L.length);
}
void MSort(int SR[],int TR1[],int s,int t)
{//将SR[s..t]归并排序为TR1[s..t]。
 int m;
 int TR2[MAXSIZE];
 if(s==t) TR1[s]=SR[s];
 else
   {m=(s+t)/2;           //将SR[s..t]平分为SR[s..m]和SR[m+1..t]
    MSort(SR,TR2,s,m);   //递归地将SR[s..m]归并为有序的TR2[s..m]
    MSort(SR,TR2,m+1,t); //递归地将SR[m+1..t]归并为有序的TR2[m+1..t]
    Merge(TR2,TR1,s,m,t);//将TR2[s..m]和TR2[m+1..t]归并到TR1[s..t]
   }
}
void Merge(int SR[],int TR[],int i,int m,int n)
{//将有序的SR[i..m]和SR[m+1..n]归并为有序的TR[i..n]
 int j,k,p;
 for(j=m+1,k=i;i<=m&&j<=n;++k) //将SR中的记录有小到大地并入TR
   {if(SR[i]<SR[j]) TR[k]=SR[i++];
    else TR[k]=SR[j++];
   }
 if(i<=m)
   for(p=k;p<=n;p++) //将剩余的SR[i..m]复制到TR
     {TR[p]=SR[i];   
      i++;
     }
 if(j<=n)
   for(p=k;p<=n;p++) //将剩余的SR[j..n]复制到TR
     {TR[p]=SR[j];
      j++;
     }
}
void PrintSqList(SqList L)
{//显示表中所有元素
 int i;
 printf("已排好序的序列如下：\n");
 for(i=1;i<=L.length;i++)
    printf("%4d",L.elemword[i]);
 printf("\n");
}
