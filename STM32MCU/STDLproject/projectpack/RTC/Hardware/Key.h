#ifndef __KEY_H__
#define __KEY_H__

// 定义按键状态枚举
typedef enum {
    KEY_DOWN,
    KEY_UP,
} KeyStatus;

// 定义按键事件枚举
typedef enum {
    NULL_PRESS,
    SHORT_PRESS,
    LONG_PRESS
} KeyEvent;

// 定义按键配置结构体
typedef struct {
    KeyStatus status;
    KeyEvent event;
    uint16_t LongPressCount;
} KeyHandler;

extern KeyHandler Key[4];
extern uint16_t KEY[4];
extern GPIO_TypeDef* Key_Prot[4];
extern uint16_t Key_Pin[4];

void Key_Init(void);
void Key_handler(void);

#endif