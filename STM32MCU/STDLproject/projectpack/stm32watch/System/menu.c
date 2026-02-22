#include <stddef.h>
#include "stm32f10x.h"
#include "MyRTC.h"
#include "OLED.h"

#include "Key.h"
#include "Flashlight.h"
#include "Communciate.h"
#include "Time.h"
#include "Emoji.h"
uint8_t choose=0;//局部变量，储存在首页选择的选项的值

//移动动画相关函数//////////////////////////////////////////////////////////////////////////////////////

void Mouse() {
    //光标显示，光标移动
}
//时间设置的每个时间的UI的结构体
//菜单中每一项的结构体


//显示函数//////////////////////////////////////////////////////////////
/**
 * 首页菜单显示函数
 */
void First_Page_DisPlay() {
    //显示电量（未设计）
    Show_Time();//显示时分秒，年月日
}
/**
 * 时间设置菜单显示函数1
 */
void Time_Set_Page_Display_1(void)
{
    OLED_Printf(0,0,OLED_8X16,"<-");
    OLED_Printf(0,16,OLED_8X16,"年",MyRTC_Time[0]);
    OLED_Printf(0,32,OLED_8X16,"月",MyRTC_Time[1]);
    OLED_Printf(0,48,OLED_8X16,"日",MyRTC_Time[2]);
}
/**
 * 时间设置菜单显示函数2
 */
void Time_Set_Page_Display_2(void)
{
    OLED_Printf(0,0,OLED_8X16,"时",MyRTC_Time[3]);
    OLED_Printf(0,16,OLED_8X16,"分",MyRTC_Time[4]);
    OLED_Printf(0,32,OLED_8X16,"秒",MyRTC_Time[5]);
}
/**
 * 滑动功能菜单显示函数
 */
void Choose_Function_Display() {
    OLED_ShowImage(31, 0, 32, 32,Menu_Graph_Back );
    OLED_Printf(0,32,OLED_8X16,"月",MyRTC_Time[1]);
    OLED_Printf(0,48,OLED_8X16,"日",MyRTC_Time[2]);
}
void CountDown_Display() {
    //显示倒计时的时间，按键1旁边显示设置
}
void StopWatch_Display() {
    //显示倒计时的时间，按键1旁边显示设置
}
//一级菜单函数////////////////////////////////////////////////////////////////

/**
 * 首页菜单函数【一级菜单】
 * @return 首页菜单选择选项的标志位
 */
uint8_t First_Page_Menu() {
    uint8_t first_page_flag = 1;//定义首页选项选择标志位
    while (1) {
        First_Page_DisPlay();//显示首页
        uint8_t temp_flag = Key_To_Flag_Move(&first_page_flag, 2);
        switch (temp_flag) {//检测需要被光标选中的选项
            case 1://光标选择多功能菜单
                OLED_ReverseArea(0,48,32,16);//显示区域反转颜色实现光标选中
                OLED_Update();//刷新显示
                break;
            case 2://光标选择时间设置
                OLED_ReverseArea(96,48,32,16);//显示区域反转颜色实现光标选中
                OLED_Update();//刷新显示
                break;
            case 0://确认执行命令
                return first_page_flag;//确认键按下，返回当前光标选中的选项
            default:// 异常值：默认选中第1项
                first_page_flag = 1;
                OLED_ReverseArea(0, 48, 32, 16);
                OLED_Update();
                break;
        }
    }
}
//二级菜单函数////////////////////////////////////////////////////////////////

/**
 * 功能菜单函数【二级菜单】
 * @return 功能菜单选择选项的标志位
 */
uint8_t Choose_Function_Menu() {
    uint8_t choose_function_flag=1;
    while (1) {
        uint8_t temp_flag = Key_To_Flag_Move(&choose_function_flag, 2);
        switch (temp_flag) {//检测需要被光标选中的选项
            case 1://时间计算功能
                OLED_ShowImage(31, 0, 32, 32,Menu_Graph_Clock );
                OLED_Update();//刷新显示
                break;
            case 2://水平仪测算功能
                OLED_ShowImage(31, 0, 32, 32,Menu_Graph_Elevel );
                OLED_Update();//刷新显示
                break;
            case 3://电子罗盘功能
                OLED_ShowImage(31, 0, 32, 32,Menu_Graph_Compass );
                OLED_Update();//刷新显示
                break;
            case 4://手电筒功能
                OLED_ShowImage(31, 0, 32, 32,Menu_Graph_Flashlight );
                OLED_Update();//刷新显示
                break;
            case 5://姿态解算功能
                OLED_ShowImage(31, 0, 32, 32,Menu_Graph_Balance );
                OLED_Update();//刷新显示
                break;
            case 6://动态表情包功能
                OLED_ShowImage(31, 0, 32, 32,Menu_Graph_Emoji );
                OLED_Update();//刷新显示
                break;
            case 7://小游戏功能
                OLED_ShowImage(31, 0, 32, 32,Menu_Graph_Game);
                OLED_Update();//刷新显示
                break;
            case 8://指令交换功能
                OLED_ShowImage(31, 0, 32, 32,Menu_Graph_Communciate );
                OLED_Update();//刷新显示
                break;
            case 0:return choose_function_flag;//确认键按下，返回当前光标选中的选项
        }

    }
}
/**
 * 时间设置菜单函数【二级菜单】
 * @return 时间设置菜单选择选项的标志位
 */
uint8_t Time_Set_Menu() {
    uint8_t time_set_flag=1;
    while (1) {
        uint8_t temp_flag = Key_To_Flag_Move(&time_set_flag, 8);
        switch (temp_flag) {//检测需要被光标选中的选项
            case 1://显示第一页，返回
                OLED_Clear();
                Time_Set_Page_Display_1();
                OLED_ReverseArea(0,0,16,16);
                OLED_Update();
                break;
            case 2://显示第一页，年
                OLED_Clear();
                Time_Set_Page_Display_1();
                OLED_ReverseArea(0,16,16,16);
                OLED_Update();
                break;
            case 3://显示第一页，月
                OLED_Clear();
                Time_Set_Page_Display_1();
                OLED_ReverseArea(0,32,16,16);
                OLED_Update();
                break;
            case 4://显示第一页，日
                OLED_Clear();
                Time_Set_Page_Display_1();
                OLED_ReverseArea(0,48,16,16);
                OLED_Update();
                break;
            case 5://显示第二页，时
                OLED_Clear();
                Time_Set_Page_Display_2();
                OLED_ReverseArea(0,0,16,16);
                OLED_Update();
                break;
            case 6://显示第二页，分
                OLED_Clear();
                Time_Set_Page_Display_2();
                OLED_ReverseArea(0,16,16,16);
                OLED_Update();
                break;
            case 7://显示第二页，秒
                OLED_Clear();
                Time_Set_Page_Display_2();
                OLED_ReverseArea(0,32,16,16);
                OLED_Update();
                break;
            case 0:return time_set_flag;//确认键按下，返回当前光标选中的选项
            default:// 异常值：默认选中第1项
                time_set_flag = 1;
                OLED_ReverseArea(0,0,16,16);
                OLED_Update();
                break;
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
        uint8_t clock_flag = 0;//定义选项选择标志位
        switch (Key_To_Flag_Move(clock_flag,2)) {//检测需要被光标选中的选项
            case 1:();//工作
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 2:();//设置时间
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 0:return clock_flag;//确认键按下，返回当前光标选中的选项
        }
    }
}
//四级菜单函数//////////////////////////////////////////////////////////////////
//秒表
uint8_t CountDown_Menu() {
    //按键1进入时间设置，默认都是0
    //按键3选择下一项，按键1,2为选中项加减
    //按键3按下3次后自动跳出设置
    //按键1开始，按键2暂停，按键3返回上一级菜单
    while (1) {
        uint8_t countdown_flag=0;
        switch (Key_To_Flag_Move(countdown_flag,2)) {
            case 1:();//默认模式
            case 2:();//设置模式
            case 0:return countdown_flag;//确认键按下，返回当前光标选中的选项
        }
    }
}
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

/**
 * 倒计时选项执行函数【四级】
 * 功能：停表选择的选项，进入相应的菜单
 */
void CountDown_do() {
    if (CountDown_Menu()==0){return;}
    else if (CountDown_Menu()==1){CountDown_Work();}//倒计时执行
    else if (CountDown_Menu()==2){CountDown_Set();}//倒计时设置
}
/**
 * 功能表菜单选项执行函数【三级】
 * 功能：执行功能表菜单选择的选项，进入相应的菜单
 */
void Clock_do() {
    if (Clock_menu()==0){return;}
    else if (Clock_menu()==1){CountDown_do();}//倒计时菜单
    else if (Clock_menu()==2){StopWatch();}//停表
}
/**
 * 时间设置菜单选项执行函数【三级】
 * 功能：执行时间设置菜单选择的选项，进入相应的菜单
 */
void Game_do() {
    if (Game_menu()==0){return;}
    else if (Game_menu()==1){}//打开游戏1
    else if (Game_menu()==2){}//打开游戏2
}
/**
 * 时间设置菜单选项执行函数【二级】
 * 功能：执行时间设置菜单选择的选项，进入相应的菜单
 */
void Time_Set_do() {
    if (Time_Set_Menu()==0){return;}
    else if (Time_Set_Menu()==1){Change_First_Page_Time(1);}//修改年菜单
    else if (Time_Set_Menu()==2){Change_First_Page_Time(2);}//修改月菜单
    else if (Time_Set_Menu()==3){Change_First_Page_Time(3);}//修改日菜单
    else if (Time_Set_Menu()==4){Change_First_Page_Time(4);}//修改时菜单
    else if (Time_Set_Menu()==5){Change_First_Page_Time(5);}//修改分菜单
    else if (Time_Set_Menu()==6){Change_First_Page_Time(6);}//修改秒菜单
}
/**
 * 功能菜单选项执行函数【二级】
 * 功能：功能菜单选择的选项，进入相应的菜单
 */
void Choose_Function_do() {
    if (Choose_Function_Menu()==0){return;}
    else if (Choose_Function_Menu()==1){Clock_do();}//时间计算（秒表，停表）
    //else if (Choose_Function_Menu()==2){Elevel();}//水平仪
    //else if (Choose_Function_Menu()==3){Compass();}//电子罗盘
    else if (Choose_Function_Menu()==4){Flashlight();}//手电筒
    else if (Choose_Function_Menu()==5){Balance();}//姿态解算
    else if (Choose_Function_Menu()==6){Emoji();}//动态表情包
    else if (Choose_Function_Menu()==7){Game();}//小游戏
    else if (Choose_Function_Menu()==8){Communciate();}//上位机交换指令
}
/**
 * 首页选项执行函数【一级】
 * 功能：执行首页选择的选项，进入相应的菜单
 * 整个菜单系统执行的入口
 */
void First_Page_do() {
    if (First_Page_Menu()==2){Time_Set_do();}
    else if (First_Page_Menu()==1){Choose_Function_do();}
}