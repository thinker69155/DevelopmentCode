#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

#include <math.h>
#include <string.h>

// --------------------------  按键编号定义--------------------------
// 4×4矩阵键盘（编号0~15）
#define KEY_1       0    // 矩阵键1
#define KEY_2       1    // 矩阵键2
#define KEY_3       2    // 矩阵键3
#define KEY_ADD     3    // 矩阵键+
#define KEY_4       4    // 矩阵键4
#define KEY_5       5    // 矩阵键5
#define KEY_6       6    // 矩阵键6
#define KEY_SUB     7    // 矩阵键-
#define KEY_7       8    // 矩阵键7
#define KEY_8       9    // 矩阵键8
#define KEY_9       10   // 矩阵键9
#define KEY_MUL     11   // 矩阵键×
#define KEY_L_BRACK 12   // 矩阵键(
#define KEY_0       13   // 矩阵键0
#define KEY_R_BRACK 14   // 矩阵键)
#define KEY_DIV     15   // 矩阵键÷

// 4个独立键（编号16~19）
#define KEY_EQ      16   // 独立键=
#define KEY_CLR     17   // 独立键C（清零）
#define KEY_M_PLUS  18   // 独立键M+
#define KEY_FN      19   // 独立键FN（修饰键）

// --------------------------  硬件引脚定义--------------------------




// 矩阵键盘引脚（行P1.0~P1.3，列P1.4~P1.7）
sbit KEY_ROW0 = P1^0;
sbit KEY_ROW1 = P1^1;
sbit KEY_ROW2 = P1^2;
sbit KEY_ROW3 = P1^3;
sbit KEY_COL0 = P1^4;
sbit KEY_COL1 = P1^5;
sbit KEY_COL2 = P1^6;
sbit KEY_COL3 = P1^7;
// 独立键引脚
sbit KEY_EQ_PIN    = P3^0;
sbit KEY_CLR_PIN   = P3^1;
sbit KEY_M_PLUS_PIN = P3^2;
sbit KEY_FN_PIN    = P3^3;

//LCD1602引脚配置：
sbit LCD_RS=P3^5;
sbit LCD_RW=P3^6;
sbit LCD_EN=P3^4;
#define LCD_DataPort P0

// --------------------------  全局变量--------------------------
// 按键检测标志位（替代返回值）
unsigned char key_pressed_flag = 0;  // 0=未按下，1=按下
unsigned char fn_comb_flag = 0;      // 0=组合键未触发，1=触发

// 计算器原有变量（保持不变）
unsigned char disp_buf[16] = {0};
unsigned char disp_len = 0;
double result = 0;
double memory = 0;
double pow_base = 0;
bit flag_eq = 0;
bit flag_pow = 0;
#endif  // __CALCULATOR_H__