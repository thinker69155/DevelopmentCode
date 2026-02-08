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
#include "OLED.h"
#include "IRLED_sensor.h"

uint8_t KeyNum;

int main()
{
    OLED_Init();
    IRLED_sensor_Init();
    OLED_ShowString(1,1,"count");
    while (1)
    {
        OLED_ShowNum(1,7,IRLED_sensor_Get(),5);
        
    }
}