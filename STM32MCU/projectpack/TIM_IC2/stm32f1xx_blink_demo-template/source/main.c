/*
 * ************************************************
 * 
 * STM32 blink demo
 * 
 * CPU:     STM32F103C8
 * PIN:     PA1
 * 
 * ************************************************
*/

#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "PWM.h"
#include "IC.h"

uint16_t i;

int main()
{
    OLED_Init();
    PWM_Init();
    IC_Init();

    OLED_ShowString(1,1,"Freq");
    OLED_ShowString(2,1,"Duty");

    PWM_SetPrescaler(7200-1);
    PWM_SetCompare1(80);

    while (1)
    {
        OLED_ShowNum(1,6,IC_GetFreq(),5);
        OLED_ShowNum(2,6,IC_GetDuty(),5);
    }
    

}
