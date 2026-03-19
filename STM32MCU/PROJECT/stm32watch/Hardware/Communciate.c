//
// Created by c'z'w'x'k'n on 2026/2/15.
//

#include "Communciate.h"
#include "Serial.h"
#include "OLED.h"
#include "string.h"
#include "Key.h"
void Communciate_Init(void) {
    Serial_Init();//串口通信初始化
}
uint8_t Communciate(void) {
    OLED_Clear();
    OLED_Update();
    uint8_t KeyNum_communciate=0;
    while (1) {
        KeyNum_communciate=Key_GetNum();
        if (KeyNum_communciate!=3) {
            if (Serial_RxFlag == 0) {
                OLED_Clear();
                /*显示静态字符串*/
                OLED_Printf(0, 0,OLED_8X16, "接收");
                OLED_Printf(0, 32, OLED_8X16, "发送");
                OLED_Update();
            }
            else if (Serial_RxFlag == 1)		//如果接收到数据包
            {
                OLED_Clear();
                OLED_ShowString(0, 16, Serial_RxPacket,OLED_8X16);				//OLED清除指定位置，并显示接收到的数据包
                OLED_Update();
                /*将收到的数据包与预设的指令对比，以此决定将要执行的操作*/
                if (strcmp(Serial_RxPacket, "LED_ON") == 0)			//如果收到LED_ON指令
                {
                    Serial_SendString("LED_ON_OK\r\n");				//串口回传一个字符串LED_ON_OK
                    OLED_Clear();
                    OLED_Printf(0, 0,OLED_8X16, "接收");
                    OLED_Printf(0, 32, OLED_8X16, "发送");
                    OLED_Printf(0,48,OLED_8X16,"LED_ON_OK");				//OLED清除指定位置，并显示LED_ON_OK
                    OLED_Update();
                }
                else if (strcmp(Serial_RxPacket, "LED_OFF") == 0)	//如果收到LED_OFF指令
                {
                    Serial_SendString("LED_OFF_OK\r\n");			//串口回传一个字符串LED_OFF_OK
                    OLED_Clear();
                    OLED_Printf(0, 0,OLED_8X16, "接收");
                    OLED_Printf(0, 32, OLED_8X16, "发送");
                    OLED_Printf(0,48,OLED_8X16,"LED_OFF_OK");			//OLED清除指定位置，并显示LED_OFF_OK
                    OLED_Update();
                }
                else						//上述所有条件均不满足，即收到了未知指令
                {
                    Serial_SendString("ERROR_COMMAND\r\n");			//串口回传一个字符串ERROR_COMMAND
                    OLED_Clear();
                    OLED_Printf(0, 0,OLED_8X16, "接收");
                    OLED_Printf(0, 32, OLED_8X16, "发送");

                    OLED_Printf(0,48,OLED_8X16,"ERROR_COMMAND");			//OLED清除指定位置，并显示ERROR_COMMAND
                    OLED_Update();
                }
                Serial_RxFlag = 0;			//处理完成后，需要将接收数据包标志位清零，否则将无法接收后续数据包
            }
        }
        else {
            return 0;
        }
    }
}