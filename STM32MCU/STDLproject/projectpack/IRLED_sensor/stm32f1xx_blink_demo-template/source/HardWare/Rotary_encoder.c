#include "stm32f10x.h"

void Rotary_encoder_Init()
{
    //时钟配置
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//打开GPIOB的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//打开AFIO的时钟
    //EXIT和NVIC的时钟默认打开，不用也不能进行单独配置
    //gpio初始化
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    //afio外部中断引脚选择配置
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
    //exti中断配置
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line=EXTI_Line0|EXTI_Line1;
    EXTI_InitStructure.EXTI_LineCmd=ENABLE;
    EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);
    //nvic 配置：打开外部中断通道，设置优先级
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//选择分组(程序中规定为同一种)
    
    NVIC_InitTypeDef NVIC_InitStructure0;
    NVIC_InitStructure0.NVIC_IRQChannel=EXTI0_IRQn;
    NVIC_InitStructure0.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStructure0.NVIC_IRQChannelPreemptionPriority=1;
    NVIC_InitStructure0.NVIC_IRQChannelSubPriority=1;
    NVIC_Init(&NVIC_InitStructure0);

    NVIC_InitTypeDef NVIC_InitStructure1;
    NVIC_InitStructure1.NVIC_IRQChannel=EXTI1_IRQn;
    NVIC_InitStructure1.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStructure1.NVIC_IRQChannelPreemptionPriority=1;
    NVIC_InitStructure1.NVIC_IRQChannelSubPriority=1;
    NVIC_Init(&NVIC_InitStructure1);
}

int16_t encoder_count=0;

int16_t Rotary_encoder_Get()
{
    int16_t temp;
    temp=encoder_count;
    encoder_count=0;
    return temp;
}


void EXTI0_IRQHandler()
{
    if (EXTI_GetITStatus(EXTI_Line0)==SET)
    {
        if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
        {
            encoder_count--;
        }
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
    
}
void EXTI1_IRQHandler()
{
    if (EXTI_GetITStatus(EXTI_Line1)==SET)
    {
        if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)
        {
            encoder_count++;
        }
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}
