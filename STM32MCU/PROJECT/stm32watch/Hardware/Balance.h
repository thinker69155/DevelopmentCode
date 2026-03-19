//
// Created by c'z'w'x'k'n on 2026/2/22.
//

#ifndef TEMPLE_PROJECT_BALANCE_H
#define TEMPLE_PROJECT_BALANCE_H
#include <stdint.h>
extern float Roll,Pitch,Yaw;
void MPU6050_Calculation(void);
uint8_t Balance() ;
#endif //TEMPLE_PROJECT_BALANCE_H