#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef int ElemType;

typedef struct 
{
    ElemType *data;
    int top;
}Stack;

typedef enum
{
    Left_Part,Right_Part,Add,Sub,Mul,Div,Mod,Eos,Num
}contentType;//枚举，储存运算数据的类型

char expr[]="82/2+56*-";

//初始化
Stack* initStack()
{
    Stack *s=(Stack*)malloc(sizeof(Stack));
    s->data=(ElemType*)malloc(sizeof(ElemType));
    s->top=-1;
    return s;
}

//进栈
int push(Stack *s,ElemType e)
{
    if (s->top>=MAXSIZE-1)
    {
        printf("满了\n");
        return 0;
    }
    s->top++;
    s->data[s->top]=e;
    return 1;
}
//出栈
int pop(Stack *s,ElemType *e)
{
    if(s->top==-1)
    {
        printf("空的\n");
        return 0;
    }
    *e=s->data[s->top];
    s->top--;
    return 1;
}
//判断字符串中每一位上是什么类型
contentType getToken(char *symbol,int *index)
{
    *symbol=expr[*index];
    *index=*index+1;
    switch (*symbol)
    {
    case '(':return Left_Part;
    case ')':return Right_Part;
    case '+':return Add;
    case '-':return Sub;
    case '*':return Mul;
    case '/':return Div;
    case '%':return Mod;
    case '\0':return Eos;
    default:return Num;
    }
}



int eval(Stack *s)
{
    char symbol;
    int op1,op2;
    int index=0;
    contentType token;
    token=getToken(&symbol,&index);
    ElemType result;
    while (token!=Eos)
    {
        if (token==Num)
        {
            push(s,symbol-'0');
        }
        else
        {
            pop(s,&op2);
            pop(s,&op1);
            switch (token)
            {
                case Add:
                push(s,op1+op2);
                break;
                case Sub:
                push(s,op1-op2);
                break;
                case Mul:
                push(s,op1*op2);
                break;
                case Div:
                push(s,op1/op2);
                break;
                case Mod:
                push(s,op1%op2);
                break;
                default:
                break;
            }
            
        }
        token=getToken(&symbol,&index);
    }
    pop(s,&result);
    printf("%d\n",result);
    return 1;
}


int main(int argc, char const *argv[])
{
    Stack *s=initStack();
    eval(s);
    return 0;
}
