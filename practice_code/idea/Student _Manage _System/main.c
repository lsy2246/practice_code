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
unsigned int Total = 0;//初始化学生总数

static struct Snake
{
    //0为y,1为x
    int head[2];
    int body[2];
    int tail[2];
};

static struct Snake snake ;

static void main_printf_view ( void )//主页菜单
{
    HideCursor ( );//隐藏光标
    system ( "cls" );//清屏

    CursorJump ( 8 , 50 );
    color ( 2 );//设置颜色
    printf ( "欢迎使用学生管理系统" );
    CursorJump ( 9 , 48 );
    color ( 4 );//设置颜色
    printf ( "按下相应按键进入对应模式" );

    CursorJump ( 10 , 47 );
    for ( int i = 0 ; i < 26 ; ++ i )
    {
        color ( 7 );//设置颜色
        printf ( "-" );
    }

    CursorJump ( 11 , 52 );
    color ( 1 );//设置颜色
    printf ( "[Enter]" );
    color ( 7 );//设置颜色
    printf ( " 进入程序\n" );
    CursorJump ( 12 , 52 );
    color ( 1 );//设置颜色
    printf ( "[M]" );
    color ( 7 );//设置颜色
    printf ( "\t    管理课程" );

    CursorJump ( 13 , 52 );
    color ( 1 );//设置颜色
    printf ( "[ESC]" );
    color ( 7 );//设置颜色
    printf ( "   退出程序\n" );

    for ( int i = 6 ; i <= 15 ; ++ i )
    {
        for ( int j = 45 ; j <= 74 ; ++ j )
        {
            if ( i == 6 || i == 15 || j == 45 || j == 74 )
            {
                CursorJump ( i , j );
                color ( 7 );//设置颜色
                printf ( "■" );
            }
        }
    }
}

static void main_move_snake(void)//移动小蛇
{
    Sleep (80);
    CursorJump ( snake.tail[0] , snake.tail[1] );
    printf (" ");
    snake.tail[0]=snake.body[0];
    snake.tail[1]=snake.body[1];
    snake.body[0]=snake.head[0];
    snake.body[1]=snake.head[1];
    if(snake.head[0]==6&&snake.head[1]<74)
    {
        snake.head[1]++;
    }
    else if(snake.head[1]==74&&snake.head[0]<15)
    {
        snake.head[0]++;
    }
    else if(snake.head[0]==15&&snake.head[1]>45)
    {
        snake.head[1]--;
    }
    else if(snake.head[1]==45&&snake.head[0]>7)
    {
        snake.head[0]--;
    }
    else
    {
        snake.tail[0]=6;
        snake.tail[1]=45;
        snake.body[0]=6;
        snake.body[1]=46;
        snake.head[0]=6;
        snake.head[1]=47;
        main_printf_view();
    }
    color ( 13 );//设置颜色
    CursorJump ( snake.tail[0] , snake.tail[1] );
    printf ("□");
    CursorJump ( snake.body[0] , snake.body[1] );
    printf ("□");
    CursorJump ( snake.head[0] , snake.head[1] );
    printf ("■");
}

//主函数
int main ( void )
{
    //定义变量
    static char start_pick = '0';//开始的选择
    snake.head[0]=7;
    snake.head[1]=45;
    srand ( ( unsigned ) time ( NULL ) );
    while ( 1 )
    {
        main_move_snake();//移动小蛇
        //获取用户的输入
        if ( _kbhit ( ) )
        {
            start_pick = ( char ) _getch ( );
        }
        //判断用户输入
        switch ( start_pick )
        {
            case ENTER:
            {
                start_pick = '0';
                system_start ( );//管理系统主页
                snake.head[0]=7;
                snake.head[1]=45;
                break;
            }
            case 'm':
            case 'M':
            {
                start_pick = '0';
                course_start ( );//管理系统主页
                snake.head[0]=7;
                snake.head[1]=45;
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