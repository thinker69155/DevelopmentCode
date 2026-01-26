#include <delay.h>
// 延时函数（用于设置模式闪烁）
void delay(unsigned int ms) 
	{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 112; j++);
}