//* * * * * * * * * * * * * * * * * * * * * * *
//CHAPTER      :6 (6-1)                       *
//PROGRAM NAME :顺序查找                      *
//CONTENT      :查找                          *
//* * * * * * * * * * * * * * * * * * * * * * *
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#define MAX 30    //定义查找表的最大长度
typedef struct{
   char elem[MAX];       //线性查找表
   int length;             //length指示当前线性查找表的长度
}SSTable;
void initial(SSTable &);    //初始化线性查找表
int search(SSTable,char);        //在线性查找表中查找元素
void print(SSTable);             //显示线性查找表中所有元素
void main()
{SSTable ST;      //ST为一线性查找表
 int loc,flag=1;
 char j,ch;
 textbackground(3);  //设置屏幕颜色
 textcolor(15);
 clrscr();
 //-------------------------程序解说-------------------------------------------
 printf("本程序演示在静态表中顺序查找元素。\n");
 printf("首先输入静态表的元素个数。\n");
 printf("例如：5\n");
 printf("然后输入各个元素（字符）：\n例如：asdfg\n");
 printf("接下来就可以查找元素。\n");
 //----------------------------------------------------------------------------
 initial(ST);         //初始化线性查找表
 while(flag)
    { printf("请选择：\n");
      printf("1.显示所有元素\n");
      printf("2.查找一个元素\n");
      printf("3.退出\n");
      scanf(" %c",&j);
      switch(j)
	{case '1':print(ST); break; //显示所有元素
	 case '2':{printf("请输入要查找的元素（字符）：");
		   scanf(" %c",&ch);      //输入要查找的元素的关键字
		   loc=search(ST,ch);      //查找
		   if(loc!=0) printf("该元素所在位置：%d\n",loc); //显示该元素位置
		   else    printf("%c 不存在!\n",ch);//当前元素不存在
		   break;
		  }
	 default:flag=0;
	}
    }
 printf("程序运行结束!按任意键退出窗口!\n");
 getch();
}
void initial(SSTable &v)
{//初始化线性查找表
 int i;
 printf("请输入静态表的元素个数："); //输入线性查找表初始化时的长度
 scanf("%d",&v.length);
 printf("请输入%d个元素（字符）：",v.length);
 getchar();
 for(i=1;i<=v.length;i++) scanf("%c",&v.elem[i]); //输入线性查找表的各元素
}

int search(SSTable v,char ch)
{//在线性查找表中查找ch的位置，成功返回其位置，失败返回0
 int i;
 v.elem[0]=ch; //设置“哨兵”
 for(i=v.length;v.elem[i]!=ch;--i)  ;  //从后往前找
 return i;     //找不到时，i为0
}
void print(SSTable v)          //显示当前线性查找表所有元素
{int i;
 for(i=1;i<=v.length;i++) printf("%c ",v.elem[i]);
 printf("\n");
}

