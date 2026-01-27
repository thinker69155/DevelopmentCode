#include <REGX52.H>

//定义引脚
sbit XPT2046_CS=P3^7;
sbit XPT2046_DCLK=P2^1;
sbit XPT2046_DIN=P2^0;//数据输入
sbit XPT2046_DOUT=P2^5;//数据输出


unsigned int XPT2046_ReadAD(unsigned char Command)
{
    unsigned int Data=0;
    unsigned char i;
    XPT2046_DCLK=0;
    XPT2046_CS=0;
    for ( i = 0; i < 8; i++)
    {
        XPT2046_DIN=Command&(0x80>>i);
        XPT2046_DCLK=1;
        XPT2046_DCLK=0;
    }
    for ( i = 0; i < 16; i++)
    {
        XPT2046_DCLK=1;
        XPT2046_DCLK=0;
        if (XPT2046_DOUT)
        {
            Data|=(0x8000>>i);
        }
    }
    XPT2046_CS=1;
    return Data>>8;
}