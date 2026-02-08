#include "stm32f10x.h"
#include "Delay.h"

uint16_t CountSensor=0;

void IRLED_sensor_Init()
{
    //时钟配置
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//打开GPIOB的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//打开AFIO的时钟
    //EXIT和NVIC的时钟默认打开，不用也不能进行单独配置
    //gpio初始化
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    //afio外部中断引脚选择配置
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
    //exti中断配置：14线路，下降沿触发，中断模式
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line=EXTI_Line14;
    EXTI_InitStructure.EXTI_LineCmd=ENABLE;
    EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);
    //nvic 配置：打开外部中断通道，设置优先级
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//选择分组(程序中规定为同一种)
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel=EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
    NVIC_Init(&NVIC_InitStructure);

}

uint16_t IRLED_sensor_Get()
{
    return CountSensor;
}



//中断函数
void EXTI15_10_IRQHandler()
{
    if(EXTI_GetITStatus(EXTI_Line14)==SET)
    {
        Delay_ms(20);
        if(EXTI_GetITStatus(EXTI_Line14)==SET)
        {
            CountSensor++;
        }
        /* Delay_ms(1); */
        
        EXTI_ClearITPendingBit(EXTI_Line14);
    }
}