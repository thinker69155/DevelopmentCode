#include "Communciate.h"
#include "Flashlight.h"
#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Key.h"
#include "menu.h"
#include "MPU6050.h"
#include "Timer.h"
#include "MyRTC.h"
#include "Serial.h"
#include "Time_do.h"
#include "MyI2C.h"
int main(void) {
    //外设初始化函数
    Timer_Init();
    OLED_Init();
    Key_Init();
    MyI2C_Init();
    MPU6050_Init();
    Flashlight_LED_Init();
    MyRTC_Init();
    Communciate_Init();

    while (1) {
        OLED_Clear();
        OLED_Update();
        First_Page_do();
    }
}

//定时器中断
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        Key3_Tick();
        Key_Tick();
        StopWatch_Tick();
        Countdown_Tick();
        //Dino_Tick();
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
