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
    // 11.0592MHz晶振，1ms中断初值计算：
    // 机器周期 = 12/11059200 = 1.085us
    // 1ms = 1000us，需计数次数 = 1000 / 1.085 ≈ 921
    // 初值 = 65536 - 921 = 64615 = 0xFC67
    TH0 = 0xFC;  // 高8位
    TL0 = 0x67;  // 低8位
    ET0 = 1;     // 允许定时器0中断
    EA = 1;      // 总中断允许
    TR0 = 1;     // 启动定时器0
}

// 定时器0中断服务函数（修复：重装载统一的1ms初值）
void timer0_isr() interrupt 1 
{
    // 重装载1ms初值（与初始化一致）
    TH0 = 0xFC;
    TL0 = 0x67;
    
    ms_cnt++;              // 毫秒计数+1（0-65535循环，足够使用）
    flag_1ms = 1;          // 1ms标志位
    
    if (ms_cnt % 1000 == 0) 
		{  // 每1000ms=1秒
        flag_1s = 1;           // 1秒标志位
    }
}

