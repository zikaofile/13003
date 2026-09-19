//* * * * * * * * * * * * * * * * * * * * * * *
//CHAPTER      :2 (2-1)                       *
//PROGRAM NAME :顺序结构的线性表              *
//CONTENT      :插入,删除,查找                *
//* * * * * * * * * * * * * * * * * * * * * * *
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#define MAX 30    //定义线性表的最大长度
enum BOOL{False,True};  //定义BOOL型
typedef struct{
   char elem[MAX];       //线性表
   int last;             //last指示当前线性表的长度
}sqlisttp;               
void initial(sqlisttp &);    //初始化线性表
BOOL insert(sqlisttp &,int,char); //在线性表中插入元素
BOOL del(sqlisttp&,int,char &);   //在线性表中删除元素
int locate(sqlisttp,char);        //在线性表中定位元素
void print(sqlisttp);             //显示线性表中所有元素
void main()
{sqlisttp S;      //S为一线性表
 int loc,flag=1;
 char j,ch;
 BOOL temp;
 textbackground(3);  //设置屏幕颜色
 textcolor(15);
 clrscr();
 //---------------------------程序解说--------------------------
 printf("本程序用来实现顺序结构的线性表。\n");
 printf("可以实现查找、插入、删除等操作。\n");
 //-------------------------------------------------------------
 initial(S);         //初始化线性表
 while(flag)
    { printf("请选择:\n");
      printf("1.显示所有元素\n");
      printf("2.插入一个元素\n");
      printf("3.删除一个元素\n");
      printf("4.查找一个元素\n");
      printf("5.退出程序    \n");
      scanf(" %c",&j);
      switch(j)
	{case '1':print(S); break; //显示所有元素
	 case '2':{printf("请输入要插入的元素(一个字符)和插入位置:\n");
		   printf("格式：字符，位置；例如:a,2\n");
		   scanf(" %c,%d",&ch,&loc);  //输入要插入的元素和插入的位置
		   temp=insert(S,loc,ch);     //插入
		   if(temp==False)  printf("插入失败!\n");  //插入失败
                   else  {printf("插入成功!\n");   print(S);} //插入成功
		   break;
		  }
	 case '3':{printf("请输入要删除元素的位置:");
		   scanf("%d",&loc);    //输入要删除的元素的位置
		   temp=del(S,loc,ch);  //删除
		   if(temp==True) printf("删除了一个元素:%c\n",ch); //删除成功
		   else printf("该元素不存在!\n");  //删除失败
		   print(S);
		   break;
		  }
	 case '4':{printf("请输入要查找的元素:");
		   scanf(" %c",&ch);      //输入要查找的元素
		   loc=locate(S,ch);      //定位
		   if(loc!=-1) printf("该元素所在位置:%d\n",loc+1); //显示该元素位置
		   else    printf("%c 不存在!\n",ch);//当前元素不存在
		   break;
		  }
	 default:flag=0;printf("程序结束，按任意键退出!\n");
	}
    }
 getch();
}
void initial(sqlisttp &v)
{//初始化线性表
 int i;
 printf("请输入初始线性表长度：n="); //输入线性表初始化时的长度
 scanf("%d",&v.last);
 printf("请输入从1到%d的各元素(字符)，例如:abcdefg\n",v.last);
 getchar();
 for(i=0;i<v.last;i++) scanf("%c",&v.elem[i]); //输入线性表的各元素
}

BOOL insert(sqlisttp &v,int loc,char ch)        
{//插入一个元素，成功返回True，失败返回False
 int i;
 if((loc<1)||(loc>v.last+1))
   {printf("插入位置不合理!\n");  //位置不合理
    return False;
   }
 else if(v.last>=MAX)         //线性表已满
     {printf("线性表已满!\n");
      return False;
     }
 else {for(i=v.last-1;i>=loc-1;i--) v.elem[i+1]=v.elem[i];//其后元素依次后移
       v.elem[loc-1]=ch;     //插入元素
       v.last++;                      //线性表长度加一
       return True;
     }
}

BOOL del(sqlisttp &v,int loc,char &ch)           
{//删除一个元素，成功返回True，并用ch返回该元素值，失败返回False
 int j;
 if(loc<1||loc>v.last)    //删除位置不合理
    return False;
 else {ch=v.elem[loc-1];  //ch取得该元素值
       for(j=loc-1;j<v.last-1;j++) v.elem[j]=v.elem[j+1];   //其后元素依次前移
       v.last--;       //线性表长度减一
       return True;
      }
}

int locate(sqlisttp v,char ch)
{//在线性表中查找ch的位置，成功返回其位置，失败返回-1
 int i=0;
 while(i<v.last&&v.elem[i]!=ch) i++;  //当前位置后移，直到找到为止
 if(v.elem[i]==ch)               //找到当前元素
    return i;
 else  return(-1);
}
void print(sqlisttp v)          //显示当前线性表所有元素
{int i;
 for(i=0;i<v.last;i++) printf("%c ",v.elem[i]);
 printf("\n");
}

