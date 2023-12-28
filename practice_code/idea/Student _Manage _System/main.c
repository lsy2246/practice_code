//头文件
#include <stdio.h>
#include <windows.h>
#include <conio.h>

//自定义头文件
#include "founction_statement_page.h"//界面
#include "function_statement_effect.h"//功能

//主函数
int main ( void )
{
    //定义变量
    char start_pick='0';//开始的选择

    while(1)
    {
        //打印菜单
        HideCursor ();//隐藏光标
        system ( "cls" );//清屏
        printf ( "\n\n\n\n\n\n\n\n" );
        color(2);//设置颜色
        printf ("\t\t\t\t\t\t————欢迎使用学生管理系统————\n");
        color(1);//设置颜色
        printf ("\t\t\t\t\t\t[Enter]");
        color(7);//设置颜色
        printf ("  进入程序\n");
        color(1);//设置颜色
        printf ( "\t\t\t\t\t\t[ESC]" );
        color(7);//设置颜色
        printf ("    退出程序\n");
        color(4);//设置颜色
        printf ("\t\t\t\t\t\t按下相应按键进入对应模式\n");
        //获取用户的输入
        start_pick=(char)_getch();
        //判断用户输入
        switch(start_pick)
        {
            case ENTER:
            {

                break;
            }
            case ESC:
            {
                return 0;
            }
        }
    }
    return 0;
}

