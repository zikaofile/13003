/*将有序序列sr[s..m]和sr[m+1..t]归并为有序的tr[s..t]*/
void merge(int sr[],int tr[],int m,int s,int t) 
{
    int i,j,k;
    for(i=s,j=m+1,k=s;i<=m&&j<=t;++k)/*将sr中记录由小到大并入tr*/
       if(sr[i]<=sr[j])
          tr[k]=sr[i++];
       else 
          tr[k]=sr[j++];
    while(i<=m)
    {
        tr[k]=sr[i];i++;k++;     /*将剩余的sr[i..m]复制到tr*/
    }
    while(j<=t)
    {
        tr[k]=sr[j];j++;k++;     /*将剩余的sr[j..t]复制到tr*/
    }
}

2-路归并排序实现，其归并完整算法如程序8-10 所示：
程序8-10:

/*将有序序列sr[s..m]和sr[m+1..t]归并为有序的tr[s..t]*/
void merge(int sr[],int tr[],int m,int s,int t) 
{
    /*算法同前*/
}

/*本算法对r中若干个长度为l(最后一个可能小于l)的有序序列进行一趟2-路归并排序,结果存入a中*/
void mergepass(int r[],int a[],int n,int l)
{  
   int p,i;                 /*定义两个整型变量p,i*/
   p=1;                     /*p为每一个待合并的数组元素第一个下标,初值为1*/
   while(p+2*l-1<=n)        /*成对合并长度为l的子序列*/
   {
       merge(r,a,p+l-1,p,p+2*l-1);
       p=p+2*l;
   }
   if(p+l-1<n)              /*将剩余的长度为l和长度小于l的两个子序列合并*/
       merge(r,a,p+l-1,p,n);
   else
   {
       for(i=p;i<=n;i++)    /*将剩余的最后一个子序列复制到数组a中*/
           a[i]=r[i];
   }
   for(i=1;i<=n;i++)        /*将a[]返回r[],为下一趟归并排序做准备*/
       r[i]=a[i];
}

#define LENGTH 8   /*定义符号常量表示待排序序列长度*/
main()             /*主程序*/
{
   int i;
   int sr1[LENGTH+1],sr[LENGTH+1]={0,42,36,56,78,67,11,27,36};
                                     /*数组0号元素数值无意义*/
   int l;                            /*定义子序列长度变量l*/
   l=1;                              /*第一趟归并排序初值为1*/
   while(l<LENGTH)    /*子序列的长度小于记录总长度时进行归并*/
   {
      mergepass(sr,sr1,LENGTH,l);     /*调用一趟2-路归并排序算法*/
      l=2*l;                          /*长度加倍*/
   }
   printf("\n");
   for(i=1;i<=LENGTH;i++)             /*输出排序后的记录序列*/
      printf("%4d",sr1[i]);
}
程序运行结果：
11 27 36 36 42 56 67 78
