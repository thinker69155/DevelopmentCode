#include <REGX52.H>
#include "delay.h"  // 保留原delay.h（若无需可删除，驱动中已内置简单延时）

// OLED I2C引脚定义（可根据实际接线修改，默认P2.0=SCL，P2.1=SDA）
sbit OLED_SCL = P2^0;
sbit OLED_SDIN = P2^1;

// 字库引用（必须包含OLED_Font.h，8x16 ASCII字库）
#include "OLED_Font.h"

// #################### OLED底层I2C驱动（内部使用，不对外暴露） ####################
void IIC_Start(void) {
    OLED_SCL = 1;
    OLED_SDIN = 1;
    OLED_SDIN = 0;
    OLED_SCL = 0;
}

void IIC_Stop(void) {
    OLED_SCL = 1;
    OLED_SDIN = 0;
    OLED_SDIN = 1;
}

void IIC_Wait_Ack(void) {
    OLED_SCL = 1;
    OLED_SCL = 0;
}

void Write_IIC_Byte(unsigned char IIC_Byte) {
    unsigned char i;
    for(i = 0; i < 8; i++) {
        OLED_SDIN = (IIC_Byte >> 7) & 0x01;
        IIC_Byte <<= 1;
        OLED_SCL = 1;
        OLED_SCL = 0;
    }
    IIC_Wait_Ack();
}

void Write_IIC_Cmd(unsigned char Cmd) {
    IIC_Start();
    Write_IIC_Byte(0x78);  // OLED I2C地址（默认0x78，若不显示可改为0x7A）
    Write_IIC_Byte(0x00);  // 写命令标志
    Write_IIC_Byte(Cmd);
    IIC_Stop();
}

void Write_IIC_Data(unsigned char Data) {
    IIC_Start();
    Write_IIC_Byte(0x78);
    Write_IIC_Byte(0x40);  // 写数据标志
    Write_IIC_Byte(Data);
    IIC_Stop();
}

// OLED设置坐标（内部使用，适配LCD1602的行/列规则）
// LCD1602：Line=1~2行，Column=1~16列；OLED：对应页0~1，列0~127
void OLED_Set_Pos(unsigned char Line, unsigned char Column) {
    unsigned char Y = (Line == 1) ? 0 : 1;  // LCD第1行→OLED页0，第2行→OLED页1
    unsigned char X = (Column - 1) * 8;     // LCD列1→OLED列0，每列占8像素（8x16字体）
    Write_IIC_Cmd(0xB0 | Y);                // 设置页地址
    Write_IIC_Cmd(0x10 | ((X & 0xF0) >> 4));// 设置高4位列地址
    Write_IIC_Cmd(0x00 | (X & 0x0F));       // 设置低4位列地址
}

// OLED清屏（内部使用，适配LCD1602清屏逻辑）
void OLED_Clear(void) {
    unsigned char i, j;
    for(i = 0; i < 2; i++) {  // 只清前2页（对应LCD1602的2行）
        Write_IIC_Cmd(0xB0 + i);
        Write_IIC_Cmd(0x00);
        Write_IIC_Cmd(0x10);
        for(j = 0; j < 128; j++) Write_IIC_Data(0x00);
    }
}

// OLED初始化（内部使用）
void OLED_Init(void) {
    delay(100);  // 上电延时稳定
    Write_IIC_Cmd(0xAE);  // 关闭显示
    Write_IIC_Cmd(0x00);  // 低列地址
    Write_IIC_Cmd(0x10);  // 高列地址
    Write_IIC_Cmd(0x40);  // 起始行地址
    Write_IIC_Cmd(0xB0);  // 页地址模式
    Write_IIC_Cmd(0x81);  // 对比度控制
    Write_IIC_Cmd(0xCF);  // 对比度值（0x00~0xFF，可微调）
    Write_IIC_Cmd(0xA1);  // 段重映射
    Write_IIC_Cmd(0xA6);  // 正常显示
    Write_IIC_Cmd(0xA8);  // 多路复用比
    Write_IIC_Cmd(0x3F);  // 1/32占空比
    Write_IIC_Cmd(0xC8);  // 行重映射
    Write_IIC_Cmd(0xD3);  // 显示偏移
    Write_IIC_Cmd(0x00);  // 偏移0
    Write_IIC_Cmd(0xD5);  // 振荡频率
    Write_IIC_Cmd(0x80);  // 默认频率
    Write_IIC_Cmd(0xD9);  // 预充电周期
    Write_IIC_Cmd(0xF1);  // 预充电配置
    Write_IIC_Cmd(0xDA);  // COM引脚配置
    Write_IIC_Cmd(0x12);  // COM硬件配置
    Write_IIC_Cmd(0xDB);  // VCOMH电压
    Write_IIC_Cmd(0x40);  // VCOMH输出
    Write_IIC_Cmd(0x20);  // 内存地址模式
    Write_IIC_Cmd(0x02);  // 页地址模式
    Write_IIC_Cmd(0x8D);  // 电荷泵控制
    Write_IIC_Cmd(0x14);  // 开启电荷泵
    Write_IIC_Cmd(0xAF);  // 开启显示
    OLED_Clear();         // 清屏
}

// #################### 完全兼容LCD1602的对外接口（函数名/参数/功能不变） ####################
/**
  * @brief  OLED初始化（完全兼容LCD1602_Init()）
  * @param  无
  * @retval 无
  */
void LCD_Init() {
    OLED_Init();  // 内部调用OLED初始化
}

/**
  * @brief  在指定位置显示一个字符（完全兼容LCD1602_ShowChar()）
  * @param  Line 行位置，范围：1~2（与LCD1602一致）
  * @param  Column 列位置，范围：1~16（与LCD1602一致）
  * @param  Char 要显示的字符（ASCII码）
  * @retval 无
  */
void LCD_ShowChar(unsigned char Line, unsigned char Column, char Char) {
    unsigned char i;
    OLED_Set_Pos(Line, Column);
    // F8x16[字符索引][点阵字节索引]，二维数组引用，无语法错误
    for(i = 0; i < 8; i++) {
        Write_IIC_Data(F8x16[Char - ' '][i]);  // 上半部分8字节
    }
    OLED_Set_Pos(Line, Column);
    for(i = 0; i < 8; i++) {
        Write_IIC_Data(F8x16[Char - ' '][i + 8]);  // 下半部分8字节
    }
}

/**
  * @brief  在指定位置显示字符串（完全兼容LCD1602_ShowString()）
  * @param  Line 起始行位置，范围：1~2
  * @param  Column 起始列位置，范围：1~16
  * @param  String 要显示的字符串
  * @retval 无
  */
void LCD_ShowString(unsigned char Line, unsigned char Column, char *String) {
    unsigned char i;
    for(i = 0; String[i] != '\0'; i++) {
        // 列数超过16则换行（与LCD1602逻辑一致）
        if(Column + i > 16) {
            Line = Line == 1 ? 2 : 1;
            Column = 1;
        }
        LCD_ShowChar(Line, Column + i, String[i]);
    }
}

/**
  * @brief  返回值=X的Y次方（内部辅助函数，与LCD1602一致）
  */
int LCD_Pow(int X, int Y) {
    unsigned char i;
    int Result = 1;
    for(i = 0; i < Y; i++) {
        Result *= X;
    }
    return Result;
}

/**
  * @brief  显示无符号数字（完全兼容LCD1602_ShowNum()）
  * @param  Line 起始行位置，范围：1~2
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~65535
  * @param  Length 要显示数字的长度，范围：1~5
  * @retval 无
  */
void LCD_ShowNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length) {
    unsigned char i;
    for(i = Length; i > 0; i--) {
        LCD_ShowChar(Line, Column + Length - i, Number / LCD_Pow(10, i - 1) % 10 + '0');
    }
}

/**
  * @brief  显示带符号数字（完全兼容LCD1602_ShowSignedNum()）
  * @param  Line 起始行位置，范围：1~2
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：-32768~32767
  * @param  Length 要显示数字的长度，范围：1~5
  * @retval 无
  */
void LCD_ShowSignedNum(unsigned char Line, unsigned char Column, int Number, unsigned char Length) {
    unsigned char i;
    unsigned int Number1;
    if(Number >= 0) {
        LCD_ShowChar(Line, Column, '+');
        Number1 = Number;
    } else {
        LCD_ShowChar(Line, Column, '-');
        Number1 = -Number;
    }
    for(i = Length; i > 0; i--) {
        LCD_ShowChar(Line, Column + Length - i + 1, Number1 / LCD_Pow(10, i - 1) % 10 + '0');
    }
}

/**
  * @brief  显示十六进制数字（完全兼容LCD1602_ShowHexNum()）
  * @param  Line 起始行位置，范围：1~2
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~0xFFFF
  * @param  Length 要显示数字的长度，范围：1~4
  * @retval 无
  */
void LCD_ShowHexNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length) {
    unsigned char i, SingleNumber;
    for(i = Length; i > 0; i--) {
        SingleNumber = Number / LCD_Pow(16, i - 1) % 16;
        if(SingleNumber < 10) {
            LCD_ShowChar(Line, Column + Length - i, SingleNumber + '0');
        } else {
            LCD_ShowChar(Line, Column + Length - i, SingleNumber - 10 + 'A');
        }
    }
}

/**
  * @brief  显示二进制数字（完全兼容LCD1602_ShowBinNum()）
  * @param  Line 起始行位置，范围：1~2
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~0xFFFF
  * @param  Length 要显示数字的长度，范围：1~16
  * @retval 无
  */
void LCD_ShowBinNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length) {
    unsigned char i;
    for(i = Length; i > 0; i--) {
        LCD_ShowChar(Line, Column + Length - i, Number / LCD_Pow(2, i - 1) % 2 + '0');
    }
}