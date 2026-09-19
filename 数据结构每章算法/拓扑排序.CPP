//* * * * * * * * * * * * * * * * * * * * * * * *
//*CHAPTER          :5  (5_3)                   *
//*PROGRAM          :拓扑排序      	        *
//*CONTENT          :拓扑排序                   *
//* * * * * * * * * * * * * * * * * * * * * * * *
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VERTEX_NUM 20 //图的最大顶点数
#define MAX 30       //栈的最大容量
enum BOOL {False,True};
typedef struct ArcNode
{int adjvex;              //该弧所指向的顶点的位置
 struct ArcNode *nextarc; //指向下一条弧的指针
}ArcNode;       //弧结点
typedef struct
{int indegree[MAX_VERTEX_NUM]; //存放各顶点的入度
 ArcNode* AdjList[MAX_VERTEX_NUM]; //指向第一条依附该顶点的弧的指针
 int vexnum,arcnum;                //图的当前顶点和弧数
}Graph;
typedef struct    //定义堆栈结构
{int elem[MAX];   //栈区
 int top;         //栈顶指针
}Stack;
void CreateGraph(Graph &);    //生成图的邻接表
BOOL TopologicalSort(Graph);  //进行拓扑排序
void FindInDegree(Graph&);    //求图各顶点的入度
void Initial(Stack &);     //初始化一个堆栈
BOOL Push(Stack &,int); //将一个元素入栈
BOOL Pop(Stack&,int &); //将一个元素出栈
BOOL StackEmpty(Stack); //判断堆栈是否为空
void main()
{Graph G;  //采用邻接表结构的图
 char j='y';
 BOOL temp;
 textbackground(3);  //设定屏幕颜色
 textcolor(15);
 clrscr();
 //------------------程序解说----------------------------
 printf("本程序将演示怎样对图进行拓扑排序.\n");
 printf("首先输入图的顶点数和弧数.\n格式：顶点数，弧数；例如:4,4\n");
 printf("再输入各条弧(弧尾,弧头).\n例如:\n1,2\n1,3\n2,4\n4,3\n");
 printf("程序将会生成一个图并对它进行拓扑排序.\n");
 printf("拓扑排序结果:1->2->4->3\n");
 //------------------------------------------------------
 while(j!='N'&&j!='n')
      {CreateGraph(G);          //生成邻接表结构的图
       temp=TopologicalSort(G); //进行拓扑排序
       if(temp==False) printf("该图有回路!\n");
		 //若返回为False,表明该图存在有环路
       else printf("该图没有回路!\n");
       printf("拓扑排序完毕，继续进行吗?(Y/N)");
       scanf(" %c",&j);
     }
}

void CreateGraph(Graph &G)
{//构造邻接表结构的图G
 int i;
 int start,end;
 ArcNode *s;
 printf("请输入图的顶点数和弧数:");
 scanf("%d,%d",&G.vexnum,&G.arcnum); //输入图的顶点数和弧数
 for(i=1;i<=G.vexnum;i++) G.AdjList[i]=NULL; //初始化指针数组
 printf("请输入各弧, 格式：弧尾,弧头\n");
 for(i=1;i<=G.arcnum;i++)
   {scanf("%d,%d",&start,&end); //输入弧的起点和终点
    s=(ArcNode *)malloc(sizeof(ArcNode)); //生成一个弧结点
    s->nextarc=G.AdjList[start]; //插入到邻接表中
    s->adjvex=end;
    G.AdjList[start]=s;
   }
}
BOOL TopologicalSort(Graph G)
{//对图G进行拓扑排序，若G存在回路，返回False,否则返回True
 int i,k;
 int count; //计数器
 ArcNode* p;
 Stack S;
 FindInDegree(G); //求出图中各顶点的入度
 Initial(S);      //堆栈初始化，存放入度为零的顶点
 for(i=1;i<=G.vexnum;i++)
  if(!G.indegree[i]) Push(S,i); //入度为零的顶点入栈
 count=0;     //对输出顶点记数
 printf("拓扑排序:");
 while(!StackEmpty(S))
  {Pop(S,i);  //输出i号顶点并记数
   printf("%d->",i);
   count++;
   for(p=G.AdjList[i];p;p=p->nextarc)
     {k=p->adjvex;       //对i号顶点的每个邻接顶点的入度减一
      if(!(--G.indegree[k])) Push(S,k); //若入度为零，入栈
     }
  }
 printf("\b\b  \n");
 if(count<G.vexnum) return False; //如输出顶点数少于图中顶点数，则该图有回路
 else return True;
}
void FindInDegree(Graph &G)
{//求出图G的各顶点的入度，存放在G.indegree[1..G.vexnum]中
 int i;
 ArcNode* p;
 for(i=1;i<=G.vexnum;i++)
   G.indegree[i]=0; 
 for(i=1;i<=G.vexnum;i++)
    {
     for(p=G.AdjList[i];p;p=p->nextarc)
       G.indegree[p->adjvex]++;  //弧头顶点的入度加一
    }
}
void Initial(Stack &S)
{S.top=-1;   //栈顶指针初始化为-1
}

BOOL Push(Stack &S,int ch)
{//将元素ch入栈，成功返回True,失败返回False
 if(S.top>=MAX-1) return False;//判断是否栈满
 else {S.top++;               //栈顶指针top加一
       S.elem[S.top]=ch;      //入栈
       return True;
      }
}

BOOL Pop(Stack &S,int &ch)
{//将栈顶元素出栈,成功返回True，并用ch返回该元素值，失败返回False
 if(S.top<=-1) return False;//判断是否栈空
 else {S.top--;                                //栈顶指针减一
       ch=S.elem[S.top+1];
       return True;
      }
}
BOOL StackEmpty(Stack S)
{//判断堆栈是否已空，若空返回True,不空返回False
 if(S.top<=-1) return True;
 else return False;
}