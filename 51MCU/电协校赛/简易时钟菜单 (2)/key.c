#include <REGX52.H>
//#include "delay.h"
//按键匹配功能
sbit Key1 = P3^0;  // 模式切换
sbit Key2 = P3^1;  // 设置/确认
sbit Key3 = P3^2;  // 加
sbit Key4 = P3^3;  // 减



void dela(unsigned int ms) 
	{
    unsigned int i, j;
    for(i=0; i<ms; i++)
        for(j=0; j<112; j++);
}
	


// 按键扫描函数：返回键值（0=无按键，1=Key1，2=Key2，3=Key3，4=Key4）
unsigned char key_scan(void) {
    unsigned char key_val = 0;  // 初始化为无按键
    
    // 检测Key1（模式切换）
    if(Key1 == 0) {
        dela(20);  // 消抖（需确保delay_ms函数已实现）
        if(Key1 == 0) {
            key_val = 1;  // 返回键值1
            while(Key1 == 0);  // 等待按键释放
        }
    }
    // 检测Key2（确认/启动/暂停）
    else if(Key2 == 0) {
        dela(20);
        if(Key2 == 0) {
            key_val = 2;  // 返回键值2
            while(Key2 == 0);
        }
    }
    // 检测Key3（加/上一条）
    else if(Key3 == 0) {
        dela(20);
        if(Key3 == 0) {
            key_val = 3;  // 返回键值3
            while(Key3 == 0);
        }
    }
    // 检测Key4（减/下一条）
    else if(Key4 == 0) {
        dela(20);
        if(Key4 == 0) {
            key_val = 4;  // 返回键值4
            while(Key4 == 0);
        }
    }
    
    return key_val;  // 返回键值（无按键返回0）
}