//* * * * * * * * * * * * * * * * * * * * * * * *
//*CHAPTER          :6  (6_3)                   *
//*PROGRAM          :静态树表的查找             *
//*CONTENT          :CreateSOSTree,Search       *
//* * * * * * * * * * * * * * * * * * * * * * * *
#include <dos.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 30  //静态树表的记录的最大个数
enum BOOL{False,True};
typedef struct  BiTNode       //定义二叉树节点结构
{char  data;                  //数据域
 struct BiTNode *lchild,*rchild; //左右孩子指针域
}BiTNode,*BiTree,*SOSTree; 
typedef struct SSTable //定义有序表的结构
{char elem[MAXSIZE];   //关键字
 int weight[MAXSIZE];  //权值 
 int length;           //有序表的当前长度 
}SSTable;
void CreateSOSTree(SOSTree&,SSTable);    //构造一个次优查找树
void SecondOptimal(BiTree &,SSTable,int sw[],int,int);
SOSTree Search(SOSTree,char); //在查找树中查找一个记录
void main()
{SOSTree T,p;
 SSTable ST;
 char ch,j='y';
 int i;
 textbackground(3);  //设定屏幕颜色
 textcolor(15);
 clrscr();
 //-------------------------程序说明-------------------------------
 printf("This program will show how to create a Nearly Optimal Search Tree\nand search a record in the Tree.\n");
 printf("First you input the number of the record:\nfor example:5\n");
 printf("Then you input the records(from small to big) and their weight: for example:\n");
 printf("A,1\nB,1\nC,2\nD,5\nE,3\n");
 printf("A NOSTree will be created and you can search a record.\n");   
 //----------------------------------------------------------------
 printf("Please input the number of the Record:\n");
 scanf("%d",&ST.length); //输入有序表的长度
 printf("Please input the Records and their weights:\nFormat:Record,weight,for example A,2\n");
 for(i=1;i<=ST.length;i++)
   scanf(" %c,%d",&ST.elem[i],&ST.weight[i]); //从小到大依次输入各个记录及其权值
 CreateSOSTree(T,ST);       //构造一颗次优查找树
 getchar();
 while(j!='N'&&j!='n')
    {printf("Please input the char you want to find:");
     scanf(" %c",&ch); //输入要查找的记录的关键字
     p=Search(T,ch);   //查找关键字为ch的记录
     if(p==NULL) printf("%c isn't existed!\n",ch); //没找到
     else printf("%c has been found.\n",ch);     //成功找到
     printf("Do you want to search next one?(Y/N)");
     scanf(" %c",&j);
    }
 printf("The program is over!\n");
}
void CreateSOSTree(SOSTree &T,SSTable ST)
{//由有序表ST构造一颗次优查找树T,ST的数据元素含有权域weight
 int sw[MAXSIZE];
 int i;
 if(ST.length==0) T=NULL;
 else
   {sw[0]=0;
    for(i=1;i<=ST.length;i++) sw[i]=sw[i-1]+ST.weight[i]; 
       //按照由有叙表ST中各数据元素的weight求累计权值表sw
    SecondOptimal(T,ST,sw,1,ST.length);
   }
}
void SecondOptimal(SOSTree &T,SSTable ST,int sw[],int low,int high)
{//由有序表ST及其累计权值表sw(sw[0]=0)递归构造次优查找树T。
 int i,j,min,dw;
 i=low;
 min=abs(sw[high]-sw[low]);
 dw=sw[high]+sw[low-1];
 for(j=low+1;j<=high;j++)     //选择最小的△P值
   if(abs(dw-sw[j]-sw[j-1])<min)
     {i=j;min=abs(dw-sw[j]-sw[j-1]);}
 T=(SOSTree)malloc(sizeof(BiTNode));
 T->data=ST.elem[i];        //生成结点
 if(i==low) T->lchild=NULL; //左子树空
 else SecondOptimal(T->lchild,ST,sw,low,i-1);  //构造左子树
 if(i==high) T->rchild=NULL; //右子树空
 else SecondOptimal(T->rchild,ST,sw,i+1,high); //构造右子树 
}
SOSTree Search(SOSTree T,char ch)
{//在次优查找树中查找关键字为ch的记录，找到则返回其地址指针，否则返回NULL
 SOSTree p;
 if(T==NULL) return NULL; //根结点为空，返回NULL
 for(p=T;p->data!=ch&&p!=NULL;) 
    if(p->data>ch) p=p->lchild; //若当前结点的关键字比ch大，则在其左子树中继续查找
    else p=p->rchild;           //若当前结点的关键字比ch小，则在其右子树中继续查找
 return p;
}
