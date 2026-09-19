1.初始化顺序栈

SqStack InitStack_sq()
{   
    SqStack s;
    s.top=-1;
    return(s);
} /*建立一个空栈s*/


2.取栈顶元素

int GetTop_sq(SqStack *s,elementtype *x)   
{
    if(s->top==-1)
        return(0); 
    else
    {
        *x=s->element[s->top];
        return(1);
    }
} /*取栈顶元素,若栈s非空,用*x返回栈顶元素*/


3.进栈操作

int Push_sq(SqStack *s,elementtype x)      
{
    if(s->top==MAXLEN-1)
        return(0); 
    s->top++;
    s->element[s->top]=x;
    return(1);
} /*进栈操作,若栈s未满，将元素x进栈*/


4.出栈操作

int Pop_sq(SqStack *s,elementtype *x)       
{
    if(s->top==-1)
        return(0);
    *x=s->element[s->top];
    s->top--;
    return(1);
}/*出栈操作,若栈s非空,删除s的栈顶元素,并用*x返回栈顶元素*/


5.判空栈操作

int Empty_sq(SqStack *s)                   
{
    return(s->top==-1);
} /*判断栈s是否为空,空则返回1,非空返回0*/

