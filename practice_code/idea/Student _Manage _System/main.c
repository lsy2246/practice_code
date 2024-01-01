//头文件
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

//自定义头文件
#include "founction_statement_page.h"//界面
#include "function_statement_effect.h"//功能

//初始化全局变量
bool pick_revision = true;//初始化文件是否修改
bool pick_view_mode = false;//视图模式
unsigned int Total =0;//初始化学生总数

//主函数
int main ( void )
{
    //定义变量
    static char start_pick='0';//开始的选择
    srand((unsigned)time(NULL));
    while(1)
    {
        //打印菜单
        HideCursor ();//隐藏光标
        system ( "cls" );//清屏
        printf ( "\n\n\n\n\n\n\n\n" );
        color(2);//设置颜色
        printf ("\t\t\t\t\t\t    欢迎使用学生管理系统\n");

        printf ("\t\t\t\t\t\t");
        for ( int i = 0 ; i < 28 ; ++ i )
        {
            color(rand()%9+1);//设置颜色
            printf ("■");
        }
        printf("\n");
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
        if(_kbhit())
        {
            start_pick=(char)_getch();
        }
        //判断用户输入
        switch(start_pick)
        {
            case ENTER:
            {
                start_pick='0';
                system_start();//管理系统主页
                break;
            }
            case ESC:
            {
                return 0;
            }
        }
        Sleep(2);
    }
    return 0;
}