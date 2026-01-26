#include "Track.h"
#include "motor.h"
#include "main.h"
#include "usart.h"
#include "gpio.h" 
#include "stm32f1xx_hal.h" 
#include "globalvars.h"



// 循迹（toggle：启动/停止循迹）
void Track_Toggle(void)
{
  car_track_flag = !car_track_flag;
  if (!car_track_flag)
  {
    // 电机停转
   Motor_Stop_All();
  }
}

void Tracking(void)
{
		// 读取四个传感器状态
    uint8_t s1 = HAL_GPIO_ReadPin(sensor1_GPIO_Port, sensor1_Pin);
    uint8_t s2 = HAL_GPIO_ReadPin(sensor2_GPIO_Port, sensor2_Pin);
    uint8_t s3 = HAL_GPIO_ReadPin(sensor3_GPIO_Port, sensor3_Pin);
    uint8_t s4 = HAL_GPIO_ReadPin(sensor4_GPIO_Port, sensor4_Pin);
		if (!car_track_flag) 
		return;  // 循迹未启动，直接返回
				
			/////////////////////////////////// 左转
    if (s1 ==1 )  // 左传感器s1触发高电平
    {
        while (1)
        {
            Mecanum_LeftMove(MOTOR_DEFAULT_SPEED);  
            // 重新读取传感器，判断是否回到直行状态
            s1 = HAL_GPIO_ReadPin(sensor1_GPIO_Port, sensor1_Pin);
            s2 = HAL_GPIO_ReadPin(sensor2_GPIO_Port, sensor2_Pin);
            s3 = HAL_GPIO_ReadPin(sensor3_GPIO_Port, sensor3_Pin);
            s4 = HAL_GPIO_ReadPin(sensor4_GPIO_Port, sensor4_Pin);
//             HAL_UART_Transmit_IT(&huart1, &rxByte, 1);

	
            // 退出条件：回到正常直行状态
            if (s1 ==0 && s2 == 1 && s3 == 1 && s4 == 0)
            {
                break;  
            }
        }
    }
		
    /////////////////////////////////// 右转
    else if (s4 == 1)  // 右传感器s4触发高电平
    {
        while (1)
        {
            Mecanum_RightMove(MOTOR_DEFAULT_SPEED); 
            // 重新读取传感器，判断是否回到直行状态
            s1 = HAL_GPIO_ReadPin(sensor1_GPIO_Port, sensor1_Pin);
            s2 = HAL_GPIO_ReadPin(sensor2_GPIO_Port, sensor2_Pin);
            s3 = HAL_GPIO_ReadPin(sensor3_GPIO_Port, sensor3_Pin);
            s4 = HAL_GPIO_ReadPin(sensor4_GPIO_Port, sensor4_Pin);
//             HAL_UART_Transmit_IT(&huart1, &rxByte, 1);
            // 退出条件：回到正常直行状态
            if (s1 == 0 && s2 == 1 && s3 == 1 && s4 == 0)
            {
                break;  
            }
        }
    }
		else if (s1 ==1&&s4 == 1)
		{
			while (1)
        {
						Mecanum_RightMove(MOTOR_DEFAULT_SPEED);            // 重新读取传感器，判断是否回到直行状态
            s1 = HAL_GPIO_ReadPin(sensor1_GPIO_Port, sensor1_Pin);
            s2 = HAL_GPIO_ReadPin(sensor2_GPIO_Port, sensor2_Pin);
            s3 = HAL_GPIO_ReadPin(sensor3_GPIO_Port, sensor3_Pin);
            s4 = HAL_GPIO_ReadPin(sensor4_GPIO_Port, sensor4_Pin);
            
            // 退出条件：回到正常直行状态
            if (s1 == 0 && s2 == 1 && s3 == 1 && s4 == 0)
            {
                break;  
            }
        }	
		}		
    /////////////////////////////////// 直行
    else if(s1 ==0 && s2 == 1 && s3 == 1 && s4 == 0)
    {
        Mecanum_Backward(MOTOR_DEFAULT_SPEED);
    } 
		else if(s1 ==0 && s2 == 0 && s3 == 0 && s4 == 0)
		{
			Mecanum_Backward(MOTOR_DEFAULT_SPEED);
		}	
			
}
/////////////////////////////////////////////////////////////////////////
