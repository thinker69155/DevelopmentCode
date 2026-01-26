#ifndef __GLOBALVARS_H
#define __GLOBALVARS_H

#include "stm32f1xx_hal.h"  

/* -------------------------- 全局变量声明 -------------------------- */
// 蓝牙模块：接收数据缓存（1字节）
extern uint8_t rxByte;              // 接收缓冲区（单字节）
extern char txMsg[];
#include "main.h"

// 小车运动状态标志（0=停止，1=运行）
extern uint8_t car_forward_flag;   // 向前
extern uint8_t car_backward_flag;  // 向后
extern uint8_t car_left_flag;      // 向左
extern uint8_t car_right_flag;     // 向右
extern uint8_t car_track_flag;     // 循迹

// 机械臂状态标志（0=停止，1=运行）
extern uint8_t arm_left_flag;      // 机械臂左转
extern uint8_t arm_right_flag;     // 机械臂右转
extern uint8_t arm_up_flag;        // 机械臂上抬
extern uint8_t arm_down_flag;      // 机械臂下降
extern uint8_t arm_grab_flag;      // 抓取
extern uint8_t arm_release_flag;   // 松开

// 舵机当前角度（记录位置，停止后保持）
// 舵机初始
extern uint16_t servo1_current_angle;    
extern uint16_t servo2_current_angle;   
extern uint16_t servo3_current_angle;    
extern uint16_t servo4_current_angle;    

// 初始化全局变量
void GlobalVars_Init(void);

#define MOTOR_DEFAULT_SPEED 1000  // 电机速度

#endif /* __GLOBALVARS_H */