//* * * * * * * * * * * * * * * * * * * * * * * *
//*CHAPTER          :4  (4_4)                   *
//*PROGRAM          :哈夫曼树                   *
//*CONTENT          :构造哈夫曼树,哈夫曼编码    *
//* * * * * * * * * * * * * * * * * * * * * * * *
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{unsigned int weight;  //结点权值
 unsigned int parent,lchild,rchild; //结点的父指针，左右孩子指针
}HTNode,*HuffmanTree;       //动态分配数组存储哈夫曼树
typedef char **HuffmanCode; //动态分配数组存储哈夫曼编码表
void CreateHuffmanTree(HuffmanTree &,unsigned int*,int ); //生成一棵哈夫曼树
void HuffmanCoding(HuffmanTree,HuffmanCode &,int );       //对哈夫曼树进行编码
void PrintHuffmanCode(HuffmanCode,unsigned int*,int);     //显示哈夫曼编码
void Select(HuffmanTree,int,int&,int&); //在数组中寻找权值最小的两个结点
void main()
{HuffmanTree HT;  //哈夫曼树HT
 HuffmanCode HC;  //哈夫曼编码表HC
 int n,i;         //n是哈夫曼树叶子结点数
 unsigned int *w; //w存放叶子结点权值   
 char j='y';
 textbackground(3);  //设定屏幕颜色
 textcolor(15);
 clrscr();
 //程序解说
 printf("本程序将演示构造哈夫曼树.\n");
 printf("首先输入叶子结点数目.\n例如:8\n");
 printf("然后输入每个叶子结点的权值.\n");
 printf("例如:5 29 7 8 14 23 3 11\n");
 printf("程序会构造一棵哈夫曼树并显示哈夫曼编码.\n");
 printf("  5---0110\n 29---10\n  7---1110\n  8---1111\n 14---110\n");
 printf(" 23---00\n  3---0111\n 11---010\n");
 while(j!='N'&&j!='n')
      {printf("请输入叶子结点数目:");
       scanf("%d",&n);   //输入叶子结点数
       if(n<=1) {printf("该数不合理!\n");continue;}
       w=(unsigned int*)malloc(n*sizeof(unsigned int)); //开辟空间存放权值
       printf("请输入各叶子结点的权值:\n");
       for(i=0;i<n;i++) scanf("%d",&w[i]);   //输入各叶子结点权值
       CreateHuffmanTree(HT,w,n);       //生成哈夫曼树
       HuffmanCoding(HT,HC,n);          //进行哈夫曼编码
       PrintHuffmanCode(HC,w,n);        //显示哈夫曼编码
       printf("哈夫曼树构造完毕，还要继续吗?(Y/N)");
       scanf(" %c",&j);
     }
}

void CreateHuffmanTree(HuffmanTree &HT,unsigned int *w,int n)
{//w存放n个结点的权值，将构造一棵哈夫曼树HT
 int i,m;
 int s1,s2;
 HuffmanTree p;
 if(n<=1) return;
 m=2*n-1;  //n个叶子结点的哈夫曼树，有2*n-1个结点
 HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode)); //开辟2*n各结点空间，0号单元不用
 for(p=HT+1,i=1;i<=n;++i,++p,++w) //进行初始化
       {p->weight=*w;
	p->parent=0;
	p->lchild=0;
	p->rchild=0;
       }
 for(;i<=m;++i,++p)
       {p->weight=0;
	p->parent=0;
	p->lchild=0;
	p->rchild=0;
       }
 for(i=n+1;i<=m;++i)  //建哈夫曼树
    {Select(HT,i-1,s1,s2);  
        //从HT[1...i-1]中选择parent为0且weight最小的两个结点，其序号分别为s1和s2
     HT[s1].parent=i; HT[s2].parent=i; //修改s1和s2结点的父指针parent
     HT[i].lchild=s1; HT[i].rchild=s2; //修改i结点的左右孩子指针
     HT[i].weight=HT[s1].weight+HT[s2].weight; //修改权值
    }
}
void HuffmanCoding(HuffmanTree HT,HuffmanCode &HC,int n)
{//将有n个叶子结点的哈夫曼树HT进行编码， 所编的码存放在HC中
 //方法是从叶子到根逆向求每个叶子结点的哈夫曼编码
 int i,c,f,start;
 char *cd;
 HC=(HuffmanCode)malloc((n+1)*sizeof(char *)); //分配n个编码的头指针向量
 cd=(char *)malloc(n*sizeof(char));  //开辟一个求编码的工作空间
 cd[n-1]='\0';           //编码结束符
 for(i=1;i<=n;++i)       //逐个地求哈夫曼编码
    {start=n-1;          //编码结束位置
     for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent) //从叶子到根逆向求编码
	if(HT[f].lchild==c)  cd[--start]='0';        //若是左孩子编为'0'
	else cd[--start]='1';                        //若是右孩子编为'1' 
     HC[i]=(char *)malloc((n-start)*sizeof(char));   //为第i个编码分配空间
     strcpy(HC[i],&cd[start]);         //将编码从cd复制到HC中
    }
 free(cd); //释放工作空间
}
void PrintHuffmanCode(HuffmanCode HC,unsigned int *w,int n)
{//显示有n个叶子结点的哈夫曼树的编码表
 int i;
 printf("HuffmanCode is :\n");
 for(i=1;i<=n;i++)
   {printf(" %3d---",w[i-1]);
    puts(HC[i]);
   }
 printf("\n");
}
void Select(HuffmanTree HT,int t,int&s1,int&s2)
{//在HT[1...t]中选择parent不为0且权值最小的两个结点，其序号分别为s1和s2 
 int i,m,n;
 m=n=10000;  
 for(i=1;i<=t;i++)
   {if(HT[i].parent==0&&(HT[i].weight<m||HT[i].weight<n))
	if(m<n)
	    {n=HT[i].weight;s2=i;}
	else {m=HT[i].weight;s1=i;}

   }
 if(s1>s2)  //s1放较小的序号
      {i=s1;s1=s2;s2=i;}
}