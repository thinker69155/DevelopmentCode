//
// Created by c'z'w'x'k'n on 2026/2/15.
//

#include "Time.h"
#include "Key.h"
#include "MyRTC.h"
#include "OLED.h"

/**
 * RTC时钟初始化函数
 */
void Show_time_Init() {
    MyRTC_Init();//RTC实时时钟初始化
    MyRTC_SetTime();
}

/**
 * 修改时间参数函数
 * 配合Key.c文件Key_GetNum()使用
 * @param wei 需要修改的时间参数的位数，取值范围1~6，对应：年月日时分秒
 * @return 按下确认键，返回0
 */
uint8_t Change_First_Page_Time(uint8_t wei) {
    uint8_t KeyNum_timeset=0;
    while (1) {
        KeyNum_timeset=Key_GetNum();
        if (KeyNum_timeset==1) {//按键1增加时间
            MyRTC_Time[wei-1]++;
        }
        else if (KeyNum_timeset==2){//按键2降低时间
            MyRTC_Time[wei-1]--;
        }
        else if (KeyNum_timeset==3) {//按键3退出函数，标志着完成修改
            return 0;
        }
        MyRTC_ReadTime();
        OLED_Clear();
        OLED_Printf(0,0,OLED_6X8,"%d",MyRTC_Time[wei]);//显示正在设置的时间
        OLED_Update();
    }
}
/**
 * 修改倒计时时间参数函数
 * 配合Key.c文件Key_GetNum()使用
 * @param wei 需要修改的时间参数的位数，取值范围1~3，对应：时分秒
 * @return 按下确认键，返回0
 */
uint8_t Change_CountDown_Time(uint8_t *CountDown_Time,uint8_t wei) {
    uint8_t KeyNum_timeset=0;
    while (1) {
        KeyNum_timeset=Key_GetNum();
        if (KeyNum_timeset==1) {//按键1增加时间
            CountDown_Time[wei-1]++;
        }
        else if (KeyNum_timeset==2){//按键2降低时间
            CountDown_Time[wei-1]--;
        }
        else if (KeyNum_timeset==3) {//按键3退出函数，标志着完成修改
            return 0;
        }
        //刷新显示
    }
}
///////////////////////////////////////////////////////////////////////
uint8_t CountDown_Time[]={0,0,0};
/**
 * 倒计时工作函数
 * @return 按下确认键，返回0
 */
uint8_t CountDown_Work() {
    while (1) {
       uint8_t KeyNum_countdown_work=Key_GetNum();
        if (KeyNum_countdown_work==1) {
            //开始倒计时（计算，显示，刷新）
        }
        else if(KeyNum_countdown_work==2){
            //停止倒计时（计算，显示，刷新）
        }
        else if(KeyNum_countdown_work==3){
            return 0;
        }
    }
}
/**
 * 倒计时设置函数
 * 默认选中第一位，共可选择3位：时分秒
 * @return 按下确认键，返回0
 */
uint8_t CountDown_Set() {
    uint8_t countdown_set_flag=0;
    while (1) {
        uint8_t KeyNum_countdown_set=Key_GetNum();
        if (KeyNum_countdown_set==1) {
            //当前位加1
        }
        else if(KeyNum_countdown_set==2){
            //当前位减1
        }
        else if(KeyNum_countdown_set==3){
            countdown_set_flag++;
            if (countdown_set_flag==3) {//光标移动到第4格
                return 0;
            }
        }
    }
}
/////////////////////////////////////////////////////////////////////////
uint8_t StopWatch_Time[]={0,0,0,0};
/**
 * 停表工作函数
 * key=1开始，key=2停止，key=3退出返回上一级
 * @return 按下确认键，返回0
 */
uint8_t StopWatch() {
    while (1) {
        //显示时分秒
        uint8_t KeyNum_stopwatch=Key_GetNum();
        if (KeyNum_stopwatch==1) {
            //开始
        }
        else if(KeyNum_stopwatch==2){
            //停止
        }
        else if(KeyNum_stopwatch==3){
            return 0;
            }
    }
}
//对外显示函数////////////////////////////////////////////////////////////////////
/**
 * 时间显示函数
 */
void Show_Time() {
    MyRTC_ReadTime();//读取全局数组中的时间
    MyRTC_ReadTime();
    OLED_Printf(0,0,OLED_6X8,"%d-%d-%d",MyRTC_Time[0],MyRTC_Time[1],MyRTC_Time[2]);
    OLED_Printf(16,16,OLED_12X24,"%02d:%02d:%02d",MyRTC_Time[3],MyRTC_Time[4],MyRTC_Time[5]);
    OLED_ShowString(0,48,"菜单",OLED_8X16);
    OLED_ShowString(96,48,"设置",OLED_8X16);
}
