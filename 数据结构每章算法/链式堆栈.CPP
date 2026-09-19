//* * * * * * * * * * * * * * * * * * * * * * * * *
//*CHAPTER          :3  (3_3)                     *
//*PROGRAM          :链式堆栈                     *
//*CONTENT          :初始化,入栈,出栈,取栈顶元素  *
//* * * * * * * * * * * * * * * * * * * * * * * * *
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
enum BOOL{False,True};
typedef struct Lnode       //定义节点结构
{char  data;               //数据域
 struct Lnode *next;       //后向指针
}LNode,*LPoint;
void initial(LPoint&);    //初始化一个堆栈
void  push_linkstack(LPoint&,char);       //将一个元素入栈
BOOL pop_linkstack(LPoint&,char &);        //将一个元素出栈
void print_linkstack(LPoint); //显示栈中所有元素
void main()
{LPoint ls,p;
 char ch,j;
 int flag=1;
 BOOL temp;
 textbackground(3);  //设定屏幕颜色
 textcolor(15);
 clrscr();
 //---------------------程序解说-----------------------
 printf("本程序实现链式结构的堆栈操作。\n");
 printf("链式堆栈不会产生溢出问题。\n");
 printf("可以进行入栈，出栈，取栈顶元素等操作。\n");
 //----------------------------------------------------
 
 initial(ls);       //初始化堆栈S
 while(flag)
    { printf("请选择:\n");
      printf("1.显示栈中所有元素\n");
      printf("2.入栈       \n");
      printf("3.出栈       \n");
      printf("4.退出程序   \n");
      scanf(" %c",&j);
      switch(j)
	{case '1':print_linkstack(ls);
		  break;
	 case '2':printf("请输入要入栈的元素(一个字符):");
		  scanf(" %c",&ch);   //输入要入栈的字符
		  push_linkstack(ls,ch);//入栈
		  print_linkstack(ls);
		  break;
	 case '3':temp=pop_linkstack(ls,ch);  //出栈
		  if(temp==True)
		      {printf("出栈一个元素:%c\n",ch);//若栈不空，显示出栈的元素
		       print_linkstack(ls);
		      }
		else printf("堆栈已空!\n");//否则堆栈为空
		break;
	 default:flag=0;printf("程序结束，按任意键退出!\n");
	}
    }
 getch();
}

void initial(LPoint &pi)
{pi=NULL;   //栈顶指针初始化为NULL
}

void push_linkstack(LPoint &pi,char ch)
{//入栈，由于采用链式结构，一般不会产生栈满的情况
 LPoint po;
 po=(LPoint)malloc(sizeof(LNode));//生成一个新节点
 po->data=ch;                     //赋值
 po->next=pi;                  //新节点的后向指针指向原栈顶节点
 pi=po;                          //站顶指针指向新节点
}

BOOL pop_linkstack(LPoint &pi,char &e)
{//出栈，成功返回True，并用e返回该元素值，失败返回False
 LPoint po;
 po=pi;
 pi=po->next;                  //栈顶指针指向下一个节点
 if(po==NULL) return False;    //栈已空
 else {e=po->data;
       return True;  
      }                    
}

void print_linkstack(LPoint p)     
{//显示栈中所有元素
 if(p==NULL) printf("堆栈已空!\n");//栈为空
 else  {printf("堆栈所有元素:");
	while(p!=NULL)                       //否则显示栈中所有元素
	    {printf("%c ",p->data);
	     p=p->next;
	    }
	printf("\n");
       }
}
