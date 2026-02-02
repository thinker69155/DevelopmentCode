#include "stm32f10x.h"

void PWM_Init()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    TIM_InternalClockConfig(TIM2);//内部时钟（默认）
    //GPIO初始化
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2);//置高电平，默认熄灭


    //时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//外部时钟滤波使用，这里非外部可直接不分频
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
    TIM_TimeBaseInitStructure.TIM_Period=20000-1;//1s   //ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler=72-1;     //PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
    
    //初始化输出比较单元
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse=0;     //CCR
    TIM_OC2Init(TIM2,&TIM_OCInitStructure);

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

void PWM_SetCompare2(uint16_t Compare)
{
    TIM_SetCompare2(TIM2,Compare);
}








