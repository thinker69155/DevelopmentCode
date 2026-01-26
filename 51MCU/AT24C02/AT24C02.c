#include <REGX52.H>
#include "I2C.h"

#define AT24C02_ADDRESS_WRITE 0xA0
#define AT24C02_ADDRESS_READ 0xA1

void AT24C02_WriteByte(unsigned char WordAddress,unsigned char Data)
{
    I2C_Start();
    I2C_SendByte(AT24C02_ADDRESS_WRITE);
    I2C_ReceiveAck();
    I2C_SendByte(WordAddress);
    I2C_ReceiveAck();
    I2C_SendByte(Data);
    I2C_ReceiveAck();
    I2C_Stop();
}



unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
    unsigned char Data;
    I2C_Start();
    I2C_SendByte(AT24C02_ADDRESS_WRITE);
    I2C_ReceiveAck();
    I2C_SendByte(WordAddress);
    I2C_ReceiveAck();

    I2C_Start();
    I2C_SendByte(AT24C02_ADDRESS_WRITE|0x01);
    I2C_ReceiveAck();
    Data=I2C_ReceiveByte();
    I2C_SendAck(1);
    I2C_Stop();

    return Data;
}