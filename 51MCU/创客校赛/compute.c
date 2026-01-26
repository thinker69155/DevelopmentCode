#include "calculator.h"
#include "delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"
// 表达式计算相关函数（简化版，保持原功能）
double calc_op(double a, double b, char op) 
{
    switch(op) 
		{
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b != 0) ? (a / b) : 0;
        default: return 0;
    }
}

void calc_expression(void) 
{
    char expr[32] = {0};
    unsigned char i, j=0;
    for(i=0; i<disp_len; i++) 
		{
        if(disp_buf[i] == '×') expr[j++] = '*';
        else if(disp_buf[i] == '÷') expr[j++] = '/';
        else expr[j++] = disp_buf[i];
    }
    // 表达式计算
    double num_stack[16], op_stack[16];
    unsigned char num_idx=0, op_idx=0;
    double num=0, sign=1;
    char *p = expr;
    while(*p != '\0') 
		{
        if(*p >= '0' && *p <= '9') 
				{
            num = num*10 + (*p-'0');
            p++;
            if(*p < '0' || *p > '9') 
						{
                num_stack[num_idx++] = num*sign;
                num=0; sign=1;
            }
        } 
				else if(*p == '(') { op_stack[op_idx++] = *p; p++; }
        else if(*p == ')') 
				{
            while(op_idx>0 && op_stack[op_idx-1] != '(') 
						{
                double b=num_stack[--num_idx], a=num_stack[--num_idx];
                char op=op_stack[--op_idx];
                num_stack[num_idx++] = calc_op(a, b, op);
            }
            op_idx--; p++;
        } 
				else if(*p == '+' || *p == '-') 
				{
            while(op_idx>0 && op_stack[op_idx-1] != '(') 
						{
                double b=num_stack[--num_idx], a=num_stack[--num_idx];
                char op=op_stack[--op_idx];
                num_stack[num_idx++] = calc_op(a, b, op);
            }
            op_stack[op_idx++] = *p; p++;
        } 
				else if(*p == '*' || *p == '/') 
				{
            while(op_idx>0 && (op_stack[op_idx-1] == '*' || op_stack[op_idx-1] == '/')) 
						{
                double b=num_stack[--num_idx], a=num_stack[--num_idx];
                char op=op_stack[--op_idx];
                num_stack[num_idx++] = calc_op(a, b, op);
            }
            op_stack[op_idx++] = *p; p++;
        } else p++;
    }
    while(op_idx>0) 
		{
        double b=num_stack[--num_idx], a=num_stack[--num_idx];
        char op=op_stack[--op_idx];
        num_stack[num_idx++] = calc_op(a, b, op);
    }
    result = num_stack[0];
}

// 科学功能处理函数
void sin_func(double angle) 
{
    result = sin(angle * 3.1415926 / 180);
    reset_calc();
    sprintf((char*)disp_buf, "sin(%.1f)=%.2f", angle, result);
    disp_len = strlen((char*)disp_buf);
    flag_eq = 1;
}

void sq_func(double val) 
{
    result = val * val;
    reset_calc();
    sprintf((char*)disp_buf, "%.1f2=%.2f", val, result);
    disp_len = strlen((char*)disp_buf);
    flag_eq = 1;
}

void pow_func(double base) 
{
    pow_base = base;
    reset_calc();
    sprintf((char*)disp_buf, "%.1f^?", pow_base);
    disp_len = strlen((char*)disp_buf);
    flag_pow = 1;
}
//////////////////////////////////////////////////////////////////////////////////////////////
// 主键盘处理函数（调用总扫描函数，获取编号后处理）
void key_process(unsigned char key_num) 
{
    if(key_num == 0xFF) return;  // 无按键，直接返回

    // 先处理组合键（FN+目标键）
    // 1. FN + KEY_CLR → MC（记忆清除）
    is_fn_comb(KEY_CLR);
    if(fn_comb_flag == 1) 
		{
        memory = 0;
        lcd_show_str(0, 1, "MC: 0.00");
        delay_ms(500);
        // 等待按键释放
        while(1) 
				{ 
					is_fn_comb(KEY_CLR); 
					if(fn_comb_flag == 0) break; 
				}
        disp_update();
        return;
    }

    // 2. FN + KEY_M_PLUS → M-（记忆减）
    is_fn_comb(KEY_M_PLUS);
    if(fn_comb_flag == 1) 
		{
        memory -= result;
        char mem_str[16];
        sprintf(mem_str, "M-: %.2f", memory);//?
        lcd_show_str(0, 1, mem_str);
        delay_ms(500);
        while(1) 
				{ 
					is_fn_comb(KEY_M_PLUS); 
					if(fn_comb_flag == 0) break;
				}
        disp_update();
        return;
    }

    // 3. FN + KEY_ADD（矩阵键+）→ sin函数
    is_fn_comb(KEY_ADD);
    if(fn_comb_flag == 1) 
		{
        if(disp_len > 0) 
				{					
            double angle = atof((char*)disp_buf);
            sin_func(angle);
        }
        while(1) 
				{ 
					is_fn_comb(KEY_ADD); 
					if(fn_comb_flag == 0) break; 
				}
        return;
    }

    // 4. FN + KEY_SUB（矩阵键-）→ x2函数
    is_fn_comb(KEY_SUB);
    if(fn_comb_flag == 1) 
		{
        if(disp_len > 0) 
				{
            double val = atof((char*)disp_buf);
            sq_func(val);
        }
        while(1) { is_fn_comb(KEY_SUB); if(fn_comb_flag == 0) break; }
        return;
    }

    // 5. FN + KEY_MUL（矩阵键×）→ x?函数
    is_fn_comb(KEY_MUL);
    if(fn_comb_flag == 1) 
		{
        if(disp_len > 0) 
				{
            double base = atof((char*)disp_buf);
            pow_func(base);
        }
        while(1) { is_fn_comb(KEY_MUL); if(fn_comb_flag == 0) break; }
        return;
    }

    // 再处理单键
    if(flag_eq) 
		{ reset_calc(); flag_eq = 0; }  // 按等号后清屏重输

    // 数字键（0~9）
    if(key_num == KEY_0 || key_num == KEY_1 || key_num == KEY_2 || key_num == KEY_3 || 
       key_num == KEY_4 || key_num == KEY_5 || key_num == KEY_6 || key_num == KEY_7 || 
       key_num == KEY_8 || key_num == KEY_9) 
		{
        char num_char[] = {'0','1','2','3','4','5','6','7','8','9'};
        if(key_num == KEY_0) disp_buf[disp_len++] = num_char[0];
        else if(key_num == KEY_1) disp_buf[disp_len++] = num_char[1];
        else if(key_num == KEY_2) disp_buf[disp_len++] = num_char[2];
        else if(key_num == KEY_3) disp_buf[disp_len++] = num_char[3];
        else if(key_num == KEY_4) disp_buf[disp_len++] = num_char[4];
        else if(key_num == KEY_5) disp_buf[disp_len++] = num_char[5];
        else if(key_num == KEY_6) disp_buf[disp_len++] = num_char[6];
        else if(key_num == KEY_7) disp_buf[disp_len++] = num_char[7];
        else if(key_num == KEY_8) disp_buf[disp_len++] = num_char[8];
        else if(key_num == KEY_9) disp_buf[disp_len++] = num_char[9];
        disp_len = (disp_len > 15) ? 15 : disp_len;  // 限制显示长度
    }

    // 运算符（+、-、×、÷）
    else if(key_num == KEY_ADD) { if(disp_len < 15) disp_buf[disp_len++] = '+'; }
    else if(key_num == KEY_SUB) { if(disp_len < 15) disp_buf[disp_len++] = '-'; }
    else if(key_num == KEY_MUL) { if(disp_len < 15) disp_buf[disp_len++] = '×'; }
    else if(key_num == KEY_DIV) { if(disp_len < 15) disp_buf[disp_len++] = '÷'; }

    // 括号
    else if(key_num == KEY_L_BRACK) { if(disp_len < 15) disp_buf[disp_len++] = '('; }
    else if(key_num == KEY_R_BRACK) { if(disp_len < 15) disp_buf[disp_len++] = ')'; }

    // 独立键：=（计算）
    else if(key_num == KEY_EQ) 
		{
        if(flag_pow) 
				{
            double exp = atof((char*)disp_buf+4);
            result = pow(pow_base, exp);
            reset_calc();
            sprintf((char*)disp_buf, "%.1f^%.1f=%.2f", pow_base, exp, result);
            disp_len = strlen((char*)disp_buf);
            flag_pow = 0;
        } 
				else 
				{
            disp_buf[disp_len++] = '=';
            calc_expression();
            char temp[10];
            sprintf(temp, "%.2f", result);
            for(unsigned char i=0; temp[i]!='\0' && disp_len<16; i++) 
						{
                disp_buf[disp_len++] = temp[i];
            }
        }
        flag_eq = 1;
    }

    // 独立键：C（清零）
    else if(key_num == KEY_CLR) 
		{
        reset_calc();
    }

    // 独立键：M+（记忆加）
    else if(key_num == KEY_M_PLUS) 
		{
        memory += result;
        char mem_str[16];
        sprintf(mem_str, "M+: %.2f", memory);
        lcd_show_str(0, 1, mem_str);
        delay_ms(500);
        disp_update();
    }

    // 等待按键释放
    while(key_scan_all() != 0xFF);
}







