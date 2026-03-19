#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Store.h"
#include "Key.h"


uint8_t KeyNum = 0;

int main(void)
{
	OLED_Init();
	Key_Init();
	Store_Init();

	Store_Clear();
	while (1)
	{
		KeyNum = Key_GetNum();
		if (KeyNum==1)
		{
			Store_Data[1]=0x1234;
			Store_Data[2]=0x5678;
			Store_Save();
		}
		else if (KeyNum==2)
		{
			Store_Save();
		}
		else if (KeyNum==3)
		{
			
		}
		
	}
}
