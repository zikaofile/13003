#define MAXLEN 25              /*定义一常量MAXLEN为25*/
typedef struct string          /*定义串顺序存储结构*/
{  
   char ch[MAXLEN];
   int len;
}STRING;

int match(s,s1)                /*子串定位运算*/
STRING s,s1;
{
   int i,j,k; 
   i=0;
   while(i<=s.len-s1.len)      /*i为s串中字符的位置，每次前进一个位置，*/
   {                           /*该循环执行到s串中剩余长度不够比较时为止*/
       j=i;                    /*j用作临时计数变量*/
       k=0;                    /*用k控制比较的长度小于s1.len*/
       while((k<s1.len)&&(s.ch[j]==s1.ch[k]))      /*比较过程*/      
       { 
           j=j+1;
           k=k+1;
       }
       if(k==s1.len)           /*比较成功，返回i的位置*/
           return(i);
       else                    /*比较不成功，从s串中下一个字符继续比较*/
           i=i+1;
   }
   return(-1);                 /*比较结束时，未找到匹配字符串，返回标识-1*/
}

main()                         /*主程序*/
{
    STRING a={"Beijing Shanghai China",22}; /*定义串变量，给串变量赋初值*/
    STRING a1={"Shanghai",8};
    int r;
    r=match(a,a1);                          /*调用match函数*/  
    printf("\n%d",r);                       /*输出结果*/
}
程序运行结果：
8
