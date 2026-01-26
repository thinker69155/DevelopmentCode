#include <REGX52.H>
//串口UART通讯配置
void UART_Init(void)		//4800bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFA;		//设定定时初值
	TH1 = 0xFA;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	EA=1;
	ES=1;
}
void UART_sendyte(unsigned char byte)
{
	SBUF=byte;
	while(TI==0);
	TI=0;
	
}
void main()
{
	UART_Init();
	while(1)
	{
		
	}
}
void UART_Routine() interrupt 4
{
    if(RI==1)
    {
        P1=SBUF;
        UART_sendyte(SBUF);
        RI=0;
    }
}