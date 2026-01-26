#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "delay.h"
unsigned char Second,Minite,Hour;

void main()
{
	LCD_Init();
    DS1302_Init();
    LCD_ShowString(1,1,"RTC");
    //写入日历：19:15:30
    DS1302_WriteByte(0x8e,0x00);//关闭写保护
    DS1302_WriteByte(0x80,DS1302_DataToBCD(30));//秒
    DS1302_WriteByte(0x82,DS1302_DataToBCD(15));//分
    DS1302_WriteByte(0x84,DS1302_DataToBCD(19));//时
    DS1302_WriteByte(0x8e,0x80);//打开写保护
	while (1)
	{
        //读出数据
        //DS1302_WriteByte(0x8e,0x00);//关闭写保护
        Second=DS1302_BCDToData(DS1302_ReadByte(0x81));//读秒
        Minite=DS1302_BCDToData(DS1302_ReadByte(0x83));//读分
        Hour=DS1302_BCDToData(DS1302_ReadByte(0x85));//读时
        DS1302_WriteByte(0x8e,0x80);//打开写保护
        //显示
        LCD_ShowNum(2,1,Second,3);
        LCD_ShowNum(2,5,Minite,3);
        LCD_ShowNum(2,9,Hour,3);

        delay_ms(20);
	}
}//wow