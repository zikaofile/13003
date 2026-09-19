#define MAXLEN 25              /*定义一常量MAXLEN为25*/
typedef struct string          /*定义串顺序存储结构*/
{  char ch[MAXLEN];
   int len;
}STRING;

STRING delete(s,i,j)                        /*删除子串运算*/
STRING s;
int i,j;
{
   int k;
   if((i<1)||(i>s.len))                     /*i值不在s串值范围之内,不能删除*/
   {   printf("error\n");
       return;
   }
   else
       if(s.len-i+1<j)                      /*第i个位置开始到最后的字符数不足j个时*/
	   s.len=i-1;                       /*只修改s串长度*/
       else                                 /*i和j都可以满足要求*/
       {
	   for(k=i+j-1;k<=s.len;k++)        /*元素向前移动j位*/
	       s.ch[k-j]=s.ch[k];
	   s.len=s.len-j;                   /*s串长度减j*/
	   return(s);
       }
}
main()                                      /*主程序*/
{
    STRING s={"Beijing Shanghai China",22}; /*定义串变量，给串变量赋初值*/
    int i=8,j=9;
    s=delete(s,i,j);                        /*调用delete()函数*/
    printf("\n%s\n%d",s.ch,s.len);          /*输出删除子串后串s值和长度*/
}
程序运行结果：
Beijing China
13