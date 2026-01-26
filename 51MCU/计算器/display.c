#include <REGX52.H>
#include "keyboard.h"
#include "lcd1602.h"
#include "delay.h"
#include "calculator.h"
#include "globalvars.h"
#include <math.h>
#include <string.h>
#include <stdio.h>

// 显示函数
// 显示当前输入的表达式和计算结果
	void display(void)
{
    char show_res[17];  
    unsigned int abs_res = abs(result);  // 处理负数小数部分

    //第一行显示表达式
    LCD_ShowString(1, 1, (char *)expr);
    //清除残留字符
    if (strlen((char *)expr) < 16)
    {
//    LCD_SetCursor(1, strlen((char *)expr) + 1);
			unsigned char i;
      for ( i = strlen((char *)expr); i < 16; i++)
      {
        LCD_ShowChar(1, i + 1, ' ');  // 用空格覆盖残留
      }
    }
    //第二行显示结果,兼容3位小数
    if (result >= 0)
    {
        sprintf(show_res, "=:+%d.%03d", result / 1000, abs_res % 1000);
    }
    else
    {
        sprintf(show_res, "=:-%d.%03d", abs_res / 1000, abs_res % 1000);
    }
    LCD_ShowString(2, 1, show_res);
}