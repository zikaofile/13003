main()
{
   int i,j,first,final;
   int r[8]={42,36,56,78,67,11,27,36};   /*定义数组并初始化*/
   int d[8];                             /*建立辅助数组*/
   d[0]=r[0];
   first=final=0;                        /*初始化首尾指针*/
   for(i=1;i<8;i++)                      /*r[1]是有序的,从r[2]开始排序*/
   {
      if(r[i]>=d[0])                     /*真,r[i]插到d[0]之后的有序序列*/
      {
         for(j=final;r[i]<d[j];j--)      /*寻找r[i]应插入的位置*/
            d[j+1]=d[j];                 /*后移元素*/
         d[j+1]=r[i];                    /*将r[i]插到正确位置*/
         final++;                        /*指针后移一位*/
      }
      else                               /*假,r[i]插到d[0]之前的有序序列*/
      {
         if(first==0)                    /*若指针first在初始位置*/
         {
            first=7;                     /*使指针first指向数组尾部*/
            d[first]=r[i];               /*将r[i]插到first位置*/
         }
         else
         {
            for(j=first;r[i]>d[j]&&j<8;j++)   /*寻找r[i]的插入位置*/
               d[j-1]=d[j];                   /*向前移动元素*/
            d[j-1]=r[i];                      /*将r[i]插到正确位置*/
            first--;                          /*指针前移一位*/
         }
      }
   }
   if(first<final)             /*若first所指位置在final所指位置之前*/
      for(i=first;i<final;i++) /*从first所指位置到final所指位置依次输出*/
         printf("%d ",d[i]);
   else                        /*若first所指位置在final所指位置之后*/
   {
      for(i=first;i<8;i++)     /*先从first所指位置到数组尾部依次输出前半个序列*/
         printf("%d ",d[i]);
      for(i=0;i<=final;i++)    /*再从数组开头到final所指位置依次输出后半个序列*/
	 printf("%d ",d[i]);
   }
   printf("\n");
}
程序运行结果：
11 27 36 36 42 56 67 78
