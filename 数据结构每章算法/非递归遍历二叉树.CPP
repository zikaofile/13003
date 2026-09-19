//* * * * * * * * * * * * * * * * * * * * * * * * * * *  
//*CHAPTER          :4  (4_2)                         *
//*PROGRAM          :非递归遍历二叉树                 *
//*CONTENT          :建立，先序、中序、后序遍历二叉树 *
//* * * * * * * * * * * * * * * * * * * * * * * * * * *
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 100          //定义堆栈最大容量
enum BOOL{False,True};
enum RVISIT{Rchildnovisit,Rchildvisit};  
         //在后序遍历二叉树时用来指示是否已访问过右子树
typedef struct  BiTNode      //定义二叉树节点结构
{char  data;                     //数据域
 struct BiTNode *lchild,*rchild; //左右孩子指针域
}BiTNode,*BiTree;
typedef struct        //定义堆栈结构
{BiTree elem[MAX];   //栈区
 int top;          //栈顶指针
}BiTreeStack;
void Initial(BiTreeStack &);     //初始化一个堆栈
BOOL Push(BiTreeStack &,BiTree); //将一个元素入栈
BOOL Pop(BiTreeStack&,BiTree &); //将一个元素出栈
BOOL Gettop(BiTreeStack ,BiTree &); //取得堆栈栈顶元素 
BOOL StackEmpty(BiTreeStack);    //判断堆栈是否已空
void CreateBiTree(BiTree &);    //生成一个二叉树
void PreOrder(BiTree);          //先序非递归遍历二叉树
void InOrder(BiTree);           //中序非递归遍历二叉树
void PostOrder(BiTree);         //后序非递归遍历二叉树
void main()
{BiTree T;
 char ch,j;
 int flag=1;
 BOOL temp;
 textbackground(3);  //设定屏幕颜色
 textcolor(15);
 clrscr();
 //--------------------程序解说-----------------
 printf("本程序实现二叉树的非递归遍历操作。\n");
 printf("可以实现建立二叉树，非递归先序、中序、后序遍历二叉树\n");
 //---------------------------------------------
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
 CreateBiTree(T);       //生成一棵二叉树
 getchar();
 while(flag)
    { printf("请选择: \n");
      printf("1.非递归先序遍历\n");
      printf("2.非递归中序遍历\n");
      printf("3.非递归中序遍历\n");
      printf("4.退出程序\n");
      scanf(" %c",&j);
      switch(j)
	{case '1':if(T)
		     {printf("先序遍历二叉树:");
		      PreOrder(T);
		      printf("\n");
		     }
		  else printf("二叉树为空!\n");
		  break;
	 case '2':if(T)
		    {printf("中序遍历二叉树:");
		     InOrder(T);
		     printf("\n");
		    }
		  else printf("二叉树为空!\n");
		  break;
	 case '3':if(T)
		    {printf("后序遍历二叉树");
		     PostOrder(T);
		     printf("\n");
		    }
		  else printf("二叉树为空!\n");
		  break;
	 default:flag=0;printf("程序运行结束，按任意键结束!\n");
	}
    }
 getch();
}

void Initial(BiTreeStack &S)
{S.top=-1;   //栈顶指针初始化为-1
}

BOOL Push(BiTreeStack &S,BiTree ch)
{//将元素ch入栈，成功返回True,失败返回False
 if(S.top>=MAX-1) return False;//判断是否栈满
 else {S.top++;               //栈顶指针top加一
       S.elem[S.top]=ch;      //入栈
       return True;
      }
}

BOOL Pop(BiTreeStack &S,BiTree &ch)
{//将栈顶元素出栈,成功返回True，并用ch返回该元素值，失败返回False
 if(S.top<=-1) return False;//判断是否栈空
 else {S.top--;                                //栈顶指针减一
       ch=S.elem[S.top+1];
       return True;
      }
}
BOOL Gettop(BiTreeStack S,BiTree &ch)
{//取得栈顶元素，成功返回True，并用ch返回该元素值，失败返回False
 if(S.top<=-1)
    return False;
 else {ch=S.elem[S.top];//显示栈顶元素
       return True;
      }
}

BOOL StackEmpty(BiTreeStack S)
{//判断堆栈是否已空，若空返回True,不空返回False
 if(S.top<=-1) return True;
 else return False;
}
void CreateBiTree(BiTree &T)
{//生成一棵二叉树，该二叉树以T为根结点
 char ch;
 scanf("%c",&ch);    //读入一个字符
 if(ch==' ') T=NULL;
 else {T=(BiTNode *)malloc(sizeof(BiTNode)); //生成一个新结点
       T->data=ch;
       CreateBiTree(T->lchild);  //生成左子树
       CreateBiTree(T->rchild);  //生成右子树
      }
}
void PreOrder(BiTree T)
{//先序非递归遍历以T为根结点的二叉树
 BiTreeStack S;
 BiTree p;
 Initial(S);
 p=T;
 while(p||!StackEmpty(S))
    { if(p) {printf("%c",p->data);
	     Push(S,p);
	     p=p->lchild;
	    }
      else {Pop(S,p);
	    p=p->rchild;
	   }
    }
 printf("\n");

}
void InOrder(BiTree T)
{//中序非递归遍历以T为根结点的二叉树
 BiTreeStack S;
 BiTree p;
 Initial(S);
 p=T;
 while(p||!StackEmpty(S))
    { if(p) {Push(S,p); p=p->lchild;}
      else {Pop(S,p);
	    printf("%c",p->data);
	    p=p->rchild;
	   }
    }
 printf("\n");
}
void PostOrder(BiTree T)
{//后序非递归遍历以T为根结点的二叉树
 BiTreeStack S;
 BiTree p,q;
 RVISIT tag;
 Initial(S);
 p=T;
 do {
    while(p)
      {Push(S,p); p=p->lchild;}
    q=NULL; tag=Rchildvisit;
    while(!StackEmpty(S)&&tag)
      {Gettop(S,p);
       if(p->rchild==q)
	   {printf("%c",p->data);
	    Pop(S,p);
	    q=p;
	   }
       else {p=p->rchild; tag=Rchildnovisit;}
      }
   }while(!StackEmpty(S));
 printf("\n");
}
