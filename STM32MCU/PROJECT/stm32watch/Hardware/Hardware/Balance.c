//
// Created by c'z'w'x'k'n on 2026/2/22.
//

#include "Balance.h"
#include <tgmath.h>
#include "stm32f10x.h"
#include "MPU6050.h"
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
int16_t ax,ay,az,gx,gy,gz;
float roll_g,pitch_g,yaw_g;
float roll_a,pitch_a;
float Roll,Pitch,Yaw;
float a=0.9;
float Delta_t=0.005;
double pi=3.1415927;
float gyro_scale=0.061;
float accel_scale=0.000488;

/**
 * 姿态解算函数
 */
void MPU6050_Calculation(void){
    Delay_ms(5);
    MPU6050_GetData(&ax,&ay,&az,&gx,&gy,&gz);

    float gyro_x = gx * gyro_scale;
    float gyro_y = gy * gyro_scale;
    float gyro_z = gz * gyro_scale;

    float accel_x = ax * accel_scale;
    float accel_y = ay * accel_scale;
    float accel_z = az * accel_scale;

    roll_g=roll_g+gyro_x*Delta_t;
    pitch_g=pitch_g+gyro_y*Delta_t;
    yaw_g=yaw_g+gyro_z*Delta_t;

    pitch_a=atan2((-1)*ax,az)*180/pi;
    roll_a=atan2(ay,az)*180/pi;

    Roll=a*roll_g+(1-a)*roll_a;
    Pitch=a*pitch_g+(1-a)*pitch_a;
    Yaw=a*yaw_g;

}
void Banlance_Display() {
    OLED_Printf(0,0,OLED_8X16,"<-");
    OLED_Printf(0,16,OLED_8X16,"Roll: %6.2f",Roll);
    OLED_Printf(0,32,OLED_8X16,"Pitch:%6.2f",Pitch);
    OLED_Printf(0,48,OLED_8X16,"Yaw:  %6.2f",Yaw);
}
uint8_t Balance() {
    uint8_t KeyNum_balance=0;
    roll_g=0;
    pitch_g=0;
    yaw_g=0;
    Roll=0;
    Pitch=0;
    Yaw=0;
    while(1)
    {
        KeyNum_balance=Key_GetNum();
        if(KeyNum_balance==3)
        {
            OLED_Clear();
            OLED_Update();
            return 0;
        }
        OLED_Clear();
        MPU6050_Calculation();
        Banlance_Display();
        OLED_ReverseArea(0,0,16,16);
        OLED_Update();
    }
}