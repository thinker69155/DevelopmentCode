#include "LCD1602.h"
#include "timecount.h"
#include "timer.h"

//**************************************************************/



void see_lcd1602(unsigned char ledbuff[])//时钟菜单
{
	

LCD_ShowChar(1,7,'-');  
LCD_ShowChar(1,10,'-'); 
LCD_ShowChar(2,5,':');  
LCD_ShowChar(2,8,':');  
	
LCD_ShowSignedNum(1, 3, ledbuff[0], 4);  // 年（4位，合理）
LCD_ShowSignedNum(1, 8, ledbuff[1], 2);  // 月（2位）
LCD_ShowSignedNum(1, 11, ledbuff[2], 2); // 日（2位）
LCD_ShowSignedNum(2, 3, ledbuff[3], 2);  // 时（2位）
LCD_ShowSignedNum(2, 6, ledbuff[4], 2);  // 分（2位）
LCD_ShowSignedNum(2, 9, ledbuff[5], 2);  // 秒（2位）
}
