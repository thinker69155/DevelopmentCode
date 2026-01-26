#ifndef __GLOBALVARS_H__
#define __GLOBALVARS_H__

// 第一步：先定义宏（顺序：宏在前，使用宏的变量在后）
#define KEY_CLEAR   0x00  // 清除键（自定义值）
#define EXPR_LEN 32       // 表达式缓冲区最大长度
#define STACK    16       // 栈最大深度

// 第二步：声明跨文件全局变量（仅声明，不分配内存）
extern unsigned char get;                     // 按键输入值
extern unsigned char duli;                    // 模式变量（1=普通模式，2=FN模式）
extern unsigned char xdata expr[EXPR_LEN];    // 表达式缓冲区（用上面定义的 EXPR_LEN）
extern unsigned char expr_i;                  // 表达式输入索引
extern int xdata num_stack[STACK];            // 数字栈（用上面定义的 STACK）
extern char xdata op_stack[STACK];            // 运算符栈（用上面定义的 STACK）
extern int result;                            // 计算结果

#endif  // __GLOBALVARS_H__