// syscalls.c - 实现STM32裸机环境下的newlib系统调用（修复版）
#include <errno.h>
#include <stdint.h>
#include <stddef.h>  // 补充size_t/ptrdiff_t的标准定义
#include <sys/stat.h> // 新增：包含struct stat和S_IFCHR的定义
#include <stdlib.h>

// 定义堆内存的起始和结束地址（根据你的STM32F103配置调整）
// 堆起始地址 = _end（由链接脚本定义），堆结束地址 = RAM末尾
extern uint8_t _end[];
#define HEAP_END (0x20005000)  // STM32F103C8T6的RAM末尾（20KB: 0x20000000 ~ 0x20005000）

static uint8_t *heap_ptr = _end;

// 实现_sbrk函数 - 用于堆内存分配
void *_sbrk(ptrdiff_t incr)
{
    uint8_t *prev_heap_ptr = heap_ptr;

    // 检查堆是否超出RAM范围
    if (heap_ptr + incr > (uint8_t *)HEAP_END)
    {
        errno = ENOMEM;  // 设置内存不足错误
        return (void *)-1;
    }

    heap_ptr += incr;
    return (void *)prev_heap_ptr;
}

// 实现其他必要的系统调用（避免其他链接错误）
int _close(int file)
{
    (void)file; // 抑制未使用参数警告
    errno = ENOSYS;
    return -1;
}

int _fstat(int file, struct stat *st)
{
    (void)file; // 抑制未使用参数警告
    if (st != NULL) {
        st->st_mode = S_IFCHR; // 标记为字符设备
    }
    return 0;
}

int _isatty(int file)
{
    (void)file;
    return 1; // 模拟终端设备
}

int _lseek(int file, int ptr, int dir)
{
    (void)file;
    (void)ptr;
    (void)dir;
    return 0;
}

int _read(int file, char *ptr, int len)
{
    (void)file;
    (void)ptr;
    (void)len;
    return 0; // 无输入，返回0
}

int _write(int file, char *ptr, int len)
{
    (void)file;
    (void)ptr;
    (void)len;
    return len; // 模拟输出成功
}

// 可选：如果后续还有其他未定义引用，可添加以下函数
int _kill(int pid, int sig)
{
    (void)pid;
    (void)sig;
    errno = ENOSYS;
    return -1;
}

int _getpid(void)
{
    return 1; // 模拟进程ID
}

// 解决 _exit 未定义问题
void _exit(int status)
{
    // 裸机程序不需要退出，这里做死循环即可
    while(1);
}

