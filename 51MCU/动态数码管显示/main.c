#include <REGX52.H>
#define _CRT_SECURE_NO_WARNINGS



void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}


sbit WE = P2^7;
sbit DU = P2^6;
int main()
{
	while (1)
	{


		WE = 1;
		P0 = 0xfe;
		WE = 0;
		DU = 1;
		P0 = 0x06;
		DU = 0;
		Delay1ms();
		
   
		WE = 1;
		P0 =0xfd;
		WE = 0;
		DU = 1;
		P0 = 0x5b;
		DU = 0;
		Delay1ms();

		
		WE = 1;
		P0 = 0xfb;
		WE = 0;
		DU = 1;
		P0 = 0x4f;
		DU = 0;
		Delay1ms();
	}
	
}