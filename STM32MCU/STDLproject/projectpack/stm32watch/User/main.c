#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Key.h"
#include "menu.h"


int main(void) {
    //初始化函数
    OLED_Init();
    OLED_Clear();
    Key_Init();//按键检测初始化

    while (1) {
        First_Page_do();
    }
}
