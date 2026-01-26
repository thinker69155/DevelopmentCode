#include "globalvars.h"

/* -------------------------- 全局变量定义 -------------------------- */
// 蓝牙接收数据（初始值0）
uint8_t rxByte;              // 接收缓冲区（单字节）
char txMsg[] = "Hello STM32!\r\n";  // 要发送的测试字符串

// 小车状态初始化（默认全部停止）
uint8_t car_forward_flag = 0;
uint8_t car_backward_flag = 0;
uint8_t car_left_flag = 0;
uint8_t car_right_flag = 0;
uint8_t car_track_flag = 0;

// 机械臂状态初始化（默认全部停止）
uint8_t arm_left_flag = 0;
uint8_t arm_right_flag = 0;
uint8_t arm_up_flag = 0;
uint8_t arm_down_flag = 0;
uint8_t arm_grab_flag = 0;
uint8_t arm_release_flag = 0;

// 舵机初始
uint16_t servo1_current_angle = 500;    
uint16_t servo2_current_angle = 500;   
uint16_t servo3_current_angle = 500;    
uint16_t servo4_current_angle = 500;    

void GlobalVars_Init(void)
{
  // 复位所有状态标志
  car_forward_flag = 0;
  car_backward_flag = 0;
  car_left_flag = 0;
  car_right_flag = 0;
  car_track_flag = 0;
  
  arm_left_flag = 0;
  arm_right_flag = 0;
  arm_up_flag = 0;
  arm_down_flag = 0;
  arm_grab_flag = 0;
  arm_release_flag = 0;
  
  // 舵机复位到初始角度
 servo1_current_angle = 500;    
 servo2_current_angle = 500; 
 servo3_current_angle = 500;    
 servo4_current_angle = 500;   
}
