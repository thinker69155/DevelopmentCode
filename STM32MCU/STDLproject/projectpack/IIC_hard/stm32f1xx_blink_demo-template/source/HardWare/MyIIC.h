#ifndef __MYIIC_H
#define __MYIIC_H
uint8_t MyIIC_Read_SDA();
void MyIIC_Init(void); // 软件模拟IIC
void MyIIC_Start();
void MyIIC_Stop();
void MyIIC_SendByte(uint8_t Byte);
uint8_t MyIIC_ReceiveByte();
void MyIIC_SendAck(uint8_t AckBit);
uint8_t MyIIC_ReceiveAck();

#endif