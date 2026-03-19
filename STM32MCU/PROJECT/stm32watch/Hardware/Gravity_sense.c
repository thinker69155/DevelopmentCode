#include "Gravity_sense.h"
#include "Balance.h"
uint8_t Gravity_sense_Tick(void) {
    uint8_t Gravity_Num=0;
    MPU6050_Calculation();
    if(Pitch > 30 ){Gravity_Num=1;}
    else if(Pitch < -30  ){Gravity_Num=2;}
    return Gravity_Num;
}