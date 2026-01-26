#include <reg51.h>
#include"delay.h"
sbit DIO=P3^4;
sbit S_CLK=P3^5;//输入移位寄存器
sbit R_CLK=P3^6;//输出移位寄存器
/* void main()
{
    unsigned char i,dat;
    dat=0xfe;
    for ( i = 0; i < 8; i++)
    {
        S_CLK=0;//先把时钟拉低
        R_CLK=0;
        if (dat&0x01)
        {
            DIO=1;
        }
        else
        {
            DIO=0;
        }
        dat=dat>>1;
        S_CLK=1;//产生上升沿
    }
    dat=0x80;//发行的数据
	for(i=0;i<8;i++)//进行8次，将8位数据发送入寄存器
	{
		S_CLK=0;//产生上升沿1
		R_CLK=0;
		if(dat&0x01)//如果最低位是1
		{
			DIO=1;
		}
		else
		{
			DIO=0;
		}
		dat=dat>>1;//数据右移一位继续发送
		S_CLK=1;//产生上升沿2
	}
	R_CLK=1;//输出产生上升沿，将行和列的数据传入矩阵屏
    while (1);
    
    
} */
#define LED_PORT P0
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
void ShowColumn(unsigned char column,unsigned char data)//column为选择显示的列，data是需要显示的数据
{
    _74HC595_Write(data);
    LED_PORT=~(0x80>>column);
    delay(1);
    LED_PORT=0xff;
}
void main()
{
    S_CLK=0;
    R_CLK=0;
    while (1)
    {
        ShowColumn(0,0x3c);
        ShowColumn(1,0x42);
        ShowColumn(2,0xA9);
        ShowColumn(3,0x85);
        ShowColumn(4,0x85);
        ShowColumn(5,0xA9);
        ShowColumn(6,0x42);
        ShowColumn(7,0x3c);
    }
    
}

