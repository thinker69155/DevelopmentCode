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
#include "servo.h"
#include "Key.h"

uint16_t KeyNum;
float angle;

int main()
{
    OLED_Init();
    Servo_Init();
    Key_Init();

    OLED_ShowString(1,1,"Angle:");
    Servo_SetAngle(90); 

    while (1)
    {
        KeyNum=Key_GetNum();
        if (KeyNum==1)
        {
            angle+=30;
            if (angle>180)
            {
                angle=0;
            }
        }
       
         
         
    }
}
