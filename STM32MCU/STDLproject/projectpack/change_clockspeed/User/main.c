#include "Delay.h"
#include "stm32f10x.h"                  // Device header
#include "OLED.h"
//说明：在System。c文件中#define SYSCLK_FREQ_36MHz  36000000
int main(void) {
    /*模块初始化*/
    OLED_Init(); //OLED初始化

    OLED_ShowString(1,1,"SYSCLK:");
    OLED_ShowNum(1,8,SystemCoreClock,8);


    while (1) {
        OLED_ShowString(2,1,"Running");
        Delay_ms(500);
        OLED_ShowString(2,1,"         ");
        Delay_ms(500);
    }
}
