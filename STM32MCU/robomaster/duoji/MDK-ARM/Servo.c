#include "headfile.h"
 
 
 
 
extern TIM_HandleTypeDef htim1;
 
 
 
//stm32f103c8t6每个TIM有四个独立通道
void Servo_Init()
{
	
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1); //启动PWM的输出
	
}
 
/*
*传入参数：舵机角度
*/
void Servo_SetAngle(int8_t angle)
{
	
	uint8_t CCR;
	
	CCR = (uint8_t)((angle+135)/1.8); //计算公式 当前ARR值为999 PSC为160 
	
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,CCR);
	
	
}
 
 
 
 