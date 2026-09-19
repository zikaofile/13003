//* * * * * * * * * * * * * * * * * * * * * * * * * *
//*CHAPTER          :4  (4_3)                       *
//*PROGRAM          :线索二叉树                     *
//*CONTENT          :初始化，中序线索化，遍历线索树 *
//* * * * * * * * * * * * * * * * * * * * * * * * * *
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
enum PointerTag{Link,Thread};
	//Link==0:指针,Thread==1:线索
typedef struct  BiThrNode      //定义线索二叉树节点结构
{char  data;                     //数据域
 struct BiThrNode *lchild,*rchild; //左右孩子指针
 PointerTag LTag,RTag;            //左右标志，指明是指针还是线索
}BiThrNode,*BiThrTree;
void CreateBiThrTree(BiThrTree &);    //生成一个二叉树
void InOrder_Thr(BiThrTree);          //对中序线索二叉树进行遍历
void InOrderThreading(BiThrTree &,BiThrTree );  //对二叉树进行中序线索化  
void InThreading(BiThrTree);
BiThrTree pre;    //全局变量，在遍历时用来指示前驱结点
void main()
{BiThrTree T,Thrt;
 textbackground(3);  //设定屏幕颜色
 textcolor(15);
 clrscr();
 //---------------------程序解说-----------------------
 printf("本程序实现二叉树的操作。\n");
 printf("可以进行建立二叉树，递归先序、中序、后序遍历等操作。\n");
 //----------------------------------------------------
 printf("请将先序遍历二叉树的结果输入以建立二叉树。\n");
 printf("对于叶子结点以空格表示。\n");
 printf("例如:abc  de g  f   (回车)，建立如下二叉树：\n");
 printf("           a      \n");
 printf("          /       \n");
 printf("         b        \n");
 printf("        / \\       \n");
 printf("       c   d      \n");
 printf("          / \\     \n");
 printf("         e   f    \n");
 printf("          \\       \n");
 printf("           g      \n");
 CreateBiThrTree(T);       //生成二叉树  
 InOrderThreading(Thrt,T); //对二叉树进行中序线索化
 if(Thrt->lchild==Thrt) printf("二叉树为空!\n"); //该二叉树为空
 else {printf("遍历二叉树为:");  //否则对该二叉树进行遍历
       InOrder_Thr(Thrt);
       printf("\n");getchar();
      }
 printf("程序运行结束，按任意键退出!\n");
 getchar();
}

void CreateBiThrTree(BiThrTree &T)
{//生成一棵二叉树，该二叉树以T为根结点
 char ch;
 scanf("%c",&ch);    //读入一个字符
 if(ch==' ') T=NULL;
 else {T=(BiThrNode *)malloc(sizeof(BiThrNode)); //生成一个新结点
       T->data=ch;
       CreateBiThrTree(T->lchild);  //生成左子树
       CreateBiThrTree(T->rchild);  //生成右子树
      }
}

void InOrderThreading(BiThrTree &Thrt,BiThrTree T)
{//对二叉树T进行中序线索化，生成以Thrt为头结点的线索二叉树
 Thrt=(BiThrTree)malloc(sizeof(BiThrNode)); //生成头结点
 Thrt->LTag=Link; Thrt->RTag=Thread;        //建头指针
 Thrt->rchild=Thrt;                         //右指针回指
 if(!T) Thrt->lchild=Thrt;                  //若二叉树空，左指针回指
 else {Thrt->lchild=T; pre=Thrt;            //根结点作为头结点的左孩子
       InThreading(T);                      //中序遍历进行中序线索化
       pre->rchild=Thrt; pre->RTag=Thread;  //最后一个结点线索化
       Thrt->rchild=pre;    //头结点的右指针指向遍历时的最后一个结点
      }
}
void InThreading(BiThrTree p)
{if(p)
   {InThreading(p->lchild);  //线索化左子树
    if(!p->lchild)           //若左孩子为空，进行前驱线索化
       {p->LTag=Thread; p->lchild=pre;}
    else p->LTag=Link;       //否则，LTag标志为Link
    if(!pre->rchild)        //若前驱的右孩子为空，进行后继线索化
       {pre->RTag=Thread; pre->rchild=p;}
    else pre->RTag=Link;    //否则，RTag标志为Link
    pre=p;                  //修改前驱指针
    InThreading(p->rchild); //线索化右子树
   }
}
void InOrder_Thr(BiThrTree Thrt)
{BiThrTree p;
 p=Thrt->lchild;      //p指向根结点
 while(p!=Thrt)       //空树或遍历结束时，p==Thrt 
   {while(p->LTag==Link) p=p->lchild; //寻找最左下的左子树为空的结点
    printf("%c",p->data);             //访问该结点
    while(p->RTag==Thread&&p->rchild!=Thrt)
       {p=p->rchild;                  //访问后继结点
	printf("%c",p->data);
       }
    p=p->rchild;
   }
}
