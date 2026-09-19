#define MAXLEN 3      /*定义一常量MAXLEN为3,为索引表的大小*/
#define MAXITEM 15    /*定义一常量MAXITEM为15,为顺序表的大小*/
struct indexterm      /*索引表元素的定义*/
{
   int key;           /*待查找索引表的元素关键字域，它是该块中的最大值*/
   int low,high;      /*low是某一块的下界(下标),high是某一块的上界(下标)*/
};
typedef struct indexterm index[MAXLEN];   /*定义索引表*/

struct element        /*块内用顺序表元素的定义*/
{
   int key;           /*元素关键字域*/
                      /*若有其他域,继续定义,这里假设只有key域*/
};
typedef struct element sqlist[MAXITEM];

/*对关键字为k的数据元素,先二分查找索引表idx,再顺序检索r中相应块,*/
/*若找到了,返回其r中位置i(下标);若找不到,返回-1*/
int blksearch(r,idx,k,bn)    
sqlist r;
index idx;                       /*idx为索引表*/
int k;
int bn;                          /*bn为顺序表r中块的个数*/
{
   int i,low1=0,high1=bn-1;
   int mid1,hb,find=0;
   while(low1<=high1&&!find)     /*二分查找索引表idx*/
   {                             /*low1带出块号*/
      mid1=(low1+high1)/2;
      if(k<idx[mid1].key)
         high1=mid1-1;
      else
         if(k>idx[mid1].key)
            low1=mid1+1;
         else
         {
	    low1=mid1;
            find=1;
         }
   }
   if(low1<bn)                   /*真,k可在顺序表r相应块内继续查找*/
   {
      i=idx[low1].low;           /*在索引表中确定块起始地址*/
      hb=idx[low1].high;         /*在索引表中确定块终止地址*/

      while(i<hb&&r[i].key!=k)   /*在指定的块内采用顺序方法进行查找*/
	 i++;                   

      if(r[i].key!=k)            /*块内无关键字k的元素*/
	 i=-1;
   }
   else                          /*假,无关键字k的元素*/
      i=-1;
   return(i);
}
                                  
main()                           /*主程序*/
{
   sqlist a={9,22,12,14,35,42,44,38,48,60,58,47}; /*待查顺序表*/
   index b={22,0,3,44,4,7,60,8,11};               /*待查索引表*/
   int k,j;
   printf("输入待查关键字k : ");
   scanf("%d",&k);
   j=blksearch(a,b,k,3);         /*通过索引表b在待查顺序表a中查找关键字k*/
                                 /*待查顺序表为3块*/
   if(j>=0)
      printf("%d在第%d个下标位置.\n",k,j);
   else
      printf("无此元素!\n");
}
程序第一次运行结果：
输入待查关键字k : 44（回车）
44在第6个下标位置.

程序第二次运行结果：
输入待查关键字k : 62（回车）
无此元素!
