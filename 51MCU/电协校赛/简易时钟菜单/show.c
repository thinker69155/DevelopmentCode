#include <globalvars.h>
#include "show.h"
#include "LCD1602.h"
#include "delay.h"
// 日历模式显示
void show_calendar() 
{
    LCD_ShowString(1, 1, "DATE:");
    LCD_ShowNum(1, 6, calendar[0], 4);
    LCD_ShowChar(1, 10, '-');
    LCD_ShowNum(1, 11, calendar[1], 2);
    LCD_ShowChar(1, 13, '-');
    LCD_ShowNum(1, 14, calendar[2], 2);

    LCD_ShowString(2, 1, "TIME:");
    LCD_ShowNum(2, 6, calendar[3], 2);
    LCD_ShowChar(2, 8, ':');
    LCD_ShowNum(2, 9, calendar[4], 2);
    LCD_ShowChar(2, 11, ':');
    LCD_ShowNum(2, 12, calendar[5], 2);

    if(set_flag) 
		{
        delay(100);
        switch(select_pos) 
				{
            case 0: LCD_ShowString(1, 6, "    "); break;
            case 1: LCD_ShowString(1, 11, "  "); break;
            case 2: LCD_ShowString(1, 14, "  "); break;
            case 3: LCD_ShowString(2, 6, "  "); break;
            case 4: LCD_ShowString(2, 9, "  "); break;
            case 5: LCD_ShowString(2, 12, "  "); break;
        }
        delay(100);
        switch(select_pos) 
				{
            case 0: LCD_ShowNum(1, 6, calendar[0], 4); break;
            case 1: LCD_ShowNum(1, 11, calendar[1], 2); break;
            case 2: LCD_ShowNum(1, 14, calendar[2], 2); break;
            case 3: LCD_ShowNum(2, 6, calendar[3], 2); break;
            case 4: LCD_ShowNum(2, 9, calendar[4], 2); break;
            case 5: LCD_ShowNum(2, 12, calendar[5], 2); break;
        }
        LCD_ShowChar(1, 10, '-');
        LCD_ShowChar(1, 13, '-');
        LCD_ShowChar(2, 8, ':');
        LCD_ShowChar(2, 11, ':');
    }
}
//***************************************************************************

// 倒计时模式显示
void show_countdown() 
{
    LCD_ShowString(1, 1, "DOWN:");
    LCD_ShowNum(1, 5, countdown[0], 2);
    LCD_ShowChar(1, 7, ':');
    LCD_ShowNum(1, 8, countdown[1], 2);
    LCD_ShowChar(1, 10, ':');
    LCD_ShowNum(1, 11, countdown[2], 2);

    if (set_flag) 
		{
        LCD_ShowString(2, 1, "SET: K2=Q K1=S");
    } else 
		{
        LCD_ShowString(2, 1, countdown_running ? "RUN " : "STOP");
    }

    if(set_flag) 
		{
        delay(200);
        switch(select_pos) 
				{
            case 0: LCD_ShowString(1, 5, "  "); break;
            case 1: LCD_ShowString(1, 8, "  "); break;
            case 2: LCD_ShowString(1, 11, "  "); break;
        }
        delay(200);
        switch(select_pos) 
				{
            case 0: LCD_ShowNum(1, 5, countdown[0], 2); break;
            case 1: LCD_ShowNum(1, 8, countdown[1], 2); break;
            case 2: LCD_ShowNum(1, 11, countdown[2], 2); break;
        }
        LCD_ShowChar(1, 7, ':');
        LCD_ShowChar(1, 10, ':');
    }
}
//***************************************************************************

// 秒表模式显示（1ms精度，视觉流畅）
// 秒表模式显示（修复：首次进入强制显示零）
void show_stopwatch() 
{
    static unsigned char last_h, last_m, last_s, last_ms;
    static bit init_flag;
    unsigned char curr_ms = (stopwatch[3] / 10) % 100;  // 00-99 毫秒

    // 第一次进入函数时，强制显示初始零
    if (init_flag == 0) {
        last_h = 0xFF;  // 设为非零，确保后续判断为真
        last_m = 0xFF;
        last_s = 0xFF;
        last_ms = 0xFF;
        init_flag = 1;

        // 固定显示的字符（前缀、分隔符）
        LCD_ShowString(1, 1, "SW:");
        LCD_ShowChar(1, 6, ':');
        LCD_ShowChar(1, 9, ':');
        LCD_ShowChar(1, 12, '.');
        LCD_ShowString(2, 1, "        ");

        // 强制显示初始零（关键：首次进入直接写零）
        LCD_ShowNum(1, 4, 0, 2);  // 时：00
        LCD_ShowNum(1, 7, 0, 2);  // 分：00
        LCD_ShowNum(1, 10, 0, 2); // 秒：00
        LCD_ShowNum(1, 13, 0, 1); // 毫秒十位：0
        LCD_ShowNum(1, 14, 0, 1); // 毫秒个位：0

        // 更新缓存为零，避免重复显示
        last_h = 0;
        last_m = 0;
        last_s = 0;
        last_ms = 0;
        return;  // 首次显示完成，直接返回
    }

    // 后续仅更新变化的数值
    if (stopwatch[0] != last_h) {
        LCD_ShowNum(1, 4, stopwatch[0], 2);
        last_h = stopwatch[0];
    }
    if (stopwatch[1] != last_m) {
        LCD_ShowNum(1, 7, stopwatch[1], 2);
        last_m = stopwatch[1];
    }
    if (stopwatch[2] != last_s) {
        LCD_ShowNum(1, 10, stopwatch[2], 2);
        last_s = stopwatch[2];
    }
    if (curr_ms != last_ms) {
        LCD_ShowNum(1, 13, curr_ms / 10, 1);
        LCD_ShowNum(1, 14, curr_ms % 10, 1);
        last_ms = curr_ms;
    }
}
//***************************************************************************

// 查看记录模式显示
// 查看记录模式显示（修复2：简化显示逻辑，确保稳定可见）
void show_records() 
{
    LCD_WriteCommand(0x01);  // 清屏，避免残留内容干扰
    // 第一行：记录编号+总记录数（清晰提示当前状态）
    LCD_ShowString(1, 1, "REC:");
    LCD_ShowNum(1, 5, view_idx + 1, 1);  // 记录从1开始，符合用户习惯
    LCD_ShowChar(1, 6, '/');
    LCD_ShowNum(1, 7, record_cnt, 1);    // 显示已保存的记录数

    // 第二行：显示记录内容或无记录提示（修复拼写错误：NO DATA）
    if(record_cnt > 0) 
		{
        // 有记录时显示时分秒，格式对齐
        LCD_ShowNum(2, 4, records[view_idx][0], 2);
        LCD_ShowChar(2, 6, ':');
        LCD_ShowNum(2, 7, records[view_idx][1], 2);
        LCD_ShowChar(2, 9, ':');
        LCD_ShowNum(2, 10, records[view_idx][2], 2);
    } 
		else 
		{
        // 无记录时明确提示，避免用户误以为异常
        LCD_ShowString(2, 4, "NO DATA");
    }

    // 固定操作提示（不随记录变化，避免闪烁）
//    if(record_cnt > 1) 
//		{
//        LCD_ShowString(1, 10, "K3U K4D");
//    }
//		    LCD_ShowString(2, 12, "K1=B");

}