#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
/*
独立看门狗
void WDG_Init(void)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); // 使能写访问
    IWDG_SetPrescaler(IWDG_Prescaler_16);         // 设置分频系数为16
    IWDG_SetReload(2500-1);                       // 设置重装载值为2500-1
    IWDG_ReloadCounter();                         // 先喂狗一次，装载IWDG计数器
    IWDG_Enable();                                // 使能IWDG
                                                  //自动写保护
}
int main(void)
{

    OLED_Init();
    Key_Init();

    OLED_ShowString(1, 1, "IWDG TEST");

    if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET) {
        OLED_ShowString(2, 1, "IWDG Reset");
        Delay_ms(500);
        OLED_ShowString(2, 1, "           ");
        Delay_ms(100);
        RCC_ClearFlag(); // 清除复位标志位
    } else {
        OLED_ShowString(3, 1, "Reset");
        Delay_ms(500);
        OLED_ShowString(3, 1, "           ");
        Delay_ms(100);
        RCC_ClearFlag(); // 清除复位标志位
    }

    WDG_Init();

    while (1) {
        Key_GetNum();

        IWDG_ReloadCounter();
        OLED_ShowString(4, 1, "Feed Dog");
        Delay_ms(200);
        OLED_ShowString(4, 1, "        ");
        Delay_ms(600);

    }
}*/
// 窗口看门狗
void WWDG_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE); // 使能WWDG时钟
    WWDG_SetPrescaler(WWDG_Prescaler_8);                 // 设置分频系数为16
    WWDG_SetWindowValue(0x40 | 21);                      // 30ms
    WWDG_Enable(0x40 | 54);                              // 50ms
}
int main(void)
{

    OLED_Init();
    Key_Init();

    OLED_ShowString(1, 1, "WWDG TEST");

    if (RCC_GetFlagStatus(RCC_FLAG_WWDGRST) == SET) {
        OLED_ShowString(2, 1, "WWDGRST");
        Delay_ms(500);
        OLED_ShowString(2, 1, "           ");
        Delay_ms(100);
        RCC_ClearFlag(); // 清除复位标志位
    } else {
        OLED_ShowString(3, 1, "Reset");
        Delay_ms(500);
        OLED_ShowString(3, 1, "           ");
        Delay_ms(100);
        RCC_ClearFlag(); // 清除复位标志位
    }

    WWDG_Init();

    while (1) {
        Key_GetNum();

        /*OLED_ShowString(4, 1, "Feed Dog");
        Delay_ms(50);
        OLED_ShowString(4, 1, "        ");
        Delay_ms(50);*/
		Delay_ms(49);
		WWDG_SetCounter(0x40 | 54);
    }
}