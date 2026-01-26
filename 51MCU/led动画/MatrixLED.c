#include <reg51.h>
#include "delay.h"
#include "MatrixLED.h"
sbit DIO=P3^4;
sbit S_CLK=P3^5;//输入移位寄存器
sbit R_CLK=P3^6;//输出移位寄存器

#define LED_PORT P0
/* *
   *74HC595写入一个字节的数据
   *Byte为要写入的字节
   * 
   */
void _74HC595_Write(unsigned char Byte)
{
    unsigned char i;
    for ( i = 0; i < 8; i++)
    {
        DIO=Byte&(0x80>>i);
        S_CLK=1;
        S_CLK=0;
    }
    R_CLK=0;
    R_CLK=1;
}
/* *
   *led点阵屏初始化
   */
void LED_Init()
{
    R_CLK=0;
    S_CLK=0;
}

/* *
   *led点阵屏显示一列数据
   *column为选择的列
   * data为显示的数据高位在上，1为亮
   */
void ShowColumn(unsigned char column,unsigned char Data)//column为选择显示的列，data是需要显示的数据
{
    _74HC595_Write(Data);
    LED_PORT=~(0x80>>column);
    delay(1);
    LED_PORT=0xff;
}                  