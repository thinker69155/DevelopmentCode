#ifndef __SERVO_H
#define __SERVO_H



void Servo_Init(void);
void Arm_Left(void);
void Arm_Right(void);
void Arm_Up(void);
void Arm_Down(void);
void Arm_Grab(void);
void Arm_Release(void);
//void Arm_Run(void);
void Servo_ArmReset(void);
#endif /* __SERVO_H */