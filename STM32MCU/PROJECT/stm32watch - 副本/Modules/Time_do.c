//
// Created by c'z'w'x'k'n on 2026/2/15.
//


#include "Drivers\Key\Key.h"
#include "Drivers\RTC\MyRTC.h"
#include "Drivers\OLED\OLED.h"

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
        if (KeyNum_timeset==0) {
            MyRTC_ReadTime();
            OLED_Clear();
            OLED_Printf(31,31,OLED_8X16,"%d",MyRTC_Time[wei-1]);//显示正在设置的时间
            OLED_Update();
        }
        else if (KeyNum_timeset==1) {//按键1增加时间
            MyRTC_Time[wei-1]++;
            OLED_Clear();
            OLED_Printf(31, 31, OLED_8X16, "%d", MyRTC_Time[wei-1]);
            MyRTC_SetTime();
            OLED_Update();
        }
        else if (KeyNum_timeset==2){//按键2降低时间
            MyRTC_Time[wei-1]--;
            OLED_Clear();
            OLED_Printf(31, 31, OLED_8X16, "%d", MyRTC_Time[wei-1]);
            MyRTC_SetTime();
            OLED_Update();
        }
        else if (KeyNum_timeset==3) {//按键3退出函数，标志着完成修改
            OLED_Clear();
            OLED_Update();
            return 0;
        }
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
void CountDown_Display() {
    //显示倒计时的时间，按键1旁边显示设置
    OLED_Printf(0,0,OLED_8X16,"<-");
    OLED_Printf(32,20,OLED_8X16,"%02d:%02d:%02d",CountDown_Time[0],CountDown_Time[1],CountDown_Time[2]);
    OLED_ShowString(0,16,"work",OLED_8X16);
    OLED_ShowString(0,32,"set",OLED_8X16);
}

uint8_t countdown_flag=0;
void Countdown_Tick(void)
{
    static uint16_t Count;
    Count++;
    // 每累计1000次Tick（对应正计时的1秒）执行一次倒计时逻辑
    if(Count >= 1000)
    {
        Count = 0;
        // 仅当计时标志开启且倒计时未结束时执行
        if(countdown_flag == 1 && (CountDown_Time[2] > 0 || CountDown_Time[1] > 0 || CountDown_Time[0] > 0))
        {
            CountDown_Time[2]--;  // 秒数减1
            // 秒数减到负数时，借位处理
            if(CountDown_Time[2] > 59)  // 无符号数减1后会溢出为255，因此判断>59即可识别借位
            {
                CountDown_Time[2] = 59;
                CountDown_Time[1]--;
                // 分钟借位处理
                if(CountDown_Time[1] > 59)
                {
                    CountDown_Time[1] = 59;
                    CountDown_Time[0]--;
                    // 小时借位处理
                    if(CountDown_Time[0] > 99)  // 小时范围0-99，溢出后重置为0（倒计时结束）
                    {
                        CountDown_Time[2] = 0;
                        CountDown_Time[1] = 0;
                        CountDown_Time[0] = 0;
                        // 可选：倒计时结束后自动关闭标志
                        // start_timing_flag = 0;
                    }
                }
            }
        }
    }
}
/**
 * 倒计时工作函数
 * @return 按下确认键，返回0
 */
uint8_t CountDown_Work() {
    OLED_Clear();
    OLED_Update();
    uint8_t KeyNum_countdown_work=0;
    while (1) {
       KeyNum_countdown_work=Key_GetNum();
        if (KeyNum_countdown_work==0) {
            //开始倒计时（计算，显示，刷新）
            CountDown_Display();
            OLED_ReverseArea(0,16,16,16);
            OLED_Update();
        }
        else if (KeyNum_countdown_work==1) {
            //开始倒计时（计算，显示，刷新）
            countdown_flag=1;
            OLED_ReverseArea(0,16,16,16);
            OLED_Update();
        }
        else if(KeyNum_countdown_work==2){
            //停止倒计时（计算，显示，刷新）
            countdown_flag=0;
            OLED_ReverseArea(0,16,16,16);
            OLED_Update();
        }
        else if(KeyNum_countdown_work==3){
            countdown_flag=0;
            CountDown_Time[0]=CountDown_Time[1]=CountDown_Time[2]=0;
            OLED_Clear();
            OLED_Update();
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
    OLED_Clear();
    OLED_Update();
    uint8_t wei=0;
    uint8_t KeyNum_countdown_set=0;
    while (1) {
        KeyNum_countdown_set=Key_GetNum();
        if (KeyNum_countdown_set==0) {
            OLED_Clear();
            OLED_Printf(32+(wei*24),4,OLED_8X16,"!");
            OLED_Printf(32,20,OLED_8X16,"%02d:%02d:%02d",CountDown_Time[0],CountDown_Time[1],CountDown_Time[2]);
            OLED_Update();
        }
        if (KeyNum_countdown_set==1) {
            //当前位加1
            CountDown_Time[wei]++;

        }
        else if(KeyNum_countdown_set==2){
            //当前位减1
            CountDown_Time[wei]--;

        }
        else if(KeyNum_countdown_set==3){
            wei++;
            if (wei==3) {//光标移动到第4格
                wei=0;
                OLED_Clear();
                OLED_Update();
                return 0;
            }
        }
    }
}
/////////////////////////////////////////////////////////////////////////
uint8_t hour,min,sec;
void StopWatch_DisPlay(void)
{
    OLED_Printf(32,20,OLED_8X16,"%02d:%02d:%02d",hour,min,sec);
    OLED_ShowString(8,44,"开始",OLED_8X16);
    OLED_ShowString(48,44,"停止",OLED_8X16);
}
uint8_t start_timing_flag;//1为开始，0为停止
/**
 * 停表计时函数
 * 该函数用于处理停表的计时逻辑。它基于一个静态计数器，每调用一次该函数，计数器加一。
 * 当计数器达到1000时，如果开始计时标志位被设置，则秒数增加，并根据需要更新分钟和小时。
 * 如果小时数超过99，则重置为0。
 */
void StopWatch_Tick(void)
{
    static uint16_t Count;
    Count++;
    if(Count>=1000)
    {
        Count=0;
        if(start_timing_flag==1)
        {
            sec++;
            if(sec>=60)
            {
                sec=0;
                min++;
                if(min>=60)
                {
                    min=0;
                    hour++;
                    if(hour>99)hour=0;
                }
            }
        }
    }
}
/**
 * 停表工作函数
 * key=1开始，key=2停止，key=3退出返回上一级
 * @return 按下确认键，返回0
 */
uint8_t StopWatch() {
    OLED_Clear();
    OLED_Update();
    uint8_t KeyNum_stopwatch=0;
    while (1) {
        //显示时分秒
        KeyNum_stopwatch=Key_GetNum();
        if(KeyNum_stopwatch==0) {
            OLED_Clear();
            StopWatch_DisPlay();
            OLED_Update();
        }
        else if (KeyNum_stopwatch==1) {
            start_timing_flag=1;
            OLED_ReverseArea(8,44,32,16);
            OLED_Update();
        }
        else if(KeyNum_stopwatch==2){
            start_timing_flag=0;
            OLED_ReverseArea(48,44,32,16);
            OLED_Update();
        }
        else if(KeyNum_stopwatch==3){
            hour=min=sec=0;
            OLED_Clear();
            OLED_Update();
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
    OLED_Printf(0,0,OLED_6X8,"%d-%d-%d",MyRTC_Time[0],MyRTC_Time[1],MyRTC_Time[2]);
    OLED_Printf(31,18,OLED_8X16,"%02d:%02d:%02d",MyRTC_Time[3],MyRTC_Time[4],MyRTC_Time[5]);
    OLED_ShowString(0,48,"菜单",OLED_8X16);
    OLED_ShowString(96,48,"设置",OLED_8X16);
}
