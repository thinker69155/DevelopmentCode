//
// Created by c'z'w'x'k'n on 2026/2/18.

#include "Emoji.h"
#include "stm32f10x.h"
#include "Key.h"
/**
 * 动态表情包显示函数
 * 调用Emoji_Data.h字模库
 * 按键1上一张，按键2下一张
 * @return 按下确认键，返回0
 */
uint8_t Emoji() {
    uint8_t KeyNum_emoji=0;
    while (1) {
        KeyNum_emoji=Key_GetNum();
        if (KeyNum_emoji==1) {//按键1显示上一张

        }
        else if (KeyNum_emoji==2){//按键2显示下一张

        }
        else if (KeyNum_emoji==3) {//按键3退出函数
            return 0;
        }
        //刷新显示
    }
}