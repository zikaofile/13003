/*
    Author:     zmofun
    HomePage:   http://zmofun.yeah.net
    CopyRight:  All rights reserved.
    Date:       1999.12
*/


#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<bios.h>
#include"cur_mou.h"

#define MAINMENU_V 1
#define MAINMENU_H 2
#define SUBMENU_V  3
#define SUBMENU_H  4
#define MENUITEMCOLOR BLACK
#define MENUBACKCOLOR LIGHTGRAY
#define MENUSEITCOLOR WHITE
#define MENUSEBKCOLOR BLACK
#define WFONTCOLOR YELLOW
#define WBKCOLOR BLUE
#define WFRAMECOLOR WHITE
#define STABLEL 196
#define STABLEH 179
#define STABLE1 218
#define STABLE2 191
#define STABLE3 192
#define STABLE4 217
#define ESC 0x11b
#define RETURN 0x1c0d
#define ALT 0x08
#define ALTX 0x2d00
#define RIGHTS 0x01
#define LEFTA 0x4b00
#define UPA   0x4800
#define DOWNA 0x5000
#define RIGHTA 0x4d00


struct menu{
    int menutype;
    int menuitemnum;
    int menuitemx[10];
    int menuitemy[10];
    int width;
    int select;
    char *menuitemname[10];
    char scrbuff[400];
    struct menu * sub[10];
}mainmenu,submenu[10];

int initmenu(int menutype,int itemnum,struct menu *curmenu,
      char * itemname[20])
{ int i;

  curmenu->menutype=menutype;
  curmenu->menuitemnum=itemnum;
  for (i=0;i<itemnum;i++){
    curmenu->menuitemname[i]=itemname[i];
    curmenu->sub[i]=NULL;
  }
}
int addsubmenu(struct menu *parent,int sub,struct menu *submenu)
{
  parent->sub[sub]=submenu;
}
int definemenupos(int x,int y,struct menu * curmenu)
{ int i,j;
  int itemlen,maxlen;
  itemlen=maxlen=0;
  if (curmenu->menutype==MAINMENU_V){
    for(i=0;i<curmenu->menuitemnum;i++){
      curmenu->menuitemy[i]=y;
      curmenu->menuitemx[i]=x;
      curmenu->select=0;
      itemlen=strlen(curmenu->menuitemname[i]);
      x=x+2+itemlen;
      if (curmenu->sub[i])
	 definemenupos(curmenu->menuitemx[i]+1,curmenu->menuitemy[i],
	    curmenu->sub[i]);
    }
  }
  if (curmenu->menutype==SUBMENU_H){
    for(i=0;i<curmenu->menuitemnum;i++){
      curmenu->menuitemy[i]=y;
      curmenu->menuitemx[i]=x;
      itemlen=strlen(curmenu->menuitemname[i]);
      if (itemlen>maxlen)
	maxlen=itemlen;
      y++;
    }
    curmenu->width=maxlen;
    curmenu->select=0;
    for(i=0;i<curmenu->menuitemnum;i++)
      if(curmenu->sub[i])
	 definemenupos(curmenu->menuitemx[i],curmenu->menuitemy[i]+maxlen,
		curmenu->sub[i]);
  }
}
setscrcolor(int backcolor,int txtcolor)
{
  textcolor(txtcolor);
  textbackground(backcolor);
}
putsxy(int x,int y,char *s)
{
  gotoxy(x,y);
  cputs(s);
}
putcxy(int x,int y,char c)
{
  gotoxy(x,y);
  putch(c);
}
box(int x,int y,int w,int h)
{
  int i,j;
  for(i=x;i<x+w;i++)
    for(j=y;j<y+h;j++)
      putcxy(i,j,' ');
  for(i=x;i<x+w;i++)
    { putcxy(i,y,STABLEL);
      putcxy(i,y+h-1,STABLEL);
    }
  for(i=y;i<y+h;i++)
    { putcxy(x,i,STABLEH);
      putcxy(x+w-1,i,STABLEH);
    }
  putcxy(x,y,STABLE1);
  putcxy(x+w-1,y,STABLE2);
  putcxy(x,y+h-1,STABLE3);
  putcxy(x+w-1,y+h-1,STABLE4);
}
int hidemenu(struct menu *curmenu)
{
  if (curmenu->menutype==SUBMENU_H)
    puttext(curmenu->menuitemx[0],curmenu->menuitemy[0]+1,
      curmenu->menuitemx[0]+curmenu->width+2,
      curmenu->menuitemy[0]+curmenu->menuitemnum+2,curmenu->scrbuff);
}
int showmenu(struct menu *curmenu)
{
  int i,j;
  setscrcolor(MENUBACKCOLOR,MENUITEMCOLOR);
  if (curmenu->menutype==MAINMENU_V) {
    for(i=0;i<80;i++)
      putcxy(i+1,1,' ');
    for(i=0;i<curmenu->menuitemnum;i++){
      gotoxy(curmenu->menuitemx[i],curmenu->menuitemy[i]);
      cputs(curmenu->menuitemname[i]);
    }
  }

  if (curmenu->menutype==SUBMENU_H) {
    gettext(curmenu->menuitemx[0],curmenu->menuitemy[0]+1,
      curmenu->menuitemx[0]+curmenu->width+2,
      curmenu->menuitemy[0]+curmenu->menuitemnum+2,curmenu->scrbuff);
    box(curmenu->menuitemx[0],curmenu->menuitemy[0]+1,
       curmenu->width+2,curmenu->menuitemnum+2);
    for(i=0;i<curmenu->menuitemnum;i++){
      gotoxy(curmenu->menuitemx[i]+1,curmenu->menuitemy[i]+2);
      cputs(curmenu->menuitemname[i]);
    }
  }
}

activemenu(int acti,int sub,struct menu *curmenu)
{
  int i;
  if (acti==0)
    setscrcolor(MENUBACKCOLOR,MENUITEMCOLOR);
  else
    setscrcolor(MENUSEBKCOLOR,MENUSEITCOLOR);

  if (curmenu->menutype==MAINMENU_V) {
    gotoxy(curmenu->menuitemx[sub],curmenu->menuitemy[sub]);
    cputs(curmenu->menuitemname[sub]);
  }
  if (curmenu->menutype==SUBMENU_H) {
    for(i=1;i<=curmenu->width;i++)
      putcxy(i+curmenu->menuitemx[sub],curmenu->menuitemy[sub]+2,' ');
    gotoxy(curmenu->menuitemx[sub]+1,curmenu->menuitemy[sub]+2);
      cputs(curmenu->menuitemname[sub]);
  }
}
showmainw(int x,int y,int w,int h)
{
  setscrcolor(WBKCOLOR,WFRAMECOLOR);
  box(x,y,w,h);
  showstatus("ESC to select menu.       Alt + X to exit this program.");
}
showstatus(char *s)
{  int i;
   setscrcolor(LIGHTGRAY,BLACK);
   for (i=1;i<80;i++)
     putcxy(i,25,' ');
   putsxy(2,25,s);
}
showmessagew()
{
   char buff[2000];
   gettext(20,10,60,15,buff);
   setscrcolor(LIGHTGRAY,BLUE);
   box(20,10,40,5);
   putsxy(26,11,"Author:  zmofun\n");
   putsxy(26,12,"   All rights is reserved.\n");
   putsxy(26,13,"                      1999.12.6");
   while(bioskey(1)==0);
   bioskey(0);
   puttext(20,10,60,15,buff);
}
movesubitem(int direct,struct menu *curmenu)
{
  activemenu(0,curmenu->select,curmenu);
  if (direct)
    curmenu->select++;
  else
    curmenu->select--;
  if (curmenu->select<0)
    curmenu->select=curmenu->menuitemnum-1;
  if(curmenu->select>curmenu->menuitemnum-1)
    curmenu->select=0;
  activemenu(1,curmenu->select,curmenu);
}
movemainsub(int direct)
{
  activemenu(0,mainmenu.select,&mainmenu);
  hidemenu(mainmenu.sub[mainmenu.select]);
  if(direct)
    mainmenu.select++;
  else
    mainmenu.select--;
  if(mainmenu.select<0)
    mainmenu.select=mainmenu.menuitemnum-1;
  if(mainmenu.select>mainmenu.menuitemnum-1)
    mainmenu.select=0;
  activemenu(1,mainmenu.select,&mainmenu);
  showmenu(mainmenu.sub[mainmenu.select]);
}
getmenuitem()
{
  int itemno;
  char buff[200];
  int key=0;
  int done=0;
  struct menu *curmenu;
  showmenu(&mainmenu);
  activemenu(1,mainmenu.select,&mainmenu);
  curmenu=mainmenu.sub[mainmenu.select];
  showmenu(curmenu);
  activemenu(1,curmenu->select,curmenu);
  while (!done)
    {
      while(bioskey(1)==0);
      key=bioskey(0);
      switch(key)
	{
	  case UPA:
	    if (curmenu->menutype==SUBMENU_H)
	      movesubitem(0,curmenu);
	    break;
	  case DOWNA:
	    if (curmenu->menutype==SUBMENU_H)
	      movesubitem(1,curmenu);
	    break;
	  case LEFTA:
	    movemainsub(0);
	    curmenu=mainmenu.sub[mainmenu.select];
	    activemenu(1,curmenu->select,curmenu);
	    break;
	  case RIGHTA:
	    movemainsub(1);
	    curmenu=mainmenu.sub[mainmenu.select];
	    activemenu(1,curmenu->select,curmenu);
	    break;
	  case RETURN:
	    activemenu(0,mainmenu.select,&mainmenu);
	    hidemenu(curmenu);
	    done=1;
	    itemno=mainmenu.select*10+mainmenu.sub[mainmenu.select]->select;
	    break;
	  case ESC:
	    activemenu(0,mainmenu.select,&mainmenu);
	    hidemenu(curmenu);
	    done=1;
	    itemno=-1;
	    break;
	  default:
	    break;
	}
    }
  return itemno;
}

/*

dofunc(int itemno)
{
   switch(itemno)
    {
      case 0:
	 break;
      case 1:

	 break;
      case 2:
	 break;
      case 3:
	mainover=1;
	break;
      default:
	break;
    }
}


main()
{ int i;
  int key,funckey;
  char  *mainmenuitem[10]={"File","Edit","Run","Help"};
  char  *submenu1[10]={"Open","New a picture","Close","Exit to system     "};
  char  *submenu2[10]={"Copy","Cut","Paste"};
  char  *submenu3[20]={"Program to Compile","Reset"};
  char  *submenu4[20]={"About","Close"};
  initmenu(MAINMENU_V,4,&mainmenu,mainmenuitem);
  initmenu(SUBMENU_H,4,&submenu[0],submenu1);
  initmenu(SUBMENU_H,3,&submenu[1],submenu2);
  initmenu(SUBMENU_H,2,&submenu[2],submenu3);
  initmenu(SUBMENU_H,2,&submenu[3],submenu4);
  for(i=0;i<4;i++)
    addsubmenu(&mainmenu,i,&submenu[i]);
  definemenupos(3,1,&mainmenu);
  cursor_hide();
  showmenu(&mainmenu);
  showmainw(1,2,80,23);
  showmessagew();
  while(!mainover)
  {
    while(bioskey(1)==0);
    key=bioskey(0);
    funckey=bioskey(2);
    if (funckey)
    {
      if(funckey&ALT)
      {
	if(key==ALTX)
	  mainover=1;
      }
    }
    else
      switch(key){
	case RETURN:
	   break;
	case ESC:
	   dofunc(getmenuitem());
	default:
	  break;
      }
  }
  setscrcolor(BLACK,WHITE);
  clrscr();
  cursor_show();
}

*/