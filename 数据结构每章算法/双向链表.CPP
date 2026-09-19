//* * * * * * * * * * * * * * * * * * * * * * * *
//*CHAPTER          :2  (2_3)                   *
//*PROGRAM          :双向链表                   *
//*CONTENT          :生成,插入,删除,定位,查找   *
//* * * * * * * * * * * * * * * * * * * * * * * *
#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#define LEN sizeof(struct dunode)//定义双向链表一个节点的长度
enum BOOL{False,True};    //定义BOOL型
typedef struct dunode     //定义双向链表的结构
{char data;       //数据域
 struct dunode *prior,*next;//前项指针和后项指针
} *DuLink;

void CreatDuLink(DuLink &);   //逆序法建立一个双向链表
DuLink DuLinkFind(DuLink,int);  //按序号查找
BOOL DuLinkInsert(DuLink,char,int);   //插入
void Insafter(DuLink,char);  //插入一个元素到指定元素之后
BOOL DuLinkDelete(DuLink,int);        //删除一个元素
void DuLinkPrint(DuLink);             //显示所有元素

void main()
{DuLink DL;
 int loc,flag=1;
 char j,ch;
 BOOL temp;
 textbackground(3); //设置屏幕颜色
 textcolor(15);
 clrscr();
 //---------------------程序解说-----------------------
 printf("本程序实现双向链表结构的线性表的操作。\n");
 printf("可以进行插入，删除，定位，查找等操作。\n");
 //----------------------------------------------------
 printf("请输入初始时双向链表的各元素(以#结束):\n例如:abcdefg#\n");
 CreatDuLink(DL);              //建立一个双向链表
 DuLinkPrint(DL);              //显示
 while(flag)
    { printf("请选择:\n");
      printf("1.显示所有元素\n");
      printf("2.删除一个元素\n");
      printf("3.插入一个元素\n");
      printf("4.退出程序    \n");
      scanf(" %c",&j);
      switch(j)
	{case '1':DuLinkPrint(DL);  //显示
		  break;
	 case '2':printf("请输入要删除的元素所在位置:");
		  scanf("%d",&loc);          //输入要删除元素的序号
		  temp=DuLinkDelete(DL,loc); //删除
		  if(temp==False) printf("删除失败!\n"); //删除失败
		  else printf("删除成功!\n");  //成功删除
		  DuLinkPrint(DL);
		  break;
	 case '3':printf("请输入要插入的元素(一个字符)和插入位置:\n");
		  printf("格式：字符，位置；例如：a,3\n");
		  scanf(" %c,%d",&ch,&loc);      //输入要插入的元素和位置
		  temp=DuLinkInsert(DL,ch,loc);  //插入
		  if(temp==False) printf("插入失败!\n"); //插入失败
		  else printf("插入成功!\n");  //插入成功		  
                  DuLinkPrint(DL);
		  break;
	 default:flag=0;printf("程序结束，按任意键退出!\n");
	}
    }
getch();
}
void CreatDuLink(DuLink &head)
{//生成一个以head为头针的双向链表
 DuLink p;
 char ch;
 p=head=(DuLink)malloc(LEN);//生成头结点
 head->prior=head->next=head;//头结点的前向和后向指针都指向自己
 scanf(" %c",&ch);
 while(ch!='#')              //依次插入其后的节点到头节点之后
    {Insafter(p,ch);
     scanf("%c",&ch);
   }
 }

DuLink DuLinkFind(DuLink head,int location)
{//在双向链表中查找位置为location的元素，并返回其指针，
 //若没有找到，返回指针为NULL
 int k;
 DuLink p;
 p=head;
 k=0;
 while((k<location)&&(p->next!=head))//p指针向后移直到
    {k=k+1;p=p->next;}               //所找位置或表尾
 if(k==location||k==0)        //找到该位置，返回其指针
    return p;
 else return(NULL);     //该位置不存在，返回NULL
}

BOOL DuLinkInsert(DuLink head,char e,int loc)
{//在双向链表的第i个位置插入元素e,成功返回True，失败返回False
 DuLink p;
 if((p=DuLinkFind(head,loc-1))!=NULL)     //如果该位置存在，插入该元素
     {Insafter(p,e);return True;}
 else return False;
}
void Insafter(DuLink pi,char ch)
{//在双向链表的一个指定节点之后插入一个新节点
 DuLink s;                      
 s=(DuLink)malloc(LEN);         //生成一个新节点
 s->data=ch;                    //赋值
 s->next=pi->next;              //插入
 pi->next->prior=s;
 pi->next=s;
 s->prior=pi;
}
BOOL DuLinkDelete(DuLink head,int loc)
{//在双向链表中删除位置为loc的元素，成功返回True，失败返回False
 DuLink p;
 p=DuLinkFind(head,loc);         //寻找该元素的地址
 if(p==NULL) return False;       //如果为NULL,该序号不存在
 else {p->prior->next=p->next;   //删除该节点
       p->next->prior=p->prior;
       free(p);
       return True;              //释放所删节点的空间
       }
}

void DuLinkPrint(DuLink head)       
{//显示双向链表的所有节点
 DuLink q;
 q=head->next;
 if(head->next==head) printf("双向链表为空!\n");
 else{printf("双向链表所有元素:");
      while(q!=head)
	 {printf("%c ",q->data);q=q->next;}
      printf("\n");
     }
}