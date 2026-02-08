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
#include "Key.h"
#include "Motor.h"

uint16_t KeyNum;
float angle;

int main()
{
    OLED_Init();
    Motor_Init();
    Motor_SetSpeed(50);

    while (1)
    {
        
       
         
         
    }
}
