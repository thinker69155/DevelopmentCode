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
#include "Encoder.h"

int16_t speed;

int main()
{
    OLED_Init();
    Encoder_Init();
    Timer_Init();

    OLED_ShowString(1,1,"speed:");
    
    while (1)
    {
        OLED_ShowSignedNum(2,7,speed,5);
        
    }
}
void TIM2_IRQHandler()
{
    if (TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
    {
        speed=Encoder_Get();
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
    
} 