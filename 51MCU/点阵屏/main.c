#include <REGX52.H>
// 定义兼容别名（解决旧Keil对unsigned char的解析错误）
#define uchar unsigned char
#define uint  unsigned int

// 74HC595引脚定义
sbit DIO    = P3^4;
sbit S_CLK  = P3^5;
sbit R_CLK  = P3^6;
#define LED_PORT P0

// 函数声明（用uchar替代unsigned char）
void _74HC595_Write(uchar Byte);
void ShowColumn(uchar column, uchar data);
void delay(uint t);

// 74HC595写数据
void _74HC595_Write(uchar Byte)
{
    uchar i;
    for(i=0; i<8; i++)
    {
        DIO = Byte & (0x80 >> i);
        S_CLK = 0;
        S_CLK = 1;
    }
    R_CLK = 1;
    R_CLK = 0;
}

// 显示指定列
void ShowColumn(uchar column, uchar data)
{
    if(column >= 8) return;
    _74HC595_Write(data);
    LED_PORT = ~(0x80 >> column);
    delay(1);
    LED_PORT = 0xff;
}

// 延时函数
void delay(uint t)
{
    uint i, j;
    for(i=t; i>0; i--)
        for(j=110; j>0; j--);
}

// 主函数
void main(void)
{
    S_CLK = 0;
    R_CLK = 0;
    while(1)
    {
        ShowColumn(0, 0x3C);
        ShowColumn(1, 0x42);
        ShowColumn(2, 0xA9);
        ShowColumn(3, 0x85);
        ShowColumn(4, 0x85);
        ShowColumn(5, 0xA9);
        ShowColumn(6, 0x42);
        ShowColumn(7, 0x3C);
    }
}