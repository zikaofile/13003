void heapadjust(int r[],int s,int m)/*把r[s],..,r[m]建立成大顶堆的算法*/
{
   int rc,j;                      /*rc暂存记录的关键字*/
   rc=r[s];                       /*记录关键字送rc*/
   for(j=2*s;j<=m;j*=2)           /*沿关键字较大的孩子结点向下搜索调整*/
   {
       if((j<m)&&(r[j]<=r[j+1]))
          ++j;                    /*若右孩子大于左孩子,则j为右孩子的下标*/
       if(rc>r[j]) 
          break;                  /*将r[j]调到父结点的位置*/
       r[s]=r[j];
       s=j;
   } 
   r[s]=rc;                       /*将rc插入到最终位置*/
}

#define LENGTH 9                  /*符号常量表示数组长度*/
main()
{
   int r[LENGTH]={0,42,36,56,78,67,11,27,36}; /*给数组赋值,r[0]无意义*/
   int i,x;
   for(i=(LENGTH-1)/2;i>0;--i)             /*将待排序序列调整为大顶堆*/
      heapadjust(r,i,LENGTH);              /*调用建堆算法函数*/
   for(i=LENGTH-1;i>1;--i)   /*排序(重复进行记录交换和堆调整)*/
   {
      x=r[1];                /*将堆顶记录与当前未经排序子序列r[1..i]中*/
      r[1]=r[i];             /*最后一个记录相互交换*/
      r[i]=x;         
      heapadjust(r,1,i-1);   /*调用建堆算法将r[1..i-1]重新调整为大顶堆*/
   }
   for(i=1;i<LENGTH;i++)     /*输出排序后的记录序列*/
      printf("%d ",r[i]);
   printf("\n");
}
程序运行结果：
11 27 36 36 42 56 67 78
