#include<stdio.h>
#define M 11                       /*散列表表长*/
#define N 8                        /*待散列的关键字表表长*/
struct hterm                       /*定义散列表元素*/
{
   int key;                        /*关键字域*/
   int si;                         /*比较次数*/
};
struct hterm hashlist[M];          /*散列表*/
int x[N]={22,41,53,46,30,13,1,67}; /*待散列的关键字*/
int i,address,sum,d;
float average;

main()       /*主程序,功能为用散列法存储数据,开放地址法处理冲突*/
{
   for(i=0;i<N;i++)
   {
      hashlist[i].key=0;           /*为关键字域和比较次数赋初值*/
      hashlist[i].si=0;
   }
   for(i=0;i<N;i++) 
   {
      sum=0;
      address=(3*x[i])%M;                 /*求散列地址*/
      d=address;
      if(hashlist[address].key==0)        /*如果是开放地址*/
      {
         hashlist[address].key=x[i];      /*存入该关键字*/
         hashlist[address].si=1;          /*存入比较次数*/
      }
      else 
      {
         do
         {
            d=(d+(x[i]*7))%11;            /*冲突后再求散列地址*/ 
            sum=sum+1;                    /*冲突次数累加*/
            address=d; 
         }
         while(hashlist[address].key!=0);
         hashlist[address].key=x[i];      /*存入关键字*/
         hashlist[address].si=sum+1;      /*存入冲突次数*/
      }
   }
   printf("\n散列地址:    ");
   for(i=0;i<M;i++)
      printf("%3d",i);                    /*输出散列地址*/
   printf("\n");
   printf("散列的关键字:");
   for(i=0;i<M;i++)
      printf("%3d",hashlist[i].key);      /*输出散列的关键字*/
   printf("\n");
   printf("查找长度:    ");
   for(i=0;i<M;i++)
      printf("%3d",hashlist[i].si);       /*输出查找长度*/
   printf("\n");
   average=0;
   for(i=0;i<M;i++)
      average=average+hashlist[i].si;
   average=average/N;
   printf("平均查找长度: ASL(%d)=%4.3f",N,average);  /*输出平均查找长度*/
} 
程序运行结果：
散列地址:      0   1   2   3   4   5   6   7   8   9  10
散列的关键字: 22  67  41  30   0  53  46   0   0  13   1 
查找长度:      1   7   1   2   0   1   1   0   0   2   2
平均查找长度: ASL(8)=2.125 