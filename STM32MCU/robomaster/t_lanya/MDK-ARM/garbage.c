//// -------------------------- 机械臂控制函数 --------------------------
//// 机械臂左转（toggle：启动/停止左转，角度渐变）
//void Arm_Left_Toggle(void)
//{
//  arm_left_flag = !arm_left_flag;
//  arm_right_flag = 0;  // 关闭右转，避免冲突
//}

//// 机械臂右转（toggle）
//void Arm_Right_Toggle(void)
//{
//  arm_right_flag = !arm_right_flag;
//  arm_left_flag = 0;  // 关闭左转，避免冲突
//}

//// 机械臂上抬（toggle）
//void Arm_Up_Toggle(void)
//{
//  arm_up_flag = !arm_up_flag;
//  arm_down_flag = 0;  // 关闭下降，避免冲突
//}

//// 机械臂下降（toggle）
//void Arm_Down_Toggle(void)
//{
//  arm_down_flag = !arm_down_flag;
//  arm_up_flag = 0;  // 关闭上抬，避免冲突
//}

//// 抓取（toggle：一次发送夹紧，再次发送保持当前状态停止动作）
//void Arm_Grab_Toggle(void)
//{
//  arm_grab_flag = !arm_grab_flag;
//  arm_release_flag = 0;
//  if (arm_grab_flag)
//  {
//    // 启动抓取
//    servo4_current_angle = 1000;
//    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, servo4_current_angle);
//  }
//  // 停止抓取：保持当前夹紧状态，不松开
//}

//// 松开（toggle：一次发送松开，再次发送保持松开状态）
//void Arm_Release_Toggle(void)
//{
//  arm_release_flag = !arm_release_flag;
//  arm_grab_flag = 0;
//  if (arm_release_flag)
//  {
//    // 启动松开：抓手角度渐变到松开（CCR=5）
//    servo4_current_angle = 500;
//    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, servo4_current_angle);
//  }
//  // 停止松开：保持当前松开状态
//}

//// 机械臂角度渐变
//void Arm_Run_Loop(void)
//{
//  // 左转
//  if (arm_left_flag && servo1_current_angle > 500)
//  {
//    servo1_current_angle -= 10;
//    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, servo1_current_angle);
//  }
//  else if (arm_left_flag && servo1_current_angle <= 2500/*500？*/)
//  {
//    arm_left_flag = 0;  // 到达极限自动停止
//  }
//  
//  // 右转
//  if (arm_right_flag && servo1_current_angle < 2500)
//  {
//    servo1_current_angle += 10;
//    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, servo1_current_angle);
//  }
//  else if (arm_right_flag && servo1_current_angle >= 500)
//  {
//    arm_right_flag = 0;  // 到达极限，自动停止
//  }
//  
//  // 上抬
//  if (arm_up_flag && servo2_current_angle < 2500)
//  {
//    servo2_current_angle += 10;
//    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2, servo2_current_angle);
//  }
//  else if (arm_up_flag && servo2_current_angle >= 500)
//  {
//    arm_up_flag = 0;
//  }
//  
//  // 下降
//  if (arm_down_flag && servo2_current_angle > 500)
//  {
//    servo2_current_angle -= 10;
//    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2, servo2_current_angle);
//  }
//  else if (arm_down_flag && servo2_current_angle <= 2500)
//  {
//    arm_down_flag = 0;
//  }
//  
////  HAL_Delay(20);  // 控制舵机转动速度
//}
