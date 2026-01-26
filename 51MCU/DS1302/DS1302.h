#ifndef __DS1302_H__
#define __DS1302_H__
void DS1302_Init();
void DS1302_WriteByte(unsigned char Command, unsigned char Data);    
unsigned char DS1302_ReadByte(unsigned char Command);
unsigned char DS1302_DataToBCD(unsigned char Data);
unsigned char DS1302_BCDToData(unsigned char Data);
#endif