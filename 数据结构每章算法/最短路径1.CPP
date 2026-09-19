//* * * * * * * * * * * * * * * * * * * * * * * *
//*CHAPTER          :5  (5_5)                   *
//*PROGRAM          :最短路径                   *
//*CONTENT          :迪杰斯特拉算法             *
//* * * * * * * * * * * * * * * * * * * * * * * *
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFINITY 30000    //定义一个权值的最大值
#define MAX_VERTEX_NUM 20 //图的最大顶点数
enum BOOL {False,True};
typedef struct
{int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //邻接矩阵
 int vexnum,arcnum;                //图的当前顶点和边数
}Graph;
void CreateGraph(Graph &);    //生成图的邻接矩阵
void ShortestPath_DiJ(Graph,int,int[][MAX_VERTEX_NUM],int[]);
    //用迪杰斯特拉算法求从某一源点到其余顶点的最短路径
void Print_ShortestPath(Graph,int,int[][MAX_VERTEX_NUM],int[]);
    //显示最短路径
void main()
{Graph G;  //采用邻接矩阵结构的图
 char j='y';
 int u;
 int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //存放从源点到各顶点的最短路径
 int D[MAX_VERTEX_NUM];                 //存放从源点到各顶点的最短路径的距离
 textbackground(3);  //设定屏幕颜色
 textcolor(15);
 clrscr();
 //------------------程序解说----------------------------
 printf("本程序将演示利用迪杰斯特拉算法求\n从图的一点到其余顶点的最短路径.\n");
 printf("首先输入图的顶点数和弧数.\n格式：顶点数，弧数；例如:5,7\n");
 printf("然后输入各弧和权值.\n格式：弧尾，弧头，权值；例如:\n1,2,10\n1,3,18\n2,4,5\n3,2,5\n4,3,2\n4,5,2\n5,3,2\n");
 printf("再输入从哪个顶点出发，例如:1\n");
 printf("程序将会找出从1到其余顶点的最短路径.\n");
 printf("10  1->2\n17  1->2->4->3\n15  1->2->4\n17  1->2->4->5\n");
 //------------------------------------------------------
 while(j!='N'&&j!='n')
      {CreateGraph(G);       //生成邻接矩阵结构的图
       printf("从哪个顶点出发:");
       scanf("%d",&u);  //输入迪杰斯特拉算法中的起始顶点
       ShortestPath_DiJ(G,u,P,D); //利用迪杰斯特拉算法求最短路径
       Print_ShortestPath(G,u,P,D); //显示最短路径
       printf("最短路径演示完毕，继续进行吗?(Y/N)");
       scanf(" %c",&j);
     }
}

void CreateGraph(Graph &G)
{//构造邻接矩阵结构的图G
 int i,j;
 int start,end,weight;
 printf("请输入图的顶点数和弧数(顶点数，弧数):");
 scanf("%d,%d",&G.vexnum,&G.arcnum); //输入图的顶点数和边数
 for(i=1;i<=G.vexnum;i++)
    for(j=1;j<=G.vexnum;j++)
      G.arcs[i][j]=INFINITY; //初始化邻接矩阵
 printf("输入各弧和权值，格式：弧尾，弧头，权值\n");
 for(i=1;i<=G.arcnum;i++)
   {scanf("%d,%d,%d",&start,&end,&weight); //输入边的起点和终点及权值
    G.arcs[start][end]=weight;
   }
}
void ShortestPath_DiJ(Graph G,int v0,int P[][MAX_VERTEX_NUM],int D[])
{//用迪杰斯特拉算法求有向网G的v0顶点到其余顶点v的最短路径P[v]及其带权路径长度D[v]
 //若P[v][0]≠0,表明从源点出发存在一条到顶点v的最短路径，该路径存放在P[v]中
 //final[v]为True则表明已经找到从v0到v的最短路径
 int i,j,w,v;
 int min;
 BOOL final[MAX_VERTEX_NUM];
 for(v=1;v<=G.vexnum;v++)   //初始化
   {final[v]=False; D[v]=G.arcs[v0][v];
    for(i=0;i<=G.vexnum;i++) P[v][i]=0; //设空路径
    //if(D[v]<INFINITY) P[v][0]=v0; //若从v0到v有直达路径
   }
 D[v0]=0; final[v0]=True; //初始时，v0属于S集
 //开始主循环，每次求得v0到某个顶点v的最短路径，并加v到S集
 for(i=1;i<=G.vexnum;i++)  //寻找其余G.vexnum-1个顶点
   {v=0;
    min=INFINITY;
    for(w=1;w<=G.vexnum;w++)   //寻找当前离v0最近的顶点v
      if((!final[w])&&(D[w]<min))
	 {v=w;min=D[w];}
    if(!v) break;  //若v=0表明所有与v0有通路的顶点均已找到了最短路径，退出主循环
    final[v]=True; //将v加入S集
    for(j=0;P[v][j]!=0;j++) ;
    P[v][j]=v;     //将路径P[v]延伸到顶点v
    for(w=1;w<=G.vexnum;w++) //更新当前最短路径及距离
      if(!final[w]&&(min+G.arcs[v][w]<D[w]))
	 {D[w]=min+G.arcs[v][w];
	  for(j=0;P[v][j]!=0;j++) P[w][j]=P[v][j];
	 }
   }
}

void Print_ShortestPath(Graph G,int v0,int P[][MAX_VERTEX_NUM],int D[])
{//显示从顶点u到其余顶点的最短路径及距离
 int v,j;
 printf("The shortest path from Vertex %d to the other Vertex:\n");
 for(v=1;v<=G.vexnum;v++)
      {if(P[v][0]==0) continue; //表明顶点v0到顶点v没有通路
       printf("%-4d",D[v]);
       printf("%d->",v0);
       for(j=0;P[v][j]!=0;j++)
	 printf("%d->",P[v][j]);
       printf("\b\b  \n");
      }
}