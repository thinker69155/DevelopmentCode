#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

/**
  * 坐标轴定义：
  * 左上角为(0, 0)点
  * 横向向右为X轴，取值范围：0~127
  * 纵向向下为Y轴，取值范围：0~63
  *
  *       0             X轴           127
  *      .------------------------------->
  *    0 |
  *      |
  *      |
  *      |
  *  Y轴 |
  *      |
  *      |
  *      |
  *   63 |
  *      v
  *
  */

int main(void)
{
	/*OLED初始化*/
	OLED_Init();

	/*在(0, 0)位置显示字符'A'，字体大小为8*16点阵*/
	OLED_ShowChar(0, 0, 'A', OLED_8X16);
	/*调用OLED_Update函数，将OLED显存数组的内容更新到OLED硬件进行显示*/
	OLED_Update();
	while (1) {

	}
}
