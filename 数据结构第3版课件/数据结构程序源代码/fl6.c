#include<alloc.h>
#define MAX_VEX 50
typedef struct arcnode                  /*定义表结点*/
{
    int vextex;
    struct arcnode *next;
}ARCNODE;

typedef struct vexnode                  /*定义头结点*/
{
    int data;
    ARCNODE *firstarc;
}VEXNODE;
VEXNODE adjlist[MAX_VEX];               /*定义表头向量adjlist*/

int creatadjlist()                      /*建立邻接表*/
{
    ARCNODE *ptr;
    int arcnum,vexnum,k,v1,v2;
    printf("input vexnum,arcnum :\n");
    scanf("%d,%d",&vexnum,&arcnum);     /*输入图的顶点数和边数(弧数)*/
    for(k=0;k<vexnum;k++)
        adjlist[k].firstarc=NULL;       /*为邻接链表的adjlist数组各元素的链域赋初值*/
    for(k=0;k<arcnum;k++)               /*为adjlist数组的各元素分别建立各自的链表*/
    {
        printf("v1,v2 = ");
        scanf("%d,%d",&v1,&v2);
        ptr=(ARCNODE*)malloc(sizeof(ARCNODE));  /*给顶点V1的相邻顶点V2分配内存空间*/
        ptr->vextex=v2;
        ptr->next=adjlist[v1].firstarc;
        adjlist[v1].firstarc=ptr;               /*将相邻顶点V2 插入表头结点V1 之后*/
        
        ptr=(ARCNODE*)malloc(sizeof(ARCNODE));  /*对于有向图此后的四行语句要删除*/
        ptr->vextex=v1;                         /*给顶点V2 的相邻顶点V1分配内存空间*/
        ptr->next=adjlist[v2].firstarc;
        adjlist[v2].firstarc=ptr;               /*将相邻顶点V1插入表头结点V2之后*/
    }
    return(vexnum);
}

void bfs(v)                  /*从某顶点V出发按广度优先搜索进行图的遍历*/
int v;
{
    int queue[MAX_VEX];
    int front=0,rear=1;
    int w;
    ARCNODE *p;
    p=adjlist[v].firstarc;
    printf("%d\n",v);                      /*访问初始顶点*/
    adjlist[v].data=1;                     /*置已访问标志*/
    queue[rear]=v;                         /*初始顶点入队列*/
    while(front!=rear)                     /*队列不为空时循环*/
    {
        front=(front+1)%MAX_VEX;
        v=queue[front];                    /*按访问次序依次出队列*/
        p=adjlist[v].firstarc;             /*找V的邻接点*/
        while(p!=NULL)
        {
            if(adjlist[p->vextex].data==0)
            {
                adjlist[p->vextex].data=1;
                printf("%d\n",p->vextex);  /*访问该点并使之入队列*/
                rear=(rear+1)%MAX_VEX;
                queue[rear]=p->vextex;
            }
            p=p->next;                     /*找V的下一个邻接点*/
        }
    }
}

main()
{
    int i,n;
    ARCNODE *p;
    n=creatadjlist();           /*建立邻接表并返回顶点的个数*/
    printf("bfs output : \n");
    for(i=0;i<n;i++)            /*从图中的每个顶点出发进行bfs*/
        if(adjlist[i].data==0)  /*如果顶点i未被访问过*/
            bfs(i);             /*从顶点i出发,按bfs进行图的遍历*/
}
程序运行结果：
input vexnum,arcnum :
6,6（回车）
v1,v2 = 0,1（回车）
v1,v2 = 0,2（回车）
v1,v2 = 0,3（回车）
v1,v2 = 1,3（回车）
v1,v2 = 2,3（回车）
v1,v2 = 4,5（回车）
bfs output : 
0
3
2
1
4
5
