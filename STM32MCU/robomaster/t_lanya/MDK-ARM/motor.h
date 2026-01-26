#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H
#include"stm32f1xx_hal.h"
//电机方向引脚宏定义
#define MOTOR1_IN1_Port GPIOA
#define MOTOR1_IN1_Pin GPIO_PIN_15
#define MOTOR1_IN2_Port GPIOA
#define MOTOR1_IN2_Pin GPIO_PIN_11

#define MOTOR2_IN3_Port GPIOC
#define MOTOR2_IN3_Pin GPIO_PIN_13
#define MOTOR2_IN4_Port GPIOC
#define MOTOR2_IN4_Pin GPIO_PIN_14
#define MOTOR3_IN1_Port GPIOB
#define MOTOR3_IN1_Pin GPIO_PIN_3
#define MOTOR3_IN2_Port GPIOA
#define MOTOR3_IN2_Pin GPIO_PIN_12

#define MOTOR4_IN3_Port GPIOC
#define MOTOR4_IN3_Pin GPIO_PIN_15
#define MOTOR4_IN4_Port GPIOB
#define MOTOR4_IN4_Pin GPIO_PIN_0

// 运动状态枚举（记录每个动作的启停状态）
typedef enum {
    MOTOR_STATE_STOP = 0,  // 停止状态
    MOTOR_STATE_RUN        // 运行状态
} Motor_StateTypeDef;

// 4个运动的状态（分别记忆每个动作的启停）
extern Motor_StateTypeDef fwd_state, bwd_state, left_state, right_state;

void Motor_Stop_All(void);  // 停止所有电机void 

//PWM定时器句柄外部声明
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

//所有电机控制函数声明
void Mecanum_Forward(uint16_t speed);
void Mecanum_Backward(uint16_t speed);
void Mecanum_LeftMove(uint16_t speed);
void Mecanum_RightMove(uint16_t speed);
void Mecanum_TurnLeft(uint16_t speed);
void Mecanum_TurnRight(uint16_t speed);
void Mecanum_Stop(void);
#endif

