// ÑÓÊ±º¯Êı£¨ÊÊÅä11.0592MHz¾§Õñ£©

#include "delay.h"
void delay_ms(unsigned int ms) 
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 112; j++);
}