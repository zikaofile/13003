void insertsort(int r[],int length) /*直接插入排序函数*/
{
   int i,j,x;
   for(i=1;i<length;++i)            /*第一个数总是有序的,i从2开始*/
      if(r[i]<r[i-1])               /*如"<",将r[i]插入有序序列中*/
      {
         x=r[i];                    /*r[i]的值暂存x中*/
	 for(j=i-1;x<r[j]&&j>=0;--j)
            r[j+1]=r[j];            /*记录后移*/
         r[j+1]=x;                  /*插入到正确位置*/
      }
}

void shellsort(int r[],int length)  /*希尔排序函数*/
{
   int d,i,j,k,x;
   d=length/2;                      /*取第一个步长值*/
   while(d>=1)                      /*对各组进行直接插入排序*/
   {
      for(i=d;i<length;i++)         /*对每组进行直接插入排序*/
      {
         x=r[i];                    /*记录r[i]暂存入x中*/
         j=i-d;                     /*确定每组中的记录r[i]前一个位置*/
         while(j>=0&&x<r[j])        /*在组中查找插入位置*/
         {
            r[j+d]=r[j];            /*记录后移*/
            j=j-d;                  /*记录位置前移一个步长*/
         }
         r[j+d]=x;                  /*插入记录*/
      }
      d=d/2;                        /*缩小步长值,取下一步长值*/
   }
}

int Partition(int r[],int s,int t)  /*一趟快速排序算法,将基准记录移到正确位置*/
                                    /*并返回其所在位置*/
{
   int i,j,rp;
   i=s;j=t;
   rp=r[s];                         /*基准记录暂存入rp*/
   while(i<j)                       /*从序列的两端交替向中间扫描*/
   {
      while(i<j&&r[j]>=rp)
         j--;                       /*扫描比基准记录小的位置*/
      r[i]=r[j];                    /*将比基准记录小的记录移到低端*/
      while(i<j&&r[i]<=rp)
         i++;                       /*扫描比基准记录大的位置*/
      r[j]=r[i];                    /*将比基准记录大的记录移到高端*/
   }
   r[i]=rp;                         /*基准记录到位*/
   return i;                        /*返回基准记录位置*/
}

void Qsort(int r[],int s,int t)     /*快速排序递归算法*/
{
   int k;
   if(s<t)                          /*长度大于1*/
   {
      k=Partition(r,s,t);           /*调用一趟快速排序算法将r[s]..r[t]一分为二*/
      Qsort(r,s,k-1);               /*对低端子序列递归排序,k是支点位置*/
      Qsort(r,k+1,t);               /*对高端子序列递归排序*/
   }
}

void selectsort(int r[],int length) /*简单选择排序函数*/
{
   int i,j,k,x;
   for(i=0;i<length-1;i++)          /*共进行length-1趟排序*/
   {
      k=i;                          /*初始化i趟排序的最小记录位置*/
      for(j=i+1;j<length;j++)       /*搜索关键字最小的记录位置*/
         if(r[k]>r[j])
            k=j;
      if(i!=k)                      /*交换r[i]与r[k]*/
      {
         x=r[i];
         r[i]=r[k];
         r[k]=x;
      }
   }
}

void print(int r[],int length)
{
   int i;
   for(i=0;i<length;i++)           /*输出排序后的序列*/
      printf("%d ",r[i]);
   printf("\n");
}

#define LENGTH 8                    /*定义符号常量*/

main()                              /*主程序*/
{
   int i,j;
   int r[LENGTH]={20,19,47,39,78,56,49,36}; /*定义数组并赋初值*/
   int r1[LENGTH];                          /*定义另一个长度为length的数组*/
   int x;
   printf("\n");
   printf("1---直接插入排序\n");            /*系统菜单*/
   printf("2---希尔排序\n");
   printf("3---快速排序\n");
   printf("4---简单选择排序\n");
   printf("0---退出\n");
   printf("输入你的选择(1,2,3,4,0) : ");
   while(1)
   {
      for(i=0;i<LENGTH;i++)                 /*数组r[]复制到数组r1[]*/
         r1[i]=r[i];
      scanf("%d",&x);                       /*输入菜单选项值*/
      if(x>=0&&x<=4)                        /*输入的值在0到4之间*/
      {
         /*printf("\n");*/
         switch(x)                          /*根据x值,调用不同的排序算法*/
         {
	    case 1:insertsort(r1,LENGTH);
		   printf("这是直接插入排序的结果 ：");
		   break;
	    case 2:shellsort(r1,LENGTH);
		   printf("这是希尔排序的结果 ：");
		   break;
	    case 3:Qsort(r1,0,LENGTH-1);
		   printf("这是快速排序的结果 ：");
		   break;
	    case 4:selectsort(r1,LENGTH);
		   printf("这是简单选择排序的结果 ：");
		   break;
	    case 0:printf("程序结束,退出!\n");
		   return;
         }
         /*printf("\n");*/
	 print(r1,LENGTH);                          /*输出排序后的序列*/
         printf("输入你的选择(1,2,3,4,0) : ");
      }
      else
      {
         printf("您的输入有误,请重新输入您的选择(1,2,3,4,0) : ");
         continue;
      }

   }
}
程序运行结果（通过修改数组r[]的8个数据,可实现对任意8个数据的排序。）：
1---直接插入排序
2---希尔排序
3---快速排序
4---简单选择排序
0---退出
输入你的选择(1,2,3,4,0) : 5（回车）
您的输入有误,请重新输入您的选择(1,2,3,4,0) : 1（回车）
这是直接插入排序的结果 ：19 20 36 39 47 49 56 78
输入你的选择(1,2,3,4,0) : 2（回车）
这是希尔排序的结果 ：19 20 36 39 47 49 56 78
输入你的选择(1,2,3,4,0) : 3（回车）
这是快速排序的结果 ：19 20 36 39 47 49 56 78
输入你的选择(1,2,3,4,0) : 4（回车）
这是简单选择排序的结果 ：19 20 36 39 47 49 56 78
输入你的选择(1,2,3,4,0) : 0（回车）
程序结束,退出!