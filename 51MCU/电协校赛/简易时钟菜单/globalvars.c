#include <globalvars.h>


// 全局变量
unsigned char mode = CALENDAR;
unsigned char set_flag = 0;
unsigned char select_pos = 0;

// 关键：1ms中断标志和计数器（直接对应实际毫秒）
unsigned char flag_1ms = 0;               // 1ms标志位
unsigned int ms_cnt = 0;                  // 毫秒计数器（0-999）
unsigned char flag_1s = 0;                // 1秒标志位

// 日历数据
unsigned int calendar[6] = {2025, 11, 12, 10, 30, 0};
// 倒计时数据
unsigned int countdown[3] = {0, 0, 10};
bit countdown_running = 0;

// 秒表数据（时/分/秒/毫秒）
unsigned int stopwatch[4] = {0, 0, 0, 0};  // [3]：0-999ms（真实毫秒）
bit stopwatch_running = 0;
// 秒表记录
// 秒表记录（显式初始化所有元素为0，避免随机值）
unsigned int records[3][3] = {{0,0,0}, {0,0,0}, {0,0,0}};  // 每条记录：时/分/秒
unsigned char record_cnt = 0;
unsigned char view_idx = 0;
unsigned char record_idx = 0;  // 下次保存的索引（用于循环覆盖）