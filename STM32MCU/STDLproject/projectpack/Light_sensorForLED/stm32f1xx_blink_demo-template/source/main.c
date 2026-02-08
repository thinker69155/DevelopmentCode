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
#include "Light_sensor.h"

uint8_t KeyNum;

int main()
{
    LED_Init();
    Light_sensor_Init();
    while (1)
    {
        if (Light_sensor_Get()==0)
        {
            LED_Set(GPIO_Pin_1,1);
        }
        else 
        {
            LED_Set(GPIO_Pin_1,0);
        }
        
    }
}