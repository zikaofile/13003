#include <stdio.h>

typedef int KeyType;
typedef struct{
  KeyType key;
  int maths;
  int english;
}ElemType;
#define EQ(a,b)  ((a)==(b))
#define LT(a,b)  ((a)< (b))
#define LQ(a,b)  ((a)<=(b))

typedef struct {
  ElemType *elem;
  int length;
}SSTable;

int Search_Seq(SSTable ST,KeyType key)
{
  int i;
  ST.elem[0].key=key;
  for(i=ST.length; !EQ(ST.elem[i].key,key); --i);
  return i;
}

int Search_Bin(SSTable ST,KeyType key)
{
  int low,mid,high;
  low=1;high=ST.length;
  while(low<=high){
    mid=(low+high)/2;
    if EQ(key,ST.elem[mid].key) return mid;
    else if LT(key,ST.elem[mid].key) high=mid -1;
    else  low=mid +1;
  }
}

getdata(SSTable * t)
{
  FILE *fp;
  int i=1;
  fp=fopen("stu.txt","r");
  fscanf(fp,"%d",&(t->length));
  while(i<=t->length)
    {
      fscanf(fp,"%d %d %d",&(t->elem[i].key),
		 &(t->elem[i].maths),&(t->elem[i].english)  );
      i++;
    }
  fclose(fp);
}

main()
{
  ElemType stu[50];
  SSTable  class;
  int i,j,k;
  long time;
  class.elem=stu;


  getdata(&class);

  printf("This class has %d students.\n",class.length);
  printf("Input stuno you want search:\n");
  scanf("%d",&k);

  i=Search_Seq(class,k);
  j=Search_Bin(class,k);
  printf("Maths   English\n");
  printf("%d       %d\n",class.elem[i].maths,class.elem[i].english);
  printf("%d       %d\n",class.elem[j].maths,class.elem[j].english);

  for(i=1;i<=4;i++)
    {j=stu[i].maths+stu[i].english;
      printf("%d\n",j);
    }

}
