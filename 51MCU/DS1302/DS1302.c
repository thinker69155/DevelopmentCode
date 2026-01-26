#include <REGX52.H>

//引脚定义
sbit DS1302_SCLK=P1^0;//时钟线
sbit DS1302_IO=P1^1;//数据线
sbit DS1302_CE=P1^2;//使能端

//程序设计流程
/* 写入一字节数据

读取一字节数据
BCD码转换
关闭写保护
设置DS1302时钟日历寄存器（初始显示时间）
设置写保护

关闭写保护
读取日历
设置写保护

显示 */




/**
  * @brief  DS1302初始化
  */
void DS1302_Init()
{
    DS1302_CE=0;
    DS1302_SCLK=0;
    DS1302_IO=0;
}
/**
  * @brief  DS1302写一个字节
  * @param  Command 命令字/地址
  * @param  Data 要写入的数据
  * @retval 无
  */
void DS1302_WriteByte(unsigned char Command,unsigned char Data)
{
	unsigned char i;
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
		DS1302_IO=Command&(0x01<<i);
		DS1302_SCLK=1;
		DS1302_SCLK=0;
	}
	for(i=0;i<8;i++)
	{
		DS1302_IO=Data&(0x01<<i);
		DS1302_SCLK=1;
		DS1302_SCLK=0;
	}
	DS1302_CE=0;
}

/**
  * @brief  DS1302读一个字节
  * @param  Command 命令字/地址
  * @retval 读出的数据
  */
unsigned char DS1302_ReadByte(unsigned char Command)
{
	unsigned char i,Data=0x00;
	Command|=0x01;	//将指令转换为读指令
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
		DS1302_IO=Command&(0x01<<i);
		DS1302_SCLK=0;
		DS1302_SCLK=1;
	}
	for(i=0;i<8;i++)
	{
		DS1302_SCLK=1;
		DS1302_SCLK=0;
		if(DS1302_IO){Data|=(0x01<<i);}
	}
	DS1302_CE=0;
	DS1302_IO=0;	//读取后将IO设置为0，否则读出的数据会出错
	return Data;
}
/**
  * @brief  DS1302 数据转BCD码
  * @param  Data 需要进行转换的数据  
  * @retval 返回值为BCD码
  */
 unsigned char DS1302_DataToBCD(unsigned char Data)
 {
    unsigned char Data1,Data2;
    Data1=Data/10;
    Data2=Data%10;
    Data2=Data1*16+Data2;
    return Data2;
 }
/**
  * @brief  DS1302 BCD码转数据
  * @param  Data 需要进行转换的BCD码  
  * @retval 返回值为数据
  */
 unsigned char DS1302_BCDToData(unsigned char Data)
 {
    unsigned char Data1,Data2;
    Data1=Data/16;
    Data2=Data%16;
    Data2=Data2+Data1*10;
    return Data2;
 }