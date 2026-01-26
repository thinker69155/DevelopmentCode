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
        flag_1s = 0;//1s标志位清零
        // 只要不在设置模式，日历就持续计时
        if(!set_flag) 
				{  // 仅当 set_flag=1（日历/倒计时设置模式）时暂停计时
            calendar[5]++;  // 秒
            if(calendar[5] >= 60) 
						{
                calendar[5] = 0;
                calendar[4]++;  // 分
                if(calendar[4] >= 60) 
								{
                    calendar[4] = 0;
                    calendar[3]++;  // 
                    if(calendar[3] >= 24) 
										{
                        calendar[3] = 0;
                        calendar[2]++;  // 日
                        // 月份天数边界
                        if((calendar[1]==4||calendar[1]==6||calendar[1]==9||calendar[1]==11) && calendar[2]>30) 
												{
                            calendar[2] = 1;
                            calendar[1]++;  // 月
                        }
												else if(calendar[2] > 31) 
												{
                            calendar[2] = 1;
                            calendar[1]++;  // 月
                        }
                        if(calendar[1] > 12) 
												{
                            calendar[1] = 1;
                            calendar[0]++;  // 年
                        }
                    }
                }
            }
        }
        
        // 倒计时更新（仅在倒计时模式且运行时更新）
        if(countdown_running && mode == COUNTDOWN) 
				{
            if(countdown[0]==0 && countdown[1]==0 && countdown[2]==0) 
						{
                countdown_running = 0;
                return;
            }
            countdown[2]--;
            if(countdown[2] >= 60) 
						{
                countdown[2] = 59;
                countdown[1]--;
                if(countdown[1] >= 60) 
								{									
                    countdown[1] = 59;
                    countdown[0]--;
                }
            }
        }
    }
}