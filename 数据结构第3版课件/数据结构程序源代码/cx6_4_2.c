    现就程序6-4运行的结果来作一个分析。算法中用函数creatadjlist()为图建立邻接表时，如果
对同一个图输入图中各条边（或弧）的次序不同，建立的邻接表是不同的。这样，依据此邻接表进行
dfs搜索，得到的dfs序列也就不一样了。能否任意次序输入图的各条边（或弧），而得到惟一的dfs
序列呢？我们可以对函数creatadjlist()稍作修改，在建立邻接表时，要为图中每一个顶点建立一个
单链表，在建立某顶点相关的单链表时，与此顶点相邻接的全部顶点按序号大小排列就可以了。以下
是经过修改的creatadjlist()函数。

int creatadjlist()                    /*建立邻接表*/
{      
    ARCNODE *ptr,*q,*s;
    int arcnum,vexnum,k,v1,v2;
    printf("input vexnum,arcnum:\n");
    scanf("%d,%d",&vexnum,&arcnum);   /*输入图的顶点数和边数（弧数）*/
    for(k=0;k<vexnum;k++)
    {
        adjlist[k].firstarc=NULL;     /*为邻接链表的adjlist数组各元素的链域赋初值*/
    }
    for(k=0;k<arcnum;k++)             /*为adjlist数组的各元素分别建立各自的链表*/
    {
        printf("v1,v2=");
        scanf("%d,%d",&v1,&v2);

        ptr=(ARCNODE*)malloc(sizeof(ARCNODE));  /*给结点V1 的相邻结点V2 分配内存空间*/
        ptr->vextex=v2;

        /*将顶点v2插入到链表中，使得结点插入后单链表仍然有序*/
        if((adjlist[v1].firstarc==NULL)||(adjlist[v1].firstarc->vextex>v2))
        {
             ptr->next=adjlist[v1].firstarc;
             adjlist[v1].firstarc=ptr;          /*将相邻顶点V2 插入表头结点V1 之后*/
        }
        else
        {
             q=adjlist[v1].firstarc;
             while((q!=NULL)&&(q->vextex<v2))
             {
                 s=q;
                 q=q->next;
             }
             ptr->next=q;
             s->next=ptr;
        }

        /*对于有向图此后的若干行语句要删除*/
        ptr=(ARCNODE*)malloc(sizeof(ARCNODE));  /*给结点V2 的相邻结点V1 分配内存空间*/
        ptr->vextex=v1;

        /*将顶点v1插入到链表中，使得结点插入后单链表仍然有序*/
        if((adjlist[v2].firstarc==NULL)||(adjlist[v2].firstarc->vextex>v1))
        {
             ptr->next=adjlist[v2].firstarc;
             adjlist[v2].firstarc=ptr;          /*将相邻顶点V1 插入表头结点V2之后*/
        }
        else
        {
             q=adjlist[v2].firstarc;
             while((q!=NULL)&&(q->vextex<v1))
             {
                 s=q;
                 q=q->next;
             }
             ptr->next=q;
             s->next=ptr;
	} 
        /*对于有向图到此为止的若干行语句要删除*/
    }
    return(vexnum);
}
