#ifndef INC_AHT20_H_
#define INC_AHT20_H_
#include "i2c.h"
void AHT_Read(float *Temperature,float *Humidity);
void AHT20_Init();
#endif