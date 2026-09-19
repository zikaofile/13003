//* * * * * * * * * * * * * * * * * * * * * * * *
//*CHAPTER          :3  (3_5)                   *
//*PROGRAM          :循环队列                   *
//*CONTENT          :初始化，入队列，出队列     *
//* * * * * * * * * * * * * * * * * * * * * * * *
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXQSIZE  5
enum BOOL{False,True};
typedef struct         //定义队列结构
{char  elem[MAXQSIZE]; //队列体
 int front;            //队头指针
 int rear;             //队尾指针
}SqQueue;
void initial(SqQueue &);    //初始化一个队列
BOOL En_SqQueue(SqQueue &,char);   //将一个元素入队列
BOOL De_SqQueue(SqQueue &,char &); //将一个元素出队列
void Print_SqQueue(SqQueue);//显示队列中所有元素
void main()
{SqQueue S;
 char ch,j;
 int flag=1;
 BOOL temp;
 textbackground(3);  //设定屏幕颜色
 textcolor(15);
 //---------------------程序解说-----------------------
 printf("本程序实现循环队列的操作。\n");
 printf("可以进行入队列，出队列等操作。\n");
 //----------------------------------------------------
 clrscr();
 initial(S);       //初始化队列
 while(flag)
    { printf("请选择\n");
      printf("1.显示队列所有元素\n");
      printf("2.入队列\n");
      printf("3.出队列\n");
      printf("4.退出程序\n");
      scanf(" %c",&j);
      switch(j)
	{case '1':Print_SqQueue(S);   //显示队列中所有元素
		  break;
	 case '2':printf("请输入队的元素(一个字符):");
		  scanf(" %c",&ch);   //输入要入队列的字符
		  temp=En_SqQueue(S,ch);//入队列
		  if(temp==False) printf("队列已满!\n");
		  Print_SqQueue(S);
		  break;
	 case '3':temp=De_SqQueue(S,ch);  //出队列
		  if(temp!=False) {printf("删除了一个元素:%c\n",ch);//若队列不空，显示出队列的元素
			      Print_SqQueue(S);
			     }
		else printf("队列为空!\n");//否则队列为空
		break;
	 default:flag=0;printf("程序运行结束，按任意键结束!\n");
	}
    }
 getch();
}

void initial(SqQueue &Q)   
{//队列初始化
 Q.front=Q.rear=0; //队头指针及队尾指针同置为0
}

BOOL En_SqQueue(SqQueue &Q,char ch)
{//入队列，成功返回True，失败返回False
 if((Q.rear+1)%MAXQSIZE==Q.front) return False; //若队列已满，返回False
 Q.elem[Q.rear]=ch;        
 Q.rear=(Q.rear+1)%MAXQSIZE; //修改队尾指针
 return True;
}

BOOL De_SqQueue(SqQueue &Q,char &ch)
{//出队列,成功返回True，并用ch返回该元素值，失败返回False
 if(Q.front==Q.rear) return False; //若队列已空，返回True
 ch=Q.elem[Q.front];           
 Q.front=(Q.front+1)%MAXQSIZE; //修改队头指针  
 return True;                  //成功出队列，返回True
}

void Print_SqQueue(SqQueue Q)      
{//显示队列中所有元素
 int i;
 if(Q.front==Q.rear) printf("队列为空!\n");
 else {i=Q.front;
       while(i!=Q.rear)
	{printf("%c ",Q.elem[i]);
	 i++;
	 if(i>=MAXQSIZE) i=i%MAXQSIZE;
	}
      printf("\n");
     }
}
