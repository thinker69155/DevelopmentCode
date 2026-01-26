#include <REGX52.H>
#include "delay.h"
#include "Key.h"
#include "intrins.h"
void Timer0_Init()
{	
	
	TMOD &= 0xF0;		
	TMOD |= 0x01;		
	TL0 = 0xFF;		
	TH0 = 0xFF;		
	TF0 = 0;		
	TR0 = 1;			
	ET0=1;
	EA=1;
	PT0=0;
}
unsigned char Keynum,ledmode;void main()
{
	P1=0xfe;			// 初始化P1口，LED1亮
	Timer0_Init();		// 初始化定时器0
	while(1)
	{
		Keynum=Key();	// 检测按键
		if(Keynum)
		{		if(Keynum==1)
				{
					ledmode++;	// 按键按下，模式切换
					if(ledmode>=2)
						ledmode=0;	// 模式循环，0->1->0
				}
		}		
	}
}


void Timer0_Routine() interrupt 1
{
    static unsigned int T0Count;
    TL0=0x18;  
    TH0=0xfc;
    T0Count++;
    if(T0Count>=500)  
    {
        T0Count=0;
        if(ledmode==0)
            P1 = _crol_(P1, 1);  
        if(ledmode==1)
            P1 = _cror_(P1, 1);  
    }
}