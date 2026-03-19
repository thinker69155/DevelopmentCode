/*
 * ************************************************
 *
 *              STM32 blink gcc demo
 *
 *  CPU: STM32F103C8
 *  PIN: PA1
 *
 * ************************************************
 */

#include "ucos_ii.h"
#include "stm32f10x.h"

void led_task1()
{
    while (1) {
        GPIO_SetBits(GPIOC, GPIO_Pin_13);
        OSTimeDly(1000);
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        OSTimeDly(1000);
    }
}


OS_STK buffer[128];

void SystemConfig()
{
    SysTick_Config(SystemCoreClock / 1000);

    GPIO_InitTypeDef gpioDef;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    gpioDef.GPIO_Mode  = GPIO_Mode_Out_PP;
    gpioDef.GPIO_Pin   = GPIO_Pin_13;
    gpioDef.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOC, &gpioDef);
}

int main()
{

    SystemConfig();

    OSInit();

    OSTaskCreate(led_task1, NULL, buffer, 20);


    OSStart();
}
