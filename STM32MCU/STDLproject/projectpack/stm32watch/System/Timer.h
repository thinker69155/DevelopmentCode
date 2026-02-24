#ifndef __TIMER_H
#define __TIMER_H

void Timer_Init(void);
void TImer_IT_init_ms(TIM_TypeDef* TIMx,uint32_t ms);
#endif
