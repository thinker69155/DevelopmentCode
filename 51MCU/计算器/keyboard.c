#include <REGX52.H>
#include "delay.h"
#include "globalvars.h"

  


// 独立按键定义（P3^0=Key1，P3^1=Key2）
sbit Key1 = P3^0;  
sbit Key2 = P3^1;

unsigned char key_duli(void) 
{
    // 按Key1切换到普通模式
    if (Key1 == 0 && Key2 == 1) 
		{
        delay(20);  // 消抖
        if (Key1 == 0 && Key2 == 1) 
				{
            duli = 1;
            while (Key1 == 0 && Key2 == 1);  
        }
    }
    
    // 按Key2切换到FN模式
    if (Key1 == 1 && Key2 == 0) 
		{		
       delay(20);  // 消抖
        if (Key1 == 1 && Key2 == 0) 
				{
            duli = 2;
            while (Key1 == 1 && Key2 == 0);           
        }
    }       
    return duli;
}

//矩阵键盘扫描
unsigned char key_scan(void) 
{
    unsigned char key_val = 0;
    
//    // 先检测独立按键是否按下：若按下，不扫描矩阵（避免冲突）
//    if (Key1 == 0 || Key2 == 0) 
//		{
//        return 0;
//    }
    
    // 矩阵键盘扫描（原逻辑保留，仅在无独立按键时执行）
    P3 = 0xff;       
    P3_4 = 0;        
    if (P3_0 == 0) { delay(20); while(P3_0==0); delay(20); key_val=6; }
    if (P3_1 == 0) { delay(20); while(P3_1==0); delay(20); key_val=10; }
    if (P3_2 == 0) { delay(20); while(P3_2==0); delay(20); key_val=14; }
    if (P3_3 == 0) { delay(20); while(P3_3==0); delay(20); key_val=18; }
    
    P3 = 0xff;
    P3_5 = 0;        
    if (P3_0 == 0) { delay(20); while(P3_0==0); delay(20); key_val=7; }
    if (P3_1 == 0) { delay(20); while(P3_1==0); delay(20); key_val=11; }
    if (P3_2 == 0) { delay(20); while(P3_2==0); delay(20); key_val=15; }
    if (P3_3 == 0) { delay(20); while(P3_3==0); delay(20); key_val=19; }
    
    P3 = 0xff;
    P3_6 = 0;        
    if (P3_0 == 0) { delay(20); while(P3_0==0); delay(20); key_val=8; }
    if (P3_1 == 0) { delay(20); while(P3_1==0); delay(20); key_val=12; }
    if (P3_2 == 0) { delay(20); while(P3_2==0); delay(20); key_val=16; }
    if (P3_3 == 0) { delay(20); while(P3_3==0); delay(20); key_val=20; }
    
    P3 = 0xff;
    P3_7 = 0;        
    if (P3_0 == 0) { delay(20); while(P3_0==0); delay(20); key_val=9; }
    if (P3_1 == 0) { delay(20); while(P3_1==0); delay(20); key_val=13; }
    if (P3_2 == 0) { delay(20); while(P3_2==0); delay(20); key_val=17; }
    if (P3_3 == 0) { delay(20); while(P3_3==0); delay(20); key_val=21; }
    
    return key_val;
}

unsigned char key_to_data() 
{
    unsigned char key = key_scan();
    get = 0;  // 每次调用重置
        // 普通模式
        if (duli == 1) 
				{
            P1_1 = 0;  // 确保指示灯状态正确
            P1_0 = 1;
            switch(key) 
						{
                case 6:  get = 1;      break;
                case 7:  get = 2;      break;
                case 8:  get = 3;      break;
                case 10: get = 4;      break;
                case 11: get = 5;      break;
                case 12: get = 6;      break;
                case 14: get = 7;      break;
                case 15: get = 8;      break;
                case 16: get = 9;      break;
                case 18: get = '(';    break;
                case 19: get = 0;      break;
                case 20: get = ')';    break;
                case 17: get = '=';    break;
                default: get = 0;      break;
            }
        }
        // FN模式
        else if (duli == 2) 
				{
            P1_0 = 0;  // 确保指示灯状态正确
            P1_1 = 1;
            switch(key) 
						{
                case 6:  get = '+';    break;  // 四则运算符
                case 10: get = '-';    break;
                case 14: get = '*';    break;
                case 18: get = '/';    break;
                case 7:  get = 's';    break;  // 三角运算符（sin）
                case 11: get = 'c';    break;  // cos
                case 15: get = 't';    break;  // tan
                case 19: get = 'n';    break;  // 幂运算符
                case 8:  get = 'u';    break;  // 记忆功能
                case 12: get = 'd';    break;
                case 16: get = 'q';    break;
                case 20: get = 'k';    break;  // 清零
                default: get = 0;      break;
            }
            // 可选：FN模式按功能键后自动退出，恢复普通模式
            // duli = 1;
        }
    
    return get;
}

