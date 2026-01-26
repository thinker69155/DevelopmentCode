#include <REGX52.H>
#include "delay.h"
#include "Key.h"
#include "Nixie.h"
#include "Timer0.h"

sbit  Motor=P1^0;

unsigned char Counter,Compare,KeyNum,Speed;

void main()
{
    Timer0_Init();
    Compare=5;
    while (1)
    {
        KeyNum=Key();
        if (KeyNum==1)
        {
            Speed++;
            Speed%=4;
            if (Speed==0){Compare=0;}
            if (Speed==1){Compare=5;}
            if (Speed==2){Compare=50;}
            if (Speed==3){Compare=100;}
        }
        Nixie(1,Speed);
    }
    
}
void Timer0_Routine() interrupt 1//100us
{
	TL0 = 0x9c;		//设置定时初值
	TH0 = 0xff;		//设置定时初值
    Counter++;
    Counter%=100;
    if (Counter<Compare)
    {
        Motor=1;
    }
    else
    {
        Motor=0;
    }
    
    
}