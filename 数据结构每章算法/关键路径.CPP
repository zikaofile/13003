//* * * * * * * * * * * * * * * * * * * * * * * * *
//*CHAPTER          :5  (5_4)                     *
//*PROGRAM          :关键路径	                  *
//*CONTENT          :拓扑排序，关键路径           *
//* * * * * * * * * * * * * * * * * * * * * * * * *
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VERTEX_NUM 30 //图的最大顶点数
#define MAX 30            //栈的最大容量
#define INFINITY 30000;   //定义最大的最迟发生时间
enum BOOL {False,True};
typedef struct ArcNode
{int adjvex;              //该弧所指向的顶点的位置
 int weight;              //该弧所代表的活动的持续时间
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
int ve[MAX_VERTEX_NUM];  //全局变量，存放各顶点的最早发生时间
void CreateGraph(Graph &);    //生成图的邻接表
BOOL CriticalPath(Graph);     //求图的关键路径
BOOL TopologicalSort(Graph,Stack &T);  //进行拓扑排序
void FindInDegree(Graph&);    //求图各顶点的入度
void Initial(Stack &);     //初始化一个堆栈
BOOL Push(Stack &,int);  //将一个元素入栈
BOOL Pop(Stack&,int &);  //将一个元素出栈
BOOL Gettop(Stack,int&); //得到栈顶元素
BOOL StackEmpty(Stack);  //判断堆栈是否为空
void main()
{Graph G;  //采用邻接表结构的图
 char j='y';
 BOOL temp;
 textbackground(3);  //设定屏幕颜色
 textcolor(15);
 clrscr();
 //------------------程序解说----------------------------
 printf("本程序将演示构造图的关键路径.\n");
 printf("首先输入图的顶点数和弧数.\n格式：顶点数，弧数；例如:6,8\n");
 printf("接着输入各弧(弧尾,弧头)和权值.\n格式：弧尾，弧头，权值；例如:\n1,2,3\n1,3,2\n");
 printf("2,5,3\n5,6,1\n2,4,2\n4,6,2\n3,4,4\n3,6,3\n");
 printf("程序将会构造该图并找出其关键路径.\n");
 printf("关键路径:\n1->3  2\n3->4  4\n4->5  2\n");
 //------------------------------------------------------
 while(j!='N'&&j!='n')
      {CreateGraph(G);          //生成邻接表结构的图
       temp=CriticalPath(G);    //寻找G的关键路径
       if(temp==False) printf("该图有回路!\n");
		 //若返回为False,表明该图存在有环路
       else printf("该图没有回路!\n");
       printf("关键路径演示完毕，继续进行吗?(Y/N)");
       scanf(" %c",&j);
     }
}

BOOL CriticalPath(Graph G)
{//G为有向网，输出G的各项关键活动
 int j,dut,k,ee,el;
 int vl[MAX_VERTEX_NUM]; //存放各顶点的最迟发生时间
 Stack T;     //堆栈T存放拓扑排序的顶点序列
 ArcNode*p;
 Initial(T);  //初始化堆栈T
 if(!TopologicalSort(G,T)) return False; 
    //利用拓扑排序求出各顶点的最早发生时间，并用T返回拓扑序列，
    //若返回False，表明该网有回路
 printf("Critical Path:\n");
 Gettop(T,k); //k取得拓扑序列的最后一个顶点，即该网的汇点
 vl[k]=ve[k]; //汇点的vl=ve
 for(j=1;j<=G.vexnum;j++) if(j!=k) vl[j]=INFINITY; //将其他的顶点的vl置为IFINITY
 while(!StackEmpty(T)) //按拓扑逆序求各顶点的vl值
  {Pop(T,j);
   for(p=G.AdjList[j];p;p=p->nextarc)
     {k=p->adjvex;
      dut=p->weight;
      if(vl[k]-dut<vl[j]) vl[j]=vl[k]-dut;  
         //vl的求法：vl(i)=Min{vl(j)-dut(<i,j>)} <i,j>∈S,i=n-2,...0
     }
  }
 for(j=1;j<=G.vexnum;j++)  //求每条弧的最早开始时间ee和最迟开始时间el
   for(p=G.AdjList[j];p;p=p->nextarc)
      {k=p->adjvex;
       dut=p->weight;
       ee=ve[j];
       el=vl[k]-dut;
       if(ee==el) printf("%d->%d%5d\n",j,k,dut); //若ee=el，则该弧为关键活动
      }
 return True;
}
void CreateGraph(Graph &G)
{//构造邻接表结构的图G
 int i;
 int start,end,arcweight;
 ArcNode *s;
 printf("请输入顶点数和弧数(顶点数，弧数):");
 scanf("%d,%d",&G.vexnum,&G.arcnum); //输入图的顶点数和弧数
 for(i=1;i<=G.vexnum;i++) G.AdjList[i]=NULL; //初始化指针数组
 printf("请输入各弧和权值，格式:弧尾,弧头,权值\n");
 for(i=1;i<=G.arcnum;i++)
   {scanf("%d,%d,%d",&start,&end,&arcweight); 
        //输入弧的起点和终点即该弧所代表的活动的持续时间
    s=(ArcNode *)malloc(sizeof(ArcNode)); //生成一个弧结点
    s->nextarc=G.AdjList[start]; //插入到邻接表中
    s->adjvex=end;
    s->weight=arcweight;
    G.AdjList[start]=s;
   }
}

BOOL TopologicalSort(Graph G,Stack &T)
{//有向网G采用邻接表存储结构，求各顶点事件的最早发生时间ve，
 //T为拓扑序列顶点栈，S为零入度顶点栈。
 //若G无回路，则用栈返回G的一个拓扑序列，且函数返回True,否则返回False
 int i,k;
 int count; //计数器
 ArcNode* p;
 Stack S;
 FindInDegree(G); //求出图中各顶点的入度
 Initial(S);      //堆栈初始化，存放入度为零的顶点
 for(i=1;i<=G.vexnum;i++)
  if(!G.indegree[i]) Push(S,i); //入度为零的顶点入栈
 count=0;     //对输出顶点记数
 for(i=1;i<=G.vexnum;i++)
   ve[i]=0;   //ve初始化 
 while(!StackEmpty(S))
  {Pop(S,i);  //i号顶点出S栈并入T栈，count记数
   Push(T,i); 
   count++;
   for(p=G.AdjList[i];p;p=p->nextarc)
     {k=p->adjvex;       //对i号顶点的每个邻接顶点的入度减一
      if(!(--G.indegree[k])) Push(S,k); //若入度为零，入栈
      if((ve[i]+p->weight)>ve[k]) ve[k]=ve[i]+p->weight;
             //修改k号顶点的最迟发生时间
             //ve的求法：ve(j)=Max{ve(i)+dut(<i,j>)} <i,j>∈S,j=1,2,…,n-1
     }
  }
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
BOOL Gettop(Stack S,int &ch)
{//取得栈顶元素，成功返回True，并用ch返回该元素值，失败返回False
 if(S.top<=-1)
    return False;
 else {ch=S.elem[S.top];//显示栈顶元素
       return True;
      }
}
BOOL StackEmpty(Stack S)
{//判断堆栈是否已空，若空返回True,不空返回False
 if(S.top<=-1) return True;
 else return False;
}