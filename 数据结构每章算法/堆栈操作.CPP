//* * * * * * * * * * * * * * * * * * * * * * * * *
//*CHAPTER          :3  (3_1)                     *
//*PROGRAM          :堆栈操作                     *
//*CONTENT          :初始化,入栈,出栈,取栈顶元素  *
//* * * * * * * * * * * * * * * * * * * * * * * * *
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 5          //定义堆栈最大容量
enum BOOL{False,True}; //定义BOOL型
typedef struct        //定义堆栈结构
{char elem[MAX];   //栈区
 int top;          //栈顶指针
}SqStack;
void Initial(SqStack &);    //初始化一个堆栈
BOOL Push(SqStack &,char);       //将一个元素入栈
BOOL Pop(SqStack&,char &);        //将一个元素出栈
BOOL Gettop(SqStack,char &);     //得到栈顶元素
void SqStackPrint(SqStack);//显示栈中所有元素
void main()
{SqStack St;
 int flag=1;
 char j,ch;
 BOOL temp;
// textbackground(3); //设定屏幕颜色
// textcolor(15);
 //clrscr();
 //---------------------程序解说-----------------------
 printf("本程序实现顺序结构的堆栈的操作。\n");
 printf("可以进行入栈，出栈，取栈顶元素等操作。\n");
 //----------------------------------------------------
 Initial(St);       //初始化堆栈S
 while(flag)
    { printf("请选择:\n");
      printf("1.显示栈中所有元素     \n");
      printf("2.入栈                 \n");
      printf("3.出栈                 \n");
      printf("4.取栈顶元素           \n");
      printf("5.退出程序             \n");
      scanf(" %c",&j);
      switch(j)
	{case '1':SqStackPrint(St);
		  break;
	 case '2':printf("请输入要入栈的元素(一个字符):");
		  scanf(" %c",&ch);      //输入要入栈的元素
		  temp=Push(St,ch);      //入栈
		  if(temp==False)printf("堆栈已满!入栈失败!\n");
		  else {printf("成功入栈!\n");  //成功入栈
			SqStackPrint(St);
		       }
		  break;
	 case '3':temp=Pop(St,ch);  //出栈
		  if(temp==False) printf("堆栈已空!\n"); 
		  else {printf("成功出栈一个元素:%c\n",ch); //成功出栈
			SqStackPrint(St);
		       }
		  break;
	 case '4':temp=Gettop(St,ch); //取得栈顶元素
		  if(temp==False) printf("堆栈已空!\n");
		  else printf("栈顶元素是:%c\n",ch); //显示栈顶元素
		  break;
	 default:flag=0;printf("程序结束，按任意键退出!\n");
	}
    }
getch();
}
void Initial(SqStack &S)
{S.top=-1;   //栈顶指针初始化为-1
}

BOOL Push(SqStack &S,char ch)
{//将元素ch入栈，成功返回True,失败返回False
 if(S.top>=MAX-1) return False;//判断是否栈满
 else {S.top++;               //栈顶指针top加一
       S.elem[S.top]=ch;      //入栈
       return True;
      }
}

BOOL Pop(SqStack &S,char &ch)
{//将栈顶元素出栈,成功返回True，并用ch返回该元素值，失败返回False
 if(S.top<=-1) return False;//判断是否栈空
 else {S.top--;                                //栈顶指针减一
       ch=S.elem[S.top+1];
       return True;
      }
}

BOOL Gettop(SqStack S,char &ch)
{//取得栈顶元素，成功返回True，并用ch返回该元素值，失败返回False
 if(S.top<=-1)
    return False;
 else {ch=S.elem[S.top];//显示栈顶元素
       return True;
      }
}

void SqStackPrint(SqStack S)      
{//显示栈中所有元素
 int i;
 if(S.top<=-1) printf("堆栈已空!\n");
 else {printf("堆栈所有元素:\n");
       for(i=0;i<=S.top;i++)
	  printf("%c ",S.elem[i]);
       printf("\n");
      }
}
