/*表达式二叉树的创建和计算*/
#include<stdlib.h>
struct tree                                /*定义二叉树结点结构*/
{
   char data;                              /*结点数据*/
   struct tree *left;                      /*指向左子树的指针*/
   struct tree *right;                     /*指向右子树的指针*/
};

typedef struct tree TREENODE;              /*定义二叉树结点新类型*/
typedef TREENODE *BTREE;                   /*定义二叉树结点指针类型*/

BTREE createbtree(int *data,int pos)       /*创建二叉树*/
{
   BTREE newnode;                          /*新结点指针*/
   if(data[pos]==0||pos>7)                 /*终止条件*/
      return NULL;
   else
   {                                               /*申请新结点内存*/
      newnode=(BTREE)malloc(sizeof(TREENODE));
      newnode->data=data[pos];                     /*输入新结点数据*/
      newnode->left=createbtree(data,2*pos);       /*创建左子树的递归调用*/
      newnode->right=createbtree(data,2*pos+1);    /*创建右子树的递归调用*/
      return newnode;
   }
}

void inorder(BTREE ptr)            /*表达式二叉树中序输出*/
{
   if(ptr!=NULL)                     /*终止条件*/
   {
      inorder(ptr->left);            /*左子树*/
      printf("%c",ptr->data);        /*输出结点内容*/
      inorder(ptr->right);           /*右子树*/
   }
}

void preorder(BTREE ptr)             /*表达式二叉树先序输出*/
{
   if(ptr!=NULL)                     /*终止条件*/
   {
      printf("%c",ptr->data);        /*输出结点内容*/
      preorder(ptr->left);           /*左子树*/
      preorder(ptr->right);          /*右子树*/
   }
}

void postorder(BTREE ptr)            /*表达式二叉树后序输出*/
{
   if(ptr!=NULL)                     /*终止条件*/
   {
      postorder(ptr->left);          /*左子树*/
      postorder(ptr->right);         /*右子树*/
      printf("%c",ptr->data);        /*输出结点内容*/
   }
}

int cal(BTREE ptr)                   /*表达式二叉树后序计值*/
{
   int operand1=0;                        /*前操作数变量*/
   int operand2=0;                        /*后操作数变量*/
   if(ptr->left==NULL&&ptr->right==NULL)  /*终止条件*/
      return ptr->data-48;                /*字符数字转十进制数字*/
   else
   {
      operand1=cal(ptr->left);            /*左子树*/
      operand2=cal(ptr->right);           /*右子树*/
      return getvalue(ptr->data,operand1,operand2);
   }
}

int getvalue(int op,int operand1,int operand2)  /*计算二叉树表达式的值*/
{
   switch((char)op)
   {
      case'*':return(operand1*operand2);
      case'-':return(operand1-operand2);
      case'+':return(operand1+operand2);
      case'/':return(operand1/operand2);
   }
}

main()                                     /*主程序*/
{
   BTREE root=NULL;                        /*表达式二叉树指针*/
   int result;                             /*结果变量*/
   int data[8]={' ','+','*','*','5','6','4','3'}; /*表达式二叉树结点数据*/
   root=createbtree(data,1);               /*调用创建表达式二叉树函数*/
   printf("中序表达式:");
   inorder(root);                          /*调用中序输出二叉树函数*/
   printf("\n先序表达式:");
   preorder(root);                         /*调用先序输出二叉树函数*/
   printf("\n后序表达式:");
   postorder(root);                        /*调用后序输出二叉树函数*/
   result=cal(root);                       /*调用计算表达式值函数*/
   printf("\n表达式结果是:%d\n",result);   /*输出结果*/
}
程序运行结果：
中序表达式: 5*6+4*3
先序表达式: +*56*43
后序表达式: 56*43*+
表达式结果是: 42