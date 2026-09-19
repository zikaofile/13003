#include<stdio.h>
#define QUEUESIZE 20
typedef struct binode                        /*定义结点数据类型*/
{  int data;
   struct binode *lchild,*rchild;
}BITNODE,*BITREE;

typedef struct cirqueue
{
    int front,rear;
    BITNODE *data[QUEUESIZE];
}CIRQUEUE;

BITREE insertbst(BITREE s,BITREE t)          /*在二叉排序树中插入结点*/
{  if(t==NULL)
     t=s;                                    /*如果二叉排序树为空树，则插入的结点为根结点*/
   else
     if(s->data<t->data)
        t->lchild=insertbst(s,t->lchild);    /*如果该结点的数据小于根结点的数据则插入左子树*/
      else
        t->rchild=insertbst(s,t->rchild);    /*如果该结点的数据大于根结点的数据则插入右子树*/
   return t;
}

BITREE createordbt()                         /*创建二叉排序树*/
{  BITREE s,t;
   int x;
   t=NULL;
   printf("\nInput data please : ");
   scanf("%d",&x);                           /*输入结点数据*/
   while(x!=0)
   {
      s=(BITREE)malloc(sizeof(BITNODE));
      s->data=x;                             /*为生成的结点赋值*/
      s->lchild=NULL;
      s->rchild=NULL;
      t=insertbst(s,t);                      /*调用插入函数*/
      scanf("%d",&x);
    }
    return t;
}

BITREE delete(BITREE t,int key)              /*删除二叉排序树指定结点*/
{
    BITREE p,q,r,s;
    p=t;                                     /*p指向待比较的结点，初始时指向根结点*/
    q=NULL;                                  /*q指向p的前驱结点，初始时为空*/
    while((p!=NULL)&&(p->data!=key))         /*查找被删除的结点*/
    {
	if(key==p->data)
           break;
        else
           if(key<p->data)
           {
              q=p;
              p=p->lchild;
           }
           else
           {
              q=p;
              p=p->rchild;
           }
    }
    if(p==NULL)                             /*查找失败，没有可删除的结点，停止运行*/
    {
       printf("No find!");
       exit();
    }
    else                                                    /*分三种不同情况删除结点p*/
    {
       if((p->lchild==NULL)&&(p->rchild==NULL))             /*p的左右儿子都为空*/
          if(p==t)                                          /*p是否根结点*/
             t=NULL;                                        /*p是根结点，树为空*/
          else
             if(p==q->lchild)                               /*p是其父亲结点q的左儿子*/
	        q->lchild=NULL;
             else                                           /*p是其父亲结点q的右儿子*/
                q->rchild=NULL;
       else                                                 /*p有左或右儿子*/
          if((p->lchild==NULL)||(p->rchild==NULL))
             if(p==t)                                       /*p是否根结点*/
		if(p->lchild==NULL)                         /*p的左儿子为空*/
                   t=p->rchild;                             /*p的右儿子成为树根结点*/
                else
                   t=p->lchild;                             /*否则，p的左儿子成为树根结点*/
             else
             {                                              /*当p是非根结点时，分四种情况删除非根的单支结点*/
                if((p==q->lchild)&&(p->lchild!=NULL))       /*p是q的左儿子，p有左儿子*/
                   q->lchild=p->lchild;                     /*p的左儿子成为p的父亲结点q的左儿子*/
                else
                   if((p==q->lchild)&&(p->rchild!=NULL))    /*p是q的左儿子，p有右儿子*/
                      q->lchild=p->rchild;                  /*p的右儿子成为p的父亲结点q的左儿子*/
                   else
                      if((p==q->rchild)&&(p->lchild!=NULL)) /*p是q的右儿子，p有左儿子*/
                         q->rchild=p->lchild;               /*p的左儿子成为p的父亲结点q的右儿子*/
                   else
		      if((p==q->rchild)&&(p->rchild!=NULL)) /*p是q的右儿子，p有右儿子*/
                         q->rchild=p->rchild;               /*p的右儿子成为p的父亲结点q的右儿子*/
             }
          else
	     if((p->lchild!=NULL)&&(p->rchild!=NULL))       /*p同时有左右儿子*/
             {
                r=p;
                s=p->lchild;                                /*s指向p的左子树的根结点；r指向s的前驱结点*/
                while(s->rchild!=NULL)                      /*查找p的中序前驱结点*/
                {
                   r=s;
                   s=s->rchild;
                }
                p->data=s->data;                            /*s结点的值赋给p结点*/
                if(r==p)                                    /*删除单支结点s，使它的左子树链接到它所在的链接位置*/
                   p->lchild=s->lchild;
                else
                   r->rchild=s->lchild;
                p=s;                                        /*需删除s结点,p指向s结点*/
             }
    }
    free(p);
    return(t);
}

inorder(BITREE t)                              /*中序遍历二叉排序树*/
{
   if(t!=NULL)
   {
      inorder(t->lchild);
      printf("%d ",t->data);                    /*输出结点数值*/
      inorder(t->rchild);
   }
}

main()                                         /*主函数*/
{
   BITREE root;
   int x;
   root=createordbt();                         /*调用创建二叉排序树函数*/
   printf("The inorder is : ");
   inorder(root);                              /*调用中序遍历二叉排序树函数*/
   printf("\nInput a deleted datum to x : ");
   scanf("%d",&x);
   root=delete(root,x);                        /*调用删除值为x的结点函数*/
   printf("The inorder is : ");
   inorder(root);                              /*调用中序遍历二叉排序树函数*/
   printf("\n");
}
程序运行结果：
Input data please : 6 4 8 3 7 9 0（回车）
The inorder is : 3 4 6 7 8 9
Input a deleted datum to x : 8（回车）
The inorder is : 3 4 6 7 9