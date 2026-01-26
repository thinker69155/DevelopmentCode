/*
// 获取4x4矩阵按键值（0~15：0~9、+、-、×、÷、(、)）
unsigned char key_get_val(void) {
    unsigned char val = 0xFF;
    // 行0扫描
    KEY_ROW0 = 0; KEY_ROW1 = 1; KEY_ROW2 = 1; KEY_ROW3 = 1;
    delay_ms(1);
    if(KEY_COL0 == 0) val = 1;    // 1
    else if(KEY_COL1 == 0) val = 2;// 2
    else if(KEY_COL2 == 0) val = 3;// 3
    else if(KEY_COL3 == 0) val = 10;// +
    KEY_ROW0 = 1;
    // 行1扫描
    KEY_ROW1 = 0;
    delay_ms(1);
    if(KEY_COL0 == 0) val = 4;    //4
    else if(KEY_COL1 == 0) val =5; //5
    else if(KEY_COL2 == 0) val =6; //6
    else if(KEY_COL3 == 0) val =11;// -
    KEY_ROW1 =1;
    // 行2扫描
    KEY_ROW2 =0;
    delay_ms(1);
    if(KEY_COL0 ==0) val=7;       //7
    else if(KEY_COL1 ==0) val=8;  //8
    else if(KEY_COL2 ==0) val=9;  //9
    else if(KEY_COL3 ==0) val=12; //×
    KEY_ROW2 =1;
    // 行3扫描
    KEY_ROW3 =0;
    delay_ms(1);
    if(KEY_COL0 ==0) val=14;      //(
    else if(KEY_COL1 ==0) val=0;  //0
    else if(KEY_COL2 ==0) val=15; //)
    else if(KEY_COL3 ==0) val=13; //÷
    KEY_ROW3 =1;
    return val;
}
*/

/*

// LCD写指令（4位模式）
void lcd_write_cmd(unsigned char cmd) 
{
    LCD_RS = 0;                    // 指令模式
    LCD_DATA = (cmd >> 4) & 0x0F;  // 写高4位
    LCD_E = 1;
    delay_ms(1);
    LCD_E = 0;
    LCD_DATA = cmd & 0x0F;         // 写低4位
    LCD_E = 1;
    delay_ms(1);
    LCD_E = 0;
    delay_ms(2);
}

// LCD写数据（4位模式）
void lcd_write_data(unsigned char dat) {
    LCD_RS = 1;                    // 数据模式
    LCD_DATA = (dat >> 4) & 0x0F;  // 写高4位
    LCD_E = 1;
    delay_ms(1);
    LCD_E = 0;
    LCD_DATA = dat & 0x0F;         // 写低4位
    LCD_E = 1;
    delay_ms(1);
    LCD_E = 0;
    delay_ms(2);
}

// LCD显示字符串（x：列0~15，y：行0~1）
void lcd_show_str(unsigned char x, unsigned char y, unsigned char *str) {
    if(y == 0) lcd_write_cmd(0x80 + x);  // 第一行起始地址
    else lcd_write_cmd(0xC0 + x);        // 第二行起始地址
    while(*str != '\0' && x < 16) {
        lcd_write_data(*str);
        str++;
        x++;
    }
}
*/

// 检测按键是否按下（消抖版）
void key_is_pressed(sbit key) 
{
    key_pressed_flag = 0;  // 先默认未按下
    if(key == 0) 
		{         // 检测到按键低电平
        delay_ms(20);      // 消抖延时
        if(key == 0) 
				{     // 消抖后仍为低电平，确认按下
            key_pressed_flag = 1;
        }
    }
}


// 组合键判断：返回1=FN+目标键同时按下，0=否
void is_fn_comb(sbit target_key) 
{
    fn_comb_flag = 0;  // 先默认未触发
    
    // 步骤1：检测FN键是否按下（调用上面的void函数）
    key_is_pressed(KEY_FN);
    unsigned char fn_pressed = key_pressed_flag;  // 暂存FN键状态
    
    // 步骤2：检测目标键是否按下
    key_is_pressed(target_key);
    unsigned char target_pressed = key_pressed_flag;  // 暂存目标键状态
    
    // 步骤3：两个键都按下，才置位组合键标志
    if(fn_pressed == 1 && target_pressed == 1) 
		{
        fn_comb_flag = 1;
    }
}

/ 键盘扫描（4x4矩阵+独立按键）
void key_scan(void) 
{
    // 第一步：处理独立键组合（FN+独立键）
    // 1. FN + KEY_CLR → MC（记忆清除）
    if(is_fn_comb(KEY_CLR))
		{
        memory = 0;  // 记忆值清零
        lcd_show_str(0, 1, "MC: 0.00");  // 第二行提示
        delay_ms(500);  // 提示500ms
        // 等待两个按键同时释放
        while(key_is_pressed(KEY_FN) || key_is_pressed(KEY_CLR));
        disp_update();  // 恢复显示
        return;
    }
    // 2. FN + KEY_M_PLUS → M-（记忆减）
    if(is_fn_comb(KEY_M_PLUS)) 
		{
        memory -= result;  // 记忆值 -= 当前结果
        char mem_str[16];
        sprintf(mem_str, "M-: %.2f", memory);
        lcd_show_str(0, 1, mem_str);
        delay_ms(500);
        while(key_is_pressed(KEY_FN) || key_is_pressed(KEY_M_PLUS));
        disp_update();
        return;
    }

    // 第二步：处理矩阵键组合（FN+矩阵运算符键）
    unsigned char mat_key = matrix_key_scan();  // 扫描矩阵键（下方实现）
    if(mat_key != 0xFF) 
		{  // 有矩阵键按下
        if(key_is_pressed(KEY_FN))
				{  // 检测FN+矩阵键组合
            switch(mat_key) 
							{
                case 10:  // FN + 矩阵键“+” → sin函数
                    sin_func();  // 自定义sin处理函数
                    break;
                case 11:  // FN + 矩阵键“-” → x2函数
                    sq_func();   // 自定义x2处理函数
                    break;
                case 12:  // FN + 矩阵键“×” → x?函数
                    pow_func();  // 自定义x?处理函数
                    break;
                default:
                    break;
            }
            while(key_is_pressed(KEY_FN) || (matrix_key_scan() != 0xFF));
            return;
        }
    }

    // 第三步：处理单键（原逻辑不变，仅保留基础功能）
    // 3.1 独立键单按
    if(key_is_pressed(KEY_EQ))
		{  // 单按= → 计算
        calc_handler();  // 原计算逻辑
        while(key_is_pressed(KEY_EQ));
        return;
    }
    if(key_is_pressed(KEY_CLR)) 
		{  // 单按C → 清零
        reset_calc();
        while(key_is_pressed(KEY_CLR));
        return;
    }
    if(key_is_pressed(KEY_M_PLUS)) 
		{  // 单按M+ → 记忆加
        memory += result;
        char mem_str[16];
        sprintf(mem_str, "M+: %.2f", memory);
        lcd_show_str(0, 1, mem_str);
        delay_ms(500);
        while(key_is_pressed(KEY_M_PLUS));
        disp_update();
        return;
    }

    // 3.2 矩阵键单按（数字、运算符、括号）
    if(mat_key != 0xFF) 
		{
        matrix_key_handler(mat_key);  // 原矩阵键处理逻辑
        while(matrix_key_scan() != 0xFF);
        return;
    }
}
////////////////////////////////////////////////////////////////////////
// x2函数处理
void sq_func(void) 
{
    if(disp_len ==0) return;
    double val = atof((char*)disp_buf);
    result = val * val;
    reset_calc();
    sprintf((char*)disp_buf, "%.1f2=%.2f", val, result);
    disp_len = strlen((char*)disp_buf);
    flag_eq =1;
}

// x?函数处理（先输入底数→FN+×→输入指数→按=）
void pow_func(void) 
{
    if(disp_len ==0) return;
    pow_base = atof((char*)disp_buf);  // 记录底数
    reset_calc();
    sprintf((char*)disp_buf, "%.1f^?", pow_base);  // 提示输入指数
    disp_len = strlen((char*)disp_buf);
    flag_pow =1;  // 标记x?模式
}

// 计算处理（含x?模式判断）
void calc_handler(void) 
{
    if(flag_pow) 
		{  // x?模式：计算底数^指数
        double exp = atof((char*)disp_buf+4);  // 提取指数（跳过"x.xx^?"）
        result = pow(pow_base, exp);
        reset_calc();
        sprintf((char*)disp_buf, "%.1f^%.1f=%.2f", pow_base, exp, result);
        disp_len = strlen((char*)disp_buf);
        flag_pow =0;
    }
		else 
		{  // 普通表达式计算
        disp_buf[disp_len++] = '=';
        calc_expression();  // 原表达式计算逻辑（含括号、优先级）
        char temp[10];
        sprintf(temp, "%.2f", result);
        for(unsigned char i=0; temp[i]!='\0' && disp_len<16; i++) 
				{
            disp_buf[disp_len++] = temp[i];
        }
    }
    flag_eq =1;
}


