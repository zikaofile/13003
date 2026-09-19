#define MAXLEN 13                  /*定义一常量MAXLEN为13*/
typedef struct string              /*定义串顺序存储结构*/
{  char ch[MAXLEN];
   int len; 
}STRING;

STRING substring(s,n1,n2)          /*取子串运算*/
STRING s;
int n1,n2;
{
    STRING sub;
    int i;
    if((n1>=1)&&(n1<=s.len)&&(n2>=1)&&(n2<=s.len-n1+1))
    {                                  /*如果长度和起始位置合理*/
	 for(i=0;i<n2;i++)
	     sub.ch[i]=s.ch[n1+i-1];
         sub.ch[i]='\0';               /*设置字符串结尾标志*/
         sub.len=n2;
    }
    else                               /*如果长度和起始位置不合理*/
    {
         sub.ch[0]='\0';               /*设置字符串结尾标志*/
         sub.len=0;
    }
    return(sub);                       /*如果取子串成功,返回子串;不成功,则返回空串*/
}
main()
{
    STRING a1={"Beijing China",13},s;  /*定义串变量，给串变量赋初值*/
    s=substring(a1,1,7);               /*调用substring()函数*/
    printf("\n%s",s.ch);               /*输出结果*/
    s=substring(a1,14,1);
    printf("\n%s",s.ch);
    s=substring(a1,9,5);
    printf("\n%s",s.ch);
}
程序运行结果：
Beijing
                                       /*运行结果的中间行无内容,表示输出空串*/
China