#define MAX_VEX 50
typedef struct edges        /*定义边集数组元素结构*/
{ 
    int bv,ev,w;
}EDGES;
EDGES edgeset[MAX_VEX];     /*定义边集数组,用于存储图的各条边*/

int createdgeset()             /*建立边集数组函数*/
{
    int arcnum,i;
    printf("\nInput arcnum : ");
    scanf("%d",&arcnum);       /*输入图中的边数*/
    for(i=0;i<arcnum;i++)
    {
        printf("bv,ev,w = ");  /*输入每条边的起、终点及边上的权值*/
        scanf("%d,%d,%d",&edgeset[i].bv,&edgeset[i].ev,&edgeset[i].w);
    }
    return(arcnum);            /*返回图中的边数*/
}

sort(int n) /*对边集数组按权值升序排序,其中n为数组元素的个数,即图的边数*/
{
    int i,j;
    EDGES t;
    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
           if(edgeset[i].w>edgeset[j].w)
           { 
                t=edgeset[i];
                edgeset[i]=edgeset[j];
                edgeset[j]=t;
           }
}

int seeks(int set[],int v)     /*确定顶点V所在的连通分量的根结点*/
{ 
    int i=v;
    while(set[i]>0)
    i=set[i];
    return(i); 
}

kruskal(int e) /*Kruskal算法求最小生成树,参数e为边集数组中的边数*/
{
    int set[MAX_VEX],v1,v2,i,j;
    printf("Output of Kruskal : \n"); 
    for(i=0;i<MAX_VEX;i++)
        set[i]=0;      /*set数组的初值为0,表示每一个顶点自成一个分量*/
    i=0;               /*i表示待获取的生成树中的边在边集数组中的下标*/
    while(i<e)
    {
        v1=seeks(set,edgeset[i].bv);  /*确定边的起始顶点所在的连通分量的根结点*/
        v2=seeks(set,edgeset[i].ev);  /*确定边的终止顶点所在的连通分量的根结点*/
        if(v1!=v2)   /*当边所依附的两个顶点不在同一连通分量时,将该边加入生成树*/
        {
            printf("(%d,%d)  %d\n",edgeset[i].bv,edgeset[i].ev,edgeset[i].w);
            set[v1]=v2;                         /*将v1,v2 设为在同一连通分量中*/ 
        }
        i++;
    }
}

main()                             /*主程序*/
{
   int i,arcnum;
   arcnum=createdgeset();          /*建立图的边集数组,并返回其中的边数*/
   sort(arcnum);                   /*对边集数组按权值升序排序*/
   printf("Output edgeset according to ascending Cost : "); 
   printf("\nbv   ev   w \n");
   for(i=0;i<arcnum;i++)           /*输出排序后的边集数组*/
      printf("%d    %d    %d\n",edgeset[i].bv,edgeset[i].ev,edgeset[i].w);
   kruskal(arcnum);                /*利用克鲁斯卡尔算法求图的最小生成树*/
}
程序运行结果（以图6.28中的A图为例）：
Input arcnum : 10（回车）
bv,ev,w = 0,2,5（回车）
bv,ev,w = 0,1,6（回车）
bv,ev,w = 0,5,1（回车）
bv,ev,w = 1,3,3（回车）
bv,ev,w = 1,5,5（回车）
bv,ev,w = 2,4,2（回车）
bv,ev,w = 2,5,5（回车）
bv,ev,w = 3,4,6（回车）
bv,ev,w = 3,5,6（回车）
bv,ev,w = 4,5,4（回车）
Output edgeset according to ascending Cost :
bv   ev   w
0    5    1
2    4    2
1    3    3
4    5    4
0    2    5
2    5    5
1    5    5
3    4    6
3    5    6
0    1    6
Output of Kruskal :
(0,5)  1
(2,4)  2
(1,3)  3
(4,5)  4
(1,5)  5 