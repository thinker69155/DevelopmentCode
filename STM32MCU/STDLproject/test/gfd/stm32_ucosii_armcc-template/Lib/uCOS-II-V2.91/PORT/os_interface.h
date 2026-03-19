#ifndef _OS_INTERFACE_
#define _OS_INTERFACE_

/**
 * 芯片的相关接口
*/

#include "ucos_ii.h"
#include "stm32f10x.h"

/**
 * 初始化系统的节拍时钟
 * SysTick 频率: HCLK 8分频 (9MHz)
*/
void InitSysTick(void);

/**
 * 系统节拍器中断处理
*/
void SysTick_Handler(void);

#endif
