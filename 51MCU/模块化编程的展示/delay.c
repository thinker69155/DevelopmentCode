void delay(unsigned char xms)		//@11.0592MHz
{
	unsigned char i;
	while (1)
	{
		xms--;
		
		i = 11;
		while (--i);
	}
	
}