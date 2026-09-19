#define MAX_VEX 50
int creatcost(cost)
int cost[][MAX_VEX];                  /*cost数组表示带权图的邻接矩阵*/
{
    int vexnum,arcnum,i,j,k,v1,v2,w;  /*输入图的顶点数和边数(或弧数)*/
    printf("\nInput vexnum,arcnum : ");
    scanf("%d,%d",&vexnum,&arcnum); 
    for(i=0;i<vexnum;i++)             /*初始化带权图的邻接矩阵*/
        for(j=0;j<vexnum;j++)
            cost[i][j]=32767;         /*32767表示无穷大*/
    for(k=0;k<arcnum;k++) 
    {
        printf("v1,v2,w = ");
        scanf("%d,%d,%d",&v1,&v2,&w); /*输入所有边(或弧)的一对顶点V1,V2和权值*/
        cost[v1][v2]=w;
        cost[v2][v1]=w; 
    } 
    return(vexnum);
}

void prime(cost,vexnum)               /*Prime算法产生从顶点V0 开始的最小生成树*/
int cost[][MAX_VEX],vexnum; 
{
    int lowcost[MAX_VEX],closest[MAX_VEX],i,j,k,min; 
    for(i=0;i<vexnum;i++) 
    {
        lowcost[i]=cost[0][i];        /*初始化*/
        closest[i]=0;                 /*初始化*/
    }
    closest[0]=-1;                    /*V0选入U*/
    for(i=1;i<vexnum;i++)             /*从U之外求离U中某一顶点最近的顶点*/
    {
        min=32767;
        k=0;
        for(j=0;j<vexnum;j++)
            if(closest[j]!=-1&&lowcost[j]<min)
            { 
                min=lowcost[j];
                k=j;
            }
            if(k)
            {                         /*输出边及其权值*/
                printf("(%d,%d)%2d\n",closest[k],k,lowcost[k]); 
                closest[k]=-1;        /*k选入U*/
                for(j=1;j<vexnum;j++)
                    if(closest[j]!=-1&&cost[k][j]<lowcost[j])
                    {
                        lowcost[j]=cost[k][j]; /*由k的加入,修改lowcost数组*/
                        closest[j]=k;          /*k加入到U中*/
                    }
            }
    }
}

main()    /*主程序*/
{
    int vexnum;
    int cost[MAX_VEX][MAX_VEX];
    vexnum=creatcost(cost);                     /*建立图的邻接矩阵*/ 
    printf("Output edge(arc) and cost of MCSTree : \n");
    prime(cost,vexnum);
}
程序运行结果（以图6.27中的A图为例）：
Input vexnum,arcnum : 6,10（回车）
v1,v2,w = 0,1,6（回车）
v1,v2,w = 0,2,5（回车）
v1,v2,w = 0,5,1（回车）
v1,v2,w = 1,5,5（回车）
v1,v2,w = 1,3,3（回车）
v1,v2,w = 2,5,5（回车）
v1,v2,w = 2,4,2（回车）
v1,v2,w = 3,5,6（回车）
v1,v2,w = 3,4,6（回车）
v1,v2,w = 4,5,4（回车）
Output edge(arc) and cost of MCSTree : 
(0,5) 1
(5,4) 4
(4,2) 2
(5,1) 5
(1,3) 3