#include <REGX52.H>
#include "lcd1602.h"
#include "key.h"
#include <intrins.h>
#include "globalvars.h"
#include "delay.h"
#include "show.h"
#include "handlemode.h"
#include "modeswitch.h"
// 日历模式处理
void handle_calendar_mode(unsigned char key) 
{
    show_calendar();
    
    if(!set_flag) 
		{
        if(key == 1) 
				{
            mode_switch();
        } else if(key == 2) 
				{
            set_flag = 1;
        }
    } 
		else 
		{
        if(key == 2) 
				{
            select_pos = (select_pos + 1) % 6;
        } 
				else if(key == 3) 
				{
            calendar[select_pos]++;
            if(select_pos == 1 && calendar[1] > 12) calendar[1] = 1;
            if(select_pos == 2 && calendar[2] > 31) calendar[2] = 1;
            if(select_pos == 3 && calendar[3] > 23) calendar[3] = 0;
            if(select_pos >= 4 && calendar[select_pos] > 59) calendar[select_pos] = 0;
        } 
				else if(key == 4)
				{
            calendar[select_pos]--;
            if(select_pos == 1 && calendar[1] < 1) calendar[1] = 12;
            if(select_pos == 2 && calendar[2] < 1) calendar[2] = 31;
            if(select_pos == 3 && calendar[3] < 0) calendar[3] = 23;
            if(select_pos >= 4 && calendar[select_pos] < 0) calendar[select_pos] = 59;
        } 
				else if(key == 1) 
				{
            set_flag = 0;
            select_pos = 0;
            LCD_WriteCommand(0x01);
            show_calendar();
        }
    }
}
//***************************************************************************

// 倒计时模式处理
void handle_countdown_mode(unsigned char key) 
{
    show_countdown();
    
    if(set_flag) 
		{
        if(key == 1) 
				{
            set_flag = 0;
            select_pos = 0;
        } 
				else if(key == 2) 
				{
            select_pos = (select_pos + 1) % 3;
        } 
				else if(key == 3) 
				{
            countdown[select_pos]++;
            if(select_pos == 0 && countdown[0] > 23) countdown[0] = 0;
            if(select_pos >= 1 && countdown[select_pos] > 59) countdown[select_pos] = 0;
        } 
				else if(key == 4) 
				{
            countdown[select_pos]--;
            if(select_pos == 0 && countdown[0] < 0) countdown[0] = 23;
            if(select_pos >= 1 && countdown[select_pos] < 0) countdown[select_pos] = 59;
        }
    } 
		else 
		{
        if(key == 1) 
				{
            mode_switch();
        } 
				else if(key == 2)
				{
            if(countdown[0] > 0 || countdown[1] > 0 || countdown[2] > 0) 
						{
                countdown_running = !countdown_running;
            }
        } 
				else if(key == 3)	
				{
            set_flag = 1;
            select_pos = 0;
        }
    }
}
//***************************************************************************

// 秒表模式处理（核心：1ms中断直接驱动，无换算误差）
// 秒表模式处理（核心：1ms中断直接驱动，无换算误差）
void handle_stopwatch_mode(unsigned char key) 
{
    static unsigned int base_ms = 0;       // 基准毫秒数（启动时记录）
    static unsigned char refresh_cnt = 0;  // 刷新控制（每10ms刷新一次）
    static bit save_prompt_flag = 0;       // 保存成功提示标志
    static unsigned int prompt_cnt = 0;    // 提示计数（控制显示时长）

    // 1ms中断触发，更新毫秒数
    if (flag_1ms)		
		{
        flag_1ms = 0;  // 立即清零，防止重复处理
        
        if (stopwatch_running) 
				{
            // 当前毫秒 = 总毫秒 - 基准毫秒
            stopwatch[3] = ms_cnt - base_ms;

            // 毫秒进位到秒（1000ms = 1秒）
            if (stopwatch[3] >= 1000) 
						{
                stopwatch[3] -= 1000;  // 剩余毫秒
                base_ms += 1000;       // 基准同步
                stopwatch[2]++;        // 秒+1

                // 秒进位到分
                if (stopwatch[2] >= 60) 
								{
                    stopwatch[2] = 0;
                    stopwatch[1]++;    // 分+1

                    // 分进位到时
                    if (stopwatch[1] >= 60) 
										{
                        stopwatch[1] = 0;
                        stopwatch[0]++;  // 时+1
                        if (stopwatch[0] >= 24) stopwatch[0] = 0;
                    }
                }
            }
        }

        // 保存提示显示控制（显示500ms后自动消失）
        if (save_prompt_flag) 
				{
            prompt_cnt++;
            if (prompt_cnt >= 500) 
						{  // 500ms后关闭提示
                save_prompt_flag = 0;
                prompt_cnt = 0;
            }
        }

        // 每10ms刷新一次显示（平衡精度与视觉）
        refresh_cnt++;
        if (refresh_cnt >= 10) 
				{
            refresh_cnt = 0;
            show_stopwatch();
            // 显示保存成功提示（叠加在秒表显示上）
            if (save_prompt_flag) 
						{
                LCD_ShowString(2, 1, "Save OK!");
            } 
						else
						{
                LCD_ShowString(2, 1, "        ");  // 清除提示
            }
        }
    }

    // 按键操作时立即刷新
    if (key != 0) 
		{
        show_stopwatch();
    }

    // 按键处理
    switch(key)		
		{
        case 1:  // K1切换模式
            mode_switch();
            save_prompt_flag = 0;  // 切换模式时清除提示
            prompt_cnt = 0;
            break;
        case 2:  // K2启动/暂停
            if (!stopwatch_running) 
						{
                base_ms = ms_cnt;       // 记录当前总毫秒
                stopwatch[3] = 0;       // 从0开始计数
                stopwatch_running = 1;
            } 
						else 
						{
                stopwatch_running = 0;  // 暂停
            }
            save_prompt_flag = 0;  // 操作时清除提示
            prompt_cnt = 0;
            break;
        case 3:  // K3保存记录（修改：允许计时期间保存，循环覆盖）
            // 计时中或暂停时都可保存（根据需求调整，这里保留两种场景）
            {
                // 保存当前秒表时间（时/分/秒，忽略毫秒）
                records[record_idx][0] = stopwatch[0];
                records[record_idx][1] = stopwatch[1];
                records[record_idx][2] = stopwatch[2];

                // 更新记录数和下次保存索引（循环覆盖逻辑）
                if (record_cnt < 3)
								{
                    record_cnt++;  // 未存满3条，记录数+1
                }
                record_idx = (record_idx + 1) % 3;  // 索引循环（0→1→2→0）

                // 显示保存成功提示
                save_prompt_flag = 1;
                prompt_cnt = 0;
            }
            break;
        case 4:  // K4清零
            if (!stopwatch_running)
						{
                stopwatch[0] = stopwatch[1] = stopwatch[2] = 0;
                stopwatch[3] = 0;
                base_ms = ms_cnt;  // 基准同步当前时间
            }
            save_prompt_flag = 0;  // 操作时清除提示
            prompt_cnt = 0;
            break;
    }
}
//***************************************************************************

// 查看记录模式处理
// 查看记录模式处理（修复闪烁：仅按键时刷新显示）
void handle_view_record_mode(unsigned char key) 
{
    // 仅在有按键时才处理并刷新显示，无按键时不做任何操作
    if(key == 1) 
    {
        // 返回上一模式，清屏并切换
        LCD_WriteCommand(0x01);
        mode_switch();
    } 
    else if(key == 3 && record_cnt > 0)  // 修改：record_cnt>0即可切换
    {
        // 切换下一条记录，更新后刷新
        view_idx = (view_idx + 1) % record_cnt;
        show_records();  // 仅切换时刷新
    } 
    else if(key == 4 && record_cnt > 0)  // 修改：record_cnt>0即可切换
    {
        // 切换上一条记录，更新后刷新
        view_idx = (view_idx + record_cnt - 1) % record_cnt;
        show_records();  // 仅切换时刷新
    }
}