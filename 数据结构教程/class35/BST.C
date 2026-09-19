#include <alloc.h>

#define ERROR 0;
#define FALSE 0;
#define TRUE 1;
#define OK 1;


typedef int ElemType;
typedef int Status;
typedef int KeyType;

#define EQ(a,b)  ((a)==(b))
#define LT(a,b)  ((a)< (b))
#define LQ(a,b)  ((a)<=(b))

typedef struct BinaryTree

{
  ElemType data;
  struct BinaryTree *l;
  struct BinaryTree *r;
}*BiTree,BiNode;

BiNode * new()
{
  return( (BiNode *)malloc(sizeof(BiNode)) );
}

CreateSubTree(BiTree *T,ElemType *all,int i)
{
  if ((all[i]==0)||i>16)
    {
      *T=NULL;
      return OK;
    }
  *T=new();
  if(*T==NULL) return ERROR;
  (*T)->data=all[i];
  CreateSubTree(&((*T)->l),all,2*i);
  CreateSubTree(&((*T)->r),all,2*i+1);
}

CreateBiTree(BiTree *T)
{
  ElemType all[16]={0,1,2,3,0,0,4,5,0,0,0,0,6,0,0,0,};
  CreateSubTree(T,all,1);
}

printelem(ElemType d)
{
  printf("%d\n",d);
}

PreOrderTraverse(BiTree T,int (*Visit)(ElemType d))
{
  if(T){
    if(Visit(T->data))
      if(PreOrderTraverse(T->l,Visit))
	if(PreOrderTraverse(T->r,Visit)) return OK;
    return ERROR;
  } else  return OK;
}

InOrderTraverse(BiTree T,int (*Visit)(ElemType d))
{
  if(T){
    if(InOrderTraverse(T->l,Visit))
      if(Visit(T->data))
        if(InOrderTraverse(T->r,Visit)) return OK;
    return ERROR;
  }else return OK;
}

Status SearchBST(BiTree T,KeyType key,BiTree f,BiTree *p){

  if(!T) {*p=f;return FALSE;}
  else if EQ(key,T->data){ *p=T;return TRUE;}
  else if LT(key,T->data) SearchBST(T->l,key,T,p);
  else SearchBST(T->r,key,T,p);
}

Status InsertBST(BiTree *T,ElemType e){
  BiTree p;
  BiTree s;
  if(!SearchBST(*T,e,NULL,&p)){
    s=(BiTree)malloc(sizeof(BiNode));
    s->data=e;s->l=s->r=NULL;
    if(!p) *T=s;
    else if (LT(e,p->data)) p->l=s;
    else p->r=s;
    return TRUE;
  }
  else return FALSE;
}

void Delete(BiTree *p){
 BiTree q,s;
  if(!(*p)->r){
    q=(*p);
    (*p)=(*p)->l;
    free(q);
  }
  else if(!(*p)->l){
    q=(*p);
    (*p)=(*p)->r;
    free(q);
  }
  else {

/*    q=(*p);
    s=(*p)->l;
    while(s->r) {q=s; s=s->r;}
    (*p)->data=s->data;
    if(q!=(*p) ) q->r=s->l;
    else q->l=s->l;
    free(s);
    */

    q=s=(*p)->l;
    while(s->r) s=s->r;
    s->r=(*p)->r;
    free(*p);
    (*p)=q;

  }
}

Status DeleteBST(BiTree *T,KeyType key){
  if (!(*T) )
    {return FALSE;}
  else{
    if ( EQ(key,(*T)->data)) Delete(T);
    else if ( LT(key,(*T)->data)) DeleteBST( &((*T)->l), key);
    else DeleteBST( &((*T)->r),key);
    return TRUE;
  }
}


main()
{
  BiTree root;
  BiTree sroot=NULL;
  int i;
  int a[10]={45,23,12,3,33, 27,56,90,120,62};
  system("cls");
  CreateBiTree(&root);
  printf("PreOrderTraverse:\n");
  PreOrderTraverse(root,printelem);
  printf("InOrderTraverse:\n");
  InOrderTraverse(root,printelem);
  for(i=0;i<10;i++)
    InsertBST(&sroot,a[i]);
  printf("InOrderTraverse:\n");
  InOrderTraverse(sroot,printelem);
  for(i=0;i<3;i++)
  DeleteBST(&sroot,a[i]);
  printf("Now sroot has nodes:\n");
  InOrderTraverse(sroot,printelem);
}
