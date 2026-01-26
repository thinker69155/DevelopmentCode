#include "globalvars.h"
#include "servo.h"
#include "Bluetooth.h"
#include <string.h>
#include "track.h"
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

void Servo_Init(void)
{
  // 启动4个舵机PWM（使用app_config.h的宏定义）
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
  Servo_ArmReset();  // 初始化后复位到默认角度  
}

/* 机械臂整体复位*/
/* 机械臂整体复位*/
void Servo_ArmReset(void)
{       
	// 舵机1（TIM2_CH1）：抓取角度 CCR=25（150°，夹紧）
  __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, 500);
 
  // 舵机2（TIM2_CH2）：抓取角度 CCR=22（132°）
  __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2, 1000);  
  // 舵机3（TIM2_CH3）：抓取角度 CCR=23（138°）
  __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, 1500);
  
  // 舵机4（TIM2_CH4）：抓取角度 CCR=24（144°）
  __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 1000);
	
}

// 固定步长定义：每次发送指令的转动角度（对应CCR值，10=约0.9°，可根据需求调整）
#define STEP_ANGLE 200 
// -------------------------- 机械臂控制函数（单次固定角度转动） --------------------------
// 机械臂左转：发送一次指令，左转固定角度（STEP_ANGLE）
void Arm_Left(void)
{
  // 未到左极限（500），则左转固定步长
  if (servo1_current_angle >= 500&&servo1_current_angle < 2500 )  // 预留步长避免超程
  {
    servo1_current_angle += 50;
    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, servo1_current_angle);
    
  }
  // 若剩余角度不足固定步长，则转到极限位置
  else  
  {
    servo1_current_angle = 500;
    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, servo1_current_angle);
    
  }
  // 已到极限，不动作
}

// 机械臂右转：发送一次指令，右转固定角度（STEP_ANGLE）
void Arm_Right(void)
{
  // 未到右极限（2500），则右转固定步长
  if (servo1_current_angle >500&&servo1_current_angle <=2500 )
  {
    servo1_current_angle -= 50;
    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, servo1_current_angle);
    
  }
  // 剩余角度不足，转到极限位置
  else 
  {
    servo1_current_angle = 2500;
    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, servo1_current_angle);
    
  }
}

// 机械臂上抬：发送一次指令，上抬固定角度（STEP_ANGLE）
void Arm_Up(void)
{
  // 未到上极限（2500），上抬固定步长
  if (servo3_current_angle < 2100)
  {
    servo3_current_angle += 50;
    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, servo3_current_angle);
    
  }
//  // 剩余角度不足，转到极限位置
//  else if (servo2_current_angle < 2500 && servo2_current_angle >= 2500 - STEP_ANGLE)
//  {
//    servo2_current_angle = 2500;
//    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2, servo2_current_angle);
//    
//  }
}

// 机械臂下降：发送一次指令，下降固定角度（STEP_ANGLE）
void Arm_Down(void)
{
  // 未到下极限（500），下降固定步长
  if (servo3_current_angle > 1500 )
  {
    servo3_current_angle -= 50;
    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, servo3_current_angle);
    
  }
//  // 剩余角度不足，转到极限位置
//  else if (servo2_current_angle > 500 && servo2_current_angle <= 500 + STEP_ANGLE)
//  {
//    servo2_current_angle = 500;
//    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2, servo2_current_angle);
//    
//  }
}

// 抓取：发送一次指令，夹紧固定角度（STEP_ANGLE）（最大夹紧CCR=1000）
void Arm_Grab(void)
{
  // 未到夹紧极限（1000），夹紧固定步长
  if (servo4_current_angle < 1500 )
  {
    servo4_current_angle +=100;
    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, servo4_current_angle);
    
  }
//  // 剩余角度不足，转到夹紧极限
//  else if (servo4_current_angle < 1300 && servo4_current_angle >= 1300 )
//  {
//    servo4_current_angle = 1300;
//    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, servo4_current_angle);
//    
//  }
}

// 松开：发送一次指令，松开固定角度（STEP_ANGLE）（最小松开CCR=500）
void Arm_Release(void)
{
  // 未到松开极限（500），松开固定步长
  if (servo4_current_angle > 800)
  {
    servo4_current_angle -= 100;
    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, servo4_current_angle);
    
  }
  // 剩余角度不足，转到松开极限
//  else if (servo4_current_angle > 900 && servo4_current_angle <= 900)
//  {
//    servo4_current_angle = 900;
//    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, servo4_current_angle);
    
//  }
}
