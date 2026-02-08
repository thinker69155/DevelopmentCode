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

uint8_t KeyNum;

int main()
{
    OLED_Init();

    OLED_ShowChar(1,1,'A');
    OLED_ShowString(1,3,"HelloWorld");
    OLED_ShowNum(2,1,12345,6);
    while (1)
    {
        
        
    }
}