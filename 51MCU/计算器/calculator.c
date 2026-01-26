#include <string.h>
#include "globalvars.h"
#include "keyboard.h"
#include <math.h>





//////////////////////////////////////////////////////////////////////////


// -------------------------- 工具函数 --------------------------
//判断字符是否为数字（0-9）
bit is_digit(unsigned char a) 
{
    return (a >= '0' && a <= '9');
}

// 获取运算符优先级（数字越大优先级越高）
unsigned char priority(char op) 
{
    if (op == 's' || op == 'c' || op == 't') return 4;  // sin/cos/tan（用首字母代表）
    if (op == 'n') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    if (op == '(') return 0;
    return 0xFF;  // 无效运算符
}

// 二元运算符计算
int calc_op(int a, int b, char op) 
{
    switch(op) 
		{
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b != 0) ? (a / b) : 0;  // 除数为0返回0
        case 'n': 
				{  // 幂运算（整数指数）            
						int i=0;
						int j= 1;
            for( i=0; i<b; i++) 
						j *= a;
            return j;
        }
        default: return 0;
    }
}

//三角函数计算（参数为整数弧度，结果为整数）
int angle(int a, char b) 
{
    switch(b) 
		{
        case 's': return (int)(sin((double)a) * 1000);  // 放大1000倍，保留精度
        case 'c': return (int)(cos((double)a) * 1000);
        case 't': return (int)(tan((double)a) * 1000);
        default: return 0;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
// -------------------------- 解析与计算函数 --------------------------

// 解析正负整数：
unsigned char to_int(const unsigned char** p, int* num)
	//num一级指针，指向储存的整合后的数字，p二级指针，指向字符串指针 
{
    int sign;  
    *num = 0;
    sign = 1;  // 符号位（1=正，-1=负）

    if (**p == '-') 
		{
        sign = -1;
        (*p)++;//指针后移一位
//        if (!is_digit(**p)) return 0;
    }
		// 连续数字拼接
    while (**p != '\0' && is_digit(**p)) 
		{
        *num = *num * 10 + (**p - '0');
        (*p)++;
    }

    *num = *num * sign;//填入正负号
    return 1;
}

// 主计算函数：所有局部变量提前到函数开头定义
bit calculate(void) 
{
    unsigned char num_i = 0, op_i = 0;  		// 数字栈、运算符栈指针
    const unsigned char* p = expr;          // 字符串指针
    int num;                                // 存储解析后的数字
    int b, a;                               // a是左操作数，b是右操作数
    char current_op, top_op, op;            // 临时运算符（当前运算符、栈顶运算符）

    while (*p != '\0') 
		{
//        if (*p == ' ') 
//				{ p++; continue; }

        // 解析数字
        if (is_digit(*p) || (*p == '-' && (p == expr || *(p-1) == '(' || priority(*(p-1)) != 0xFF))) 
				{
            if (!to_int(&p, &num)) return 0;
//            if (num_i >= STACK) return 0;
            num_stack[num_i++] = num;
            continue;
        }
        // 左括号
        if (*p == '(') 
				{
            op_stack[op_i++] = *p;
            p++;
            continue;
        }

        // 右括号：使用提前定义的变量b、a、op
        if (*p == ')') 
				{
            while (op_i > 0 && op_stack[op_i-1] != '(') 
						{
                if (num_i < 2) return 0;
                b = num_stack[--num_i];  
                a = num_stack[--num_i];
                op = op_stack[--op_i];
                num_stack[num_i++] = calc_op(a, b, op);
            }
						if (op_i > 0 && (op_stack[op_i-1] == 's' || op_stack[op_i-1] == 'c' || op_stack[op_i-1] == 't')) 
						{
								// 三角函数是一元运算，只需1个参数
						//    if (num_i < 1) return 0;
								int x = num_stack[--num_i];  // 弹出参数（比如 1）
								char angle_op = op_stack[--op_i]; // 弹出三角函数运算符（比如 't'）
								num_stack[num_i++] = angle(x, angle_op); // 计算结果压回栈
						}
//            if (op_i == 0 || op_stack[op_i-1] != '(') return 0;
//            op_i--;
//            p++;
            continue;
        }

        // 普通运算符：使用提前定义的变量current_op、top_op、b、a
        if (priority(*p) != 0xFF) 
				{
            current_op = *p;
            while (op_i > 0) 
						{
                top_op = op_stack[op_i-1];
                if (top_op == '(') break;

                if (priority(current_op) > priority(top_op) ||
                    (priority(current_op) == priority(top_op) && current_op == 'n')) 
								{
                    break;
                }

                if (num_i < 2) return 0;
                b = num_stack[--num_i];  // 直接使用提前定义的变量
                a = num_stack[--num_i];
                num_stack[num_i++] = calc_op(a, b, top_op);
                op_i--;
            }
            if (op_i >= STACK) return 0;
            op_stack[op_i++] = current_op;
            p++;
            continue;
        }

        return 0;
    }

    // 处理剩余运算符：使用提前定义的变量b、a、op
    while (op_i > 0) 
		{
        if (op_stack[op_i-1] == '(') return 0;
        if (num_i < 2) return 0;
        b = num_stack[--num_i];  // 直接使用提前定义的变量
        a = num_stack[--num_i];
        op = op_stack[--op_i];
        num_stack[num_i++] = calc_op(a, b, op);
    }
//    if (num_i != 1) return 0;
    result = num_stack[0];
    return 1;
}
///////////////////////////////////////////////////////////////
// -------------------------- 按键处理函数 --------------------------
// 按键处理函数：拼接表达式、触发计算、清零
void key_process(void) 
{
    // 1. 清零功能（FN模式按'k'）
    if (get == 'k') 
		{
        memset(expr, 0, EXPR_LEN);  // 清空表达式缓冲区
        expr_i = 0;                 // 重置输入索引
        result = 0;                 // 重置结果
        get = 0;
        return;
    }

    // 2. 计算功能（普通模式按'='）
    if (get == '=') 
		{
        if (expr_i > 0) 
				{
            if (calculate() == 0) 
						{
                // 计算失败（如表达式错误："10+"、"(123"），可添加错误提示
                memset(expr, 0, EXPR_LEN);
                expr_i = 0;
                result = 0;
            }
        }
        get = 0;
        return;
    }

    // 3. 拼接输入字符到表达式缓冲区
    if (get != 0 && expr_i + 1 < EXPR_LEN) 
		{  // get!=0 表示有效输入
        expr[expr_i++] = get;
        expr[expr_i] = '\0';  // 字符串结尾加'\0'，确保calculate能识别结束
    }
    get = 0;  // 重置输入，避免重复处理
}