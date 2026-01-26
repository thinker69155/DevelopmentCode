#include "calc_common.h"



//// ********** 延时函数（软件延时，适配11.0592MHz晶振）**********
//void delay_ms(uint16_t ms) {
//    uint16_t i, j;
//    for (i = ms; i > 0; i--)
//        for (j = 110; j > 0; j--);
//}

//// ********** 定时器0初始化（1ms中断，用于长按计时）**********
//void Timer0_Init(void) {
//    TMOD |= 0x01;          // 模式1：16位定时器
//    TH0 = (65536 - 1000) / 256;  // 1ms初值（11.0592MHz）
//    TL0 = (65536 - 1000) % 256;
//    ET0 = 1;               // 使能定时器0中断
//    TR0 = 1;               // 启动定时器0
//    EA = 1;                // 开总中断
//}

//// ********** 定时器0中断服务函数 **********
//void Timer0_ISR(void) interrupt 1 {
//    TH0 = (65536 - 1000) / 256;
//    TL0 = (65536 - 1000) % 256;
//    
//    if (key_hold_flag) {
//        press_timer++;
//        if (press_timer > 1000) press_timer = 1000;  // 上限1s
//    } else {
//        press_timer = 0;
//    }
//}

//// ********** 判断是否为无效值（替代isnan，适配Keil C51）**********
//bit is_invalid(float x) {
//    return (x > 1e29f) ? 1 : 0;  // 大于1e29f视为无效值
//}