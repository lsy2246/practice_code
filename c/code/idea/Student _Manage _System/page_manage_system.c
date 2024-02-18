//头文件
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

//自定义头文件
#include "founction_statement_page.h"//界面
#include "function_statement_effect.h"//功能

//临时全局变量
struct Personal_Information that_person = {1, "lsy", true, 2023150, 1, 2020, "18888888888", {1, 2, 3}};


void system_print_view_mode1(void)//打印视图模式
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
    //打印
    CursorJump ( 3 , 0 );//位置跳转
    color(7);
    printf ("编号  ");
    printf ("姓名\t");
    printf ("性别  ");
    printf ("学号\t");
    printf ("班级\t");
    printf ("入学年份  ");
    printf ("手机号码\t");
    printf ("选课编号");
    for ( int i = 5 ; i < 27 ;  i+=2 )
    {
        //编号
        CursorJump ( i , 0 );//位置跳转
        color (10);
        printf ("%d  ",that_person.id);
        //姓名
        CursorJump ( i , 6 );//位置跳转
        color (13);
        printf ("%s",that_person.name);
        //性别
        CursorJump ( i , 16 );//位置跳转
        if(that_person.sex)
        {
            color (11);
            printf ("男");
        }
        else
        {
            color (12);
            printf ("女");
        }
        //学号
        CursorJump ( i , 22 );//位置跳转
        color (9);
        printf ("%d",that_person.student_id);
        //班级
        CursorJump ( i , 32 );//位置跳转
        color (14);
        printf ("%d班",that_person.class);
        //入学年份
        CursorJump ( i , 40 );//位置跳转
        color (9);
        printf ("%d年",that_person.year);
        //电话号码
        CursorJump ( i , 50 );//位置跳转
        color (15);
        printf ("%s",that_person.phone);
        CursorJump ( i , 64 );//位置跳转
        for ( int j = 0 ; that_person.course_number[j] != '\0'  ; ++ j )
        {
            if(j>0)
            {
                color (12);
                printf (",");
            }
            color (11);
            printf ("%d",that_person.course_number[j]);
        }
    }
}

void system_print_view_mode2(void)//打印列表模式
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

static void system_printf_start_image ( void )//打印图像信息
{
    //上边按键信息
    system ( "cls" );//清屏
    color ( 10 );
    printf ( "\t\t\t学生管理\n" );
    color ( 14 );
    printf ( "[ESC] " );
    color ( 12 );
    printf ( "退出 " );
    color ( 14 );
    printf ( "[CTRL+Z] " );
    color ( 12 );
    printf ( "重新读档 " );
    color ( 14 );
    printf ( "[CTRL+S] " );
    color ( 12 );
    printf ( "保存修改 " );
    color ( 14 );
    printf ( "[TAB] " );
    color ( 12 );
    printf ( "切换视图 " );
    color ( 14 );
    printf ( "[WSAD/箭头键] " );
    color ( 12 );
    printf ( "移动选择 " );
    color ( 14 );
    printf ( "[CTRL+A/D] " );
    color ( 12 );
    printf ( "翻页\n" );
    //打印边界
    color ( 15 );
    for ( int i = 0 ; i < 100 ; ++ i )//上面的
    {
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
        CursorJump ( 5 , i );//位置跳转
        printf ( "—" );
    }
    CursorJump ( 6 , 104 );//位置跳转
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
    printf ( "      新建学生" );
    CursorJump ( 1 , 101 );//位置跳转
    color ( 14 );
    printf ( "[F]" );
    color ( 12 );
    printf ( "      查找学生" );
    CursorJump ( 2 , 101 );//位置跳转
    color ( 14 );
    printf ( "[E]" );
    color ( 12 );
    printf ( "      编辑信息" );
    CursorJump ( 3 , 101 );//位置跳转
    color ( 14 );
    printf ( "[Q]" );
    color ( 12 );
    printf ( "      查看成绩" );
    CursorJump ( 4 , 101 );//位置跳转
    color ( 14 );
    printf ( "[Delete] " );
    color ( 12 );
    printf ( "删除学生" );

    //底部信息
    CursorJump ( 29 , 0 );//位置跳转
    color(9);
    printf ("   当前状态:");
    if(pick_revision)
    {
        color(11);
        printf("未修改\t");
    }
    else
    {
        color(11);
        printf("未保存\t");
    }

    color(9);
    printf ("学生总数:");
    color(11);
    printf("%d\t",Total);
    if(pick_view_mode)
    {
        color(9);
        printf ("视图模式:");
        color(11);
        printf("详细模式\t");
    }
    else
    {
        color(9);
        printf ("视图模式:");
        color(11);
        printf("列表模式\t");
    }
    color(9);
    printf ("选择编号:");
    color(11);
    printf("%d\t",that_person.id);
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

void system_newly_built(void)
{
    //
}//新建联系人

void system_start ( void )//学生管理主页
{
    system_printf_start_image ( );//打印图像信息
    if(pick_view_mode)//打印视图模式
    {
        system_print_view_mode1();//打印视图模式
    }
    else
    {
        system_print_view_mode2();//打印列表模式
    }
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
            else if(tmp_input ==TAB)
            {
                if(pick_view_mode)//打印视图模式
                {
                    pick_view_mode=false;
                    system_print_view_mode1();//打印视图模式
                }
                else
                {
                    pick_view_mode=true;
                    system_print_view_mode2();//打印列表模式
                }
            }
            else if(tmp_input=='N'||tmp_input=='n')
            {
                system_newly_built();//新增联系人页面
            }
        }

    }

}