//
// Created by c'z'w'x'k'n on 2026/2/15.
//

#include "Time.h"

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
/**
 * 修改时间参数函数
 * 配合Key.c文件Key_GetNum()使用
 * @param wei 需要修改的时间参数的位数，取值范围1~6，对应：年月日时分秒
 * @return 按下确认键，返回0
 */
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




//倒计时，秒表（计时，查看记录的时间）
uint8_t CountDown() {
    //按键1进入时间设置，默认都是0
    //按键3选择下一项，按键1,2为选中项加减
    //按键3按下3次后自动跳出设置
    //按键1开始，按键2暂停，按键3返回上一级菜单

}
uint8_t CountDown_Display() {
    //显示倒计时的时间，按键1旁边显示设置
}


uint8_t StopWatch() {
    //按键1开始，按键2暂停，按键3返回上一级菜单
}