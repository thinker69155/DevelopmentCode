//
// Created by c'z'w'x'k'n on 2026/2/14.
//

#include "Flashlight.h"
#include "Drivers\Key\Key.h"
#include "stm32f10x.h"
#include "Drivers\OLED\OLED.h"
/**
  * 函    数：手电筒LED初始化
  * 参    数：无
  * 返 回 值：无
  */
void Flashlight_LED_Init(void){
    /*开启时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//开启GPIOA的时钟

    /*GPIO初始化*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);						//将PA1引脚初始化为推挽输出

    /*设置GPIO初始化后的默认电平*/
    GPIO_SetBits(GPIOA, GPIO_Pin_0);				//设置PA1为高电平
}



/**
 * 手电筒函数
 * @return 按下确认键，返回0
 */
uint8_t Flashlight() {
    OLED_Clear();
    OLED_ShowImage(46, 0, 32, 32,Menu_Graph_Flashlight );
    OLED_Update();
    uint8_t KeyNum_flashlight=0;
    while (1) {

        KeyNum_flashlight=Key_GetNum();
        if (KeyNum_flashlight==0) {
            OLED_ShowImage(46, 0, 32, 32,Menu_Graph_Flashlight );
        }
        else if (KeyNum_flashlight==1) {
            GPIO_WriteBit(GPIOA,GPIO_Pin_1,1);
            OLED_Clear();
            OLED_ShowImage(46, 0, 32, 32,Menu_Graph_Flashlight );
            OLED_ShowString(0,30,"ON",OLED_6X8);
            OLED_Update();
        }
        else if(KeyNum_flashlight==2){
            GPIO_WriteBit(GPIOA,GPIO_Pin_1,0);
            OLED_Clear();
            OLED_ShowImage(46, 0, 32, 32,Menu_Graph_Flashlight );
            OLED_ShowString(0,30,"OFF",OLED_6X8);
            OLED_Update();
        }
        else if(KeyNum_flashlight==3){
            OLED_Clear();
            OLED_Update();
            GPIO_WriteBit(GPIOA,GPIO_Pin_1,0);
            return 0;
        }

    }
}