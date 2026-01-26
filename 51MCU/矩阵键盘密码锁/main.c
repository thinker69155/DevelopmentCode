#include <REGX52.H>
#include "delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"
unsigned char Keynum;
unsigned int Password,count;
void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"Password:");
	while (1)
	{
    Keynum=MatrixKey();
		if(Keynum)
		{
			if (Keynum <= 10) 
		 {
	
			if(count<4)
			{
				Password *= 10;           
				Password += Keynum % 10;
				count++;
			}      
			LCD_ShowNum(2,1,Password,4);
		 }
			if(Keynum==11)
			{
				if(Password==2345)
                {
                    LCD_ShowString(1,14,"OK");
                    Password=0;
                    count=0;
                    LCD_ShowNum(2,1,Password,4);
                }
                else
                {
                    LCD_ShowString(1,14,"ERR");
                    Password=0;
                    count=0;
                    LCD_ShowNum(2,1,Password,4);
                }
			}
			if(Keynum==12)
            {
                Password=0;
                count--;
                LCD_ShowNum(2,1,Password,4);
            }
		}
	}
}