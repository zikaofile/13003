#define MAX_VEX 50
int creatcost(cost)
int cost[][MAX_VEX];                   /*cost表示图的邻接矩阵*/
{
    int vexnum,arcnum,i,j,k,v1,v2,w;   /*输入图的顶点数和弧数(或边数)*/
    printf("\nInput vexnum,arcnum : ");
    scanf("%d,%d",&vexnum,&arcnum);
    for(i=0;i<vexnum;i++)
        for(j=0;j<vexnum;j++)
           cost[i][j]=9999;            /*本例设9999代表无限大*/
    for(k=0;k<arcnum;k++)
    {
        printf("v1,v2,w = ");
        scanf("%d,%d,%d",&v1,&v2,&w);  /*输入所有弧(或边)的一对顶点V1,V2 */
        cost[v1][v2]=w;
    }
    return(vexnum);                    /*返回图的顶点数*/
}

int p[MAX_VEX][MAX_VEX];               /*定义存放路径的数组P*/
void floyed(cost,vexnum)
int cost[][MAX_VEX],vexnum;            /*Floyed算法求每一对顶点之间的最短路径*/
{
    int a[MAX_VEX][MAX_VEX],i,j,k;
    for(i=0;i<vexnum;i++)
        for(j=0;j<vexnum;j++)
        {
            a[i][j]=cost[i][j];        /*给A和P数组赋初值*/
            p[i][j]=-1;
        }
    
    for(i=0;i<vexnum;i++)              /*同一顶点间的最短路径为零*/
        a[i][i]=0;

    for(k=0;k<vexnum;k++)              /*通过递推求最短路径长度和路径*/
    {
        for(i=0;i<vexnum;i++)
             for(j=0;j<vexnum;j++)
                 if(a[i][k]+a[k][j]<a[i][j])
                 {
                     a[i][j]=a[i][k]+a[k][j];
                     p[i][j]=k;
                 }
    }
    printf("Shortest distance of each pair of nodes :\n");
    for(i=0;i<vexnum;i++)              /*输出每对顶点间的最短路径*/
    {
        for(j=0;j<vexnum;j++)
	    printf("%d  ",a[i][j]);
        printf("\n");
    }
    printf("Shortest path of each pair of nodes :\n"); 
    for(i=0;i<vexnum;i++)              /*输出每一对顶点间的最短路径上的各个点*/
        for(j=0;j<vexnum;j++)
        {
            printf("%d-->",i);
            putpath(i,j);
	    printf("%d \n",j);
        }
}

putpath(int i,int j)                   /*输出一对顶点间的最短路径上的各个点*/
{
    int k;
    k=p[i][j];
    if(k==-1)
       return;
    putpath(i,k);
    printf("%d-->",k);
    putpath(k,j);
}

main()                          /*主程序*/
{
   int vexnum;
   int cost[MAX_VEX][MAX_VEX];
   vexnum=creatcost(cost);      /*建立图的邻接矩阵*/
   floyed(cost,vexnum);         /*调用算法求每一对顶点间的最短路径*/
}
程序运行结果（以图6.34中的图为例）：
Input vexnum,arcnum : 3,5（回车）
v1,v2,w =  0,1,4 （回车）
v1,v2,w =  0,2,11（回车）
v1,v2,w =  1,2,2 （回车）
v1,v2,w =  2,0,3 （回车）
v1,v2,w =  1,0,6 （回车）
Shortest distance of each pair of nodes :
0  4  6
5  0  2
3  7  0
Shortest path of each pair of nodes :
0-->0
0-->1
0-->1-->2
1-->2-->0
1-->1
1-->2
2-->0
2-->0-->1
2-->2

