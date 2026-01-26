#include "timeupdate.h"

#include <REGX52.H>
#include "lcd1602.h"
#include "key.h"
#include <intrins.h>
#include "globalvars.h"
#include "delay.h"
#include "show.h"
#include "handlemode.h"
#include "modeswitch.h"
// 时间更新处理
void handle_time_update() 
{
    if(flag_1s) 
		{
        flag_1s = 0;
        
        // 核心修改：移除 mode == CALENDAR 的判断，仅保留 set_flag == 0 的判断
        // 含义：所有模式下，只要不在设置模式（set_flag=0），日历就持续计时
        if(!set_flag) 
				{  // 仅当 set_flag=1（日历/倒计时设置模式）时暂停计时
            calendar[5]++;  // 秒递增
            if(calendar[5] >= 60) 
						{
                calendar[5] = 0;
                calendar[4]++;  // 分递增
                if(calendar[4] >= 60) 
								{
                    calendar[4] = 0;
                    calendar[3]++;  // 时递增
                    if(calendar[3] >= 24) 
										{
                        calendar[3] = 0;
                        calendar[2]++;  // 日递增
                        // 月份天数边界处理（保持原逻辑不变）
                        if((calendar[1]==4||calendar[1]==6||calendar[1]==9||calendar[1]==11) && calendar[2]>30) {
                            calendar[2] = 1;
                            calendar[1]++;  // 月递增
                        }
												else if(calendar[2] > 31) 
												{
                            calendar[2] = 1;
                            calendar[1]++;  // 月递增
                        }
                        if(calendar[1] > 12) 
												{
                            calendar[1] = 1;
                            calendar[0]++;  // 年递增
                        }
                    }
                }
            }
        }
        
        // 倒计时更新逻辑保持不变（仅在倒计时模式且运行时更新）
        if(countdown_running && mode == COUNTDOWN) {
            if(countdown[0]==0 && countdown[1]==0 && countdown[2]==0) {
                countdown_running = 0;
                return;
            }
            countdown[2]--;
            if(countdown[2] >= 60) {
                countdown[2] = 59;
                countdown[1]--;
                if(countdown[1] >= 60) {
                    countdown[1] = 59;
                    countdown[0]--;
                }
            }
        }
    }
}