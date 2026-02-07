#include "stm32f10x.h"

void AD_Init()
{
    //打开总线时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);//12MHZ

    //GPIO
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;//模拟输入模式，ADC专属
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    //规则组的输入(第一个位置，写入通道0)
    ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);

    //初始化ADC
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_ContinuousConvMode=ENABLE;
    ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
    ADC_InitStructure.ADC_NbrOfChannel=1;//在非扫描模式下，实际上只能扫描第一个通道，是无效的
    ADC_InitStructure.ADC_ScanConvMode=DISABLE;
    ADC_Init(ADC1,&ADC_InitStructure);

    //中断和看门狗选择配置

    //ADC使能
    ADC_Cmd(ADC1,ENABLE);

    //配置校准
    ADC_ResetCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1)==SET);//判断校准完成
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1)==SET);

   


}

uint16_t AD_GetValue(uint8_t ADC_Channel)
{
    ADC_RegularChannelConfig(ADC1,ADC_Channel,1,ADC_SampleTime_55Cycles5);

    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
    while (ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
    return ADC_GetConversionValue(ADC1);
}