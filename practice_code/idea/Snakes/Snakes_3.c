#include <stdio.h>
#include <unistd.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define map_Longitudinal 27//地图高度
#define map_across 102//地图宽度
int map[map_Longitudinal][map_across];//储存地图状态

int MAX_integral = 0;//玩家最高分
//定义是哪条蛇
#define mark_NULL 97//标记空
#define mark_food 98//标记为食物
#define mark_wall 99//标记墙

#define UP 72 //方向键：上
#define DOWN 80 //方向键：下
#define LEFT 75 //方向键：左
#define RIGHT 77 //方向键：右

//蛇

//得分
typedef struct
{
    int y;//纵坐标
    int x;//横坐标
    int MAX_x;//横坐标
    int integral;//玩家积分
} game_Integral;

//蛇头
typedef struct
{
    int y;//纵坐标
    int x;//横坐标
    int direction;//蛇移动的方向
    int move_x;//更新移动所产生的横坐标
    int move_y;//更新移动所产生的纵坐标
    int food;//判断是否吃到食物
} snake_head;

//蛇身
typedef struct
{
    int color;//蛇的颜色
    int y[99];//纵坐标
    int x[99];//横坐标
    int length;//蛇身体长度
} snake_body;

//哪条蛇
typedef struct
{
    snake_head * head;//头
    snake_body * body;//身体
    game_Integral * score;//积分
} name_snake;

name_snake * snake[99];//给蛇全局声明
//蛇

void HideCursor ()//隐藏光标
{
    CONSOLE_CURSOR_INFO curInfo; //定义光标信息的结构体变量
    curInfo . dwSize = 1; //如果没赋值的话，光标隐藏无效
    curInfo . bVisible = FALSE; //将光标设置为不可见
    HANDLE handle = GetStdHandle ( STD_OUTPUT_HANDLE ); //获取控制台句柄
    SetConsoleCursorInfo ( handle , & curInfo ); //设置光标信息
}

void CursorJump ( int y , int x )//光标跳转
{
    COORD pos; //定义光标位置的结构体变量
    pos . X = x; //横坐标
    pos . Y = y; //纵坐标
    HANDLE handle = GetStdHandle ( STD_OUTPUT_HANDLE ); //获取控制台句柄
    SetConsoleCursorPosition ( handle , pos ); //设置光标位置
}

void color ( int c )//颜色设置
{
    SetConsoleTextAttribute ( GetStdHandle ( STD_OUTPUT_HANDLE ) , c ); //颜色设置
    //注：SetConsoleTextAttribute是一个API（应用程序编程接口）
}


void print_score ( int pick_score )//打印积分
{

    if ( pick_score == 1 )
    {
        color ( snake[ 0 ] -> body -> color );//设置积分颜色
        CursorJump ( snake[ 0 ] -> score -> y , snake[ 0 ] -> score -> x );
        printf ( "当前积分为%d分" , snake[ 0 ] -> score -> integral );
        CursorJump ( snake[ 0 ] -> score -> y , snake[ 0 ] -> score -> MAX_x );
        printf ( "最高积分为%d分" , MAX_integral );
    }
    else if ( pick_score == 2 )
    {
        color ( snake[ 0 ] -> body -> color );//设置积分颜色
        CursorJump ( snake[ 0 ] -> score -> y , snake[ 0 ] -> score -> x );
        printf ( "一号玩家积分为%d分" , snake[ 0 ] -> score -> integral );
        CursorJump ( snake[ 0 ] -> score -> y + 1 , snake[ 0 ] -> score -> x );
        printf ( "W S A D进行上下左右移动" );
        color ( snake[ 1 ] -> body -> color );//设置积分颜色
        CursorJump ( snake[ 0 ] -> score -> y , snake[ 0 ] -> score -> MAX_x - 5 );
        printf ( "二号玩家积分为%d分" , snake[ 1 ] -> score -> integral );
        CursorJump ( snake[ 0 ] -> score -> y + 1 , snake[ 0 ] -> score -> MAX_x - 5 );
        printf ( "↑ ↓ ← → 进行上下左右移动" );
    }

}

void food_map ()//在动图上生成食物
{
    int i = rand ( ) % map_Longitudinal;//随机食物纵坐标
    int j = rand ( ) % map_across;//随机食物横坐标
    int random = rand ( ) % 14 + 1;//随机生成颜色
    if ( map[ i ][ j ] == mark_NULL )//监测到有物体就重新生成
    {
        map[ i ][ j ] = mark_food; // 正确标记食物
        color ( random );
        CursorJump ( i , j );
        printf ( "●" );
    }
    else
    {
        food_map ( );
    }
}

void move ( int snake_digit )//移动逻辑
{
    color ( snake[ snake_digit ] -> body -> color ); //颜色设置
    if ( snake[ snake_digit ] -> head -> food == 1 )//如果吃到食物
    {
        snake[ snake_digit ] -> body -> x[ snake[ snake_digit ] -> body -> length ] = snake[ snake_digit ] -> body -> x[
                snake[ snake_digit ] -> body -> length - 1 ];//新增的一节赋值现在最后一节的x
        snake[ snake_digit ] -> body -> y[ snake[ snake_digit ] -> body -> length ] = snake[ snake_digit ] -> body -> y[
                snake[ snake_digit ] -> body -> length - 1 ];//新增的一节赋值现在最后一节的y
        map[ snake[ snake_digit ] -> body -> y[ snake[ snake_digit ] -> body -> length ] ][ snake[ snake_digit ] -> body -> x[ snake[ snake_digit ] -> body -> length ] ] = snake_digit;//标记蛇
        snake[ snake_digit ] -> body -> length += 1;//增加蛇身体长度
        if ( snake_digit == 1 || snake_digit == 0 )
        {
            snake[ snake_digit ] -> score -> integral += 10;//增加积分
        }
    }
    //将之前身体的置空
    for ( int i = 0 ; i < snake[ snake_digit ] -> body -> length ; ++ i )
    {
        map[ snake[ snake_digit ] -> body -> y[ i ] ][ snake[ snake_digit ] -> body -> x[ i ] ] = mark_NULL;//标记为空
        CursorJump ( snake[ snake_digit ] -> body -> y[ i ] , snake[ snake_digit ] -> body -> x[ i ] );
        printf ( " " );
    }

    //更新蛇身坐标
    for ( int i = snake[ snake_digit ] -> body -> length - 1 ; i > 0 ; -- i )
    {
        snake[ snake_digit ] -> body -> x[ i ] = snake[ snake_digit ] -> body -> x[ i - 1 ];//将本节的x坐标换成前一节的
        snake[ snake_digit ] -> body -> y[ i ] = snake[ snake_digit ] -> body -> y[ i - 1 ];//将本节的y坐标换成前一节的
    }
    snake[ snake_digit ] -> body -> x[ 0 ] = snake[ snake_digit ] -> head -> x;//将第一个的x坐标换成头部
    snake[ snake_digit ] -> body -> y[ 0 ] = snake[ snake_digit ] -> head -> y;//将第一个的u坐标换成头部
    //将重新打印身体
    for ( int i = 0 ; i < snake[ snake_digit ] -> body -> length ; ++ i )
    {
        map[ snake[ snake_digit ] -> body -> y[ i ] ][ snake[ snake_digit ] -> body -> x[ i ] ] = snake_digit;//标记蛇
        CursorJump ( snake[ snake_digit ] -> body -> y[ i ] , snake[ snake_digit ] -> body -> x[ i ] );
        printf ( "□" );
    }

    //更新蛇头坐标
    snake[ snake_digit ] -> head -> x += snake[ snake_digit ] -> head -> move_x;
    snake[ snake_digit ] -> head -> y += snake[ snake_digit ] -> head -> move_y;
    //把蛇头的坐标在地图更新
    map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x ] = snake_digit;//标记蛇
    CursorJump ( snake[ snake_digit ] -> head -> y , snake[ snake_digit ] -> head -> x );
    printf ( "■" );

}

int Begin ()//开始界面
{
    begin_tab:
    system ( "cls" );
    printf ( "\n\n\n\n\n\n\n\n\t\t\t\t\t————————————贪吃蛇————————————\n" );
    printf ( "\t\t\t\t\t|1.单人模式\t\t     |\n" );
    printf ( "\t\t\t\t\t|2.双人模式(先出现的为一号蛇)|\n" );
    printf ( "\t\t\t\t\t|3.人机模式(先出现的为用户蛇)|\n" );
    printf ( "\t\t\t\t\t 请输入:" );
    int pick_Begin;//接收开始页面的选择
    while ( ( scanf ( "%d" , & pick_Begin ) ) != 1 )
    {
        while ( getchar ( ) != '\n' );
        goto begin_tab;
    }
    if ( pick_Begin == 0 )
    {
        exit ( 0 );
    }
    else if ( pick_Begin >= 1 && pick_Begin <= 3 )
    {
        return pick_Begin;
    }
    else
    {
        while ( getchar ( ) != '\n' );
        printf ( "输入错误,请重新输入" );
        goto begin_tab;
    }
}

void initial_snake ( int snake_digit )//生成蛇
{
    int pick_x = rand ( ) % 60 + 12;//随机生成横坐标
    int pick_y = rand ( ) % 17 + 1;//随机生成纵坐标
    snake[ snake_digit ] -> body -> color = rand ( ) % 14 + 1;//给蛇随机生成颜色
    color ( snake[ snake_digit ] -> body -> color ); //给蛇设置颜色
    while ( map[ pick_y ][ pick_x ] != mark_NULL || map[ pick_y ][ pick_x - 1 ] != mark_NULL ||
            map[ pick_y ][ pick_x - 2 ] != mark_NULL )//判断生成的位置是不是空地
    {
        pick_x = rand ( ) % 70 + 10;//随机生成横坐标
        pick_y = rand ( ) % 17 + 1;//随机生成纵坐标
    }
    //初始化蛇头
    snake[ snake_digit ] -> head -> x = pick_x;
    snake[ snake_digit ] -> head -> y = pick_y;
    //初始化蛇身
    snake[ snake_digit ] -> body -> x[ 0 ] = pick_x - 1;
    snake[ snake_digit ] -> body -> y[ 0 ] = pick_y;
    snake[ snake_digit ] -> body -> x[ 1 ] = pick_x - 2;
    snake[ snake_digit ] -> body -> y[ 1 ] = pick_y;
    snake[ snake_digit ] -> body -> length = 2;
    //生成蛇的图像
    //蛇头
    map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x ] = snake_digit;//标记蛇
    CursorJump ( snake[ snake_digit ] -> head -> y , snake[ snake_digit ] -> head -> x );
    printf ( "■" );
    //蛇身
    for ( int i = snake[ snake_digit ] -> body -> length - 1 ; i >= 0 ; -- i )
    {
        map[ snake[ snake_digit ] -> body -> y[ i ] ][ snake[ snake_digit ] -> body -> x[ i ] ] = snake_digit;//标记蛇
        CursorJump ( snake[ snake_digit ] -> body -> y[ i ] , snake[ snake_digit ] -> body -> x[ i ] );
        printf ( "□" );
    }
    //初始化积分
    snake[ snake_digit ] -> score -> integral = 0;
    //初始化移动所产生的坐标
    snake[ snake_digit ] -> head -> move_x = 0;
    snake[ snake_digit ] -> head -> move_y = 0;
    //初始蛇移动方向
    snake[ snake_digit ] -> head -> direction = 4;
    //有没有吃到食物
    snake[ snake_digit ] -> head -> food = 0;
}

void print_map ()//初始地图
{
    color ( 12 );
    for ( int i = 0 ; i < map_Longitudinal ; ++ i )
    {
        if ( i == 0 || i == map_Longitudinal - 1 )
        {
            for ( int j = 0 ; j < map_across ; ++ j )
            {
                //打印墙并且标记状态为墙
                map[ i ][ j ] = mark_wall;
                printf ( "█" );
            }
            printf ( "\n" );
        }
        else
        {
            for ( int j = 0 ; j < map_across ; ++ j )
            {
                if ( j == 0 || j == map_across - 1 )//打印边界
                {
                    //打印墙并且标记状态为墙
                    map[ i ][ j ] = mark_wall;
                    printf ( "█" );
                }
                else
                {
                    map[ i ][ j ] = mark_NULL;//标记为空
                    printf ( " " );//输出地图
                }
            }
            printf ( "\n" );
        }
    }
    snake[ 0 ] -> score -> x = 1;//积分横坐标
    snake[ 0 ] -> score -> y = map_Longitudinal;//积分纵坐标
    snake[ 0 ] -> score -> MAX_x = map_across - 14;//最大积分横坐标
}

void defeat ( int snake_digit , int toll )//失败界面
{
    defeat_tab:
    color ( 12 );
    CursorJump ( 10 , 50 );
    printf ( "\n\t\t\t\t———————游戏失败———————\n" );
    if ( toll == 2 )
    {
        printf ( "\t\t\t\t|%d号玩家的蛇死亡     |\n" , snake_digit + 1 );
    }
    printf ( "\t\t\t\t|0.退出游戏          |\n" );
    printf ( "\t\t\t\t|1.返回主页          |\n" );
    printf ( "\t\t\t\t|2.重新开始          |\n" );
    printf ( "\t\t\t\t 请输入:" );
    int pick_defeat;//接收选择
    while ( ( scanf ( "%d" , & pick_defeat ) ) != 1 )
    {
        while ( getchar ( ) != '\n' );
        system ( "cls" );
        goto defeat_tab;
    }
    if ( pick_defeat == 0 )
    {
        exit ( 0 );
    }
    else if ( pick_defeat == 1 )
    {
        snake[ snake_digit ] -> head -> direction = 6;
    }
    else if ( pick_defeat == 2 )
    {
        snake[ snake_digit ] -> head -> direction = 5;
    }
    else
    {
        while ( getchar ( ) != '\n' );
        system ( "cls" );
        goto defeat_tab;
    }

}

void reception_input ( int snake_digit , int toll )//接收用户输入
{
    //将上一次的状态转为方向
    char direction_test;//方向接收
    if ( toll == 1 )
    {
        if ( _kbhit ( ) )//接收用户输入
        {
            direction_test = _getch ( );
            if ( direction_test == 'W' || direction_test == 'w' || direction_test == UP )//向上
            {
                snake[ 0 ] -> head -> direction = 1;
            }
            else if ( direction_test == 'S' || direction_test == 's' || direction_test == DOWN )//向下
            {
                snake[ 0 ] -> head -> direction = 2;
            }
            else if ( direction_test == 'A' || direction_test == 'a' || direction_test == LEFT )//向右
            {
                snake[ 0 ] -> head -> direction = 3;
            }
            else if ( direction_test == 'D' || direction_test == 'd' || direction_test == RIGHT )//向左
            {
                snake[ 0 ] -> head -> direction = 4;//方向
            }
            else if ( direction_test == 'R' || direction_test == 'r' )//重开
            {
                snake[ 0 ] -> head -> direction = 5;//重开
            }
        }
    }
    else if ( toll == 2 )
    {
        if ( _kbhit ( ) )//接收用户输入
        {
            direction_test = _getch ( );
            if ( direction_test == 'W' || direction_test == 'w' && snake[ 0 ] -> head -> move_y != 1 )//向上
            {
                snake_digit = 0;//更新蛇
                snake[ snake_digit ] -> head -> direction = 1;//更新蛇移动方向
            }
            if ( direction_test == 'S' || direction_test == 's' && snake[ 0 ] -> head -> move_y != - 1 )//向下
            {
                snake_digit = 0;//更新蛇
                snake[ snake_digit ] -> head -> direction = 2;//更新蛇移动方向
            }
            if ( direction_test == 'A' || direction_test == 'a' && snake[ 0 ] -> head -> move_x != 1 )//向左
            {
                snake_digit = 0;//更新蛇
                snake[ snake_digit ] -> head -> direction = 3;//更新蛇移动方向
            }
            if ( direction_test == 'D' || direction_test == 'd' && snake[ 0 ] -> head -> move_x != - 1 )//向右
            {
                snake_digit = 0;//更新蛇
                snake[ snake_digit ] -> head -> direction = 4;//更新蛇移动方向
            }
            if ( direction_test == UP && snake[ 1 ] -> head -> move_y != 1 )//向上
            {
                snake_digit = 1;//更新蛇
                snake[ snake_digit ] -> head -> direction = 1;//更新蛇移动方向
            }
            if ( direction_test == DOWN && snake[ 1 ] -> head -> move_y != - 1 )//向下
            {
                snake_digit = 1;//更新
                snake[ snake_digit ] -> head -> direction = 2;//更新蛇移动方向
            }
            if ( direction_test == LEFT && snake[ 1 ] -> head -> move_x != 1 )//向左
            {
                snake_digit = 1;//更新蛇
                snake[ snake_digit ] -> head -> direction = 3;//更新蛇移动方向
            }
            if ( direction_test == RIGHT && snake[ 1 ] -> head -> move_x != 1 )//向右
            {
                snake_digit = 1;//更新
                snake[ snake_digit ] -> head -> direction = 4;//更新蛇移动方向
            }
        }
    }
    else
    {
        int pick = rand ( ) % 4 + 1;
        switch ( pick )
        {
            case 1:
            {
                if ( map[ snake[ snake_digit ] -> head -> y - 1 ][ snake[ snake_digit ] -> head -> x ] == mark_food &&
                     snake[ snake_digit ] -> head -> direction != 2 )
                {
                    snake[ snake_digit ] -> head -> direction = 1;
                    break;
                }//判断要不要往上
            }
            case 2:
            {
                if ( map[ snake[ snake_digit ] -> head -> y + 1 ][ snake[ snake_digit ] -> head -> x ] == mark_food &&
                     snake[ snake_digit ] -> head -> direction != 1 )
                {
                    snake[ snake_digit ] -> head -> direction = 2;
                    break;
                }//判断要不要往下
            }
            case 3:
            {
                if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x - 1 ] == mark_food &&
                     snake[ snake_digit ] -> head -> direction != 4 )
                {
                    snake[ snake_digit ] -> head -> direction = 3;
                    break;
                }//判断要往左
            }
            case 4:
            {
                if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x + 1 ] == mark_food &&
                     snake[ snake_digit ] -> head -> direction != 3 )
                {
                    snake[ snake_digit ] -> head -> direction = 4;
                    break;
                }//判断要不要往右
            }
            case 5:
            {
                if ( map[ snake[ snake_digit ] -> head -> y - 1 ][ snake[ snake_digit ] -> head -> x ] == mark_food &&
                     snake[ snake_digit ] -> head -> direction != 2 )
                {
                    snake[ snake_digit ] -> head -> direction = 1;
                    break;
                }//判断要不要往上
                else if ( map[ snake[ snake_digit ] -> head -> y + 1 ][ snake[ snake_digit ] -> head -> x ] ==
                          mark_food && snake[ snake_digit ] -> head -> direction != 1 )
                {
                    snake[ snake_digit ] -> head -> direction = 2;
                    break;
                }//判断要不要往下

                else if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x - 1 ] ==
                          mark_food && snake[ snake_digit ] -> head -> direction != 4 )
                {
                    snake[ snake_digit ] -> head -> direction = 3;
                    break;
                }//判断要往左

                else if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x + 1 ] ==
                          mark_food && snake[ snake_digit ] -> head -> direction != 3 )
                {
                    snake[ snake_digit ] -> head -> direction = 4;
                    break;
                }//判断要不要往右
            }
            case 6:
            {
                switch ( pick )
                {
                    case 1:
                    {
                        if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x + 1 ] ==
                             mark_NULL && snake[ snake_digit ] -> head -> direction != 3 )
                        {
                            snake[ snake_digit ] -> head -> direction = 4;
                            break;
                        }//判断要不要往右
                    }
                    case 2:
                    {
                        if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x - 1 ] ==
                             mark_NULL && snake[ snake_digit ] -> head -> direction != 4 )
                        {
                            snake[ snake_digit ] -> head -> direction = 3;
                            break;
                        }//判断要往左
                    }
                    case 3:
                    {
                        if ( map[ snake[ snake_digit ] -> head -> y + 1 ][ snake[ snake_digit ] -> head -> x ] ==
                             mark_NULL && snake[ snake_digit ] -> head -> direction != 1 )
                        {
                            snake[ snake_digit ] -> head -> direction = 2;
                            break;
                        }//判断要不要往下
                    }
                    case 4:
                    {
                        if ( map[ snake[ snake_digit ] -> head -> y - 1 ][ snake[ snake_digit ] -> head -> x ] ==
                             mark_NULL && snake[ snake_digit ] -> head -> direction != 2 )
                        {
                            snake[ snake_digit ] -> head -> direction = 1;
                            break;
                        }//判断要不要往上
                    }
                }
            }
            case 7:
            {
                if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x + 1 ] == mark_NULL &&
                     snake[ snake_digit ] -> head -> direction != 3 )
                {
                    snake[ snake_digit ] -> head -> direction = 4;
                    break;
                }//判断要不要往右
                else if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x - 1 ] ==
                          mark_NULL && snake[ snake_digit ] -> head -> direction != 4 )
                {
                    snake[ snake_digit ] -> head -> direction = 3;
                    break;
                }//判断要往左
                else if ( map[ snake[ snake_digit ] -> head -> y + 1 ][ snake[ snake_digit ] -> head -> x ] ==
                          mark_NULL && snake[ snake_digit ] -> head -> direction != 1 )
                {
                    snake[ snake_digit ] -> head -> direction = 2;
                    break;
                }//判断要不要往下

                else if ( map[ snake[ snake_digit ] -> head -> y - 1 ][ snake[ snake_digit ] -> head -> x ] ==
                          mark_NULL && snake[ snake_digit ] -> head -> direction != 2 )
                {
                    snake[ snake_digit ] -> head -> direction = 1;
                    break;
                }//判断要不要往上
            }
            case 8:
            {
                switch ( pick )
                {
                    case 1:
                    {
                        if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x + 1 ] ==
                             snake_digit && snake[ snake_digit ] -> head -> direction != 3 )
                        {
                            snake[ snake_digit ] -> head -> direction = 4;
                            break;
                        }//判断要不要往右
                    }
                    case 2:
                    {
                        if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x - 1 ] ==
                             snake_digit && snake[ snake_digit ] -> head -> direction != 4 )
                        {
                            snake[ snake_digit ] -> head -> direction = 3;
                            break;
                        }//判断要往左
                    }
                    case 3:
                    {
                        if ( map[ snake[ snake_digit ] -> head -> y + 1 ][ snake[ snake_digit ] -> head -> x ] ==
                             snake_digit && snake[ snake_digit ] -> head -> direction != 1 )
                        {
                            snake[ snake_digit ] -> head -> direction = 2;
                            break;
                        }//判断要不要往下
                    }
                    case 4:
                    {
                        if ( map[ snake[ snake_digit ] -> head -> y - 1 ][ snake[ snake_digit ] -> head -> x ] ==
                             snake_digit && snake[ snake_digit ] -> head -> direction != 2 )
                        {
                            snake[ snake_digit ] -> head -> direction = 1;
                            break;
                        }//判断要不要往上
                    }
                }
            }
            case 9:
            {
                if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x + 1 ] == snake_digit &&
                     snake[ snake_digit ] -> head -> direction != 3 )
                {
                    snake[ snake_digit ] -> head -> direction = 4;
                    break;
                }//判断要不要往右
                else if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x - 1 ] ==
                          snake_digit && snake[ snake_digit ] -> head -> direction != 4 )
                {
                    snake[ snake_digit ] -> head -> direction = 3;
                    break;
                }//判断要往左
                else if ( map[ snake[ snake_digit ] -> head -> y + 1 ][ snake[ snake_digit ] -> head -> x ] ==
                          snake_digit && snake[ snake_digit ] -> head -> direction != 1 )
                {
                    snake[ snake_digit ] -> head -> direction = 2;
                    break;
                }//判断要不要往下

                else if ( map[ snake[ snake_digit ] -> head -> y - 1 ][ snake[ snake_digit ] -> head -> x ] ==
                          snake_digit && snake[ snake_digit ] -> head -> direction != 2 )
                {
                    snake[ snake_digit ] -> head -> direction = 1;
                    break;
                }//判断要不要往上
            }
        }

    }

}

void pick_move ( int snake_digit , int mode )//判断移动方向
{
    if ( snake[ snake_digit ] -> head -> direction == 1 )//判断向上
    {
        if ( snake[ snake_digit ] -> head -> move_y == 1 )
        {
            if ( mode >= 3 )
            {
                if ( map[ snake[ snake_digit ] -> head -> y + 1 ][ snake[ snake_digit ] -> head -> x ] != snake_digit &&
                     map[ snake[ snake_digit ] -> head -> y + 1 ][ snake[ snake_digit ] -> head -> x ] != mark_NULL &&
                     map[ snake[ snake_digit ] -> head -> y + 1 ][ snake[ snake_digit ] -> head -> x ] != mark_food ||
                     map[ snake[ snake_digit ] -> head -> y + 1 ][ snake[ snake_digit ] -> head -> x ] ==
                     mark_wall )//判断有没有失败
                {
                    snake[ snake_digit ] -> head -> direction = 0;//更新状态
                }
            }
            else
            {
                if ( map[ snake[ snake_digit ] -> head -> y + 1 ][ snake[ snake_digit ] -> head -> x ] != mark_NULL &&
                     map[ snake[ snake_digit ] -> head -> y + 1 ][ snake[ snake_digit ] -> head -> x ] != mark_food ||
                     map[ snake[ snake_digit ] -> head -> y + 1 ][ snake[ snake_digit ] -> head -> x ] ==
                     mark_wall )//判断有没有失败
                {
                    snake[ snake_digit ] -> head -> direction = 0;//更新状态
                }
            }
            if ( map[ snake[ snake_digit ] -> head -> y + 1 ][ snake[ snake_digit ] -> head -> x ] == mark_food )
            {
                snake[ snake_digit ] -> head -> food = 1;//此蛇吃到了食物
            }
            snake[ snake_digit ] -> head -> move_x = 0;//更新移动所产生的横坐标
            snake[ snake_digit ] -> head -> move_y = 1;//更新移动所产生的纵坐标
        }
        else
        {
            if ( mode >= 3 )
            {
                if ( map[ snake[ snake_digit ] -> head -> y - 1 ][ snake[ snake_digit ] -> head -> x ] != snake_digit &&
                     map[ snake[ snake_digit ] -> head -> y - 1 ][ snake[ snake_digit ] -> head -> x ] != mark_NULL &&
                     map[ snake[ snake_digit ] -> head -> y - 1 ][ snake[ snake_digit ] -> head -> x ] != mark_food ||
                     map[ snake[ snake_digit ] -> head -> y - 1 ][ snake[ snake_digit ] -> head -> x ] ==
                     mark_wall )//判断有没有失败
                {
                    snake[ snake_digit ] -> head -> direction = 0;//更新状态
                }
            }
            else
            {
                if ( map[ snake[ snake_digit ] -> head -> y - 1 ][ snake[ snake_digit ] -> head -> x ] != mark_NULL &&
                     map[ snake[ snake_digit ] -> head -> y - 1 ][ snake[ snake_digit ] -> head -> x ] != mark_food ||
                     map[ snake[ snake_digit ] -> head -> y - 1 ][ snake[ snake_digit ] -> head -> x ] ==
                     mark_wall )//判断有没有失败
                {
                    snake[ snake_digit ] -> head -> direction = 0;//更新状态
                }
            }

            if ( map[ snake[ snake_digit ] -> head -> y - 1 ][ snake[ snake_digit ] -> head -> x ] == mark_food )
            {
                snake[ snake_digit ] -> head -> food = 1;//此蛇吃到了食物
            }
            snake[ snake_digit ] -> head -> move_x = 0;//更新移动所产生的横坐标
            snake[ snake_digit ] -> head -> move_y = - 1;//更新移动所产生的纵坐标
        }
    }
    else if ( snake[ snake_digit ] -> head -> direction == 2 )//判断向下
    {
        if ( snake[ snake_digit ] -> head -> move_y == - 1 )
        {
            if ( mode >= 3 )
            {
                if ( map[ snake[ snake_digit ] -> head -> y - 1 ][ snake[ snake_digit ] -> head -> x ] != snake_digit &&
                     map[ snake[ snake_digit ] -> head -> y - 1 ][ snake[ snake_digit ] -> head -> x ] != mark_NULL &&
                     map[ snake[ snake_digit ] -> head -> y - 1 ][ snake[ snake_digit ] -> head -> x ] != mark_food ||
                     map[ snake[ snake_digit ] -> head -> y - 1 ][ snake[ snake_digit ] -> head -> x ] ==
                     mark_wall )//判断有没有失败
                {
                    snake[ snake_digit ] -> head -> direction = 0;//更新状态
                }
            }
            else
            {
                if ( map[ snake[ snake_digit ] -> head -> y - 1 ][ snake[ snake_digit ] -> head -> x ] != mark_NULL &&
                     map[ snake[ snake_digit ] -> head -> y - 1 ][ snake[ snake_digit ] -> head -> x ] != mark_food ||
                     map[ snake[ snake_digit ] -> head -> y - 1 ][ snake[ snake_digit ] -> head -> x ] ==
                     mark_wall )//判断有没有失败
                {
                    snake[ snake_digit ] -> head -> direction = 0;//更新状态
                }
            }

            if ( map[ snake[ snake_digit ] -> head -> y - 1 ][ snake[ snake_digit ] -> head -> x ] == mark_food )
            {
                snake[ snake_digit ] -> head -> food = 1;//此蛇吃到了食物
            }
            snake[ snake_digit ] -> head -> move_x = 0;//更新移动所产生的横坐标
            snake[ snake_digit ] -> head -> move_y = - 1;//更新移动所产生的纵坐标
        }
        else
        {
            if ( mode >= 3 )
            {
                if ( map[ snake[ snake_digit ] -> head -> y + 1 ][ snake[ snake_digit ] -> head -> x ] != snake_digit &&
                     map[ snake[ snake_digit ] -> head -> y + 1 ][ snake[ snake_digit ] -> head -> x ] != mark_NULL &&
                     map[ snake[ snake_digit ] -> head -> y + 1 ][ snake[ snake_digit ] -> head -> x ] != mark_food ||
                     map[ snake[ snake_digit ] -> head -> y + 1 ][ snake[ snake_digit ] -> head -> x ] ==
                     mark_wall )//判断有没有失败
                {
                    snake[ snake_digit ] -> head -> direction = 0;//更新状态
                }
            }
            else
            {
                if ( map[ snake[ snake_digit ] -> head -> y + 1 ][ snake[ snake_digit ] -> head -> x ] != mark_NULL &&
                     map[ snake[ snake_digit ] -> head -> y + 1 ][ snake[ snake_digit ] -> head -> x ] != mark_food ||
                     map[ snake[ snake_digit ] -> head -> y + 1 ][ snake[ snake_digit ] -> head -> x ] ==
                     mark_wall )//判断有没有失败
                {
                    snake[ snake_digit ] -> head -> direction = 0;//更新状态
                }
            }
            if ( map[ snake[ snake_digit ] -> head -> y + 1 ][ snake[ snake_digit ] -> head -> x ] == mark_food )
            {
                snake[ snake_digit ] -> head -> food = 1;//此蛇吃到了食物
            }
            snake[ snake_digit ] -> head -> move_x = 0;//更新移动所产生的横坐标
            snake[ snake_digit ] -> head -> move_y = 1;//更新移动所产生的纵坐标
        }
    }
    else if ( snake[ snake_digit ] -> head -> direction == 3 )//判断向左
    {
        if ( snake[ snake_digit ] -> head -> move_x == 1 )
        {
            if ( mode >= 3 )
            {
                if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x + 1 ] != snake_digit &&
                     map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x + 1 ] != mark_NULL &&
                     map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x + 1 ] != mark_food ||
                     map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x + 1 ] ==
                     mark_wall )//判断有没有失败
                {
                    snake[ snake_digit ] -> head -> direction = 0;//更新状态
                }
            }
            else
            {
                if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x + 1 ] != mark_NULL &&
                     map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x + 1 ] != mark_food ||
                     map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x + 1 ] ==
                     mark_wall )//判断有没有失败
                {
                    snake[ snake_digit ] -> head -> direction = 0;//更新状态
                }
            }

            if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x + 1 ] == mark_food )
            {
                snake[ snake_digit ] -> head -> food = 1;//此蛇吃到了食物
            }
            snake[ snake_digit ] -> head -> move_x = 1;//更新移动所产生的横坐标
            snake[ snake_digit ] -> head -> move_y = 0;//更新移动所产生的纵坐标
        }
        else
        {
            if ( mode >= 3 )
            {
                if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x - 1 ] != snake_digit &&
                     map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x - 1 ] != mark_NULL &&
                     map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x - 1 ] != mark_food ||
                     map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x - 1 ] ==
                     mark_wall )//判断有没有失败
                {
                    snake[ snake_digit ] -> head -> direction = 0;//更新状态
                }
            }
            else
            {
                if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x - 1 ] != mark_NULL &&
                     map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x - 1 ] != mark_food ||
                     map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x - 1 ] ==
                     mark_wall )//判断有没有失败
                {
                    snake[ snake_digit ] -> head -> direction = 0;//更新状态
                }
            }

            if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x - 1 ] == mark_food )
            {
                snake[ snake_digit ] -> head -> food = 1;//此蛇吃到了食物
            }
            snake[ snake_digit ] -> head -> move_x = - 1;//更新移动所产生的横坐标
            snake[ snake_digit ] -> head -> move_y = 0;//更新移动所产生的纵坐标
        }
    }
    else if ( snake[ snake_digit ] -> head -> direction == 4 )//判断右
    {
        if ( snake[ snake_digit ] -> head -> move_x == - 1 )
        {
            if ( mode >= 3 )
            {
                if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x - 1 ] != snake_digit &&
                     map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x - 1 ] != mark_NULL &&
                     map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x - 1 ] != mark_food ||
                     map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x - 1 ] ==
                     mark_wall )//判断有没有失败
                {
                    snake[ snake_digit ] -> head -> direction = 0;//更新状态
                }
            }
            else
            {
                if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x - 1 ] != mark_NULL &&
                     map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x - 1 ] != mark_food ||
                     map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x - 1 ] ==
                     mark_wall )//判断有没有失败
                {
                    snake[ snake_digit ] -> head -> direction = 0;//更新状态
                }
            }

            if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x - 1 ] == mark_food )
            {
                snake[ snake_digit ] -> head -> food = 1;//此蛇吃到了食物
            }
            snake[ snake_digit ] -> head -> move_x = - 1;//更新移动所产生的横坐标
            snake[ snake_digit ] -> head -> move_y = 0;//更新移动所产生的纵坐标
        }
        else
        {
            if ( mode >= 3 )
            {
                if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x + 1 ] != snake_digit &&
                     map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x + 1 ] != mark_NULL &&
                     map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x + 1 ] != mark_food ||
                     map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x + 1 ] ==
                     mark_wall )//判断有没有失败
                {
                    snake[ snake_digit ] -> head -> direction = 0;//更新状态
                }
            }
            else
            {
                if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x + 1 ] != mark_NULL &&
                     map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x + 1 ] != mark_food ||
                     map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x + 1 ] ==
                     mark_wall )//判断有没有失败
                {
                    snake[ snake_digit ] -> head -> direction = 0;//更新状态
                }
            }

            if ( map[ snake[ snake_digit ] -> head -> y ][ snake[ snake_digit ] -> head -> x + 1 ] == mark_food )
            {
                snake[ snake_digit ] -> head -> food = 1;//此蛇吃到了食物
            }
            snake[ snake_digit ] -> head -> move_x = 1;//更新移动所产生的横坐标
            snake[ snake_digit ] -> head -> move_y = 0;//更新移动所产生的纵坐标
        }
    }
}

int main ()
{
    //初始化
    int toll;//初始化真实人数
    int snake_digit;//初始化蛇有几条
    int total_food;//判断食物总数
    int New_food;//现有食物
    srand ( time ( NULL ) );//设置随机数
    //开始界面
    int pick_Begin;//接收开始页面的选择
    HideCursor ( );//隐藏光标
    game_Begin:
    pick_Begin = Begin ( );
    system ( "cls" );
    //选择进入哪个模式
    switch ( pick_Begin )
    {
        case 1:
        {
            goto Single_player;
            break;
        }
        case 2:
        {
            goto Two_player;
            break;
        }
        case 3:
        {
            goto Human_computer;
            break;
        }
    }

    //单人模式
    Single_player:
    //动态分配蛇头和身体
    toll = 1;//用户数量
    snake_digit = 1;//蛇数量
    total_food = 10;//食物总数
    for ( int i = 0 ; i < snake_digit ; ++ i )//动态分配蛇的内存
    {
        snake[ i ] = ( name_snake * ) malloc ( sizeof ( name_snake ) );
        snake[ i ] -> head = ( snake_head * ) malloc ( sizeof ( snake_head ) );
        snake[ i ] -> body = ( snake_body * ) malloc ( sizeof ( snake_body ) );
        snake[ i ] -> score = ( game_Integral * ) malloc ( sizeof ( game_Integral ) );
    }
    print_map ( );//生成地图
    for ( int i = 0 ; i < snake_digit ; ++ i )//生成蛇
    {
        initial_snake ( i );
    }
    print_score ( 1 );//打印积分
    for ( int i = 0 ; i < total_food ; ++ i )
    {
        food_map ( );//在动图上生成食物
    }
    while ( 1 )
    {
        reception_input ( 0 , 1 );//接收用户输入
        pick_move ( 0 , 1 );//判断移动方向
        if ( snake[ 0 ] -> head -> direction == 0 )//判断是否重开游戏
        {
            defeat ( 0 , toll );
        }
        if ( snake[ 0 ] -> head -> direction == 5 || snake[ 0 ] -> head -> direction == 6 )//判断是否重新游戏
        {
            if ( snake[ 0 ] -> score -> integral > MAX_integral )//更新积分
            {
                MAX_integral = snake[ 0 ] -> score -> integral;
            }
            if ( snake[ 0 ] -> head -> direction == 6 )
            {
                system ( "cls" );
                free ( snake[ 0 ] -> score );
                free ( snake[ 0 ] -> head );
                free ( snake[ 0 ] -> body );
                free ( snake[ 0 ] );
                goto game_Begin;//返回主页
            }
            else
            {
                system ( "cls" );
                free ( snake[ 0 ] -> score );
                free ( snake[ 0 ] -> head );
                free ( snake[ 0 ] -> body );
                free ( snake[ 0 ] );
                goto Single_player;//重新开始
            }
        }

        move ( 0 );//移动坐标
        if ( snake[ 0 ] -> head -> food == 1 )//检查有没有吃到食物的
        {
            food_map ( );
            print_score ( toll );//重新打印积分
            snake[ 0 ] -> head -> food = 0;//重置积分状态
        }
        Sleep ( 80 );//停顿
    }

    //双人模式
    Two_player:
    //初始化
    toll = 2;//用户数量
    snake_digit = 2;//蛇数量
    total_food = 20;//食物总数
    for ( int i = 0 ; i < snake_digit ; ++ i )//动态分配蛇的内存
    {
        snake[ i ] = ( name_snake * ) malloc ( sizeof ( name_snake ) );
        snake[ i ] -> head = ( snake_head * ) malloc ( sizeof ( snake_head ) );
        snake[ i ] -> body = ( snake_body * ) malloc ( sizeof ( snake_body ) );
        snake[ i ] -> score = ( game_Integral * ) malloc ( sizeof ( game_Integral ) );
    }
    print_map ( );//打印当前地图
    for ( int i = 0 ; i < snake_digit ; ++ i )//生成蛇
    {
        initial_snake ( i );
        sleep ( 1 );//避免生成一样的蛇
    }
    print_score ( 2 );//打印积分
    for ( int i = 0 ; i < total_food ; ++ i )//在动图上生成食物
    {
        food_map ( );
    }
    while ( 1 )
    {
        for ( int i = 0 ; i < 10 ; ++ i )//接收用户输入
        {
            reception_input ( toll - 1 , toll );
        }
        for ( int i = 0 ; i < snake_digit ; ++ i )//判断移动方向
        {
            pick_move ( i , 2 );//判断移动方向
        }
        for ( int i = 0 ; i < snake_digit ; ++ i )//移动
        {
            if ( snake[ i ] -> head -> direction == 0 )//判断是否失败
            {
                defeat ( i , toll );
            }
            if ( snake[ i ] -> head -> direction == 5 || snake[ i ] -> head -> direction == 6 )//判断是否重新游戏
            {
                system ( "cls" );
                if ( snake[ i ] -> head -> direction == 6 )
                {
                    for ( int j = 0 ; j < snake_digit ; ++ j )
                    {
                        free ( snake[ j ] -> score );
                        free ( snake[ j ] -> head );
                        free ( snake[ j ] -> body );
                        free ( snake[ j ] );
                    }
                    goto game_Begin;//返回主页
                }
                else
                {
                    for ( int j = 0 ; j < snake_digit ; ++ j )
                    {
                        free ( snake[ j ] -> score );
                        free ( snake[ j ] -> head );
                        free ( snake[ j ] -> body );
                        free ( snake[ j ] );
                    }
                    goto Two_player;//重新开始
                }
            }
            move ( i );//移动坐标
        }
        for ( int i = 0 ; i < snake_digit ; ++ i )//判断食物
        {
            if ( snake[ i ] -> head -> food == 1 )//检查有没有吃到食物的
            {
                food_map ( );
                print_score ( toll );//重新打印积分
                snake[ i ] -> head -> food = 0;//重置积分状态
            }
        }

        Sleep ( 80 );//停顿
    }

    //人机模式
    Human_computer:
    //动态分配蛇头和身体
    toll = 1;//用户数量
    snake_digit = 7;//蛇数量
    total_food = 30;//食物总数
    New_food = 0;//新增食物
    for ( int i = 0 ; i < snake_digit ; ++ i )//动态分配蛇的内存
    {
        snake[ i ] = ( name_snake * ) malloc ( sizeof ( name_snake ) );
        snake[ i ] -> head = ( snake_head * ) malloc ( sizeof ( snake_head ) );
        snake[ i ] -> body = ( snake_body * ) malloc ( sizeof ( snake_body ) );
        snake[ i ] -> score = ( game_Integral * ) malloc ( sizeof ( game_Integral ) );
    }
    print_map ( );//生成地图
    for ( int i = 0 ; i < snake_digit ; ++ i )//生成蛇
    {
        initial_snake ( i );
        sleep ( 1 );
    }
    print_score ( 1 );//打印积分
    for ( int i = 0 ; i < total_food ; ++ i )
    {
        food_map ( );//在动图上生成食物
    }
    while ( 1 )
    {
        //用户
        reception_input ( 0 , 1 );//接收用户输入
        pick_move ( 0 , 3 );//判断移动方向
        if ( snake[ 0 ] -> head -> direction == 0 )//判断是否重新游戏
        {
            defeat ( 0 , toll );
        }
        if ( snake[ 0 ] -> head -> direction == 5 || snake[ 0 ] -> head -> direction == 6 )//判断是否重开游戏
        {
            if ( snake[ 0 ] -> score -> integral > MAX_integral )//更新积分
            {
                MAX_integral = snake[ 0 ] -> score -> integral;
            }
            system ( "cls" );
            if ( snake[ 0 ] -> head -> direction == 6 )
            {
                for ( int j = 0 ; j < snake_digit ; ++ j )
                {
                    free ( snake[ j ] -> score );
                    free ( snake[ j ] -> head );
                    free ( snake[ j ] -> body );
                    free ( snake[ j ] );
                }
                goto game_Begin;//返回主页
            }
            else
            {
                for ( int j = 0 ; j < snake_digit ; ++ j )
                {
                    free ( snake[ j ] -> score );
                    free ( snake[ j ] -> head );
                    free ( snake[ j ] -> body );
                    free ( snake[ j ] );
                }
                goto Human_computer;//重新开始
            }
        }
        move ( 0 );//移动坐标
        if ( snake[ 0 ] -> head -> food == 1 )//检查有没有吃到食物的
        {
            if ( New_food == 0 )
            {
                snake[ 0 ] -> body -> color = rand ( ) % 14 + 1;//给蛇随机生成颜色
                food_map ( );
                print_score ( toll );//重新打印积分
                snake[ 0 ] -> head -> food = 0;//重置积分状态
            }
            else
            {
                New_food -= 1;
                print_score ( toll );//重新打印积分
                snake[ 0 ] -> head -> food = 0;//重置积分状态
            }

        }

        //人机
        for ( int i = 1 ; i < snake_digit ; ++ i )//生成坐标
        {
            reception_input ( i , snake_digit );//生成坐标
            pick_move ( i , 3 );//判断移动方向
            if ( snake[ i ] -> head -> direction == 0 )//判断是否重新生成
            {
                //将身体变成食物
                for ( int j = 0 ; j < snake[ i ] -> body -> length ; ++ j )
                {
                    color ( snake[ i ] -> body -> color );//设置食物颜色
                    CursorJump ( snake[ i ] -> body -> y[ j ] , snake[ i ] -> body -> x[ j ] );//光标跳转
                    map[ snake[ i ] -> body -> y[ j ] ][ snake[ i ] -> body -> x[ j ] ] = mark_food; // 正确标记食物
                    printf ( "●" );
                    New_food += 1;//增加新增食物
                }
                //将头变为空
                CursorJump ( snake[ i ] -> head -> y , snake[ i ] -> head -> x );//光标跳转
                map[ snake[ i ] -> head -> y ][ snake[ i ] -> head -> x ] = mark_NULL; // 正确标记空气
                printf ( " " );
                //释放本条蛇
                free ( snake[ i ] -> score );
                free ( snake[ i ] -> head );
                free ( snake[ i ] -> body );
                free ( snake[ i ] );
                //重新生成蛇
                snake[ i ] = ( name_snake * ) malloc ( sizeof ( name_snake ) );
                snake[ i ] -> head = ( snake_head * ) malloc ( sizeof ( snake_head ) );
                snake[ i ] -> body = ( snake_body * ) malloc ( sizeof ( snake_body ) );
                snake[ i ] -> score = ( game_Integral * ) malloc ( sizeof ( game_Integral ) );
                initial_snake ( i );
            }
            move ( i );//移动坐标
            if ( snake[ i ] -> head -> food == 1 )//检查有没有吃到食物的
            {
                if ( New_food == 0 )
                {
                    food_map ( );
                    print_score ( toll );//重新打印积分
                    snake[ i ] -> head -> food = 0;//重置积分状态
                }
                else
                {
                    New_food -= 1;
                    print_score ( toll );//重新打印积分
                    snake[ i ] -> head -> food = 0;//重置积分状态
                }

            }
        }

        Sleep ( 80 );//停顿
    }

    return 0;
}