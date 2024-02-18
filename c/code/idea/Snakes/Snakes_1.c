#include <stdio.h>
#include <unistd.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define map_Longitudinal 25//地图高度
#define map_across 80//地图宽度
int integral = 0;//玩家积分
int MAX_integral =0;//最高积分
int pick_food=1;//判断地图上有没有食物

char map[map_Longitudinal][map_across];//贪吃蛇地图

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


void food_map ()//在动图上生成食物
{
    int i = rand ( ) % map_Longitudinal;//随机食物纵坐标
    int j = rand ( ) % map_across;//随机食物横坐标
    if ( map[ i ][ j ] == '*' )//监测到有蛇就重新生成
    {
        food_map ( );
    }
    else
    {
        map[ i ][ j ] = '@';
    }
}

void move ( int move_x , int move_y )//移动逻辑
{
    if(pick_food==0)
    {
        body -> x[ body->length ] = body -> x[ body->length - 1 ];
        body -> y[ body->length ] = body -> y[ body->length - 1 ];
        body->length+=1;//增加蛇身体长度
        integral+=10;//增加积分
    }

    map[ body -> y[ body->length - 1 ] ][ body -> x[ body->length - 1 ] ] = ' ';//将蛇尾最后一个取消
    //更新蛇身坐标
    for ( int i = body->length - 1 ; i > 0 ; -- i )
    {
        body -> x[i] = body -> x[ i - 1 ];
        body -> y[i ] = body -> y[ i- 1 ];
    }
    body -> x[ 0 ] = head -> x;
    body -> y[ 0 ] = head -> y;
    //将蛇头原来的坐标替换为身体
    map[ head -> y ][ head -> x ] = '*';
    //更新蛇头坐标
    head -> x += move_x;
    head -> y += move_y;
    //把蛇头的坐标在地图更新
    map[ head -> y ][ head -> x] = '#';
    if(pick_food==0)
    {
        food_map ();
        pick_food=1;
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

void initial_snake ()//初始化蛇
{
    //初始化蛇头
    head -> x = 10;
    head -> y = 10;
    //初始化蛇身
    body -> x[ 1 ] = 9;
    body -> y[ 1 ] = 10;
    body -> x[ 0 ] = 8;
    body -> y[ 0 ] = 10;
    body->length = 2;
    //生成蛇的图像
    map[ head -> y][ head -> x] = '#';
    map[ body -> y[ body->length - 1 ] ][ body -> x[ body->length - 1 ] ] = '*';
    map[ body -> y[ body->length - 2 ] ][ body -> x[ body->length - 2 ] ] = '*';

}

void initial_map ()//初始化地图
{
    for ( int i = 0 ; i < map_Longitudinal ; ++ i )//给地图初始化为空
    {
        for ( int j = 0 ; j < map_across ; ++ j )
        {
            map[ i ][ j ] = ' ';
        }
    }
    food_map ( );//在动图上生成食物
}

void print_map ()//打印地图
{

    for ( int i = 0 ; i < map_Longitudinal ; ++ i )
    {
        if ( i == 0 )
        {
            for ( int j = 0 ; j <= map_across + 1 ; ++ j )
            {
                printf ( "▄" );
            }
            printf ( "\n" );
        }

        for ( int j = 0 ; j < map_across ; ++ j )
        {
            if ( j == 0 )//打印边界
            {
                printf ( "█" );
            }
            printf ( "%c" , map[ i ][ j ] );//输出地图
        }
        printf ( "█" );//打印边界
        printf ( "\n" );
    }
    for ( int j = 0 ; j <= map_across + 1 ; ++ j )
    {
        printf ( "▀" );
    }
    printf ( "\n当前积分为%d分\t\t\t\t\t\t\t最高积分为%d分" , integral,MAX_integral );
}

int defeat ()//失败界面
{
    printf ( "\n\n\t\t\t—————————游戏失败—————————\n" );
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
        MAX_integral=integral;//保存最大积分
        integral = 0;//玩家积分
        a=1;
        return a;
    }


}


int main ()
{
    Begin ( );//开始界面
    game_Begin:
    head = ( snake_head * ) malloc ( sizeof ( snake_head ) );// 动态分配蛇头内存
    body = ( snake_body * ) malloc ( sizeof ( snake_body ) );// 动态分配蛇头内存
    srand ( time ( NULL ) );//设置随机数
    char direction_test;//方向接收
    char direction = 's';//方向
    int move_x = 0;//更新移动所产生的横坐标
    int move_y = 0;//更新移动所产生的纵坐标
    int pick=0;//接收是否重开游戏
    HideCursor ( );//隐藏光标
    initial_map ( );//初始化地图
    initial_snake ( );//初始化地图里面的蛇
    while ( 1 )
    {
        system ( "cls" );//清屏
        print_map ( );//打印当前地图
        if ( _kbhit ( ) )//接收用户输入
        {
            direction_test = _getch ( );
            if ( direction_test == 'W' || direction_test == 'w' || direction_test == 'S' || direction_test == 's' ||
                 direction_test == 'A' || direction_test == 'a' || direction_test == 'D' ||
                 direction_test == 'd' )//判断方向对不对
            {
                direction = direction_test;
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
                if ( head -> y - 1 < 0 ||map[ head -> y- 1 ][ head -> x] == '*' )//判断有没有失败
                {
                    pick=defeat ( );
                }
                if(map[ head -> y - 1 ][ head -> x] == '@')
                {
                    pick_food=0;//提示食物没有了
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
                if (  head -> y + 1 >= map_Longitudinal||map[ head -> y+ 1 ][ head -> x] == '*' )//判断有没有失败
                {
                    pick=defeat ( );
                }
                if(map[ head -> y+ 1 ][ head -> x] == '@' )
                {
                    pick_food=0;//提示食物没有了
                }
                move_x = 0;//更新移动所产生的横坐标
                move_y = 1;//更新移动所产生的纵坐标
            }
        }
        else if ( direction_test == 'A' || direction_test == 'a' )//判断向左
        {
            if ( move_x == 1 )
            {
                move_x = 1;//更新移动所产生的横坐标
                move_y = 0;//更新移动所产生的纵坐标
            }
            else
            {
                if (head -> x- 1 < 0 ||map[ head -> y][ head -> x- 1 ] == '*'  )//判断有没有失败
                {
                    pick=defeat ( );
                }
                if(map[ head -> y][ head -> x- 1 ] == '@')
                {
                    pick_food=0;//提示食物没有了
                }
                move_x = - 1;//更新移动所产生的横坐标
                move_y = 0;//更新移动所产生的纵坐标
            }
        }
        else if ( direction_test == 'D' || direction_test == 'd' )//判断右
        {
            if ( move_x == - 1 )
            {
                move_x = - 1;//更新移动所产生的横坐标
                move_y = 0;//更新移动所产生的纵坐标
            }
            else
            {
                if (head -> x+ 1 >=map_across ||map[ head -> y][ head -> x+ 1 ] == '*'  )//判断有没有失败
                {
                    pick=defeat ( );
                }
                if(map[ head -> y][ head -> x+ 1 ] == '@')
                {
                    pick_food=0;//提示食物没有了
                }
                move_x = 1;//更新移动所产生的横坐标
                move_y = 0;//更新移动所产生的纵坐标
            }
        }

        if(pick==1)
        {
            goto game_Begin;
        }
        move ( move_x , move_y );//将坐标移动
        Sleep ( 80 );//停顿一秒
    }
    return 0;
}
