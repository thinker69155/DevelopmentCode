//
// Created by c'z'w'x'k'n on 2026/2/18.

#include "Emoji.h"

#include "Delay.h"
#include "stm32f10x.h"
#include "Key.h"
#include "OLED.h"

void Emoji_1() {
    /*闭眼*/
    for(uint8_t i=0;i<3;i++)
    {
        OLED_Clear();
        OLED_ShowImage(30,10+i,16,16,Eyebrow[0]);//×óÃ¼Ã«
        OLED_ShowImage(82,10+i,16,16,Eyebrow[1]);//ÓÒÃ¼Ã«
        OLED_DrawEllipse(40,32,6,6-i,1);//×óÑÛ
        OLED_DrawEllipse(88,32,6,6-i,1);//ÓÒÑÛ
        OLED_ShowImage(54,40,20,20,Mouth);
        OLED_Update();
        Delay_ms(100);
    }
    /*睁眼*/
    for(uint8_t i=0;i<3;i++)
    {
        OLED_Clear();
        OLED_ShowImage(30,12-i,16,16,Eyebrow[0]);//×óÃ¼Ã«
        OLED_ShowImage(82,12-i,16,16,Eyebrow[1]);//ÓÒÃ¼Ã«
        OLED_DrawEllipse(40,32,6,4+i,1);//×óÑÛ
        OLED_DrawEllipse(88,32,6,4+i,1);//ÓÒÑÛ
        OLED_ShowImage(54,40,20,20,Mouth);
        OLED_Update();
        Delay_ms(100);
    }
    Delay_ms(500);
}
/**
 * 动态表情包显示函数
 * 调用Emoji_Data.h字模库
 * 按键1上一张，按键2下一张
 * @return 按下确认键，返回0
 */
uint8_t Emoji() {
    uint8_t KeyNum_emoji=0;
    /*while (1) {
        KeyNum_emoji=Key_GetNum();
        if (KeyNum_emoji==1) {//按键1显示上一张

        }
        else if (KeyNum_emoji==2){//按键2显示下一张

        }
        else if (KeyNum_emoji==3) {//按键3退出函数
            return 0;
        }
        //刷新显示
    }*/
    while (1) {
        KeyNum_emoji=Key_GetNum();
        if (KeyNum_emoji==3) {
            return 0;
        }
        Emoji_1();

    }
}