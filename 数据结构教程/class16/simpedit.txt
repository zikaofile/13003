#include <conio.h>
#include <string.h>
#include "keyscode.h"
#include "menu.h"

struct line{
  int charnum;
  char *base;
};

typedef struct line SequListElemType;

#include "sequlist.h"


#define MAXLINES 1000

int key;
int cureditline=0;
int curscrtopline=0;
int cureditcol=0;
int funckey;
int editwinx=2;
int editwiny=3;
int editwinlines=20;
int mainover=0;
FILE *curfile;

char filename[255]="test.txt";

SequList *Document;

char ascii(int k);
printdoc(int startfileline,int startscrline);
readdoc(FILE *fp);

editline(int curline,int maxcolnum)
{
  char s[2000];
  setscrcolor(BLUE,YELLOW);
  strcpy(s,Document->elem[curline].base);
  getstring(editwinx,editwiny+curline-curscrtopline,s,maxcolnum);
  free(Document->elem[curline].base);
  Document->elem[curline].base=(char *)malloc(strlen(s)+1);
  strcpy(Document->elem[curline].base,s);
}

printdoc(int startfileline,int startscrline)
{
  int i;
  int j;
  cursor_hide();
  i=startscrline;
  j=startfileline;
  setscrcolor(BLUE,YELLOW);
  gotoxy(editwinx,editwiny+startscrline);
  while(i<=editwinlines && i<Document->length)
    {
      clearscrline(editwinx,editwiny+i,78);
      putsxy(editwinx,editwiny+i++,Document->elem[j++ -1].base);
    }
  while(i<=editwinlines)
    clearscrline(editwinx,editwiny+i++,78);
  cursor_show();
}

getline(FILE *fp,char *l)
{
  int i=0;
  while(!feof(fp))
    if((l[i++]=fgetc(fp))=='\n')
      break;
  l[i-1]='\0';
}

closedoc(FILE *fp)
{

  int i;
  fclose(fp);
  for(i=0;i<Document->length;i++)
    free(Document->elem[i].base);
  SequListDestroy(Document);
}

readdoc(FILE *fp)
{
  char *newline;
  char s[20000];
  int linenum=0;
  struct line curline;
  if(!fp) return;
  while(!feof(fp))
    {
      getline(fp,s);
      linenum++;
      newline=(char *)malloc(strlen(s)+1);
      strcpy(newline,s);
      curline.base=newline;
      curline.charnum=strlen(newline);
      SequListInsert(Document,linenum,curline);
    }
}

char ascii(int k)
{
  char c;
  c=(k<<8)>>8;
  if(c>=32&&c<127)
    return c;
  else
    return 0;
}

insertchar(char *s,char c,int pos)
{
  int i;
  for(i=strlen(s)+1;i>pos;i--)
    s[i]=s[i-1];
  s[i]=c;
}
deletechar(char *s,int pos)
{
  int i;
  int j;
  j=strlen(s);
  for(i=pos;i<=j;i++)
    s[i]=s[i+1];
}
clearscrline(int x,int y,int num)
{
  int i;
  for(i=0;i<num;i++)
    putcxy(x+i,y,'');
}
getsindiag(int x,int y,int w,char *title,char *s)
{
  char buf[2000];
  gettext(x,y,x+w+2,y+2,buf);
  setscrcolor(LIGHTGRAY,BLACK);
  box(x,y,w+2,3);
  putsxy(x+3,y,title);
  getstring(x+1,y+1,s,w);
  puttext(x,y,x+w+2,y+2,buf);
}

insertnewline(int linenum)
{
  struct line  l;
  l.base=(char *)malloc(80);
  l.charnum=0;
  l.base[0]='\0';
  SequListInsert(Document,linenum,l);
}
deleteline(int linenum)
{
  SequListDelete(Document,linenum);
}

getstring(int x,int y,char *s,int num)
{
  int k;
  int n;
  char c;
  int curpos=0;
  int thisover=0;
  cursor_show();
/*  putsxy(x,y,s); */
  gotoxy(x,y);
  while(!thisover)
    {
      if(k=bioskey(1))
       { switch(k){
	   case KEYEsc:
	   case KEYReturn:
	   case KEYUp:
	   case KEYDown:
	   case KEYAlt_x:
	   case KEYCtrl_y:
	     return;
	     break;
	   default:
	     bioskey(0);
	   }
       }
      else
	continue;
      switch(k){
	case KEYHome:
	  curpos=0;
	  gotoxy(x+curpos,y);
	  break;
	case KEYEnd:
	  curpos=strlen(s);
	  gotoxy(x+curpos,y);
	  break;
	case KEYReturn:
	  thisover=1;
	  break;
	case KEYLeft:
	  if(curpos) curpos--;
	  gotoxy(x+curpos,y);
	  break;
	case KEYRight:
	  if(curpos<num) curpos++;
	  gotoxy(x+curpos,y);
	  break;
	case KEYDelete:
	  if(curpos<strlen(s))
	   {
	     deletechar(s,curpos);
	     cursor_hide();
	     clearscrline(x,y,num);
	     putsxy(x,y,s);
	     gotoxy(x+curpos,y);
	     cursor_show();
	   }
	  break;
	case KEYBackspace:
	  if(curpos)
	    {
	      deletechar(s,curpos-1);
	      curpos--;
              cursor_hide();
	      clearscrline(x,y,num);
	      putsxy(x,y,s);
	      gotoxy(x+curpos,y);
	      cursor_show();
	    }
	  break;
	case KEYEsc:
	  return;
	default:
	  c=ascii(k);
	  if (c&&strlen(s)<num)
	    {
	      insertchar(s,c,curpos);
	      cursor_hide();
	      clearscrline(x,y,num);
	      curpos++;
	      putsxy(x,y,s);
	      gotoxy(x+curpos,y);
	      cursor_show();
	    }
	break;
      }
    }
}

dofunc(int itemno)
{
   switch(itemno)
    {
      case 0:
	 break;
      case 1:  /*Open file*/
	 getsindiag(3,4,50,"Open file Name",filename);
	 if(curfile=fopen(filename,"r+"))
	   {
	     readdoc(curfile);
	     printdoc(1,0);
	   }
	 break;
      case 3:
	mainover=1;
	break;
      case 21:
	showmessagew();
      default:
	break;
    }
}


main()
{ int i;
  char c;

  char  *mainmenuitem[10]={"File","Edit    ","Help"};
  char  *submenu1[10]={"New","Open","Save","Exit to system"};
  char  *submenu2[10]={"Copy","Cut","Paste   "};
  char  *submenu3[20]={"HelpContent","About"};

  initmenu(MAINMENU_V,3,&mainmenu,mainmenuitem);
  initmenu(SUBMENU_H,4,&submenu[0],submenu1);
  initmenu(SUBMENU_H,3,&submenu[1],submenu2);
  initmenu(SUBMENU_H,2,&submenu[2],submenu3);
  for(i=0;i<3;i++)
    addsubmenu(&mainmenu,i,&submenu[i]);
  definemenupos(3,1,&mainmenu);
  cursor_hide();
  showmenu(&mainmenu);
  showmainw(1,2,80,23);
  showmessagew();

  SequListInit(&Document,MAXLINES);
  insertnewline(1);
  setscrcolor(BLUE,YELLOW);
  while(!mainover)
  {
    if(key=bioskey(1))
      {if(!ascii(key))
	bioskey(0);
      }
    else
      continue;
    switch(key){
	case KEYBackspace:
	case KEYDelete:
	case KEYHome:
	case KEYEnd:
	case KEYReturn:
	  if(cureditline-curscrtopline<editwinlines)
	    cureditline++;
	  else
	    {
	       curscrtopline++;
	       printdoc(curscrtopline+1,editwiny);
	    }
	  insertnewline(cureditline+1);
	  printdoc(curscrtopline+1,0);
	  gotoxy(editwinx,editwiny+cureditline);
	  editline(cureditline,78);
	  break;
	case KEYUp:
	  if (cureditline>0)
	    {
	      cureditline--;
	      gotoxy(editwinx,editwiny+cureditline);
	      editline(cureditline,78);
	    }
	  break;
	case KEYDown:
	  if (cureditline<Document->length-1)
	    {
	      cureditline++;
	      gotoxy(editwinx,editwiny+cureditline);
	      editline(cureditline,78);
	    }
	  break;
	case KEYCtrl_y:
	  deleteline(cureditline+1);
	  if(Document->length==0)
	    insertnewline(cureditline+1);
	  if(cureditline>=Document->length)
	    insertnewline(cureditline+1);
	  printdoc(cureditline+1,cureditline-curscrtopline);
	  gotoxy(editwinx,editwiny+cureditline);
	  editline(cureditline,78);
	  break;
	case KEYLeft:
	case KEYRight:
          break;
	case KEYCtrl_s:
	  break;
	case ESC:
	   cursor_hide();
	   dofunc(getmenuitem());
	   break;
	case KEYAlt_x:
	  mainover=1;
	  break;
	default:
	  gotoxy(editwinx,editwiny+cureditline-curscrtopline);
	  editline(cureditline,78);
	  break;
    }
  }
  closedoc(curfile);
  setscrcolor(BLACK,WHITE);
  clrscr();
  cursor_show();
}


