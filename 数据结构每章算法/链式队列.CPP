//* * * * * * * * * * * * * * * * * * * * * * * *
//*CHAPTER          :3  (3_4)                   *
//*PROGRAM          :链式队列                   *
//*CONTENT          :初始化,入队列,出队列       *
//* * * * * * * * * * * * * * * * * * * * * * * *
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
enum BOOL{False,True};
typedef struct QNode       //定义节点结构
{char  data;               //数据域
 struct QNode *next;       //后向指针
}QNode,*QueuePtr;
typedef struct linkqueue{  //定义队列结构
 QueuePtr front;           //队首指针
 QueuePtr rear;            //队尾指针
}LinkQueue;
void initial(LinkQueue &);    //初始化一个队列
BOOL En_LinkQueue(LinkQueue &,char);   //将一个元素入队列
BOOL De_LinkQueue(LinkQueue &,char &); //将一个元素出队列
void Print_LinkQueue(LinkQueue);//显示队列中所有元素
void main()
{LinkQueue ls;
 char ch,j;
 int flag=1;
 BOOL temp;
 textbackground(3); //设定屏幕颜色
 textcolor(15);
 clrscr();
 //---------------------程序解说-----------------------
 printf("本程序实现链式结构的队列的操作。\n");
 printf("可以进行入队列，出队列等操作。\n");
 //----------------------------------------------------
 initial(ls);       //初始化队列
 while(flag)
    { printf("请选择:\n");
      printf("1.显示队列所有元素\n");
      printf("2.入队列\n");
      printf("3.出队列\n");
      printf("4.退出程序\n");
      scanf(" %c",&j);
      switch(j)
	{case '1':Print_LinkQueue(ls);   //显示队列中所有元素
		  break;
	 case '2':printf("请输入要人队的元素(一个字符):");
		  scanf(" %c",&ch);   //输入要入队列的字符
		  En_LinkQueue(ls,ch);//入队列
		  Print_LinkQueue(ls);
		  break;
	 case '3':temp=De_LinkQueue(ls,ch);  //出队列
		  if(temp!=False) {printf("出队一个元素:%c\n",ch);//若队列不空，显示出队列的元素
			      Print_LinkQueue(ls);
			     }
		else printf("队列为空!\n");//否则队列为空
		break;
	 default:flag=0;printf("程序运行结束，按任意键退出!\n");
	}
    }
 getch();
}

void initial(LinkQueue &Q)      
{//队列初始化
 Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode)); //生成一个头结点，并把首尾指针指向头结点 
 Q.front->next=NULL;
}

BOOL En_LinkQueue(LinkQueue &Q,char ch)
{//入队列，成功返回True，失败返回False
 QueuePtr p;
 p=(QueuePtr)malloc(sizeof(QNode));//生成一个新节点
 p->data=ch;                     //赋值
 p->next=NULL;                
 Q.rear->next=p;                 //插入至队列尾
 Q.rear=p;                       //修改队尾指针 
 return True;		        
}

BOOL De_LinkQueue(LinkQueue &Q,char &ch)
{//出队列,成功返回True，并用ch返回该元素值，失败返回False
 QueuePtr p;
 if(Q.front==Q.rear) return False;     //判断队列是否已空，已空返回False
 p=Q.front->next;           //p指向队列中第一个元素                              
 ch=p->data;                //取得该元素值
 Q.front->next=p->next;     //修改队首指针
 if(Q.rear==p) Q.rear=Q.front;//若队列已空，把队尾指针指向头结点
 return True;                     //成功出队列，返回True
}

void Print_LinkQueue(LinkQueue Q)      
{//显示队列中所有元素
 QueuePtr p;
 p=Q.front->next;
 if(p==NULL) printf("队列为空!\n");//队列为空
 else  {while(p!=NULL)                       //否则显示队列中所有元素
	    {printf("%c ",p->data);
	     p=p->next;
	    }
	printf("\n");
       }
}
