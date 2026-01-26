#include <globalvars.h>
#include "timer.h"
#include <intrins.h>
#include <REGX52.H>
// 定时器0初始化（1ms中断，硬件级精准计时）
// 定时器0初始化（修复：统一1ms初值）
void Timer0_Init() 
{
    TMOD &= 0xF0;
    TMOD |= 0x01;  // 定时器0工作模式1（16位自动重装）
    TH0 = 0xFC;  // 高8位
    TL0 = 0x67;  // 低8位
    ET0 = 1;     // 允许定时器0中断
    EA = 1;      // 总中断允许
    TR0 = 1;     // 启动定时器0
}

// 定时器0中断服务函数
void timer0_isr() interrupt 1 
{
    // 重装载1ms初值（与初始化一致）
    TH0 = 0xFC;
    TL0 = 0x67;
    ms_cnt++;              // 毫秒计数+1
    flag_1ms = 1;          // 1ms标志位
    
    if (ms_cnt % 1000 == 0) // 每1000ms=1秒
		{  
        flag_1s = 1;           // 1秒标志位
    }
}