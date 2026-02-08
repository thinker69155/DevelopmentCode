#include "stm32f10x.h"

void Timer_Init()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    //GPIO初始化
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x0f);//外部时钟
    //时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//外部时钟滤波使用，这里非外部可直接不分频
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
    TIM_TimeBaseInitStructure.TIM_Period=10-1;//1s
    TIM_TimeBaseInitStructure.TIM_Prescaler=1-1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
    //使能中断
    TIM_ClearFlag(TIM2,TIM_FLAG_Update);//手动清零中断标志位
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    //NVIC
    //分组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
    NVIC_Init(&NVIC_InitStructure);
    //启动定时器
    TIM_Cmd(TIM2,ENABLE);
}

uint16_t Timer_GetCounter()
{
    return TIM_GetCounter(TIM2);
}


/* void TIM2_IRQHandler()
{
    if (TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
    {


        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
    
} */









