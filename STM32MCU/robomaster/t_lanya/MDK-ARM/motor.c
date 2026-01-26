#include "motor.h"
#include "gpio.h"

// 4个运动的状态初始化（默认均为停止）
Motor_StateTypeDef fwd_state = MOTOR_STATE_STOP;
Motor_StateTypeDef bwd_state = MOTOR_STATE_STOP;
Motor_StateTypeDef left_state = MOTOR_STATE_STOP;
Motor_StateTypeDef right_state = MOTOR_STATE_STOP;



// 停止所有电机（重置所有运动状态）
void Motor_Stop_All(void)
{
  Mecanum_Stop();
  fwd_state = MOTOR_STATE_STOP;
  bwd_state = MOTOR_STATE_STOP;
  left_state = MOTOR_STATE_STOP;
  right_state = MOTOR_STATE_STOP;
}

//void Motor_SetSpeed(uint16_t speed1,uint16_t speed2,uint16_t speed3, uint16_t speed4)
//{
//	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,speed1);//电机1（TIM2_CH1)
//	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,speed2);//电机2 (TIM2_CH2)
//	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,speed3);//电机3 (TIM3_CH1)
//	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,speed4);//电机4 (TIM3_CH2)
//}
//小车前进：所有电机正转
void Mecanum_Forward(uint16_t speed)
{
	//设置速度
//  Motor_SetSpeed(1000,1000,1000,1000);
	HAL_GPIO_WritePin(MOTOR1_IN1_Port,MOTOR1_IN1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTOR1_IN2_Port,MOTOR1_IN2_Pin,GPIO_PIN_RESET);
	//电机2正转
	HAL_GPIO_WritePin(MOTOR2_IN3_Port,MOTOR2_IN3_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR2_IN4_Port,MOTOR2_IN4_Pin,GPIO_PIN_SET);
	//电机3正转
	HAL_GPIO_WritePin(MOTOR3_IN1_Port,MOTOR3_IN1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR3_IN2_Port,MOTOR3_IN2_Pin,GPIO_PIN_SET);
	//电机4正转
	HAL_GPIO_WritePin(MOTOR4_IN3_Port,MOTOR4_IN3_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTOR4_IN4_Port,MOTOR4_IN4_Pin,GPIO_PIN_RESET);
	
}
//小车后退：所有电机反转
void Mecanum_Backward(uint16_t speed)
{
	//电机1反转
	HAL_GPIO_WritePin(MOTOR1_IN1_Port,MOTOR1_IN1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR1_IN2_Port,MOTOR1_IN2_Pin,GPIO_PIN_SET);
	//电机2反转
	HAL_GPIO_WritePin(MOTOR2_IN3_Port,MOTOR2_IN3_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTOR2_IN4_Port,MOTOR2_IN4_Pin,GPIO_PIN_RESET);
	//电机3反转
	HAL_GPIO_WritePin(MOTOR3_IN1_Port,MOTOR3_IN1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTOR3_IN2_Port,MOTOR3_IN2_Pin,GPIO_PIN_RESET);
	//电机4反转
	HAL_GPIO_WritePin(MOTOR4_IN3_Port,MOTOR4_IN3_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR4_IN4_Port,MOTOR4_IN4_Pin,GPIO_PIN_SET);
	//设置速度
//  Motor_SetSpeed(speed,speed,speed,speed);
}

//小车向左移动：1，3电机正转，2，4电机反转
void Mecanum_LeftMove(uint16_t speed)
{
	//电机1正转
	HAL_GPIO_WritePin(MOTOR1_IN1_Port,MOTOR1_IN1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR1_IN2_Port,MOTOR1_IN2_Pin,GPIO_PIN_SET);
	//电机2反转
	HAL_GPIO_WritePin(MOTOR2_IN3_Port,MOTOR2_IN3_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR2_IN4_Port,MOTOR2_IN4_Pin,GPIO_PIN_SET);
	//电机3正转
	HAL_GPIO_WritePin(MOTOR3_IN1_Port,MOTOR3_IN1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR3_IN2_Port,MOTOR3_IN2_Pin,GPIO_PIN_SET);
	//电机4反转
	HAL_GPIO_WritePin(MOTOR4_IN3_Port,MOTOR4_IN3_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTOR4_IN4_Port,MOTOR4_IN4_Pin,GPIO_PIN_RESET);
	//设置速度
//  Motor_SetSpeed(speed,speed,speed,speed);
}
//小车向右移动：1，3电机反转，2，4电机正转
void Mecanum_RightMove(uint16_t speed)
{
	//电机1正转
	HAL_GPIO_WritePin(MOTOR1_IN1_Port,MOTOR1_IN1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTOR1_IN2_Port,MOTOR1_IN2_Pin,GPIO_PIN_RESET);
	//电机2反转
	HAL_GPIO_WritePin(MOTOR2_IN3_Port,MOTOR2_IN3_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTOR2_IN4_Port,MOTOR2_IN4_Pin,GPIO_PIN_RESET);
	//电机3正转
	HAL_GPIO_WritePin(MOTOR3_IN1_Port,MOTOR3_IN1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTOR3_IN2_Port,MOTOR3_IN2_Pin,GPIO_PIN_RESET);
	//电机4反转
	HAL_GPIO_WritePin(MOTOR4_IN3_Port,MOTOR4_IN3_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR4_IN4_Port,MOTOR4_IN4_Pin,GPIO_PIN_SET);
	//设置速度
  //Motor_SetSpeed(speed,speed,speed,speed);
}

//小车原地右转：1，4电机正转，2，3电机反转
void Mecanum_TurnRight(uint16_t speed)
{
	//电机1正转
	HAL_GPIO_WritePin(MOTOR1_IN1_Port,MOTOR1_IN1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTOR1_IN2_Port,MOTOR1_IN2_Pin,GPIO_PIN_RESET);
	//电机2反转
	HAL_GPIO_WritePin(MOTOR2_IN3_Port,MOTOR2_IN3_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR2_IN4_Port,MOTOR2_IN4_Pin,GPIO_PIN_SET);
	//电机3反转
	HAL_GPIO_WritePin(MOTOR3_IN1_Port,MOTOR3_IN1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR3_IN2_Port,MOTOR3_IN2_Pin,GPIO_PIN_SET);
	//电机4正转
	HAL_GPIO_WritePin(MOTOR4_IN3_Port,MOTOR4_IN3_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR4_IN4_Port,MOTOR4_IN4_Pin,GPIO_PIN_SET);
	//设置速度
//  Motor_SetSpeed(speed,speed,speed,speed);
}
//小车原地左转：1，4电机反转，2，3电机正转
void Mecanum_TurnLeft(uint16_t speed)
{
	//电机1正转
	HAL_GPIO_WritePin(MOTOR1_IN1_Port,MOTOR1_IN1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTOR1_IN2_Port,MOTOR1_IN2_Pin,GPIO_PIN_RESET);
	//电机2正转
	HAL_GPIO_WritePin(MOTOR2_IN3_Port,MOTOR2_IN3_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTOR2_IN4_Port,MOTOR2_IN4_Pin,GPIO_PIN_RESET);
	//电机3正转
	HAL_GPIO_WritePin(MOTOR3_IN1_Port,MOTOR3_IN1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTOR3_IN2_Port,MOTOR3_IN2_Pin,GPIO_PIN_RESET);
	//电机4正转
	HAL_GPIO_WritePin(MOTOR4_IN3_Port,MOTOR4_IN3_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTOR4_IN4_Port,MOTOR4_IN4_Pin,GPIO_PIN_RESET);
	//设置速度
// Motor_SetSpeed(speed,speed,speed,speed);
}
//小车停止：所有电机停止转动
void Mecanum_Stop(void)
{
	HAL_GPIO_WritePin(MOTOR1_IN1_Port,MOTOR1_IN1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR1_IN2_Port,MOTOR1_IN2_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR2_IN3_Port,MOTOR2_IN3_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR2_IN4_Port,MOTOR2_IN4_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR3_IN1_Port,MOTOR3_IN1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR3_IN2_Port,MOTOR3_IN2_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR4_IN3_Port,MOTOR4_IN3_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR4_IN4_Port,MOTOR4_IN4_Pin,GPIO_PIN_RESET);
	//设置速度为0
//  Motor_SetSpeed(0,0,0,0);
}