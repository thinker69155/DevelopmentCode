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
int16_t ax,ay,az,gx,gy,gz;//MPU6050三轴加速度，角速度
float roll_g,pitch_g,yaw_g;//陀螺仪解算欧拉角
float roll_a,pitch_a;//加速度解算欧拉角
float Roll,Pitch,Yaw;//互补滤波后的欧拉角
float a=0.9;//互补滤波系数
float Delta_t=0.005;//采样周期
double pi=3.1415927;

/**
 * 姿态解算函数
 */
void MPU6050_Calculation(void){
    Delay_ms(5);
    MPU6050_GetData(&ax,&ay,&az,&gx,&gy,&gz);

    //陀螺仪算欧拉角
    roll_g=Roll+(float)gx*Delta_t;
    pitch_g=Pitch+(float)gy*Delta_t;
    yaw_g=Yaw+(float)gz*Delta_t;

    //加速度算欧拉角
    pitch_a=atan2((-1)*ax,az)*180/pi;
    roll_a=atan2(ay,az)*180/pi;

    //互补滤波
    Roll=a*roll_g+(1-a)*roll_a;
    Pitch=a*pitch_g+(1-a)*pitch_a;
    Yaw=a*yaw_g;

}
void Banlance_Display() {
    OLED_Printf(0,0,OLED_8X16,"<-");
    OLED_Printf(0,16,OLED_8X16,"Roll: %.2f",Roll);
    OLED_Printf(0,32,OLED_8X16,"Pitch:%.2f",Pitch);
    OLED_Printf(0,48,OLED_8X16,"Yaw:  %.2f",Yaw);
}
uint8_t Balance() {
    uint8_t KeyNum_balance=0;
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