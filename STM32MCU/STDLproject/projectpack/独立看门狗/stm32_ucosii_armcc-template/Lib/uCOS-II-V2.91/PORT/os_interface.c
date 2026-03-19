#include "os_interface.h"

void SysTick_Handler()
{
    OSIntEnter();
    OSTimeTick();
    OSIntExit();
}

void InitSysTick(void)
{
    SysTick->LOAD = (uint32_t)((1000U / OS_TICKS_PER_SEC) * 9000U - 1UL); /* set reload register */
    NVIC_SetPriority(SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);      /* set Priority for Systick Interrupt */
    SysTick->VAL  = 0UL;                                                  /* Load the SysTick Counter Value */
    SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;   /* Enable SysTick IRQ and SysTick Timer.
                                                                             Make AHB clock divided by 8, 
                                                                             So SysTick clock is 72 / 8 = 9MHz */
}
