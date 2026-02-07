#include "stm32f10x.h"
#include "Delay.h"

#define SCL_PORT GPIOB
#define SCL_PIN GPIO_Pin_10

void MyIIC_Write_SCL(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_10, (BitAction)BitValue);
    Delay_us(10);
}

void MyIIC_Write_SDA(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)BitValue);
    Delay_us(10);
}

uint8_t MyIIC_Read_SDA()
{
    uint8_t BitValue;
    BitValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
    Delay_us(10);
    return BitValue;
}

void MyIIC_Init(void)//软件模拟IIC
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;//开漏输出（可输出可输入）
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);//置高电平，释放IIC总线
    
}
void MyIIC_Start()
{
    MyIIC_Write_SDA(1);
    MyIIC_Write_SCL(1);
    MyIIC_Write_SDA(0);
    MyIIC_Write_SCL(0);
}

void MyIIC_Stop()
{
    MyIIC_Write_SDA(0);
    MyIIC_Write_SCL(1);
    MyIIC_Write_SDA(1);
}

void MyIIC_SendByte(uint8_t Byte)
{
    uint8_t i;
    for (i = 0; i < 8;i++)
    {
        MyIIC_Write_SDA(Byte & (0x80>>i));
        MyIIC_Write_SCL(1);
        MyIIC_Write_SCL(0);
    }
}

uint8_t MyIIC_ReceiveByte()
{
    uint8_t Byte = 0x00,i;
    MyIIC_Write_SDA(1);
    for ( i = 0; i < 8; i++)
    {
        MyIIC_Write_SCL(1);
        if(MyIIC_Read_SDA()==1)
        {
            Byte |= (0x80>>i);
        }
        MyIIC_Write_SCL(0);
    }
    return Byte;
}

void MyIIC_SendAck(uint8_t AckBit)
{

    MyIIC_Write_SDA(AckBit);
    MyIIC_Write_SCL(1);
    MyIIC_Write_SCL(0);
}

uint8_t MyIIC_ReceiveAck()
{
    uint8_t AckBit;
    MyIIC_Write_SDA(1);
    MyIIC_Write_SCL(1);
    AckBit = MyIIC_Read_SDA();
    MyIIC_Write_SCL(0);
    return AckBit;
}