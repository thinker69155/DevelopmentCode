#include "stm32f10x.h"

 

//LED初始化
void LED_Init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2);//置高电平，默认熄灭
}


//Led灯设置
void LED_Set(unsigned char LED,int set)
{
    if (set==0)
    {
        GPIO_ResetBits(GPIOA,LED);
    }
    else
    {
        GPIO_SetBits(GPIOA,LED);
    }  
}

//LED电平反转
void LED_Turn(unsigned char LED)
{
    if (GPIO_ReadOutputDataBit(GPIOA,LED)==0)
    {
        GPIO_SetBits(GPIOA,LED);
    }
    else
    {
        GPIO_ResetBits(GPIOA,LED);
    }
    
}