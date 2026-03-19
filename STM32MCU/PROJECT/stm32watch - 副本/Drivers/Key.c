
#include <stddef.h>

#include "stm32f10x.h"                  // Device header
#include "../Delay/Delay.h"


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
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);						//将PB1,PB1,PB2引脚初始化为上拉输入
}
uint8_t Key_Num;

/**
 * 函    数：Key_GetNum
 * 功    能：获取按键编号并重置存储的按键编号
 * 参    数：无
 * 返 回 值：
 *   - 非零值：返回当前存储的按键编号，并将存储的按键编号重置为0。
 *   - 0：表示没有按键被按下或按键编号已被读取且未有新的按键输入。
 */
uint8_t Key_GetNum(void)
{
	uint8_t Temp;
	if(Key_Num)
	{
		Temp=Key_Num;
		Key_Num=0;
		return Temp;
	}
	else
	{
		return 0;
	}
}
int press_time;
/**
 * 函数：Key3_Tick
 * 功能：处理按键GPIOB的Pin 10的定时器中断，用于检测按键按下状态并更新按键按下的时间计数。
 * 参数：无
 * 返回值：无
 * 描述：此函数在每次定时器中断时被调用。如果检测到GPIOB的Pin 10为低电平（按键被按下），则增加press_time计数；若检测到高电平（按键释放），则将press_time重置为0。
 */
void Key3_Tick(void)
{
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
	{
		press_time++;
	}

	if((GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 1))
	{
		press_time=0;
	}
}
/**
 * 函数：获取按键状态
 * 参数：无
 * 返回值：按键状态，0表示没有按键被按下；1, 2, 3, 或 4 分别表示不同的按键或按键组合被按下
 */
uint8_t Key_GetState(void)
{

	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0)
	{
		return 1;
	}
	else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == 0)
	{
		return 2;
	}

	else if ((GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)&&press_time>1000)
	{
		return 4;
	}
	else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
	{
		return 3;
	}

	else
	{
		return 0;
	}

}

/**
 * 函数：Key_Tick
 * 功能：定期检查按键状态，并在按键从按下到释放时更新按键编号。
 * 参数：无
 * 返回值：无
 * 说明：此函数通过定时调用，每隔20次调用（假设每次调用间隔相等），读取一次当前按键状态并与上一次状态比较。如果检测到按键由按下变为释放，则将最后一次按下的按键编号保存至全局变量Key_Num中。
 */
void Key_Tick(void)
{
	static uint8_t Count;
	static uint8_t CurrentState,PreState;
	Count++;
	if(Count>=20)
	{
		Count=0;
		PreState=CurrentState;
		CurrentState=Key_GetState();
		if(PreState!=0&&CurrentState==0)
		{
			Key_Num=PreState;
		}
	}
}
////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/**
 * 标志位移动函数
 * @param Flag 需要通过按键进行控制的标志位的地址
 * @param Length 标志位的移动范围：1~Length
 * @return key=1,2返回当前Flag，key=3（按下确认）返回0
 */
uint8_t Flag=1;
uint8_t Key_To_Flag_Move(uint8_t Length) {
	uint8_t KeyNum=Key_GetNum();// 读取按键值
	if (KeyNum==0) {
		return Flag;
	}
	else if (KeyNum==1) {//光标向上移动
		Flag--;
		if (Flag<1){Flag=Length;}
		return Flag;
	}
	else if (KeyNum==2) {//光标向下移动
		(Flag)++;
		if (Flag>Length){Flag=1;}
		return Flag;
	}
	else if (KeyNum==3) {// 确认键按下
		Flag=1;
		return 0;
	}

}
/**
 * 标志位移动函数（带自定义光标位置）
 * @param Flag 需要通过按键进行控制的标志位的地址
 * @param Length 标志位的移动范围：1~Length
 * @return key=1,2返回当前Flag，key=3（按下确认）返回0
 */
uint8_t Key_To_Flag_Move_WithFlag(uint8_t *Flag, uint8_t Length) {
	uint8_t KeyNum=Key_GetNum();// 读取按键值
	if (KeyNum==0) {
		return *Flag;
	}
	else if (KeyNum==1) {//光标向上移动
		(*Flag)--;
		if (*Flag<1){*Flag=Length;}
		return *Flag;
	}
	else if (KeyNum==2) {//光标向下移动
		(*Flag)++;
		if (*Flag>Length){*Flag=1;}
		return *Flag;
	}
	else if (KeyNum==3) {// 确认键按下
		return 0;
	}

}
