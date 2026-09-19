/*二叉树的复制*/
#include<stdlib.h>
struct tree                                /*定义二叉树结点结构*/
{
   int data;                               /*结点数据*/
   struct tree *left;                      /*指向左子树的指针*/
   struct tree *right;                     /*指向右子树的指针*/
};

typedef struct tree TREENODE;              /*定义二叉树结点新类型*/
typedef TREENODE *BTREE;                   /*定义二叉树结点指针类型*/ 

BTREE createbtree(int *data,int pos)       /*创建二叉树*/
{
   BTREE newnode;                          /*新结点指针*/
   if(data[pos]==0||pos>15)                /*终止条件*/
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

BTREE copybtree(BTREE root)                        /*复制二叉树*/
{
   BTREE newnode;                                  /*新结点指针*/
   if(root==NULL)                                  /*终止条件*/
      return NULL;
   else
   {                                               /*以先序遍历方式复制*/
      newnode=(BTREE)malloc(sizeof(TREENODE));     /*创建新结点内存*/
      newnode->data=root->data;                    /*创建结点内容*/
      newnode->left=copybtree(root->left);         /*复制左子树*/
      newnode->right=copybtree(root->right);       /*复制右子树*/
      return newnode;
   }
}

void printbtree(BTREE ptr)                         /*中序输出二叉树*/
{
   if(ptr!=NULL)                                   /*终止条件*/
   {
      printbtree(ptr->left);                       /*左子树*/
      printf("[%2d] ",ptr->data);                  /*输出结点内容*/
      printbtree(ptr->right);                      /*右子树*/
   }
}

main()                                             /*主程序*/
{
   BTREE root=NULL;                                /*原二叉树指针*/
   BTREE backup=NULL;                              /*复制二叉树指针*/
   int data[16]={0,5,4,6,2,0,0,8,1,3,0,0,0,0,7,9}; /*二叉树结点数据,data[0]元素不用*/
   root=createbtree(data,1);                       /*调用创建二叉树函数*/
   backup=copybtree(root);                         /*调用复制二叉树函数*/
   printf("原二叉树的结点内容\n");
   printbtree(root);                               /*调用中序输出二叉树函数*/
   printf("\n备份二叉树的结点内容\n");
   printbtree(backup);                             /*调用中序输出二叉树函数*/
   printf("\n");
} 
程序运行结果：
原二叉树的结点内容
[1] [2] [3] [4] [5] [6] [7] [8] [9]
备份二叉树的结点内容
[1] [2] [3] [4] [5] [6] [7] [8] [9]
