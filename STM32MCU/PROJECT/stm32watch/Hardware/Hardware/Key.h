#ifndef __KEY_H
#define __KEY_H
#include <stdint.h>
void Key_Init(void);
uint8_t Key_GetNum(void);
void Key3_Tick(void);
uint8_t Key_GetState(void);
void Key_Tick(void);
uint8_t Key_To_Flag_Move(uint8_t Length);
uint8_t Key_To_Flag_Move_WithFlag(uint8_t *Flag, uint8_t Length);
#endif
