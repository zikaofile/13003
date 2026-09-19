#define MAXLEN 25              /*定义一常量MAXLEN为25*/
typedef struct string          /*定义串顺序存储结构*/
{
   char ch[MAXLEN];
   int len;
}STRING;

int match(s,s1)                /*子串定位函数*/
STRING s,s1;
{
   int i,j,k;
   i=0;
   while(i<=s.len-s1.len)      /*i为s串中字符的位置,每次前进一个位置,*/
   {                           /*该循环执行到s串中剩余长度不够比较时为止*/
      j=i;                     /*j用作临时计数变量*/
      k=0;                     /*用k控制比较的长度小于s1.len*/
      while((k<s1.len)&&(s.ch[j]==s1.ch[k]))      /*比较过程*/
      {
         j=j+1;
         k=k+1;
      }
      if(k==s1.len)        /*比较成功,返回位置(下标i+1)*/
         return(i+1);      /*i+1表示第几个位置,如下标(i=0)为0位置是第1个位置等*/
      else                 /*比较不成功,从s串中下一个字符继续比较*/
         i=i+1;
   }
   return(-1);             /*比较结束时,未找到匹配字符串,返回标识-1*/
}

STRING delete(s,i,j)                /*删除子串函数*/
STRING s;
int i,j;
{
   int k;
   if((i<1)||(i>s.len))             /*i值不在s串值范围之内,不能删除*/
   {
      printf("error\n");
      return;
   }
   else
      if(s.len-i+1<j)               /*第i个位置开始到最后的字符数不足j个时*/
       	 s.len=i-1;                 /*只修改s串长度*/
      else                          /*i和j都可以满足要求*/
      {
         for(k=i+j-1;k<=s.len;k++)  /*元素向前移动j位*/
	    s.ch[k-j]=s.ch[k];
	 s.len=s.len-j;             /*s串长度减j*/
	 return(s);
      }
}

STRING insert(s,s1,i)          /*插入子串函数*/
STRING s,s1;
int i;
{
   int j;
   if(s.len+s1.len>=MAXLEN||(i>s.len+1)||(i<1))
   {                           /*如果长度不够或起始位置不合理,输出溢出信息*/
      printf("overflow\n");
      return;
   }
   else
   {   
      for(j=s.len;j>=i;j--)
         s.ch[j+s1.len-1]=s.ch[j-1];  /*s串最后一个到第i个位置的元素后移*/
      for(j=0;j<s1.len;j++)
	 s.ch[j+i-1]=s1.ch[j];        /*插入s1串到s串指定位置*/
      s.len=s.len+s1.len;             /*s串长度增加*/
      s.ch[s.len]='\0';               /*设置字符串结尾标志*/
      return(s);                      /*返回s*/
   }
}

STRING replace(s,s1,s2)        /*串置换函数*/
STRING s,s1,s2;
{
   int k;
   k=match(s,s1);
   if(k!=-1)
   {
      s=delete(s,k,s1.len);  /*调用删除函数,在s串中从第k+1个字符开始删除,*/
	                       /*共删除s1.len个字符*/
      s=insert(s,s2,k);      /*调用插入函数,在s串中,从第k+1个位置开始插入s2子串*/
   }
   else
      printf("not exist.");
   return(s);
}

main()                                  /*主程序*/
{
   STRING a={"Beijing Shanghai China",22}; /*定义结构变量,给结构变量赋初值*/
   STRING a1={"Shanghai",8};
   STRING a2={"Dalian",6};
   STRING s;
   int i;
   s=replace(a,a1,a2);                 /*调用置换函数*/
   printf("\n");
   for(i=0;i<s.len;i++)                /*输出结果*/
      printf("%c",s.ch[i]);
   printf("\n%d",s.len);
}
程序运行结果：
Beijing Dalian China
20