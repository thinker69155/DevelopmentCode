#include <REGX52.H>
#include "lcd1602.h"
#include "key.h"
#include <intrins.h>
#include "globalvars.h"
#include "delay.h"
#include "show.h"
#include "handlemode.h"
#include "modeswitch.h"
#include "timeupdate.h"
#include "timer.h"

void delay(unsigned int ms);

// 主函数
void main() 
{
    unsigned char key;
    LCD_Init();
    Timer0_Init();
    show_calendar();
    
    while(1) 
		{
        key = key_scan();          // 按键扫描（无按键返回0）
        handle_time_update();      // 时间更新
        
        switch(mode) 
				{
            case CALENDAR:
                handle_calendar_mode(key);
                break;
            case COUNTDOWN:
                handle_countdown_mode(key);
                break;
            case STOPWATCH:
                handle_stopwatch_mode(key);
                break;
            case VIEW_RECORD:
                handle_view_record_mode(key);
                break;
        }
    }
}