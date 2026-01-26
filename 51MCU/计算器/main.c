#include <REGX52.H>
#include "keyboard.h"
#include "lcd1602.h"
#include "delay.h"
#include "calculator.h"
#include "globalvars.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "display.h"




void main(void) 
{
    // 初始化：I/O口、显示模块（根据硬件补充）
    P1_0 = 1;  // 初始指示灯熄灭（普通模式灯）
    P1_1 = 1;  // FN模式灯熄灭
    P3 = 0xff; // 按键口初始化为高电平（上拉输入）
   
    // LCD初始化（若有显示模块，需添加）
//     lcd_init();
     display();  // 初始显示空表达式和0结果

    while (1) 
		{  // 死循环，持续扫描
        // 扫描独立按键切换模式
        key_duli();        
        //  扫描矩阵键盘
        key_to_data();        
        // 处理按键输入
        key_process();        
        // 刷新显示
        display();        
        //  延时
//        delay(10);
    }
}