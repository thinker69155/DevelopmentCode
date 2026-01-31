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

/* int main()
{
    //led灯闪烁
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//打开时钟
    //设置GPIO的初始化
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);                                                                               
    while (1)
    {
        GPIO_WriteBit(GPIOA,GPIO_Pin_6,0);//点亮LED
        Delay_ms(1000);
        GPIO_WriteBit(GPIOA,GPIO_Pin_6,1);//熄灭
        Delay_ms(1000);
    }
    
    
} */

int main()
{
    //LED流水灯
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//打开时钟
    
    //初始化GPIO
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_All;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    while (1)
    {
        unsigned char i;
        for ( i = 0; i < 8; i++)
        {
            GPIO_Write(GPIOA,~(0x0001<<(i)));
            Delay_ms(500);
        }
        if (i==8)
        {
            i=0;
        }
    }
  
}
