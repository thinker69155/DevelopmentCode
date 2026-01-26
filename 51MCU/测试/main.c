#include <REGX52.H>
void delay(unsigned int xms)		//@11.0592MHz
{
	unsigned char i, j;
	while(xms)
	{
		i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
		xms=xms-1;
	}
	
}
int fn_flag=0;
unsigned char key_fn()
{
        
    if(P3_3==0)  
    {
        delay(20);            
        if(P3_3==0)
        {           
            fn_flag = !fn_flag;  
            while(P3_3==0);  
        }
    }       
    return fn_flag;
}
void main()
{
	while(1)
	{
		key_fn();
		if(fn_flag==1)
		{
			
			P1_0=0;
		}
		
		else if(fn_flag==0)
			P1_0=1;
	}
}
	