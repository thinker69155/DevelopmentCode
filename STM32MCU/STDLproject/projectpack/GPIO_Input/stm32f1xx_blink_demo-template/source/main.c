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
#include "LED.h"
#include "Delay.h"
#include "Key.h"

uint8_t KeyNum;

int main()
{
    LED_Init();
    Key_Init();

    while (1)
    {
        KeyNum=Key_GetNum();
        if (KeyNum==1)
        {
            LED_Turn(GPIO_Pin_1);
        }
        if (KeyNum==2)
        {
            LED_Turn(GPIO_Pin_2);
        }
        
    }
}