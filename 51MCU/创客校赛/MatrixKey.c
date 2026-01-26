#include <REGX52.H>
#include "delay.h"
#include "calculator.h"
// -------------------------- 3.1 总键盘扫描函数：返回按下按键的编号（0~19），无按键返回0xFF --------------------------
void key_scan_all(void) 
{
    unsigned char key_num = 0xFF;  // 初始化为无按键

    // 第一步：扫描4个独立键（编号16~19）
    if(KEY_EQ_PIN == 0) { delay_ms(20); if(KEY_EQ_PIN == 0) key_num = KEY_EQ; }
    else if(KEY_CLR_PIN == 0) { delay_ms(20); if(KEY_CLR_PIN == 0) key_num = KEY_CLR; }
    else if(KEY_M_PLUS_PIN == 0) { delay_ms(20); if(KEY_M_PLUS_PIN == 0) key_num = KEY_M_PLUS; }
    else if(KEY_FN_PIN == 0) { delay_ms(20); if(KEY_FN_PIN == 0) key_num = KEY_FN; }

    // 第二步：扫描4×4矩阵键（编号0~15）
    if(key_num == 0xFF) {  // 若独立键未按下，扫描矩阵键
        // 行0扫描（1、2、3、+）
        KEY_ROW0 = 0; KEY_ROW1=1; KEY_ROW2=1; KEY_ROW3=1;
        delay_ms(1);
        if(KEY_COL0 == 0) key_num = KEY_1;
        else if(KEY_COL1 == 0) key_num = KEY_2;
        else if(KEY_COL2 == 0) key_num = KEY_3;
        else if(KEY_COL3 == 0) key_num = KEY_ADD;
        KEY_ROW0 = 1;

        // 行1扫描（4、5、6、-）
        if(key_num == 0xFF) {
            KEY_ROW1 = 0; delay_ms(1);
            if(KEY_COL0 == 0) key_num = KEY_4;
            else if(KEY_COL1 == 0) key_num = KEY_5;
            else if(KEY_COL2 == 0) key_num = KEY_6;
            else if(KEY_COL3 == 0) key_num = KEY_SUB;
            KEY_ROW1 = 1;
        }

        // 行2扫描（7、8、9、×）
        if(key_num == 0xFF) {
            KEY_ROW2 = 0; delay_ms(1);
            if(KEY_COL0 == 0) key_num = KEY_7;
            else if(KEY_COL1 == 0) key_num = KEY_8;
            else if(KEY_COL2 == 0) key_num = KEY_9;
            else if(KEY_COL3 == 0) key_num = KEY_MUL;
            KEY_ROW2 = 1;
        }

        // 行3扫描（(、0、)、÷）
        if(key_num == 0xFF) {
            KEY_ROW3 = 0; delay_ms(1);
            if(KEY_COL0 == 0) key_num = KEY_L_BRACK;
            else if(KEY_COL1 == 0) key_num = KEY_0;
            else if(KEY_COL2 == 0) key_num = KEY_R_BRACK;
            else if(KEY_COL3 == 0) key_num = KEY_DIV;
            KEY_ROW3 = 1;
        }
    }

    return key_num;  // 返回按键编号（0~19）或0xFF（无按键）
}

// -------------------------- 检测“指定编号的按键”是否按下（参数=按键编号）--------------------------
void key_processed(unsigned char key_num)	
{
    key_pressed_flag = 0;  // 默认未按下

    // 根据按键编号，检测对应引脚电平
    switch(key_num) 
		{
        // 独立键
        case KEY_EQ:      if(KEY_EQ_PIN == 0) { delay_ms(20); if(KEY_EQ_PIN == 0) key_pressed_flag = 1; } break;
        case KEY_CLR:     if(KEY_CLR_PIN == 0) { delay_ms(20); if(KEY_CLR_PIN == 0) key_pressed_flag = 1; } break;
        case KEY_M_PLUS:  if(KEY_M_PLUS_PIN == 0) { delay_ms(20); if(KEY_M_PLUS_PIN == 0) key_pressed_flag = 1; } break;
        case KEY_FN:      if(KEY_FN_PIN == 0) { delay_ms(20); if(KEY_FN_PIN == 0) key_pressed_flag = 1; } break;
        // 矩阵键
        case KEY_1:       KEY_ROW0=0; delay_ms(1); if(KEY_COL0==0) { delay_ms(20); if(KEY_COL0==0) key_pressed_flag=1; } KEY_ROW0=1; break;
        case KEY_2:       KEY_ROW0=0; delay_ms(1); if(KEY_COL1==0) { delay_ms(20); if(KEY_COL1==0) key_pressed_flag=1; } KEY_ROW0=1; break;
        case KEY_3:       KEY_ROW0=0; delay_ms(1); if(KEY_COL2==0) { delay_ms(20); if(KEY_COL2==0) key_pressed_flag=1; } KEY_ROW0=1; break;
        case KEY_ADD:     KEY_ROW0=0; delay_ms(1); if(KEY_COL3==0) { delay_ms(20); if(KEY_COL3==0) key_pressed_flag=1; } KEY_ROW0=1; break;
        case KEY_4:       KEY_ROW1=0; delay_ms(1); if(KEY_COL0==0) { delay_ms(20); if(KEY_COL0==0) key_pressed_flag=1; } KEY_ROW1=1; break;
        case KEY_5:       KEY_ROW1=0; delay_ms(1); if(KEY_COL1==0) { delay_ms(20); if(KEY_COL1==0) key_pressed_flag=1; } KEY_ROW1=1; break;
        case KEY_6:       KEY_ROW1=0; delay_ms(1); if(KEY_COL2==0) { delay_ms(20); if(KEY_COL2==0) key_pressed_flag=1; } KEY_ROW1=1; break;
        case KEY_SUB:     KEY_ROW1=0; delay_ms(1); if(KEY_COL3==0) { delay_ms(20); if(KEY_COL3==0) key_pressed_flag=1; } KEY_ROW1=1; break;
        case KEY_7:       KEY_ROW2=0; delay_ms(1); if(KEY_COL0==0) { delay_ms(20); if(KEY_COL0==0) key_pressed_flag=1; } KEY_ROW2=1; break;
        case KEY_8:       KEY_ROW2=0; delay_ms(1); if(KEY_COL1==0) { delay_ms(20); if(KEY_COL1==0) key_pressed_flag=1; } KEY_ROW2=1; break;
        case KEY_9:       KEY_ROW2=0; delay_ms(1); if(KEY_COL2==0) { delay_ms(20); if(KEY_COL2==0) key_pressed_flag=1; } KEY_ROW2=1; break;
        case KEY_MUL:     KEY_ROW2=0; delay_ms(1); if(KEY_COL3==0) { delay_ms(20); if(KEY_COL3==0) key_pressed_flag=1; } KEY_ROW2=1; break;
        case KEY_L_BRACK: KEY_ROW3=0; delay_ms(1); if(KEY_COL0==0) { delay_ms(20); if(KEY_COL0==0) key_pressed_flag=1; } KEY_ROW3=1; break;
        case KEY_0:       KEY_ROW3=0; delay_ms(1); if(KEY_COL1==0) { delay_ms(20); if(KEY_COL1==0) key_pressed_flag=1; } KEY_ROW3=1; break;
        case KEY_R_BRACK: KEY_ROW3=0; delay_ms(1); if(KEY_COL2==0) { delay_ms(20); if(KEY_COL2==0) key_pressed_flag=1; } KEY_ROW3=1; break;
        case KEY_DIV:     KEY_ROW3=0; delay_ms(1); if(KEY_COL3==0) { delay_ms(20); if(KEY_COL3==0) key_pressed_flag=1; } KEY_ROW3=1; break;
        default: break;
    }
}

// -------------------------- 3.3 void函数：检测“FN+指定编号按键”是否同时按下（参数=目标按键编号）--------------------------
void is_fn_comb(unsigned char target_key_num) 
{
    fn_comb_flag = 0;  // 默认未触发

    // 步骤1：检测FN键（编号KEY_FN）是否按下
    key_process(KEY_FN);
    unsigned char fn_pressed = key_pressed_flag;

    // 步骤2：检测目标键是否按下
    key_is_pressed(target_key_num);
    unsigned char target_pressed = key_pressed_flag;

    // 步骤3：两个键都按下，置位组合键标志
    if(fn_pressed == 1 && target_pressed == 1) 
		{
        fn_comb_flag = 1;
    }
}