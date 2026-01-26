#include <REGX52.H>
#include "delay.h"
#include "MatrixKey.h"

/// 全局变量 ////////////////////////////////////////////////////////////
unsigned char count1=0;    
unsigned char count2_1=0;  //高位计数器
unsigned char count2_2=0;  //低位计数器
unsigned char bits1 = 4;   // 计数器1位数（默认4位）
unsigned char bits2 = 4;   // 计数器2位数（默认4位）
unsigned char func_choice = 0;

/// 拼接双计数器为8位////////////////////////////////////////////////////////////
unsigned char concatenate_bit() 
{
    unsigned char val1 = count2_1 % (1 << bits1);  
    unsigned char val2 = count2_2 % (1 << bits2);  
    return (val1 << bits2) | val2;  // 拼接：val1（高位）+ val2（低位）
}

/// led八位显示 ////////////////////////////////
void counter_single()
{
    unsigned char key=MatrixKey();  
    if(key == 12)  // 按键12让count1++
    {
        count1++;
        count1 %= 256;
        delay(20);  // 按键防抖
    }
    P1=count1;  
    delay(50); 
}

/// led八位显示反转 ////////////////////////////
void counter_twist()
{
    unsigned char count1_twist = 0;
    unsigned char temp = count1;
    int i = 0;
    
    // 检测按键：按键12才让count1++
    unsigned char key=MatrixKey();
    if(key == 12)
    {
        count1++;
        count1 %= 256;
        delay(20);
    }
    
    // 反转
    for( i = 0; i < 8; i++) 
    {
        count1_twist <<= 1;
        count1_twist |= (temp & 1);  
        temp >>= 1;
    }
    P1 = count1_twist;  
    delay(50);
}

/// led两个四位显示//////////////////////////////////////////////////
void counter_double()
{
    unsigned char key=MatrixKey();
    switch(key)
    {
        case 10:count2_1++;delay(20);break;  
        case 11:count2_2++;delay(20);break;
    }
    P1=concatenate_bit();
    delay(50);
}

/// led自设位数显示 //////////////////////////////////////////////////
void counter_set_manual()
{
    unsigned char key=MatrixKey();
    switch(key)
    {
        case 14:bits1=1;bits2=7;delay(20);break;
        case 15:bits1=2;bits2=6;delay(20);break;
        case 16:bits1=3;bits2=5;delay(20);break;
        case 17:bits1=4;bits2=4;delay(20);break;
        case 18:bits1=5;bits2=3;delay(20);break;
        case 19:bits1=6;bits2=2;delay(20);break;
        case 20:bits1=7;bits2=1;delay(20);break;
    }
    P1=concatenate_bit();
    delay(50);
}

/// 主函数 //////////////////////////////////////////////////////////
void main()
{
    P1=0xff;
    while(1)
    {
        unsigned char key=MatrixKey();
        
        // 检测功能切换键
        if(key == 6)      func_choice = 1;  // 切换到single
        else if(key == 7) func_choice = 2;  // 切换到twist
        else if(key == 8) func_choice = 3;  // 切换到double
        else if(key == 9) func_choice = 4;  // 切换到set_manual
        
        // 持续执行对应功能
        switch (func_choice)
        {
            case 1: counter_single();  break;
            case 2: counter_twist();   break;
            case 3: counter_double();  break;
            case 4: counter_set_manual(); break;
            default: P1=0xff; break;  
        }
        delay(20);
    } 
}