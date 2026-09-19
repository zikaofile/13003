//* * * * * * * * * * * * * * * * * * * * * * * *
//*CHAPTER          :6  (6_5)                   *
//*PROGRAM          :Æ½ºâ¶ş²æÅÅĞòÊ÷µÄ×ÛºÏ²Ù×÷   *
//*CONTENT          :Insert,Search              *
//* * * * * * * * * * * * * * * * * * * * * * * *
#include <dos.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define LH 1   //×ó×ÓÊ÷¸ß
#define EH 0   //×óÓÒ×ÓÊ÷µÈ¸ß
#define RH -1  //ÓÒ×ÓÊ÷¸ß
enum BOOL{False,True};
typedef struct //¶¨Òå¼ÇÂ¼µÄ½á¹¹
{int keynum;   //ÔÚ±¾³ÌĞòÖĞÖ»º¬ÓĞ¹Ø¼ü×ÖÒ»Ïî
}Record;
typedef struct  BSTNode   //¶¨ÒåÆ½ºâ¶ş²æÊ÷½Úµã½á¹¹
{Record  data;		  //Êı¾İÓò
 int bf;                  //Æ½ºâÒò×Ó
 struct BSTNode *lchild,*rchild; //×óÓÒº¢×ÓÖ¸ÕëÓò
}BSTNode,*BSTree;
BSTree SearchBST(BSTree,int); //ÔÚÆ½ºâ¶ş²æÅÅĞòÊ÷ÖĞ²éÕÒÔªËØ
BOOL InsertAVL(BSTree &,Record,BOOL&);  //ÔÚÆ½ºâ¶ş²æÅÅĞòÊ÷ÖĞ²åÈëÔªËØ
void LeftBalance(BSTree &);    //×óÆ½ºâĞı×ª´¦Àí
void RightBalance(BSTree &);   //ÓÒÆ½ºâĞı×ª´¦Àí
void InorderBST(BSTree); //ÖĞĞò±éÀú¶ş²æÅÅĞòÊ÷£¬¼´´ÓĞ¡µ½´óÏÔÊ¾¸÷ÔªËØ
void R_Rotate(BSTree &); //ÓÒĞı´¦Àí
void L_Rotate(BSTree &); //×óĞı´¦Àí
void main()
{BSTree T,p;
 Record R;
 char ch,keyword,j='y';
 BOOL temp,taller;
 textbackground(3);  //Éè¶¨ÆÁÄ»ÑÕÉ«
 textcolor(15);
 clrscr();
 //-------------------------³ÌĞòËµÃ÷-------------------------------
 printf("This program will show how to operate to \na Balanced Binary Sort  Tree.\n");
 printf("You can display all elems,search a elem,insert a elem.\n");
 //----------------------------------------------------------------
 T=NULL;
 while(j!='n')
    {printf("1.display\n");
     printf("2.search\n");
     printf("3.insert\n");
     printf("4.exit\n");
     scanf(" %c",&ch); //ÊäÈë²Ù×÷Ñ¡Ïî
     switch(ch)
      {case '1':if(!T) printf("The BST has no elem.\n"); //´ËÊ±Æ½ºâ¶ş²æÅÅĞòÊ÷¿Õ
		else {InorderBST(T);printf("\n");} //ÖĞĞò±éÀú¶ş²æÊ÷£¬¼´´ÓĞ¡µ½´óÏÔÊ¾ËùÓĞÔªËØ
		break;
       case '2':printf("Input the keynumber of elem to be searched(int number):");
		scanf("%d",&R.keynum); //ÊäÈëÒª²éÕÒÔªËØµÄ¹Ø¼ü×Ö
		p=SearchBST(T,R.keynum);
                  //p=NULL:²éÕÒ²»³É¹¦£»p!=NULL:²éÕÒ³É¹¦£¬pÖ¸Ïò¸Ã¼ÇÂ¼
		if(!p) printf("The record isn't existed!\n"); //Ã»ÓĞÕÒµ½
		else printf("The record has been found!\n"); //³É¹¦ÕÒµ½
		break;
       case '3':printf("Input the record to be inserted(int number):");
		scanf("%d",&R.keynum); //ÊäÈëÒª²åÈëÔªËØµÄ¹Ø¼ü×Ö
		temp=InsertAVL(T,R,taller);
	         //temp=True:³É¹¦²åÈë¸Ã¼ÇÂ¼;temp=False:Ê÷ÖĞÒÑÓĞÓë¼ÇÂ¼RÓĞÏàÍ¬¹Ø¼ü×ÖµÄ¼ÇÂ¼
                if(!temp) printf("The record has been existed!\n"); //¸ÃÔªËØÒÑ¾­´æÔÚ
		else printf("Sucess to insert!\n"); //³É¹¦²åÈë
		break;
       default: j='n';
    }
 }
 printf("The program is over!\nPress any key to shut off the window!\n");
 getchar();getchar();
}
void InorderBST(BSTree T)
{//ÒÔÖĞĞò·½Ê½±éÀú¶ş²æÅÅĞòÊ÷T£¬¼´´ÓĞ¡µ½´óÏÔÊ¾¶ş²æÅÅĞòÊ÷µÄËùÓĞÔªËØ
 if(T->lchild) InorderBST(T->lchild);
 printf("%-4d",T->data.keynum);
 if(T->rchild) InorderBST(T->rchild);
}

BSTree SearchBST(BSTree T,int key)
{//ÔÚ¸ùÖ¸ÕëTËùÖ¸¶ş²æÅÅĞòÊ÷ÖĞµİ¹éµÄ²éÕÒÆä¹Ø¼ü×ÖµÈÓÚkeyµÄÔªËØ£¬Èô²éÕÒ³É¹¦
 //Ôò·µ»Ø¸ÃÔªËØµÄµØÖ·£¬Èô²éÕÒ²»³É¹¦£¬·µ»ØµØÖ·ÎªNULL
 if((!T)||key==T->data.keynum) return (T);
 else if(key<T->data.keynum) return(SearchBST(T->lchild,key));
 else return(SearchBST(T->rchild,key));
}

BOOL InsertAVL(BSTree &T,Record e,BOOL &taller)
{//ÈôÔÚÆ½ºâ¶ş²æÅÅĞòÊ÷TÖĞÖĞ²»´æÔÚºÍeÓĞÏàÍ¬¹Ø¼ü×ÖµÄ½áµã£¬Ôò²åÈëÒ»¸öÊı¾İÔªËØ
 //ÎªeµÄĞÂ½áµã£¬²¢·µ»ØTrue£¬·ñÔò·µ»ØFalse¡£ÈôÒò²åÈë¶øÊ¹Æ½ºâ¶ş²æÅÅĞòÊ÷Ê§È¥
 //Æ½ºâ£¬Ôò×öÆ½ºâĞı×ª´¦Àí£¬²¼¶û±äÁ¿taller·´Ó³T³¤¸ßÓë·ñ
 if(!T)      //²åÈëĞÂ½áµã£¬Ê÷¡°³¤¸ß¡±£¬ÖÃtallerÎªTrue
   {T=(BSTree)malloc(sizeof(BSTNode));
    T->data=e;
    T->lchild=T->rchild=NULL;
    T->bf=EH;
    taller=True;
   }
 else  
    {if(e.keynum==T->data.keynum)  //Ê÷ÖĞÒÑÓĞÓëeÓĞÏàÍ¬¹Ø¼ü×ÖµÄ½áµã
	{taller=False; return False;} //²»ÔÙ²åÈë
     if(e.keynum<T->data.keynum)   //Ó¦¼ÌĞøÔÚ*TµÄ×ó×ÓÊ÷ÖĞ½øĞĞËÑË÷
	{if(!InsertAVL(T->lchild,e,taller)) return False; //Î´²åÈë
	 if(taller)         //ÒÑ²åÈëµ½*TµÄ×ó×ÓÊ÷ÖĞÇÒ×ó×ÓÊ÷¡°³¤¸ß¡±
	   switch(T->bf)    //¼ì²é*TµÄÆ½ºâ¶È
	     {case LH:LeftBalance(T); //Ô­±¾×ó×ÓÊ÷±ÈÓÒ×ÓÊ÷¸ß£¬ĞèÒª×ö×óÆ½ºâ´¦Àí
		      taller=False;
		      break;
	      case EH:T->bf=LH;    //Ô­±¾×óÓÒ×ÓÊ÷µÈ¸ß£¬ÏÖÒò×ó×ÓÊ÷Ôö¸ß¶øÊ¹Ê÷Ôö¸ß
		      taller=True;
		      break;
	      case RH:T->bf=EH;    //Ô­±¾ÓÒ×ÓÊ÷±È×ó×ÓÊ÷¸ß£¬ÏÖ×óÓÒ×ÓÊ÷µÈ¸ß    
		      taller=False;
		      break;
	     }
	}
    else            //Ó¦¼ÌĞøÔÚ*TµÄÓÒ×ÓÊ÷ÖĞ½øĞĞËÑË÷
	{if(!InsertAVL(T->rchild,e,taller)) return False;//Î´²åÈë
	 if(taller)         //ÒÑ²åÈëµ½*TµÄÓÒ×ÓÊ÷ÖĞÇÒÓÒ×ÓÊ÷¡°³¤¸ß¡±
	   switch(T->bf)    //¼ì²é*TµÄÆ½ºâ¶È
	     {case LH:T->bf=EH;  //Ô­±¾×ó×ÓÊ÷±ÈÓÒ×ÓÊ÷¸ß£¬ÏÖ×óÓÒ×ÓÊ÷µÈ¸ß  
		      taller=False;
		      break;
	      case EH:T->bf=RH;  //Ô­±¾×óÓÒ×ÓÊ÷µÈ¸ß£¬ÏÖÒòÓÒ×ÓÊ÷Ôö¸ß¶øÊ¹Ê÷Ôö¸ß
		      taller=True;
		      break;
	      case RH:RightBalance(T);//Ô­±¾ÓÒ×ÓÊ÷±È×ó×ÓÊ÷¸ß£¬ĞèÒª×öÓÒÆ½ºâ´¦Àí
		      taller=False;
		      break;
	     }
	}
   }
 return True;
}
void LeftBalance(BSTree &T)
{//¶ÔÒÔÖ¸ÕëTËùÖ¸½áµãÎª¸ùµÄ¶ş²æÊ÷×ö×óÆ½ºâĞı×ª´¦Àí£¬±¾Ëã·¨½áÊøÊ±£¬
 //Ö¸ÕëTÖ¸ÏòĞÂµÄ¸ù½áµã
 BSTree lc,rd;
 lc=T->lchild;  //lcÖ¸Ïò*TµÄ×ó×ÓÊ÷¸ù½áµã
 switch(lc->bf) //¼ì²é*TµÄ×ó×ÓÊ÷µÄÆ½ºâ¶È£¬²¢×÷ÏàÓ¦Æ½ºâ´¦Àí 
    {case LH:T->bf=lc->bf=EH; //ĞÂ½áµã²åÈëÔÚ*TµÄ×óº¢×ÓµÄ×ó×ÓÊ÷ÉÏ£¬Òª×÷µ¥ÓÒĞı´¦Àí
	     R_Rotate(T);
	     break;
     case RH:               //ĞÂ½áµã²åÈëÔÚ*TµÄ×óº¢×ÓµÄÓÒ×ÓÊ÷ÉÏ£¬Òª×÷Ë«Ğı´¦Àí
             rd=lc->rchild; //rdÖ¸Ïò*TµÄ×óº¢×ÓµÄÓÒ×ÓÊ÷¸ù
	     switch(rd->bf) //ĞŞ¸Ä*T¼°Æä×óº¢×ÓµÄÆ½ºâÒò×Ó 
		{case LH:T->bf=RH;lc->bf=EH;break;
		 case EH:T->bf=lc->bf=EH;break;
		 case RH:T->bf=EH;lc->bf=LH;break;
		}
	     rd->bf=EH;
	     L_Rotate(T->lchild); //¶Ô*TµÄ×ó×ÓÊ÷×÷×óĞıÆ½ºâ´¦ÀíÓ 
	     R_Rotate(T);    //¶Ô*T×÷ÓÒĞıÆ½ºâ´¦Àí 
     }
}
void RightBalance(BSTree &T)
{//¶ÔÒÔÖ¸ÕëTËùÖ¸½áµãÎª¸ùµÄ¶ş²æÊ÷×öÓÒÆ½ºâĞı×ª´¦Àí£¬±¾Ëã·¨½áÊøÊ±£¬
 //Ö¸ÕëTÖ¸ÏòĞÂµÄ¸ù½áµã
 BSTree rc,ld;
 rc=T->rchild;   //rcÖ¸Ïò*TµÄÓÒ×ÓÊ÷¸ù½áµã
 switch(rc->bf)  //¼ì²é*TµÄÓÒ×ÓÊ÷µÄÆ½ºâ¶È£¬²¢×÷ÏàÓ¦Æ½ºâ´¦Àí 
    {case LH:    //ĞÂ½áµã²åÈëÔÚ*TµÄÓÒº¢×ÓµÄ×ó×ÓÊ÷ÉÏ£¬Òª×÷Ë«Ğı´¦Àí
             ld=rc->lchild; //ldÖ¸Ïò*TµÄÓÒº¢×ÓµÄ×ó×ÓÊ÷¸ù
	     switch(ld->bf) //ĞŞ¸Ä*T¼°ÆäÓÒº¢×ÓµÄÆ½ºâÒò×Ó 
		{case LH:T->bf=EH;rc->bf=RH;break;
		 case EH:T->bf=rc->bf=EH;break;
		 case RH:T->bf=LH;rc->bf=EH;break;
		}
	     ld->bf=EH;
	     R_Rotate(T->rchild); //¶Ô*TµÄÓÒ×ÓÊ÷×÷ÓÒĞıÆ½ºâ´¦ÀíÓ 
	     L_Rotate(T);    //¶Ô*T×÷×óĞıÆ½ºâ´¦Àí 
	     break;
     case RH:T->bf=rc->bf=EH;  //ĞÂ½áµã²åÈëÔÚ*TµÄÓÒº¢×ÓµÄÓÒ×ÓÊ÷ÉÏ£¬Òª×÷µ¥×óĞı´¦Àí
	     L_Rotate(T);
	 }
}

void L_Rotate(BSTree &p)
{//¶ÔÒÔ*pÎª¸ùµÄ¶ş²æÅÅĞòÊ÷×÷×óĞı´¦Àí£¬´¦ÀíÖ®ºópÖ¸ÏòĞÂµÄ¸ù½áµã£¬¼´Ğı×ª´¦Àí
 //Ö®Ç°µÄÓÒ×ÓÊ÷µÄ¸ù½áµã
 BSTree rc;
 rc=p->rchild;         //rcÖ¸ÏòpÓÒ×ÓÊ÷¸ù½áµã
 p->rchild=rc->lchild; //rcµÄ×ó×ÓÊ÷¹Ò½ÓÎªpµÄÓÒ×ÓÊ÷
 rc->lchild=p;         //pÖ¸ÏòĞÂµÄ¸ù½áµã
 p=rc;
}
void R_Rotate(BSTree &p)
{//¶ÔÒÔ*pÎª¸ùµÄ¶ş²æÅÅĞòÊ÷×÷ÓÒĞı´¦Àí£¬´¦ÀíÖ®ºópÖ¸ÏòĞÂµÄ¸ù½áµã£¬¼´Ğı×ª´¦Àí
 //Ö®Ç°µÄ×ó×ÓÊ÷µÄ¸ù½áµã
 BSTree lc;
 lc=p->lchild;         //lcÖ¸Ïòp×ó×ÓÊ÷¸ù½áµã
 p->lchild=lc->rchild; //lcµÄÓÒ×ÓÊ÷¹Ò½ÓÎªpµÄ×ó×ÓÊ÷
 lc->rchild=p;         //pÖ¸ÏòĞÂµÄ¸ù½áµã 
 p=lc;
}