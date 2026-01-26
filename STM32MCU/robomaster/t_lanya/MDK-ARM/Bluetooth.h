#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

#include "stm32f1xx_hal.h"

// 蓝牙指令枚举（4个运动+机械臂+红外）
typedef enum {
    CMD_UNKNOWN = 0,
    // 机械臂指令
    CMD_ARM_UP,
    CMD_ARM_GRAB,
    CMD_ARM_DOWN,
    CMD_ARM_RELEASE,
    CMD_ARM_LEFT,
    CMD_ARM_RIGHT,
    // 4个核心运动指令（对应4个Toggle按键）
    CMD_MOTOR_FWD,    // 前进
    CMD_MOTOR_BWD,    // 后退
    CMD_MOTOR_LEFT,   // 原地左转
    CMD_MOTOR_RIGHT,  // 原地右转
    // 红外循迹指令
    CMD_INFRARED_ON
} Bluetooth_CmdType;



// 外部变量声明
extern uint8_t rxByte;


// 函数声明
void Bluetooth_Init(void);
#endif