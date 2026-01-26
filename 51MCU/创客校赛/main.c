#include "calculator.h"
#include "delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"
#include "compute.h"
//#include <REGX52.H>

//////////////////////////////////////////////////////////////////////////////
// 主函数
void main(void) 
{
    LCD_Init();
    reset_calc();
    while(1) 
		{
        unsigned char key_num = key_scan_all();  // 获取按键编号
        if(key_num != 0xFF) 
				{                   // 有按键按下
            key_process(key_num);               // 处理按键（参数=按键编号）
            disp_update();                      // 更新显示
        }
    }
}
//////////////////////////////////////////////////////////////////////////////



