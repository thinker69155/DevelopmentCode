#ifndef __GLOBALVARS_H__
#define __GLOBALVARS_H__


// 模式定义
#define CALENDAR 0      // 日历模式
#define COUNTDOWN 1     // 倒计时模式
#define STOPWATCH 2     // 秒表模式（1ms精度）
#define VIEW_RECORD 3   // 查看记录模式
// 全局变量
extern unsigned char mode ;
extern unsigned char set_flag ;
extern unsigned char select_pos ;

// 关键：1ms中断标志和计数器（直接对应实际毫秒）
extern unsigned char flag_1ms ;               // 1ms标志位
extern unsigned int ms_cnt ;                  // 毫秒计数器（0-999）
extern unsigned char flag_1s ;                // 1秒标志位

// 日历数据
extern unsigned int calendar[6] ;
// 倒计时数据
extern unsigned int countdown[3] ;
extern bit countdown_running ;

// 秒表数据（时/分/秒/毫秒）
extern unsigned int stopwatch[4] ;  // [3]：0-999ms（真实毫秒）
extern bit stopwatch_running ;
// 秒表记录
// 秒表记录（显式初始化所有元素为0，避免随机值）
extern unsigned int records[3][3] ;  // 每条记录：时/分/秒
extern unsigned char record_cnt;
extern unsigned char view_idx ;
extern unsigned char record_idx ;  // 下次保存的索引（用于循环覆盖）
#endif 