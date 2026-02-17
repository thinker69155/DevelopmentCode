#include "stm32f10x.h"
#include "Key.h"
#include "Flashlight.h"
#include "Communciate.h"
#include "Time.h"

uint8_t KeyNum=0;//全局变量，记录按键检测的值
uint8_t choose=0;//局部变量，储存在首页选择的选项的值

//移动动画相关函数//////////////////////////////////////////////////////////////////////////////////////

void Mouse() {
    //光标显示，光标移动
}
//时间设置的每个时间的UI的结构体
//菜单中每一项的结构体

/**
 * 标志位移动函数（menu.c内部函数）
 * 配合Key.c文件Key_GetNum()使用
 * @param Flag 需要通过按键进行控制的标志位
 * @param Length 标志位的移动范围：1~Length
 * @return key=1,2返回当前Flag，key=3（按下确认）返回0
 */
uint8_t Key_To_Flag_Move(uint8_t Flag,uint8_t Length) {
    KeyNum=Key_GetNum();
    if (KeyNum==1) {//光标向上移动并选择
        Flag--;
        if (Flag==0){Flag==Length;}
        return Flag;
    }
    else if (KeyNum==2) {//光标向下移动并选择
        Flag++;
        if (Flag==Length+1){Flag==1;}
        return Flag;
    }
    else if (KeyNum==3) {
        return 0;
    }
}
//显示函数//////////////////////////////////////////////////////////////
/**
 * 首页菜单显示函数
 */
void First_Page_DisPlay() {
    //显示电量
    //显示年月日
    Show_Time();//显示时分秒
    //显示设置和菜单
}
/**
 * 时间设置菜单显示函数
 */
void Time_Set_Display() {
    //显示内容：返回上一级，时，分，秒，年，月，日（汉字和当前值）
}
/**
 * 滑动功能菜单显示函数
 */
void Choose_Function_Display() {

}


//一级菜单函数////////////////////////////////////////////////////////////////

/**
 * 首页菜单函数【一级菜单】
 * @return 首页菜单选择选项的标志位
 */
uint8_t First_Page_Menu() {
    while (1) {
        uint8_t first_page_flag = 0;//定义首页选项选择标志位
        switch (Key_To_Flag_Move(first_page_flag,2)) {//检测需要被光标选中的选项
            case 1:First_Page_DisPlay();
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 2:First_Page_DisPlay();
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 0:return first_page_flag;//确认键按下，返回当前光标选中的选项
        }
    }
}
//二级菜单函数////////////////////////////////////////////////////////////////

/**
 * 功能菜单函数【二级菜单】
 * @return 功能菜单选择选项的标志位
 */
uint8_t Choose_Function_Menu() {
    while (1) {
        uint8_t choose_function_flag=0;
        switch (Key_To_Flag_Move(choose_function_flag,2)) {//检测需要被光标选中的选项
            case 1:();//时间计算功能
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 2:();//水平仪测算功能
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 3:();//电子罗盘功能
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 4:();//手电筒功能
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 5:();//姿态解算功能
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 6:();//动态表情包功能
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 7:();//小游戏功能
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 8:();//指令交换功能
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 0:return choose_function_flag;//确认键按下，返回当前光标选中的选项
        }

    }
}
/**
 * 时间设置菜单函数【二级菜单】
 * @return 时间设置菜单选择选项的标志位
 */
uint8_t Time_Set_Menu() {
    while (1) {
        uint8_t time_set_flag=0;
        switch (Key_To_Flag_Move(time_set_flag,7)) {//检测需要被光标选中的选项
            case 1:();
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 2:();
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 3:();
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 4:();
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 5:();
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 6:();
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 0:return time_set_flag;//确认键按下，返回当前光标选中的选项
        }
    }
}
//三级菜单函数////////////////////////////////////////////////////////////////

/**
 * 游戏菜单函数【三级菜单】
 * @return 游戏菜单选择选项的标志位
 */
uint8_t Game_menu() {
    while (1) {
        uint8_t game_flag = 0;//定义首页选项选择标志位
        switch (Key_To_Flag_Move(game_flag,2)) {//检测需要被光标选中的选项
            case 1:();
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 2:();
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 0:return game_flag;//确认键按下，返回当前光标选中的选项
        }
    }
}
/**
 * 功能表菜单函数【三级菜单】
 * @return 功能表菜单选择选项的标志位
 */
uint8_t Clock_menu() {
    while (1) {
        uint8_t clock_flag = 0;//定义首页选项选择标志位
        switch (Key_To_Flag_Move(clock_flag,2)) {//检测需要被光标选中的选项
            case 1:();
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 2:();
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 0:return clock_flag;//确认键按下，返回当前光标选中的选项
        }
    }
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/**
 * 功能表菜单选项执行函数
 * 功能：执行功能表菜单选择的选项，进入相应的菜单
 */
void Clock_do() {
    if (Clock_menu()==0){return;}
    else if (Clock_menu()==1){Change_Time(1);}//打开游戏1
    else if (Clock_menu()==2){Change_Time(2);}//打开游戏2
}
/**
 * 时间设置菜单选项执行函数
 * 功能：执行时间设置菜单选择的选项，进入相应的菜单
 */
void Game_do() {
    if (Game_menu()==0){return;}
    else if (Game_menu()==1){Change_Time(1);}//打开游戏1
    else if (Game_menu()==2){Change_Time(2);}//打开游戏2
}
/**
 * 时间设置菜单选项执行函数
 * 功能：执行时间设置菜单选择的选项，进入相应的菜单
 */
void Time_Set_do() {
    if (Time_Set_Menu()==0){return;}
    else if (Time_Set_Menu()==1){Change_Time(1);}//修改年菜单
    else if (Time_Set_Menu()==2){Change_Time(2);}//修改月菜单
    else if (Time_Set_Menu()==3){Change_Time(3);}//修改日菜单
    else if (Time_Set_Menu()==4){Change_Time(4);}//修改时菜单
    else if (Time_Set_Menu()==5){Change_Time(5);}//修改分菜单
    else if (Time_Set_Menu()==6){Change_Time(6);}//修改秒菜单
}
/**
 * 功能菜单选项执行函数
 * 功能：功能菜单选择的选项，进入相应的菜单
 */
void Choose_Function_do() {
    if (Choose_Function_Menu()==0){return;}
    else if (Choose_Function_Menu()==1){Change_Time(1);}//时间计算
    else if (Choose_Function_Menu()==2){Change_Time(2);}
    else if (Choose_Function_Menu()==3){Change_Time(3);}
    else if (Choose_Function_Menu()==4){Flashlight();}//手电筒
    else if (Choose_Function_Menu()==5){Change_Time(5);}
    else if (Choose_Function_Menu()==6){Change_Time(6);}
    else if (Choose_Function_Menu()==7){Change_Time(5);}//小游戏
    else if (Choose_Function_Menu()==8){Communciate();}//上位机交换指令
}
/**
 * 首页选项执行函数
 * 功能：执行首页选择的选项，进入相应的菜单
 * 整个菜单系统执行的入口
 */
void First_Page_do() {
    if (First_Page_Menu()==2){Time_Set_do();}
    else if (First_Page_Menu()==1){Choose_Function_do();}
}