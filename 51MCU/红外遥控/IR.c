#include <REGX52.H>
#include "Timer0.h"
#include "int0.h"

unsigned int IR_Time;
unsigned char IR_State;

unsigned char IR_Data[4];
unsigned char IR_pData;

unsigned char IR_DataFlag;
unsigned char IR_RepeatFlag;
unsigned char IR_Address;
unsigned char IR_Command;


void IR_Init()
{
    Timer0_Init();
    Int0_Init();

}

void Int0_Routine() interrupt 0
{    
    if (IR_State==0)
    {
        
        Timer0_SetCounter(0);//清零
        Timer0_Run(1);//启动运行
        IR_State=1;//状态完成
    }
    else if (IR_State==1)
    {
        
        IR_Time=Timer0_GetCounter();
        Timer0_SetCounter(0);
        if(IR_Time>13500-1000&&IR_Time<13500+1000)
        {
            IR_State==2;
            
        }
        else if (IR_Time>11250-1000&&IR_Time<11250+1000)
        {
            IR_RepeatFlag=1;
            Timer0_Run(0);
            IR_State=0;
        }
        else  //出错
        {
            IR_State=1;
        }
    } 
    else if (IR_State==2)
    {
        IR_Time=Timer0_GetCounter();
        Timer0_SetCounter(0);
        if(IR_Time>1120-1000&&IR_Time<1120+1000)
        {
            IR_Data[IR_pData/8]&=~(0x01<<IR_pData%8);
            IR_pData++;
        }
        else if(IR_Time>2250-1000&&IR_Time<2250+1000)
        {
            IR_Data[IR_pData/8]|=(0x01<<IR_pData%8);
            IR_pData++;
        }
        else
        {
            IR_pData=0;
            IR_State=1;
        }
        if (IR_pData>=32)
        {
            IR_pData=0;
        }
        
    }
      
} 