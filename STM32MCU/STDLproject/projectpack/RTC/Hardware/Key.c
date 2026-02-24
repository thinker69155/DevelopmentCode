#include "stm32f10x.h"                  // Device header
#include "Key.h"

//KEY1----->PC14	KEY2----->PC15		KEY3----->PA5		KEY4----->PC4
KeyHandler Key[4];

GPIO_TypeDef* Key_Prot[4] = {GPIOC, GPIOC, GPIOA, GPIOC};
uint16_t Key_Pin[4] = {GPIO_Pin_14, GPIO_Pin_15, GPIO_Pin_5, GPIO_Pin_4};
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     按键初始化函数
// 参数说明     void
// 返回参数     void
// 使用示例     Key_Init();
// 备注信息     设置所有按键为上拉输入，并初始化按键事件、状态和长按计数器
//-------------------------------------------------------------------------------------------------------------------
void Key_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);

	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    for(uint8_t i; i < 4; i++)
    {
        Key[i].event = NULL_PRESS;
        Key[i].status = KEY_UP;
        Key[i].LongPressCount = 0;
    }

}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     按键处理函数
// 参数说明     void
// 返回参数     void
// 使用示例     Key_handler(); // 扫描按键状态并判断是否为短按或长按
// 备注信息     根据按键状态和按下持续时间，判断按键事件为短按或长按
//-------------------------------------------------------------------------------------------------------------------
void Key_handler(void)
{
    for(uint8_t i = 0; i < 4; i++)
    {
        if(Key[i].status == KEY_UP)
        {
            if(Key[i].LongPressCount <= 4)
            {
                Key[i].event = NULL_PRESS;
            }
            if(Key[i].LongPressCount > 4 && Key[i].LongPressCount <200)
            {
                Key[i].event = SHORT_PRESS;
                Key[i].LongPressCount = 0;
            }
            if(Key[i].LongPressCount >= 200)
            {
                Key[i].event = LONG_PRESS;
                Key[i].LongPressCount = 0;
            }
        }
    }
}