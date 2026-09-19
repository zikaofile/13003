//* * * * * * * * * * * * * * * * * * * * * * * *
//*CHAPTER          :3  (3_2)                   *
//*PROGRAM          :表达式求值                 *
//*CONTENT          :堆栈的应用                 *
//* * * * * * * * * * * * * * * * * * * * * * * *
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#define MAX 10       //定义堆栈最大容量
void push_opnd(char);//操作数堆栈入栈操作
float pop_opnd();    //操作数堆栈出栈操作
void push_optr(char);//操作符堆栈入栈操作
char pop_optr();     //操作符堆栈出栈操作
char relation(char,char);//比较两个操作符的优先级
float operate(float,char,float);//运算
float opnd[MAX];      //操作数堆栈
char optr[MAX];       //操作符堆栈
int topd=0;           //栈顶指针初始化
int top=0;
char symb[30];        //表达式字符串
void main()
{int i=0;
 char sy;
 float a,b;
// textbackground(3);   //设定屏幕颜色
// textcolor(15);
// clrscr();
 //---------------------程序解说-----------------------
 printf("本程序实现表达式求值的操作。可以进行加减乘除运算。\n");
 printf("这是堆栈应用的一个例子\n");
 //----------------------------------------------------
 printf("请输入表达式(以#结束):\n例如: 3*(3+2)/5#\n");
 push_optr('#');
 gets(symb);         //输入表达式，以#为结束符
 while((symb[i]!='#')||(optr[top]!='#'))
 {if((symb[i]!='+')&&(symb[i]!='-')&&(symb[i]!='*')&&(symb[i]!='/')
	 &&(symb[i]!='(')&&(symb[i]!=')')&&(symb[i]!='#')&&(symb[i]!=' '))
     {push_opnd(symb[i]);i++;}           //如果当前字符不是操作符，则入操作数栈，字符串指针加一
  else  switch(relation(optr[top],symb[i]))  //若是操作符，比较其和操作符栈的栈顶元素的优先级
	   {case '<':push_optr(symb[i]);i++;break;  //若栈顶元素优先级低，则当前字符入栈，指针加一
	    case '=':sy=pop_optr();i++; break;      //若优先级相等，必为两个配对的括号，退栈，指针加一
	    case '>':sy=pop_optr();b=pop_opnd();    //若优先级高，则栈顶元素退栈，进行运算
		     a=pop_opnd();
		     topd=topd+1;
		     opnd[topd]=operate(a,sy,b);     //把运算结果入栈
		     break;
	    case ' ':printf("语法错误!\n");exit(0);
	   }
  }
  printf("运算结果=%1.2f\n",opnd[topd]);
  printf("程序结束，按任意键退出!\n");
  getch();
}
void push_opnd(char ch)
{int ch_i;
 ch_i=ch-'0';   //把字符换算成数字，并入操作数栈
 topd++;
 opnd[topd]=ch_i;
}
float pop_opnd() 
{//操作数栈出栈
topd=topd-1;
 return opnd[topd+1];
}
void push_optr(char ch)
{//操作符入栈
 top++;
 optr[top]=ch;
}
char pop_optr()  
{//操作数出栈
 top--;
 return optr[top+1];
}
char relation(char sym1,char sym2)  
{//比较两个操作符的优先级
 int i;
 char chl[2];
 int ind[2];
 char re[7][7]={'>','>','<','<','<','>','>',
		'>','>','<','<','<','>','>',
		'>','>','>','>','<','>','>',
		'>','>','>','>','<','>','>',
		'<','<','<','<','<','=',' ',
		'>','>','>','>',' ','>','>',
		'<','<','<','<','<',' ','='};
 chl[0]=sym1;
 chl[1]=sym2;
 for(i=0;i<=1;i++)
    {switch(chl[i])
      {case '+':ind[i]=0;break;
       case '-':ind[i]=1;break;
       case '*':ind[i]=2;break;
       case '/':ind[i]=3;break;
       case '(':ind[i]=4;break;
       case ')':ind[i]=5;break;
       case '#':ind[i]=6;break;
       default:printf("Error!\n");return('0');
      }
    }
 return(re[ind[0]][ind[1]]);
}
float operate(float a,char sym,float b)  
{//进行运算
 float re;
 switch(sym)
    {case '+':re=a+b;break;
     case '-':re=a-b;break;
     case '*':re=a*b;break;
     case '/':re=a/b;break;
     default:printf("Error!\n");return(0);
    }
 return re;
}
