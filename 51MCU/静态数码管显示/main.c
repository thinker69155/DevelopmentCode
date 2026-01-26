#include <REGX52.H>
#define _CRT_SECURE_NO_WARNINGS
//#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char

sbit WE=P2^7;
sbit DU=P2^6;
int main()
{
	WE = 1;
	P0_7 = 0;
	WE = 0;
	DU = 1;
	P0 = 0x7d;
	DU = 0; 
	while (1)
	{

	}

}