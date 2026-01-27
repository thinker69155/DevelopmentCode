#include <REGX52.H>
#include <INTRINS.H>
#include "delay.h"
#include "LCD1602.h"

#define MAIN_Fosc 11059200UL//宏定义时钟

sbit CS=P3^7; 
sbit DCLK=P2^1;
sbit DIN=P2^0;
sbit DOUT=P2^5;
sbit DU=P2^6;//数码管的段选位选
sbit WE=P2^7;

unsigned char voltage;

#define AD_CH3 0xe4

void SPI_Write(unsigned char Data)
{
    unsigned char i;
    for ( i = 0; i < 8; i++)
    {
        DCLK=0;//拉低时钟线，允许DIN变化
        if (Data&0x80)//写入数据高位
        {
            DIN=1;
        }
        else
        {
            DIN=0;
        }
        DCLK=1;//拉高时钟线，产生上升沿，从机读取DIN
        Data<<=1;//左移一位
    } 
}

unsigned char SPI_Read()
{
    unsigned char i,Data;
    for ( i = 0; i < 12; i++)//读取十二位信息
    {
        Data<<=1;//左移一位，准备接收下一位信息
        DCLK=1;//产生上升沿，读取DIN上的数据
        DCLK=0;//拉低时钟线，允许DIN数据变化
        if (DOUT)
        {
            Data|=0x01;
        }
        
    }
    return Data;
}

unsigned char ReadAD(unsigned char cmd)
{
    unsigned char Data;
    CS=0;
    SPI_Write(cmd);
    DCLK=0;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    Data=SPI_Read();
    CS=1;
    return (Data);
}

void main()
{
    LCD_Init();
    while (1)
    {  
        voltage=ReadAD(AD_CH3);
        voltage=voltage*1.2207; 
        LCD_ShowNum(1,1,voltage,5);
        delay_ms(5);
    }
    
}