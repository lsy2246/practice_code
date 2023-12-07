#include <stdio.h>
#include <unistd.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define map_Longitudinal 27//地图高度
#define map_across 102//地图宽度
int integral = 0;//玩家积分
int MAX_integral = 0;//最高积分
int pick_food = 1;//判断地图上有没有食物
int map[map_Longitudinal][map_across];//储存地图状态
#define mark_NULL 0//标记空
#define mark_snake 1//标记蛇
#define mark_wall 2//标记墙
#define mark_food 3//标记为食物

void color ( int c )//颜色设置
{
    SetConsoleTextAttribute ( GetStdHandle ( STD_OUTPUT_HANDLE ) , c ); //颜色设置
    //注：SetConsoleTextAttribute是一个API（应用程序编程接口）
}

typedef struct
{
    int y;//纵坐标
    int x;//横坐标
    int MAX_x;//横坐标
} game_Integral;//得分

game_Integral * score;//全局声明得分

typedef struct
{
    int y;//纵坐标
    int x;//横坐标
} snake_head;//蛇头

snake_head * head;//全局声明蛇头

typedef struct
{
    int y[99];//纵坐标
    int x[99];//横坐标
    int length;//蛇身体长度
} snake_body;//蛇身

snake_body * body;//全局声明蛇身

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

void print_score ()//打印积分
{
    color ( 14 );
    CursorJump ( score -> y , score -> x );
    printf ( "\n当前积分为%d分\n" , integral );
    CursorJump ( score -> y + 1 , score -> MAX_x );
    printf ( "最高积分为%d分\n" , MAX_integral );
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

void move ( int move_x , int move_y )//移动逻辑
{
    color ( 10 ); //颜色设置为绿色
    if ( pick_food == 0 )
    {
        body -> x[ body -> length ] = body -> x[ body -> length - 1 ];
        body -> y[ body -> length ] = body -> y[ body -> length - 1 ];
        map[ body -> y[ body -> length ] ][ body -> x[ body -> length ] ] = mark_snake;//标记蛇
        body -> length += 1;//增加蛇身体长度
        integral += 10;//增加积分
    }
    //将最后一个取消
    map[ body -> y[ body -> length - 1 ] ][ body -> x[ body -> length - 1 ] ] = mark_NULL;//标记为空
    CursorJump ( body -> y[ body -> length - 1 ] , body -> x[ body -> length - 1 ] );
    printf ( " " );
    //更新蛇身坐标
    for ( int i = body -> length - 1 ; i > 0 ; -- i )
    {
        body -> x[ i ] = body -> x[ i - 1 ];
        body -> y[ i ] = body -> y[ i - 1 ];
    }
    body -> x[ 0 ] = head -> x;
    body -> y[ 0 ] = head -> y;
    //将蛇头原来的坐标替换为身体
    CursorJump ( head -> y , head -> x );
    printf ( "□" );
    //更新蛇头坐标
    head -> x += move_x;
    head -> y += move_y;
    //把蛇头的坐标在地图更新
    map[ head -> y ][ head -> x ] = mark_snake;//标记蛇
    CursorJump ( head -> y , head -> x );
    printf ( "■" );
    if ( pick_food == 0 )
    {
        food_map ( );
        print_score ( );//重新打印积分
        pick_food = 1;
    }
}

void Begin ()//开始界面
{
    printf ( "\n\n\n\n\n\n\n\n\t\t\t\t\t——————————贪吃蛇——————————\n" );
    printf ( "\t\t\t\t\t|使用WSAD进行上下左右移动|\n" );
    printf ( "\t\t\t\t\t|按ESC退出游戏           |\n" );
    printf ( "\t\t\t\t\t|回车进入游戏            |\n" );
    printf ( "\t\t\t\t\t——————————贪吃蛇——————————\n" );
    int a = _getch ( );
    if ( a == 27 )
    {
        exit ( 0 );
    }
}

void initial_snake ()//初始蛇
{
    color ( 10 ); //颜色设置为绿色
    //初始化蛇头
    head -> x = 10;
    head -> y = 10;
    //初始化蛇身
    body -> x[ 1 ] = 9;
    body -> y[ 1 ] = 10;
    body -> x[ 0 ] = 8;
    body -> y[ 0 ] = 10;
    body -> length = 2;
    //生成蛇的图像
    //蛇头
    map[ head -> y ][ head -> x ] = mark_snake;//标记蛇
    CursorJump ( head -> y , head -> x );
    printf ( "■" );
    //蛇身
    for ( int i = body -> length - 1 ; i >= 0 ; -- i )
    {
        map[ body -> y[ i ] ][ body -> x[ i ] ] = mark_snake;//标记蛇
        CursorJump ( body -> y[ i ] , body -> x[ i ] );
        printf ( "□" );
    }

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

}

int defeat ()//失败界面
{
    CursorJump ( 10 , 50 );
    printf ( "\n\t\t\t—————————游戏失败—————————\n" );
    printf ( "\t\t\t|按ESC退出游戏           |\n" );
    printf ( "\t\t\t|其他键继续游戏          |\n" );
    printf ( "\t\t\t—————————游戏失败—————————\n" );
    int a = _getch ( );
    if ( a == 27 )
    {
        exit ( 0 );
    }
    else
    {
        MAX_integral = integral;//保存最大积分
        return 5;
    }


}

int main ()
{
    HideCursor ( );//隐藏光标

    game_Begin:
    system ( "cls" );
    score = ( game_Integral * ) malloc ( sizeof ( game_Integral ) );//动态分配光标内存
    head = ( snake_head * ) malloc ( sizeof ( snake_head ) );// 动态分配蛇头内存
    body = ( snake_body * ) malloc ( sizeof ( snake_body ) );// 动态分配蛇头内存
    score -> x = 1;//积分横坐标
    score -> y = map_Longitudinal;//积分纵坐标
    score -> MAX_x = map_across - 13;//最大积分横坐标
    srand ( time ( NULL ) );//设置随机数
    char direction_test = 'd';//方向接收
    char direction = 'd';//方向
    int move_x = 0;//更新移动所产生的横坐标
    int move_y = 0;//更新移动所产生的纵坐标
    int pick = 0;//接收是否重开游戏
    print_map ( );//打印当前地图
    print_score ( );//打印积分
    initial_snake ( );//生成蛇
    food_map ( );//在动图上生成食物
    while ( 1 )
    {
        if ( _kbhit ( ) )//接收用户输入
        {
            direction_test = _getch ( );
            if ( direction_test == 'W' || direction_test == 'w' || direction_test == 'S' || direction_test == 's' ||
                 direction_test == 'A' || direction_test == 'a' || direction_test == 'D' ||
                 direction_test == 'd' )//判断方向对不对
            {
                direction = direction_test;//更新移动方向
            }
        }


        //判断移动的坐标
        if ( direction == 'W' || direction == 'w' )//判断向上
        {
            if ( move_y == 1 )
            {
                move_x = 0;//更新移动所产生的横坐标
                move_y = 1;//更新移动所产生的纵坐标
            }
            else
            {
                if ( map[ head -> y - 1 ][ head -> x ] == mark_snake ||
                     map[ head -> y - 1 ][ head -> x ] == mark_wall )//判断有没有失败
                {
                    pick = defeat ( );
                }
                if ( map[ head -> y - 1 ][ head -> x ] == mark_food )
                {
                    pick_food = 0;//提示食物没有了
                }
                move_x = 0;//更新移动所产生的横坐标
                move_y = - 1;//更新移动所产生的纵坐标
            }
        }
        else if ( direction == 'S' || direction == 's' )//判断向下
        {
            if ( move_y == - 1 )
            {
                move_x = 0;//更新移动所产生的横坐标
                move_y = - 1;//更新移动所产生的纵坐标
            }
            else
            {
                if ( map[ head -> y + 1 ][ head -> x ] == mark_wall ||
                     map[ head -> y + 1 ][ head -> x ] == mark_snake )//判断有没有失败
                {
                    pick = defeat ( );
                }
                if ( map[ head -> y + 1 ][ head -> x ] == mark_food )
                {
                    pick_food = 0;//提示食物没有了
                }
                move_x = 0;//更新移动所产生的横坐标
                move_y = 1;//更新移动所产生的纵坐标
            }
        }
        else if ( direction == 'A' || direction == 'a' )//判断向左
        {
            if ( move_x == 1 )
            {
                move_x = 1;//更新移动所产生的横坐标
                move_y = 0;//更新移动所产生的纵坐标
            }
            else
            {
                if ( map[ head -> y ][ head -> x - 1 ] == mark_wall ||
                     map[ head -> y ][ head -> x - 1 ] == mark_snake )//判断有没有失败
                {
                    pick = defeat ( );
                }
                if ( map[ head -> y ][ head -> x - 1 ] == mark_food )
                {
                    pick_food = 0;//提示食物没有了
                }
                move_x = - 1;//更新移动所产生的横坐标
                move_y = 0;//更新移动所产生的纵坐标
            }
        }
        else if ( direction == 'D' || direction == 'd' )//判断右
        {
            if ( move_x == - 1 )
            {
                move_x = - 1;//更新移动所产生的横坐标
                move_y = 0;//更新移动所产生的纵坐标
            }
            else
            {
                if ( map[ head -> y ][ head -> x + 1 ] == mark_wall ||
                     map[ head -> y ][ head -> x + 1 ] == mark_snake )//判断有没有失败
                {
                    pick = defeat ( );
                }
                if ( map[ head -> y ][ head -> x + 1 ] == mark_food )
                {
                    pick_food = 0;//提示食物没有了
                }
                move_x = 1;//更新移动所产生的横坐标
                move_y = 0;//更新移动所产生的纵坐标
            }
        }

        if ( pick == 5 || direction_test == 'R' || direction_test == 'r' )//判断是否重开游戏
        {
            system ( "cls" );
            integral = 0;//重置玩家积分
            free ( score );
            free ( head );
            free ( body );
            goto game_Begin;
        }
        move ( move_x , move_y );//将坐标移动
        Sleep ( 80 );//停顿一秒
    }
    return 0;
}