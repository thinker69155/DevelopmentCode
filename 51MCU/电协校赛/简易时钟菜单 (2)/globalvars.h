#ifndef __GLOBALVARS_H__
#define __GLOBALVARS_H__


// 模式定义
#define CALENDAR 0      // 日历模式
#define COUNTDOWN 1     // 倒计时模式
#define STOPWATCH 2     // 秒表模式（1ms精度）
#define VIEW_RECORD 3   // 查看记录模式
// 全局变量
extern unsigned char mode ;//模式
extern unsigned char set_flag ;//判断是否在设置的标志位
extern unsigned char select_pos ;//选择的位置

// 1ms中断标志和计数器
extern unsigned char flag_1ms ; // 1ms标志位
extern unsigned int ms_cnt ; // 毫秒计数器
extern unsigned char flag_1s ; // 1秒标志位

// 日历数据
extern unsigned int calendar[6] ;
// 倒计时数据
extern unsigned int countdown[3] ;
extern bit countdown_running ;
// 秒表数据
extern unsigned int stopwatch[4] ;  
extern bit stopwatch_running ;
// 秒表记录
extern unsigned int records[3][3] ;  // 时/分/秒
extern unsigned char record_cnt;
extern unsigned char view_idx ;
extern unsigned char record_idx ;  // 下次保存的索引
#endif 