#include "stm32f10x.h"
#include "MyRTC.h"
#include "OLED.h"
#include "Key.h"
#include "Flashlight.h"
#include "Communciate.h"
#include "Emoji.h"
#include "Balance.h"
#include "Time_do.h"

static uint8_t first_page_flag = 1;
static uint8_t choose_function_flag = 1;
static uint8_t time_set_flag = 1;
static uint8_t clock_flag = 1;
static uint8_t countdown_flag = 1;

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
    OLED_Printf(0,16,OLED_8X16,"年");
    OLED_Printf(0,32,OLED_8X16,"月");
    OLED_Printf(0,48,OLED_8X16,"日");
}
/**
 * 时间设置菜单显示函数2
 */
void Time_Set_Page_Display_2(void)
{
    OLED_Printf(0,0,OLED_8X16,"时");
    OLED_Printf(0,16,OLED_8X16,"分");
    OLED_Printf(0,32,OLED_8X16,"秒");
}
/**
 * 功能表菜单显示函数
 */
void Clock_Display() {
    OLED_Printf(0,0,OLED_8X16,"<-");
    OLED_Printf(0,16,OLED_8X16,"倒计时");
    OLED_Printf(0,32,OLED_8X16,"停表");
}
//一级菜单函数////////////////////////////////////////////////////////////////

/**
 * 首页菜单函数【一级菜单】
 * @return 首页菜单选择选项的标志位
 */
uint8_t First_Page_Menu() {
    while (1) {
        uint8_t temp_flag = Key_To_Flag_Move_WithFlag(&first_page_flag, 2);

        switch (temp_flag) {
            case 1:
                OLED_Clear();
                First_Page_DisPlay();
                OLED_ReverseArea(0,48,32,16);
                OLED_Update();
                break;
            case 2:
                OLED_Clear();
                First_Page_DisPlay();
                OLED_ReverseArea(96,48,32,16);
                OLED_Update();
                break;
            case 0:return first_page_flag;
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
        uint8_t temp_flag = Key_To_Flag_Move_WithFlag(&choose_function_flag, 8);
        switch (temp_flag) {
            case 1:
                OLED_Clear();
                OLED_ShowImage(46, 0, 32, 32,Menu_Graph_Clock );
                OLED_Printf(0,48,OLED_8X16,"功能表");
                OLED_Update();
                break;
            case 2:
                OLED_Clear();
                OLED_ShowImage(46, 0, 32, 32,Menu_Graph_Elevel );
                OLED_Printf(0,48,OLED_8X16,"水平仪");
                OLED_Update();
                break;
            case 3:
                OLED_Clear();
                OLED_ShowImage(46, 0, 32, 32,Menu_Graph_Compass );
                OLED_Printf(0,48,OLED_8X16,"罗盘");
                OLED_Update();
                break;
            case 4:
                OLED_Clear();
                OLED_ShowImage(46, 0, 32, 32,Menu_Graph_Flashlight );
                OLED_Printf(0,48,OLED_8X16,"手电筒");
                OLED_Update();
                break;
            case 5:
                OLED_Clear();
                OLED_ShowImage(46, 0, 32, 32,Menu_Graph_Balance );
                OLED_Printf(0,48,OLED_8X16,"姿态解算");
                OLED_Update();
                break;
            case 6:
                OLED_Clear();
                OLED_ShowImage(46, 0, 32, 32,Menu_Graph_Emoji );
                OLED_Printf(0,48,OLED_8X16,"表情包");
                OLED_Update();
                break;
            case 7:
                OLED_Clear();
                OLED_ShowImage(46, 0, 32, 32,Menu_Graph_Game);
                OLED_Printf(0,48,OLED_8X16,"游戏");
                OLED_Update();
                break;
            case 8:
                OLED_Clear();
                OLED_ShowImage(46, 0, 32, 32,Menu_Graph_Communciate );
                OLED_Printf(0,48,OLED_8X16,"指令交换");
                OLED_Update();
                break;
            case 0:return choose_function_flag;
        }

    }
}
/**
 * 时间设置菜单函数【二级菜单】
 * @return 时间设置菜单选择选项的标志位
 */
uint8_t Time_Set_Menu() {
    while (1) {
        uint8_t temp_flag = Key_To_Flag_Move_WithFlag(&time_set_flag, 7);
        switch (temp_flag) {
            case 1:
                OLED_Clear();
                Time_Set_Page_Display_1();
                OLED_ReverseArea(0,0,16,16);
                OLED_Update();
                break;
            case 2:
                OLED_Clear();
                Time_Set_Page_Display_1();
                OLED_ReverseArea(0,16,16,16);
                OLED_Update();
                break;
            case 3:
                OLED_Clear();
                Time_Set_Page_Display_1();
                OLED_ReverseArea(0,32,16,16);
                OLED_Update();
                break;
            case 4:
                OLED_Clear();
                Time_Set_Page_Display_1();
                OLED_ReverseArea(0,48,16,16);
                OLED_Update();
                break;
            case 5:
                OLED_Clear();
                Time_Set_Page_Display_2();
                OLED_ReverseArea(0,0,16,16);
                OLED_Update();
                break;
            case 6:
                OLED_Clear();
                Time_Set_Page_Display_2();
                OLED_ReverseArea(0,16,16,16);
                OLED_Update();
                break;
            case 7:
                OLED_Clear();
                Time_Set_Page_Display_2();
                OLED_ReverseArea(0,32,16,16);
                OLED_Update();
                break;
            case 0:return time_set_flag;
        }
    }
}
//三级菜单函数////////////////////////////////////////////////////////////////

/**
 * 游戏菜单函数【三级菜单】
 * @return 游戏菜单选择选项的标志位
 */
/*uint8_t Game_menu() {
    uint8_t game_flag = 1;//定义首页选项选择标志位
    while (1) {
        uint8_t temp_flag = Key_To_Flag_Move(&game_flag, 2);
        switch (temp_flag) {//检测需要被光标选中的选项
            case 1:();
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 2:();
                //显示区域反转颜色实现光标选中
                //刷新显示
            case 0:return game_flag;//确认键按下，返回当前光标选中的选项
        }
    }
}*/
/**
 * 功能表菜单函数【三级菜单】
 * @return 功能表菜单选择选项的标志位
 */
uint8_t Clock_menu() {
    while (1) {
        uint8_t temp_flag = Key_To_Flag_Move_WithFlag(&clock_flag, 3);
        switch (temp_flag) {
            case 1:
                OLED_Clear();
                Clock_Display();
                OLED_ReverseArea(0,0,16,16);
                OLED_Update();
                break;
            case 2:
                OLED_Clear();
                Clock_Display();
                OLED_ReverseArea(0,16,48,16);
                OLED_Update();
                break;
            case 3:
                OLED_Clear();
                Clock_Display();
                OLED_ReverseArea(0,32,32,16);
                OLED_Update();
                break;
            case 0:return clock_flag;
        }
    }
}
//四级菜单函数//////////////////////////////////////////////////////////////////

/**
 * 倒计时菜单处理函数
 * 按键1用于进入时间设置，默认值为0；
 * 按键3用于在菜单项之间移动，按键1和2用于调整当前选中项的值；
 * 连续按三次按键3会自动退出设置；
 * 按键1开始倒计时，按键2暂停倒计时，按键3返回上一级菜单。
 *
 * @return 返回一个uint8_t类型的标志，表示用户最后的选择：1-返回上级菜单；2-工作模式；3-设置模式。
 */
uint8_t CountDown_Menu() {
    while (1) {
        uint8_t temp_flag=Key_To_Flag_Move_WithFlag(&countdown_flag, 3);
        switch (temp_flag) {
            case 1:
                OLED_Clear();
                CountDown_Display();
                OLED_ReverseArea(0,0,16,16);
                OLED_Update();
                break;
            case 2:
                OLED_Clear();
                CountDown_Display();
                OLED_ReverseArea(0,16,32,16);
                OLED_Update();
                break;
            case 3:
                OLED_Clear();
                CountDown_Display();
                OLED_ReverseArea(0,32,24,16);
                OLED_Update();
                break;
            case 0:return countdown_flag;
        }
    }
}
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

/**
 * 倒计时选项执行函数【四级】
 * 功能：停表选择的选项，进入相应的菜单
 */
uint8_t CountDown_do() {
    while (1) {
        uint8_t choose=CountDown_Menu();
        if (choose==1){return 0;}
        else if (choose==2){CountDown_Work();}//倒计时执行
        else if (choose==3){CountDown_Set();}//倒计时设置
    }
}
/**
 * 游戏菜单选项执行函数【三级】
 * 功能：执行游戏菜单选择的选项，进入相应的菜单
 */
/*void Game_do() {
     if (Game_menu()==1){CountDown_Work();}//倒计时菜单
    else if (Game_menu()==2){CountDown_Set();}//停表
}*/
/**
 * 功能表菜单选项执行函数【三级】
 * 功能：执行功能表菜单选择的选项，进入相应的菜单
 */
uint8_t Clock_do() {
    while (1) {
        uint8_t choose=Clock_menu();
        if (choose==1){return 0;}
        else if (choose==2){
            if (CountDown_do() == 0) return 0;
        }
        else if (choose==3){StopWatch();}//停表
    }
}
/**
 * 时间设置菜单选项执行函数【三级】
 * 功能：执行时间设置菜单选择的选项，进入相应的菜单
 */
/*void Game_do() {
     if (Game_menu()==1){}//打开游戏1
    else if (Game_menu()==2){}//打开游戏2
}*/
/**
 * 时间设置菜单选项执行函数【二级】
 * 功能：执行时间设置菜单选择的选项，进入相应的菜单
 */
uint8_t Time_Set_do() {
    while (1) {
        uint8_t choose=Time_Set_Menu();
        if(choose==1){return 0;}
        else if (choose==2){Change_First_Page_Time(1);}//修改年菜单
        else if (choose==3){Change_First_Page_Time(2);}//修改月菜单
        else if (choose==4){Change_First_Page_Time(3);}//修改日菜单
        else if (choose==5){Change_First_Page_Time(4);}//修改时菜单
        else if (choose==6){Change_First_Page_Time(5);}//修改分菜单
        else if (choose==7){Change_First_Page_Time(6);}//修改秒菜单
    }
}
/**
 * 功能菜单选项执行函数【二级】
 * 功能：功能菜单选择的选项，进入相应的菜单
 */
uint8_t Choose_Function_do() {
    while (1) {
        uint8_t choose=Choose_Function_Menu();
        if (choose==1){
            if (Clock_do() == 0) return 0;
        }
        //else if (choose==2){Elevel();}//水平仪
        //else if (choose==3){Compass();}//电子罗盘
        else if (choose==4){Flashlight();}//手电筒
        else if (choose==5){Balance();}//姿态解算
        else if (choose==6){Emoji();}//动态表情包
        //else if (Choose_Function_Menu()==7){Game_do();}//小游戏
        else if (choose==8){Communciate();}//上位机交换指令
    }
}
/**
 * 首页选项执行函数【一级】
 * 功能：执行首页选择的选项，进入相应的菜单
 * 整个菜单系统执行的入口
 */
void First_Page_do() {
    while (1) {
        uint8_t choose=First_Page_Menu();
        if (choose==1){
            Choose_Function_do();
        }
        else if (choose==2){
            Time_Set_do();
        }
    }
}