//
// Created by c'z'w'x'k'n on 2026/2/15.
//

#include "Show_time.h"

#include "Key.h"
#include "MyRTC.h"
#include "OLED.h"

void Show_time_Init() {
    MyRTC_Init();//RTC实时时钟初始化
    MyRTC_SetTime();
}

/**
 * 时间显示函数
 */
void Show_Time() {
    MyRTC_ReadTime();//读取全局数组中的时间
    OLED_ShowNum(1, 6, MyRTC_Time[0], 4);		//显示MyRTC_Time数组中的时间值，年
    OLED_ShowNum(1, 11, MyRTC_Time[1], 2);		//月
    OLED_ShowNum(1, 14, MyRTC_Time[2], 2);		//日
    OLED_ShowNum(2, 6, MyRTC_Time[3], 2);		//时
    OLED_ShowNum(2, 9, MyRTC_Time[4], 2);		//分
    OLED_ShowNum(2, 12, MyRTC_Time[5], 2);		//秒
}
uint8_t Change_Time(uint8_t wei) {
    uint8_t KeyNum_timeset=0;
    while (1) {
        KeyNum_timeset=Key_GetNum();
        if (KeyNum_timeset==1) {//按键1增加时间
            MyRTC_Time[wei-1]++;
            MyRTC_SetTime();//刷新时间
        }
        else if (KeyNum_timeset==2){//按键2降低时间
            MyRTC_Time[wei-1]--;
            MyRTC_SetTime();//刷新时间
        }
        else if (KeyNum_timeset==3) {//按键3退出函数，标志着完成修改
            return 0;
        }
        //刷新显示
    }
}