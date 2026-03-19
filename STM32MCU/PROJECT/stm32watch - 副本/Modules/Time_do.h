#ifndef TEMPLE_PROJECT_TIME_H
#define TEMPLE_PROJECT_TIME_H
#include <stdint.h>

extern uint8_t CountDown_Time[];


void Show_time_Init();
void Show_Time();
void CountDown_Display();
void StopWatch_Tick(void);
void Countdown_Tick(void);
uint8_t Change_First_Page_Time(uint8_t wei);
uint8_t CountDown_Work();
uint8_t CountDown_Set();
uint8_t StopWatch();
#endif //TEMPLE_PROJECT_TIME_H