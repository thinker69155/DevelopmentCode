#include "ucos_ii.h"
#include "stm32f10x.h"

//
// GCC section utils
//

#define AT_SECTION(section_name)        __attribute__((used)) __attribute__((section("." #section_name)))
#define GET_SECTION_BEGIN(section_name) __start_##section_name
#define GET_SECTION_END(section_name)   __end_##section_name
#define FOREACH_SECTION_VAR(var_type, section_name)                       \
    extern uint32_t GET_SECTION_BEGIN(section_name);                      \
    extern uint32_t GET_SECTION_END(section_name);                        \
    for (uint32_t var_ptr = (uint32_t)(&GET_SECTION_BEGIN(section_name)); \
         var_ptr < (uint32_t)(&GET_SECTION_END(section_name));            \
         var_ptr += sizeof(var_type))
#define FOREACH_SECTION_GET_VAR_PTR(var_type) ((const var_type *)var_ptr)

//
// Task Define utils
//

#define TASK_STK_SIZE_DEFAULT 128 // 128 words == 512 bytes

typedef struct {
    char *name;
    void (*entry)(void *p_arg);
    void *args;
    uint8_t prio;
    OS_STK *stack;
    uint32_t stack_size;
    OS_STK *stack_top;
} Task_DeclareInfo;

#define TaskDefineEx(task_name, entry_name, stk_size, task_prio, args_ptr)                     \
    static OS_STK __app_task_stk__##entry_name[stk_size] __attribute__((used));                \
    void entry_name(void *);                                                                   \
    const static Task_DeclareInfo __app_task_info__##entry_name AT_SECTION(sec_tasks_info) = { \
        .name       = task_name,                                                               \
        .entry      = entry_name,                                                              \
        .args       = args_ptr,                                                                \
        .prio       = task_prio,                                                               \
        .stack      = __app_task_stk__##entry_name,                                            \
        .stack_size = stk_size,                                                                \
        .stack_top  = &__app_task_stk__##entry_name[stk_size - 1],                             \
    };                                                                                         \
    void entry_name(void *args)

#define TaskDefine(entry_name, task_prio, args_ptr) \
    TaskDefineEx(#entry_name, entry_name, TASK_STK_SIZE_DEFAULT, task_prio, args_ptr)

//
// define user tasks here
//

TaskDefineEx("main task", Task_Main, 256, 0, NULL)
{
    while (1) {
        OSTimeDly(500);
    }
}

TaskDefine(Task_WorkIndicator, 1, NULL)
{
    while (1) {
        GPIO_SetBits(GPIOC, GPIO_Pin_13);
        OSTimeDly(500);
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        OSTimeDly(500);
    }
}

//
// main entry point
//

void BoardInit()
{
    SysTick_Config(SystemCoreClock / 1000);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef gpioDef;
    gpioDef.GPIO_Mode  = GPIO_Mode_Out_PP;
    gpioDef.GPIO_Pin   = GPIO_Pin_13;
    gpioDef.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOC, &gpioDef);
}

void Error_Handler(void)
{
    while (1)
    {
    }
}

int main()
{
    BoardInit();

    OSInit();

    FOREACH_SECTION_VAR(Task_DeclareInfo, sec_tasks_info)
    {
        const Task_DeclareInfo *task_info = FOREACH_SECTION_GET_VAR_PTR(Task_DeclareInfo);

        if (OSTaskCreateExt(task_info->entry,
                            task_info->args,
                            task_info->stack_top,
                            task_info->prio,
                            task_info->prio,
                            task_info->stack,
                            task_info->stack_size,
                            NULL,
                            OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR) != OS_ERR_NONE) {
            Error_Handler();
        }

        INT8U err;
        OSTaskNameSet(task_info->prio, (INT8U *)task_info->name, &err);
        if (err != OS_ERR_NONE) {
            Error_Handler();
        }
    }

    OSStart();
}
