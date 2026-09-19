#define MAXITEM 100    /*定义一常量MAXITEM为100,为有序表的大小*/
struct element         /*有序表元素的定义*/
{
    int key;           /*结点关键字域*/
                       /*若有其他数据,继续定义,这里假设只有key域*/
};
typedef struct element sqlist[MAXITEM];

int bin_search(r,k,n)  /*在有序表r中二分查找其关键字等于k的记录*/
sqlist r;              /*若找到,则函数值为该数据在表中的位置,否则为-1*/
int k;
int n;                 /*n为有序表r中记录个数*/
{
    int low=1,high=n,found=0,mid;
    while((low<=high)&&!found)
    {
        mid=(low+high)/2;      /*求中点*/
        if(k==r[mid].key)
            return(mid);       /*找到k*/
        else
        {
            if(k>r[mid].key)
               low=mid+1;      /*在后半部分查找*/
            else
               high=mid-1;     /*在前半部分查找*/
        } 
    }
    return(-1);                /*查找不成功,返回-1作为标记*/
}

main()                         /*主程序*/
{
    sqlist a={0,3,4,5,7,8,10}; /*有序表a有n=6个元素,下标0中无元素*/
    int i,k;
    printf("\nInput a key : ");
    scanf("%d",&k);
    i=bin_search(a,k,6);       /*找k=8的元素下标*/
    if(i!=-1)
       printf("%d的下标是%d\n",k,i);
    else
       printf("无此元素\n");
}
程序第一次运行结果：
Input a key : 8（回车）
8的下标是5
程序第二次运行结果：
Input a key : 20（回车）
无此元素

