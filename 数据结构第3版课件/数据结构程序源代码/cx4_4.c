#define MAXLEN 25              /*定义一常量MAXLEN为25*/
typedef struct string          /*定义串顺序存储结构*/
{  char ch[MAXLEN];
   int len;
}STRING;

STRING insert(s,s1,i)          /*插入子串运算*/
STRING s,s1;
int i;
{
     int j;
     if(s.len+s1.len>=MAXLEN||(i>s.len+1)||(i<1))
     {                                        /*如果长度不够或起始位置不合理，输出溢出信息*/
         printf("overflow\n");
         return;
     }
     else
     {   for(j=s.len;j>=i;j--)
	     s.ch[j+s1.len-1]=s.ch[j-1];      /*s串最后一个到第i个位置的元素后移*/
         for(j=0;j<s1.len;j++)
	     s.ch[j+i-1]=s1.ch[j];            /*插入s1串到s串指定位置*/
         s.len=s.len+s1.len;                  /*s串长度增加*/
         s.ch[s.len]='\0';                    /*设置字符串结尾标志*/
         return(s);                           /*返回s*/
     }
}

main()                                        /*主程序*/
{
     STRING a={"Beijing China",13};           /*定义串变量，给串变量赋初值*/
     STRING a1={" Shanghai",9},s;
     int i=8;
     s=insert(a,a1,i);                        /*调用insert函数*/
     for(i=0;i<s.len;i++)
         printf("%c",s.ch[i]);                /*输出插入后串s*/
     printf("\n%d\n",s.len);                  /*输出插入后串s长度*/
}
程序运行结果：
Beijing Shanghai China
22