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
#include "Rotary_encoder.h"

int16_t Num;

int main()
{
    OLED_Init();
    Rotary_encoder_Init();
    OLED_ShowString(1,1,"count");
    while (1)
    {
        Num+=Rotary_encoder_Get();
        OLED_ShowSignedNum(1,7,Num,5);
    }
}