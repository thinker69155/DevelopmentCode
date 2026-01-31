#include <REGX52.H>
//����UARTͨѶ����
void UART_Init(void)		//4800bps@11.0592MHz
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFA;		//�趨��ʱ��ֵ
	TH1 = 0xFA;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
	EA=1;
	ES=1;
}
void UART_sendyte(unsigned char byte)
{
	SBUF=byte;
	while(TI==0);
	TI=0;
	
}
void main()
{
	UART_Init();
	while(1)
	{
		
	}
}
void UART_Routine() interrupt 4
{
    if(RI==1)
    {
        P1=SBUF;
        UART_sendyte(SBUF);
        RI=0;
		
    }
}