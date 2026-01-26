#include <reg51.h>
#include"delay.h"
#include"MatrixLED.h"
void main()
{
    LED_Init();
    while (1)
    {
        ShowColumn(0,0x3c);
        ShowColumn(1,0x42);
        ShowColumn(2,0xA9);
        ShowColumn(3,0x85);
        ShowColumn(4,0x85);
        ShowColumn(5,0xA9);
        ShowColumn(6,0x42);
        ShowColumn(7,0x3c);
    }
    
}