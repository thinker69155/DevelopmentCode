
#include <stddef.h>

#include "stm32f10x.h"                  // Device header
#include "Delay.h"


/**
  * 函    数：按键初始化
  * 参    数：无
  * 返 回 值：无
  */
void Key_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//开启GPIOB的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);						//将PB1,PB1,PB2引脚初始化为上拉输入
}

/**
  * 函    数：按键获取键码
  * 参    数：无
  * 返 回 值：按下按键的键码值，范围：0~3，返回0代表没有按键按下
  * 注意事项：此函数是阻塞式操作，当按键按住不放时，函数会卡住，直到按键松手
  */
uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;		//定义变量，默认键码值为0
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)			//读PB1输入寄存器的状态，如果为0，则代表按键1按下
	{
		Delay_ms(20);											//延时消抖
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0);	//等待按键松手
		Delay_ms(20);											//延时消抖
		KeyNum = 1;												//置键码为1
	}
	
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)			//读PB1输入寄存器的状态，如果为0，则代表按键2按下
	{
		Delay_ms(20);											//延时消抖
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0);	//等待按键松手
		Delay_ms(20);											//延时消抖
		KeyNum = 2;												//置键码为2
	}
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == 0)			//读PB2输入寄存器的状态，如果为0，则代表按键2按下
	{
		Delay_ms(20);											//延时消抖
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == 0);	//等待按键松手
		Delay_ms(20);											//延时消抖
		KeyNum = 3;												//置键码为3
	}
	return  KeyNum;//将按键的值传递给全局指针KeyNum

}
/**
 * 标志位移动函数
 * @param Flag 需要通过按键进行控制的标志位
 * @param Length 标志位的移动范围：1~Length
 * @return key=1,2返回当前Flag，key=3（按下确认）返回0
 */
uint8_t Key_To_Flag_Move(uint8_t Flag,uint8_t Length) {
	uint8_t KeyNum=Key_GetNum();
	if (KeyNum==1) {//光标向上移动并选择
		Flag--;
		if (Flag==0){Flag==Length;}
		return Flag;
	}
	else if (KeyNum==2) {//光标向下移动并选择
		Flag++;
		if (Flag==Length+1){Flag==1;}
		return Flag;
	}
	else if (KeyNum==3) {
		return 0;
	}
}