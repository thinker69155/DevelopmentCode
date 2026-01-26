 #include "bluetooth.h"
#include "servo.h"    // 舵机功能函数头文件
#include "motor.h"    // 电机功能函数头文件
#include "globalvars.h" // 全局变量
#include "track.h"
#include "usart.h"





// 字符指令枚举
static Bluetooth_CmdType Bluetooth_ParseCmd(uint8_t rx_char)
{
  switch(rx_char)
  {
    case 'a': return CMD_ARM_UP;
    case 'b': return CMD_ARM_GRAB;
    case 'c': return CMD_ARM_DOWN;		
    case 'd': return CMD_ARM_RELEASE;
		case 'e': return CMD_ARM_LEFT;			
		case 'g': return CMD_ARM_RIGHT;		
    case 'f': return CMD_MOTOR_FWD;
    case 'k': return CMD_MOTOR_BWD;
    case 'l': return CMD_MOTOR_LEFT;
    case 'r': return CMD_MOTOR_RIGHT;
    case 't': return CMD_INFRARED_ON;
    default:  return CMD_UNKNOWN;
  }
}

// 蓝牙初始化
void Bluetooth_Init(void)
{
  // 启动 USART1 中断接收
  HAL_UART_Receive_IT(&huart1, &rxByte, 1);
	
}

// 串口接收中断回调函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart == &huart1) 
  {
    // 1. 解析接收的字符为指令
    Bluetooth_CmdType cmd = Bluetooth_ParseCmd(rxByte);

    // 2. 根据指令直接调用对应功能函数
    if (cmd != CMD_UNKNOWN)
    {
      switch(cmd)
      {
        // 机械臂操作
        case CMD_ARM_UP:    Arm_Up();    break;//机械臂上升
        case CMD_ARM_GRAB:     Arm_Grab();     break;//机械臂抓取
        case CMD_ARM_RELEASE:     Arm_Release();     break;//机械臂释放				
        case CMD_ARM_DOWN:  Arm_Down();  break;//机械臂放下
				case CMD_ARM_LEFT:		 Arm_Left(); 		break;//机械臂左转
				case CMD_ARM_RIGHT:		 Arm_Right(); 		break;//机械臂右转
        // 电机操作
        case CMD_MOTOR_FWD:  // 前进
        if (fwd_state == MOTOR_STATE_STOP)
        {
          Motor_Stop_All();  
          Mecanum_Forward(MOTOR_DEFAULT_SPEED);
          fwd_state = MOTOR_STATE_RUN;  // 标记为运行状态
        }
        else
        {
          Motor_Stop_All();  // 按第二次则停止
        }
        break;

      case CMD_MOTOR_BWD:  
        if (bwd_state == MOTOR_STATE_STOP)
        {
          Motor_Stop_All();
          Mecanum_Backward(MOTOR_DEFAULT_SPEED);
          bwd_state = MOTOR_STATE_RUN;
        }
        else
        {
          Motor_Stop_All();
        }
        break;

      case CMD_MOTOR_LEFT:  
        if (left_state == MOTOR_STATE_STOP)
        {
          Motor_Stop_All();
          Mecanum_LeftMove(MOTOR_DEFAULT_SPEED);
          left_state = MOTOR_STATE_RUN;
        }
        else
        {
          Motor_Stop_All();
        }
        break;

      case CMD_MOTOR_RIGHT:  
        if (right_state == MOTOR_STATE_STOP)
        {
          Motor_Stop_All();
          Mecanum_RightMove(MOTOR_DEFAULT_SPEED);
          right_state = MOTOR_STATE_RUN;
        }
        else
        {
          Motor_Stop_All();
        }
        break;

//        // 红外循迹操作
        case CMD_INFRARED_ON: Track_Toggle();   break;

        default: break;
      }
    }

    // 3. 重新启动中断接收（循环接收下一个指令）
    HAL_UART_Receive_IT(&huart1, &rxByte, 1);
		
  }
}