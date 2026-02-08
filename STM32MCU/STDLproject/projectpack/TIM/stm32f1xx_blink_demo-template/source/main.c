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

uint16_t Num=0;

int main()
{
    OLED_Init();
    Timer_Init();
    
    OLED_ShowString(1,1,"Num");
    
    while (1)
    {
        OLED_ShowNum(1,5,Num,5);
        OLED_ShowNum(2,5,TIM_GetCounter(TIM2),5);//看计数器中的值
    }
}
void TIM2_IRQHandler()
{
    if (TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
    {
        Num++;
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
    
} 