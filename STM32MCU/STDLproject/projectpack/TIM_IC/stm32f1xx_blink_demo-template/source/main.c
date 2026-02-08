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
    PWM_SetPrescaler(720-1);
    PWM_SetCompare1(50);

    while (1)
    {
        OLED_ShowNum(1,6,IC_GetFreq(),5);
    }
    

}
