//* * * * * * * * * * * * * * * * * * * * * * * *
//*CHAPTER          :2  (2_2)                   *
//*PROGRAM          :链式结构的线性表           *
//*CONTENT          :生成,插入,删除,定位,查找   *
//* * * * * * * * * * * * * * * * * * * * * * * *
#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#define LEN sizeof(LNode)  //定义LEN为一个节点的长度
enum BOOL{False,True};  //定义BOOL型
typedef struct node
{char data;    //数据域
 struct node *next;//指向下一个节点的指针
}LNode,*LinkList;
void CreatList(LinkList &,int);   //生成一个单链表
BOOL ListInsert(LinkList &,int,char); //在单链表中插入一个元素
BOOL ListDelete(LinkList &,int,char &); //在单链表中删除一个元素
BOOL ListFind_keyword(LinkList,char,int &); //按关键字查找一个元素
BOOL ListFind_order(LinkList,char &,int);  //按序号查找一个元素
void ListPrint(LinkList);      //显示单链表所有元素
void main()
{LinkList L;
 BOOL temp;
 int num,loc,flag=1;
 char j,ch;
 textbackground(3); //设置屏幕颜色
 textcolor(15);
 clrscr();
 //---------------------程序解说-----------------------
 printf("本程序实现链式结构的线性表的操作。\n");
 printf("可以进行插入，删除，定位，查找等操作。\n");
 //----------------------------------------------------
 printf("请输入初始时链表长度:"); //输入生成单链表时的元素个数
 scanf("%d",&num);
 CreatList(L,num);      //生成单链表
 ListPrint(L);          
 while(flag)
    { printf("请选择:\n");
      printf("1.显示所有元素\n");  //显示链表元素
      printf("2.插入一个元素\n");  //插入链表元素
      printf("3.删除一个元素\n");  //删除链表元素
      printf("4.按关键字查找元素\n");  //按关键字查找
      printf("5.按序号查找元素\n"); //按序号查找
      printf("6.退出程序      \n");  //退出
      scanf(" %c",&j);
      switch(j)
	{case '1':ListPrint(L); break;
	 case '2':{printf("请输入元素(一个字符)和要插入的位置:\n");
		   printf("格式:字符，位置；例如:a,3\n");
		   scanf(" %c,%d",&ch,&loc);       //输入要插入的元素和要插入的位置
		   temp=ListInsert(L,loc,ch);      //插入
		   if(temp==False) printf("插入失败!\n"); //插入失败
		   else printf("插入成功!\n"); //成功插入
		   ListPrint(L);
		   break;
		  }
	 case '3':printf("请输入要删除的元素所在位置:");
		  scanf("%d",&loc);              //输入要删除的节点的位置
		  temp=ListDelete(L,loc,ch);    //删除
		  if(temp==False) printf("删除失败!\n"); //删除失败
		  else printf("成功删除了一个元素:%c\n",ch);   //删除成功，显示该元素
		  ListPrint(L);
		  break;
	 case '4':if(L->next==NULL)                   //链表为空
		     printf("链表为空!\n");
		  else{printf("请输入要查找的元素(一个字符):");
		       scanf(" %c",&ch);                //输入要查找的元素
		       temp=ListFind_keyword(L,ch,loc); //按关键字查找
		       if(temp==False) printf("没有找到该元素!\n"); //查找失败
		       else printf("该元素在链表的第%d个位置。\n",loc); 
                                           //成功查找，显示该元素位置
		      }
		  break;
	 case '5':if(L->next==NULL)                   //链表为空
		     printf("链表为空!\n");
		  else{printf("请输入要查找的位置:");
		       scanf("%d",&loc);    //输入要查找的元素的位置
		       temp=ListFind_order(L,ch,loc); //按序号查找
		       if(temp==False) printf("该位置不存在!\n"); //查找失败
		       else printf("第%d个元素是：%c\n",loc,ch);
                                //成功查找，显示该元素
		      }
		  break;
	 default:flag=0;printf("程序结束，按任意键退出!\n");
	}
    }
getch();
}
void CreatList(LinkList &v,int n)
{//生成一个带头结点的有n个元素的单链表 
 int i;
 LinkList p;
 v=(LinkList)malloc(LEN); //生成头结点
 v->next=NULL;
 printf("请输入%d个字符：例如：abcdefg\n",n);
 getchar();
 for(i=n;i>0;--i)
    {p=(LinkList)malloc(LEN); //生成新结点
     scanf("%c",&p->data);
     p->next=v->next;
     v->next=p;
    }
}
BOOL ListInsert(LinkList &v,int i,char e)
{//在单链表的第i各位置插入元素e，成功返回True，失败返回False
 LinkList p,s;
 int j=0;
 p=v;
 while(p&&j<i-1) {p=p->next;++j;} //查找第i-1个元素的位置
 if(!p||j>i-1) return False;  //没有找到
 s=(LinkList)malloc(LEN);     //生成一个新结点     
 s->data=e;            
 s->next=p->next;        //将新结点插入到单链表中 
 p->next=s;
 return True;
}

BOOL ListDelete(LinkList &v,int i,char &e)
{//在单链表中删除第i个元素，成功删除返回True，并用e返回该元素值，失败返回False
 LinkList p,q;
 int j=0;
 p=v;
 while(p->next&&j<i-1)  //查找第i-1个元素位置
    {p=p->next;++j;}
 if(!(p->next)||j>i-1) return False; //查找失败
 q=p->next;p->next=q->next; //删除该元素    
 e=q->data;         //e取得该元素值
 free(q);           //释放该元素空间
 return True;
}

BOOL ListFind_keyword(LinkList v,char e,int &i)
{//在单链表中查找关键字为e的元素，成功返回True,并用i返回该元素位置，
 //失败返回False
 i=1;
 LinkList p;
 p=v->next;
 while((p->data!=e)&&(p->next!=NULL))//p指针指向下一个，直到
    {p=p->next;  i++;}                        //找到或到链表尾为止
 if(p->data!=e)                      //该元素在链表中不存在
     return False;
 else return True;
}

BOOL ListFind_order(LinkList v,char &e,int i)
{//在单链表中查找第i个元素，成功返回True，并用e返回该元素值，
 //失败返回False
 LinkList p;
 int j=0;
 p=v;
 while(p->next&&j<i)  //移动指针，直到找到第i个元素
    {p=p->next;++j;}
 if(j!=i) return False; //查找失败
 else {e=p->data;       //查找成功，用e取得该元素值
       return True;
      }
}
void ListPrint(LinkList v)   
{//显示链表所有元素
 LinkList q;
 q=v->next;
 printf("链表所有元素:");
 while(q!=NULL)
   {printf("%c ",q->data);q=q->next;}
 printf("\n");
}