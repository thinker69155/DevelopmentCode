#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

bit is_digit(unsigned char a);
unsigned char priority(char op);
int calc_op(int a, int b, char op);
int angle(int a, char b);
unsigned char to_int(const unsigned char** p, int* num);
bit calculate(void);
void key_process(void);

#endif  // __CALCULATOR_H__