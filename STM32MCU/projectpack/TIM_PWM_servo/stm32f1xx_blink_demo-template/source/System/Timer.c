#include "stm32f10x.h"

void Timer_Init()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    TIM_InternalClockConfig(TIM2);//内部时钟（默认）
    //时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//外部时钟滤波使用，这里非外部可直接不分频
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
    TIM_TimeBaseInitStructure.TIM_Period=10000-1;//1s
    TIM_TimeBaseInitStructure.TIM_Prescaler=7200-1;
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

/* void TIM2_IRQHandler()
{
    if (TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
    {


        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
    
} */









