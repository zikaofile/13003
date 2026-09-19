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

#define LENGTH 8                    /*定义符号常量,表示数组长度*/
main()                              /*主程序*/
{ 
   int i;
   int r[LENGTH]={42,36,56,78,67,11,27,36};  /*定义原始待排序序列*/
   Qsort(r,0,LENGTH-1);                      /*调用快速排序算法*/
   for(i=0;i<LENGTH;i++)
      printf("%d ",r[i]);                    /*输出排序后的有序序列*/
}
程序运行结果：
11 27 36 36 42 56 67 78
