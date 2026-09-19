/*cur_mou.h*/
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>

#define INT_MOUSE 0x33
#define CURINT 16;
#define CURSOR_TYPE 1;
#define CURSOR_SETPOS 2;
#define CURSOR_GETPOS 3;
#define CURSOR_SETPAGE 5;
#define CURSOR_UPPAGE 6;
#define CURSOR_DOWNPAGE 7;
#define CURSOR_GETPAGE 0x0f;
#define CURSOR_GETLINE 3;

mouse_close();
mouse_reset(int *buttonnum);
mouse_show();
mouse_hide() ;
mouse_pos_get(int *x,int *y);
mouse_pos_set(int x,int y);
mouse_x_scope(int left,int right);
mouse_y_scope(int top,int bottom);
mouse_info_ver(int *main,int *sub);
mouse_info_type(char *type);
mouse_info_irq();
mouse_press_left();
mouse_press_right();
mouse_press_middle();
mouse_press_info(int *haspress,int *x,int *y);
mouse_event_add(int which,int (*p)());
mouse_event(int which,int (*p)());

int cursor_getpage();
int cursor_setpage(int page);
cursor_hide();
cursor_show();
cursor_type(int type);
int cursor_getline();
int cursor_getcol();
cursor_setpos(int line,int col);


mouse_close()
{ union REGS mregs;
  mregs.x.ax=0x0;
  int86(INT_MOUSE,&mregs,&mregs);
}

mouse_reset(int *buttonnum)
{ union REGS mregs;
  mregs.x.ax=0x0;
  int86(INT_MOUSE,&mregs,&mregs);
  *buttonnum=mregs.x.bx;
  if (mregs.x.ax==0) return 0;
  if (mregs.x.ax==1) return 1;
  return -1;
}
mouse_show()
{ union REGS mregs;
  mregs.x.ax=0x1;
  int86(INT_MOUSE,&mregs,&mregs);
}
mouse_hide()
{ union REGS mregs;
  mregs.x.ax=0x2;
  int86(INT_MOUSE,&mregs,&mregs);
}
mouse_pos_get(int *x,int *y)
{ union REGS mregs;
  mregs.x.ax=0x3;
  int86(INT_MOUSE,&mregs,&mregs);
  *x=mregs.x.cx;
  *y=mregs.x.dx;
}
mouse_pos_set(int x,int y)
{ union REGS mregs;
  mregs.x.ax=0x4;
  mregs.x.cx=x;
  mregs.x.dx=y;
  int86(INT_MOUSE,&mregs,&mregs);
}

mouse_x_scope(int left,int right)
{ union REGS mregs;
  mregs.x.ax=0x7;
  mregs.x.cx=left;
  mregs.x.dx=right;
  int86(INT_MOUSE,&mregs,&mregs);
}
mouse_y_scope(int top,int bottom)
{ union REGS mregs;
  mregs.x.ax=0x8;
  mregs.x.cx=top;
  mregs.x.dx=bottom;
  int86(INT_MOUSE,&mregs,&mregs);
}
mouse_info_ver(int *main,int *sub)
{ union REGS mregs;
  mregs.x.ax=0x24;
  int86(0x33,&mregs,&mregs);
  *main=mregs.h.bh;
  *sub=mregs.h.bl;
}
int mouse_info_type(char *type)
{ int result;
  union REGS mregs;
  mregs.x.ax=0x24;
  int86(0x33,&mregs,&mregs);
  result=mregs.h.ch;
  switch (result)
  {  case 1:
	    strcpy(type,"Local Bus mouse");
	    return result;
     case 2:
	    strcpy(type,"Serial mouse");
	    return result;
     case 3:
	    strcpy(type,"InPort mouse");
	    return result;
     case 4:
	    strcpy(type,"PS/2 mouse");
	    return result;
     case 5:
	    strcpy(type,"HP mouse");
	    return result;
     default:
	    strcpy(type,"unknown mouse");
	    return 0;
  }
}
mouse_info_irq()
{
  union REGS mregs;
  mregs.x.ax=0x24;
  int86(0x33,&mregs,&mregs);
  return mregs.h.cl;
}

mouse_press_left()
{ union REGS mregs;
  mregs.x.ax=0x3;
  int86(INT_MOUSE,&mregs,&mregs);
  return(mregs.x.bx&0x1);
}
mouse_press_right()
{ union REGS mregs;
  mregs.x.ax=0x3;
  int86(INT_MOUSE,&mregs,&mregs);
  return(mregs.x.bx&0x2);
}
mouse_press_middle()
{ union REGS mregs;
  mregs.x.ax=0x3;
  int86(INT_MOUSE,&mregs,&mregs);
  return(mregs.x.bx&0x4);
}
mouse_press_info(int *haspress,int *x,int *y)
{ union REGS mregs;
  mregs.x.ax=0x5;
  int86(INT_MOUSE,&mregs,&mregs);
  *haspress=mregs.x.bx;
  *x=mregs.x.cx;
  *y=mregs.x.dx;
  if (mregs.x.ax&0x1) return 1;
  if (mregs.x.ax&0x2) return 2;
  if (mregs.x.ax&0x4) return 3;
  return 0;
}
mouse_event_add(int which,int (*p)())
{ union REGS mregs;
  struct SREGS segregs;
  mregs.x.ax=0x18;
  mregs.x.dx=FP_OFF(p);
  segregs.es=FP_SEG(p);
  switch (which)
  {case 0:
     mregs.x.cx=1;
     break;
   case 1:
     mregs.x.cx=2;
     break;
   case 2:
     mregs.x.cx=4;
     break;
   case 3:
     mregs.x.cx=8;
     break;
   case 4:
     mregs.x.cx=16;
     break;
   case 5:
     mregs.x.cx=32;
     break;
   case 6:
     mregs.x.cx=64;
     break;
   default:
     break;
  }
  int86x(INT_MOUSE,&mregs,&mregs,&segregs);
}
mouse_event(int which,int (*p)())
{ union REGS mregs;
  struct SREGS segregs;
  mregs.x.ax=0xc;
  mregs.x.dx=FP_OFF(p);
  segregs.es=FP_SEG(p);
  switch (which)
  {case 0:
     mregs.x.cx=1;
     break;
   case 1:
     mregs.x.cx=2;
     break;
   case 2:
     mregs.x.cx=4;
     break;
   case 3:
     mregs.x.cx=8;
     break;
   case 4:
     mregs.x.cx=16;
     break;
   case 5:
     mregs.x.cx=32;
     break;
   case 6:
     mregs.x.cx=64;
     break;
   default:
     break;
  }
  int86x(INT_MOUSE,&mregs,&mregs,&segregs);
}



int cursor_getpage()
{ union REGS regs;
  regs.h.ah=CURSOR_GETPAGE;
  int86(0x10,&regs,&regs);
  return(regs.h.bh);
}
int cursor_setpage(int page)
{
  union REGS regs;
  regs.h.ah=CURSOR_SETPAGE;
  regs.h.al=page;
  int86(0x10,&regs,&regs);
}
cursor_hide()
{
  union REGS regs;
  regs.h.ah=CURSOR_TYPE;
  regs.h.ch=-1;
  regs.h.cl=-1;
  int86(0x10,&regs,&regs);
}
int cursor_getline()
{
  union REGS regs;
  regs.h.ah=CURSOR_GETPAGE;
  int86(0x10,&regs,&regs);
  regs.h.ah=CURSOR_GETLINE;
  int86(0x10,&regs,&regs);
  return regs.h.dh;
}
int cursor_getcol()
{
  union REGS regs;
  regs.h.ah=CURSOR_GETPAGE;
  int86(0x10,&regs,&regs);
  regs.h.ah=CURSOR_GETLINE;
  int86(0x10,&regs,&regs);
  return regs.h.dl;
}
cursor_setpos(int line,int col)
{
  union REGS regs;
  regs.h.ah=CURSOR_GETPAGE;
  int86(0x10,&regs,&regs);
  regs.h.ah=CURSOR_SETPOS;
  regs.h.dh=line;
  regs.h.dl=col;
  int86(0x10,&regs,&regs);
}
cursor_show()
{
  union REGS regs;
  regs.h.ah=CURSOR_TYPE;
  regs.h.ch=7;
  regs.h.cl=7;
  int86(0x10,&regs,&regs);
}
cursor_type(int type)
{
  union REGS regs;

  switch (type){
  case 0:
    cursor_hide();
    break;
  case 1:
    cursor_show();
    break;
  default:
    if (type>7)
      type=7;
    regs.h.ah=CURSOR_TYPE;
    regs.h.ch=7;
    regs.h.cl=8-type;
    int86(0x10,&regs,&regs);
    break;
  }
}
