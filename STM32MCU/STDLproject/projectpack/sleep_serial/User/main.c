#include "Delay.h"
#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Serial.h"
uint8_t RxData;
int main(void) {
    /*模块初始化*/
    OLED_Init(); //OLED初始化
    OLED_ShowString(1,1,"RxData");
    Serial_Init();

    while (1) {
        if (Serial_GetRxFlag()==1) {
            RxData=Serial_GetRxData();
            Serial_SendByte(RxData);
            OLED_ShowHexNum(1,8,RxData,2);
        }

        OLED_ShowString(2,1,"Running");
        Delay_ms(100);
        OLED_ShowString(2,1,"          ");
        Delay_ms(100);

        __WFI();//中断唤醒睡眠开启
    }
}
