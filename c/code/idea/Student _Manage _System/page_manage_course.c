//头文件
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

//自定义头文件
#include "founction_statement_page.h"//界面
#include "function_statement_effect.h"//功能


static void course_print_view(void)//打印列表模式
{
    //将原来的清空
    for ( int i = 3 ; i < 28 ; ++ i )
    {
        for ( int j = 0 ; j < 100 ; ++ j )
        {
            CursorJump ( i , j );//位置跳转
            printf (" ");
        }
    }
    for ( int i = 4 ; i < 28 ;  i+=2 )
    {
        for ( int j = 6 ; j < 92 ; j+=10 )
        {
            CursorJump ( i , j );//位置跳转
            color (11);
            printf ("%s",that_person.name);
        }
    }
}

static void course_printf_start_image ( void )//打印图像信息
{
    //上边按键信息
    system ( "cls" );//清屏
    color ( 10 );
    printf ( "\t\t\t学生管理\n" );
    color ( 14 );
    printf ( "[ESC] " );
    color ( 12 );
    printf ( "退出    " );
    color ( 14 );
    printf ( "[CTRL+Z] " );
    color ( 12 );
    printf ( "重新读档  " );
    color ( 14 );
    printf ( "[CTRL+S] " );
    color ( 12 );
    printf ( "保存修改  " );
    color ( 14 );
    printf ( "[WSAD/箭头键] " );
    color ( 12 );
    printf ( "移动选择  " );
    color ( 14 );
    printf ( "[CTRL+A/D] " );
    color ( 12 );
    printf ( "翻页" );

    color ( 15 );
    for ( int i = 0 ; i < 100 ; ++ i )//上面的
    {
        CursorJump ( 3 , i );//位置跳转
        printf ( "—" );
    }
    for ( int i = 0 ; i < 100 ; ++ i )//底部
    {
        CursorJump ( 28 , i );//位置跳转
        printf ( "—" );
    }
    for ( int i = 0 ; i < 30 ; ++ i )
    {
        CursorJump ( i , 100 );//位置跳转
        printf ( "|" );
    }
    for ( int i = 101 ; i < 120 ; ++ i )//个人信息那里
    {
        CursorJump ( 4 , i );//位置跳转
        printf ( "—" );
    }
    CursorJump ( 5 , 104 );//位置跳转
    color ( 13 );
    printf ( "学生个人信息" );
    CursorJump ( 28 , 45 );//位置跳转
    color ( 13 );
    printf ( "状态栏" );
    //打印右边按键信息
    CursorJump ( 0 , 101 );//位置跳转
    color ( 14 );
    printf ( "[N]" );
    color ( 12 );
    printf ( "      新建课程" );
    CursorJump ( 1 , 101 );//位置跳转
    color ( 14 );
    printf ( "[F]" );
    color ( 12 );
    printf ( "      查找课程" );
    CursorJump ( 2 , 101 );//位置跳转
    color ( 14 );
    printf ( "[E]" );
    color ( 12 );
    printf ( "      编辑课程" );
    CursorJump ( 3 , 101 );//位置跳转
    color ( 14 );
    printf ( "[Delete] " );
    color ( 12 );
    printf ( "删除课程" );

    //底部信息
    CursorJump ( 29 , 0 );//位置跳转
    color(9);
    printf ("   当前状态:");
    if(pick_revision)
    {
        color(11);
        printf("未修改\t\t\t   ");
    }
    else
    {
        color(11);
        printf("未保存\t\t\t   ");
    }

    color(9);
    printf ("选择编号:");
    color(11);
    printf("%d\t\t\t\t\t",that_person.id);
    color(9);
    printf ("第");
    color(11);
    printf("%d/%d",that_person.id%10,Total%10);
    color(9);
    printf ("页");
    //打印时间
    color ( 11 );
    CursorJump ( 0 , 50 );//位置跳转
    time_t now_time;
    time ( & now_time );
    printf ( "当前时间为：%s\n" , asctime ( gmtime ( & now_time ) ) );
}


void course_start(void)//课程管理主页
{
    course_printf_start_image ( );//打印图像信息
    course_print_view();//打印列表模式
    while ( 1 )
    {
        //更新时间
        color ( 11 );
        CursorJump ( 0 , 50 );//位置跳转
        time_t now_time;
        time ( & now_time );
        printf ( "当前时间为：%s\n" , asctime ( gmtime ( & now_time ) ) );

        //接收用户输入
        if ( _kbhit ( ) )
        {
            static char tmp_input;//临时接收输入
            tmp_input=(char)_getch();//接收用户的输入

            if(tmp_input==ESC)
            {
                if(pick_revision)
                {
                    return;
                }
                else
                {
                    MessageBox(0,"修改未保存","警告",0);
                }
            }
            else if(tmp_input=='N'||tmp_input=='n')
            {
                //新增联系人页面
            }
        }

    }
}