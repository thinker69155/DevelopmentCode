#include "globalvars.h"  // 包含头文件，获取 EXPR_LEN、STACK 宏定义

// 定义全局变量（分配内存，与.h中的声明一一对应）
unsigned char get = 0;                          // 初始化：0（无输入）
unsigned char duli = 0;                         // 初始化：0（未切换模式）
unsigned char xdata expr[EXPR_LEN] = {0};       // 初始化：全0（空表达式）
unsigned char expr_i = 0;                       // 初始化：0（输入起始位置）
int xdata num_stack[STACK] = {0};               // 初始化：全0（空数字栈）
char xdata op_stack[STACK] = {0};               // 初始化：全0（空运算符栈）
int result = 0;                                 // 初始化：0（初始结果）                                // 2字节（留DATA区）