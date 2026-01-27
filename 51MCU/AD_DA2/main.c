#include <REGX52.H>
#include "LCD1602.h"
#include "delay.h"
#include "XPT2046.h"

unsigned int ADValue;

void main()
{
    LCD_Init();
    LCD_ShowString(1,1,"ADJ");
    while (1)
    {
        ADValue=XPT2046_ReadAD(XPT2046_VBAT);
        LCD_ShowNum(2,1,ADValue,4);
        delay_ms(10);
    }
    
}