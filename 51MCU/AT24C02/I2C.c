#include <REGX52.H>

sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;

/**
  * @brief  I2C 起始条件函数
  * @param  无
  * @retval 无
  */
void I2C_Start()
{
    I2C_SDA=1;//保证在SCL为高电平之前都是高
    I2C_SCL=1;
    I2C_SDA=0;
    I2C_SCL=0;//复原SCL为低
}

/**
  * @brief  I2C 结束条件函数
  * @param  无
  * @retval 无
  */
void I2C_Stop()
{
    I2C_SDA=0;//保证在SCL为高电平之前都是高
    I2C_SCL=1;
    I2C_SDA=1;
}

/**
  * @brief  I2C 发送一字节数据
  * @param  Byte：需要发送的字节数据
  * @retval 无
  */
void I2C_SendByte(unsigned char Byte)
{
    unsigned char i;
    for ( i = 0; i < 8; i++)
    {
        I2C_SDA=Byte&(0x80>>i);
        I2C_SCL=1;
        I2C_SCL=0;//速度快的单片机需要进行延时
    }
}

/**
  * @brief  I2C 接收一字节数据
  * @param  无
  * @retval 接收到的字节数据
  */
unsigned char I2C_ReceiveByte()
{
    unsigned char i,Byte=0x00;
    I2C_SDA=1;//释放总线，将控制权交给从机
    for ( i = 0; i < 8; i++)
    {
        I2C_SCL=1;
        if (I2C_SDA)
        {
            Byte|=(0x80>>i);
        }
        I2C_SCL=0;//速度快的单片机需要进行延时
    }
    return Byte;
}

/**
  * @brief  I2C 发送应答
  * @param  AckBit，为发送的应答，0表示应答，1表示未应答
  * @retval 无
  */
void I2C_SendAck(unsigned char AckBit)
{
    I2C_SDA=AckBit;
    I2C_SCL=1;
    I2C_SCL=0;
}

/**
  * @brief  I2C 接收应答
  * @param  无
  * @retval 接收的应答，0表示应答，1表示未应答
  */
unsigned char I2C_ReceiveAck()
{
    unsigned char AckBit;
    I2C_SDA=1;
    I2C_SCL=1;
    AckBit=I2C_SDA;
    I2C_SCL=0;
    return AckBit;
}
