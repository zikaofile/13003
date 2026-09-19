#define  LENGTH  8    /*符号常量LENGTH表示数组长度*/
main()
{
   int r[LENGTH]={42,36,56,78,67,11,27,36};  /*定义数组并赋初值*/
   int i,j,temp,mark;          /*mark某趟排序是否进行过交换标志*/ 
   for(i=1;i<=LENGTH-1;i++)    /*控制共进行LENGTH-1趟排序*/
   {
      mark=0;                  /*每趟排序前mark置0*/
      for(j=0;j<LENGTH-i;j++)  /*进行第i趟排序*/
         if(r[j]>r[j+1])       /*判断相邻两记录是否逆序*/
         {
            temp=r[j];
            r[j]=r[j+1];
            r[j+1]=temp;       /*如逆序,交换两记录*/
            mark=1;            /*交换发生,mark置1*/
         }
      if(mark==0)
         break;                /*本趟排序无交换,整个排序结束*/
   }
   for(i=0;i<LENGTH;i++)
      printf("%d ",r[i]);      /*输出排序后的序列*/
   printf("\n");
}
程序运行结果：
11 27 36 36 42 56 67 78
 
