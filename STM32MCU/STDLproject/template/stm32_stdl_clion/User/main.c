#include "stm32f10x.h"                  // Device header
#include "OLED.h"

int main(void) {
    /*模块初始化*/
    OLED_Init(); //OLED初始化

    OLED_ShowString(1,1,"Hello world");



    while (1) {
    }
}
