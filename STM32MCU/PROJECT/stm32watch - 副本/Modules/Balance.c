//
// Created by c'z'w'x'k'n on 2026/2/22.
//

#include <tgmath.h>
#include "stm32f10x.h"
#include "Drivers\MPU6050\MPU6050.h"
#include "Drivers\Delay\Delay.h"
#include "Drivers\OLED\OLED.h"
#include "Drivers\Key\Key.h"
int16_t ax,ay,az,gx,gy,gz;//MPU6050²âµÃµÄÈýÖá¼ÓËÙ¶ÈºÍ½ÇËÙ¶È
float roll_g,pitch_g,yaw_g;//ÍÓÂÝÒÇ½âËãµÄÅ·À­½Ç
float roll_a,pitch_a;//¼ÓËÙ¶È¼Æ½âËãµÄÅ·À­½Ç
float Roll,Pitch,Yaw;//»¥²¹ÂË²¨ºóµÄÅ·À­½Ç
float a=0.9;//»¥²¹ÂË²¨Æ÷ÏµÊý
float Delta_t=0.005;//²ÉÑùÖÜÆÚ
double pi=3.1415927;

/**
 * 姿态解算函数
 */
void MPU6050_Calculation(void){
    Delay_ms(5);
    MPU6050_GetData(&ax,&ay,&az,&gx,&gy,&gz);

    //Í¨¹ýÍÓÂÝÒÇ½âËãÅ·À­½Ç
    roll_g=Roll+(float)gx*Delta_t;
    pitch_g=Pitch+(float)gy*Delta_t;
    yaw_g=Yaw+(float)gz*Delta_t;

    //Í¨¹ý¼ÓËÙ¶È¼Æ½âËãÅ·À­½Ç
    pitch_a=atan2((-1)*ax,az)*180/pi;
    roll_a=atan2(ay,az)*180/pi;

    //Í¨¹ý»¥²¹ÂË²¨Æ÷½øÐÐÊý¾ÝÈÚºÏ
    Roll=a*roll_g+(1-a)*roll_a;
    Pitch=a*pitch_g+(1-a)*pitch_a;
    Yaw=a*yaw_g;

}
uint8_t i;
void Banlance_Display() {
    OLED_Printf(0,0,OLED_8X16,"<-");
    OLED_ShowFloatNum(0,16,Roll,3,2,OLED_8X16);
    OLED_ShowFloatNum(0,32,Pitch,3,2,OLED_8X16);
    OLED_ShowFloatNum(0,48,Yaw,3,2,OLED_8X16);
}
uint8_t Balance() {
    uint8_t KeyNum_balance=0;
    while(1)
    {
        i++;
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