#ifndef __LCD1602_H__
#define __LCD1602_H__

//用户调用函数：
void LCD_WriteCommand(unsigned char Command);



void LCD_Init();
void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char);
void LCD_ShowString(unsigned char Line,unsigned char Column,char *String);
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length);
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void lcd_show_str(unsigned char x, unsigned char y, unsigned char *str);
//void lcd_show_num(unsigned char x, unsigned char y, unsigned int num, unsigned char n);
//void lcd_write_dat(unsigned char dat);
//void lcd_write_cmd(unsigned char cmd);
#endif
