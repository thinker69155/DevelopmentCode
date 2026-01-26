#include "modeswitch.h"
#include <globalvars.h>
#include "LCD1602.h"
#include "show.h"
// 模式切换
void mode_switch() 
{
    mode++;
    if(mode > VIEW_RECORD) mode = CALENDAR;  // 循环切换：日历→倒计时→秒表→查看→日历
    set_flag = 0;
    stopwatch_running = 0;
    select_pos = 0;
    LCD_WriteCommand(0x01);  // 清屏

    // 核心修复：切换到哪个模式，就立即调用哪个模式的显示函数
    switch(mode) {
        case CALENDAR: show_calendar(); break;
        case COUNTDOWN: show_countdown(); break;
        case STOPWATCH: show_stopwatch(); break;
        case VIEW_RECORD: show_records(); break;  // 关键：进入查看模式直接显示
    }
}