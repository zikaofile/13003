#define LENGTH 8
main() 
{
   int r[LENGTH+1]={0,45,38,63,85,71,28,45,16}; /*定义数组并赋初值,r[0]作暂存单元*/
   int i,j,k;
   for(i=1;i<LENGTH;i++)            /*做第i趟排序*/ 
   {
      k=i;                          /*初始化第i趟排序的最小记录位置*/
      for(j=i+1;j<=LENGTH;j++)      /*搜索关键字最小的记录位置*/
         if(r[k]>r[j])
            k=j;                    /*保存当前关键字最小的记录位置*/
      if(i!=k)                      /*交换r[i]与r[k]*/
      {
         r[0]=r[i];
         r[i]=r[k];
         r[k]=r[0];
      }
   }
   for(i=1;i<=LENGTH;i++)           /*输出排序后的序列*/
      printf("%d ",r[i]);
}
程序运行结果：
16 28 38 45 45 63 71 85
