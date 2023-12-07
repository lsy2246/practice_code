#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//声明
void home ();

//初始化棋盘
char initialization ( char array_chessboard[20][20] )
{
    for ( int i = 0 ; i < 20 ; i ++ )
    {
        for ( int j = 0 ; j < 20 ; j ++ ) //填充棋盘横排
        {
            array_chessboard[ i ][ j ] = '.';
        }
    }
    return array_chessboard[ 20 ][ 20 ];
}

//输出当前棋盘
void print_chessboard ( char array_chessboard[20][20] )
{
    printf ( "    " );
    for ( int i = 0 ; i < 20 ; i ++ )
    {
        if ( i < 10 ) //输出第几行
        {
            printf ( " %d  " , i );
        } else
        {
            printf ( "%d  " , i );
        }
    }
    printf ( "\n" );
    for ( int i = 0 ; i < 20 ; i ++ )//输出棋盘竖列
    {
        if ( i < 10 ) //输出第几行
        {
            printf ( " %d" , i );
        } else
        {
            printf ( "%d" , i );
        }
        for ( int j = 0 ; j < 20 ; j ++ ) //输出棋盘横排
        {
            printf ( "   %c" , array_chessboard[ i ][ j ] );
        }
        if ( i < 10 ) //输出第几行
        {
            printf ( "   %d" , i );
        } else
        {
            printf ( "   %d" , i );
        }
        printf ( "\n" );//输出完每一排换行
    }
    printf ( "    " );
    for ( int i = 0 ; i < 20 ; i ++ )
    {
        if ( i < 10 ) //输出第几行
        {
            printf ( " %d  " , i );
        } else
        {
            printf ( "%d  " , i );
        }
    }
    printf ( "\n" );
}

//存入用户坐标
char credited ( int x , int y , char array_chessboard[20][20] , char user )
{
    while ( x < 0 || x >= 20 || y < 0 || y >= 20 ) //检查坐标是否在棋盘内
    {
        while ( getchar ( ) != '\n' );
        printf ( "非法坐标,请重新输入\n" );
        printf ( "请输入横坐标:" );
        while ( scanf ( "%d" , & x ) != 1 )
        {
            while ( getchar ( ) != '\n' );
            printf ( "请输入合法数字:" );
        }
        printf ( "请输入竖坐标:" );
        while ( scanf ( "%d" , & y ) != 1 )
        {
            while ( getchar ( ) != '\n' );
            printf ( "请输入合法数字:" );
        }
    }
    while ( array_chessboard[ x ][ y ] != '.' ) //检查坐标是否存在棋子
    {
        while ( getchar ( ) != '\n' );
        printf ( "该坐标已存在棋子,请重新输入\n" );
        printf ( "请输入横坐标:" );
        while ( scanf ( "%d" , & x ) != 1 )
        {
            while ( getchar ( ) != '\n' );
            printf ( "请输入合法数字:" );
        }
        printf ( "请输入竖坐标:" );
        while ( scanf ( "%d" , & y ) != 1 )
        {
            while ( getchar ( ) != '\n' );
            printf ( "请输入合法数字:" );
        }
    }
    if ( user == 'X' )
    {
        array_chessboard[ x ][ y ] = 'X';
    }
    if ( user == 'Y' )
    {
        array_chessboard[ x ][ y ] = 'Y';
    }
    return array_chessboard[ x ][ y ];//返回当前地图
}

//判断是否胜利
char judgment ( char user , char array_chessboard[20][20] )
{
    int i;//初始化横排
    int j;//初始化竖排

    //判断横向
    for ( i = 0 ; i < 20 ; i ++ )
    {
        for ( j = 0 ; j < 20 ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i ][ j + 1 ] == user &&
                 array_chessboard[ i ][ j + 2 ] == user &&
                 array_chessboard[ i ][ j + 3 ] == user &&
                 array_chessboard[ i ][ j + 4 ] == user
                    )
            {
                return user;
            }
        }
    }
    //判断纵向
    for ( i = 0 ; i < 20 ; i ++ )
    {
        for ( j = 0 ; j < 20 ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i + 1 ][ j ] == user &&
                 array_chessboard[ i + 2 ][ j ] == user &&
                 array_chessboard[ i + 3 ][ j ] == user &&
                 array_chessboard[ i + 4 ][ j ] == user
                    )
            {
                return array_chessboard[ i ][ j ];
            }
        }
    }
    //判断左往右边斜
    for ( i = 0 ; i < 20 ; i ++ )
    {
        for ( j = 0 ; j < 20 ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i + 1 ][ j + 1 ] == user &&
                 array_chessboard[ i + 2 ][ j + 2 ] == user &&
                 array_chessboard[ i + 3 ][ j + 3 ] == user &&
                 array_chessboard[ i + 4 ][ j + 4 ] == user
                    )
            {
                return user;
            }
        }
    }
    //判断右往左边斜
    for ( i = 0 ; i < 20 ; i ++ )
    {
        for ( j = 0 ; j < 20 ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i + 1 ][ j - 1 ] == user &&
                 array_chessboard[ i + 2 ][ j - 2 ] == user &&
                 array_chessboard[ i + 3 ][ j - 3 ] == user &&
                 array_chessboard[ i + 4 ][ j - 4 ] == user
                    )
            {
                return user;
            }
        }
    }
    return '\0';
}//

//生成随机数
void generateRandomPosition ( int * x , int * y , char array_chessboard[20][20] )
{
    int randomNumber = rand ( ) % 8;
    switch ( randomNumber )
    {
        case 0:
        {
            * y += 1;
            break;
        }
        case 1:
        {
            * x += 1;
            break;
        }
        case 2:
        {
            * x += 1;
            * y += 1;
            break;
        }
        case 3:
        {
            * x -= 1;
            break;
        }
        case 4:
        {
            * y -= 1;
            break;
        }
        case 5:
        {
            * x -= 1;
            * y -= 1;
            break;
        }
        case 6:
        {
            * x -= 1;
            * y += 1;
            break;
        }
        case 7:
        {
            * x += 1;
            * y -= 1;
            break;
        }
    }
    while ( * x < 0 || * x >= 20 || * y < 0 || * y >= 20 || array_chessboard[ * x ][ * y ] != '.' )
    {
        * x = rand ( ) % 20;
        * y = rand ( ) % 20;
        generateRandomPosition ( x , y , array_chessboard );
    }
}

//判断ai下棋位置
void AI_chess ( int * x , int * y , char user , char array_chessboard[20][20] )
{
    int i;//初始化横排
    int j;//初始化竖排

    //如果横向有三个一样
    for ( i = 0 ; i < 20 ; i ++ )
    {
        for ( j = 0 ; j < 20 ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i ][ j + 1 ] == user &&
                 array_chessboard[ i ][ j + 2 ] == user
                    )
            {
                int randomNumber = rand ( ) % 2;  // 生成 0 或 1
                switch ( randomNumber )
                {
                    case 0:
                        * x = i;
                        * y = j + 3;
                        break;
                    case 1:
                        * x = i;
                        * y = j - 1;
                        break;
                }

                if ( * x < 0 || * x >= 20 || * y < 0 || * y >= 20 || array_chessboard[ * x ][ * y ] != '.' )
                {
                    * x = rand ( ) % 20;
                    * y = rand ( ) % 20;
                    AI_chess ( x , y , user , array_chessboard );
                }
                return;
            }
        }
    }
    //判断纵向有三个一样
    for ( i = 0 ; i < 20 ; i ++ )
    {
        for ( j = 0 ; j < 20 ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i + 1 ][ j ] == user &&
                 array_chessboard[ i + 2 ][ j ] == user
                    )
            {
                int randomNumber = rand ( ) % 2;  // 生成 0 或 1
                switch ( randomNumber )
                {
                    case 0:
                        * x = i + 3;
                        * y = j;
                        break;
                    case 1:
                        * x = i - 1;
                        * y = j;
                        break;
                }

                if ( * x < 0 || * x >= 20 || * y < 0 || * y >= 20 || array_chessboard[ * x ][ * y ] != '.' )
                {
                    AI_chess ( x , y , user , array_chessboard );
                }
                return;
            }
        }
    }

    //判断左往右边斜有三个一样
    for ( i = 0 ; i < 20 ; i ++ )
    {
        for ( j = 0 ; j < 20 ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i + 1 ][ j + 1 ] == user &&
                 array_chessboard[ i + 2 ][ j + 2 ] == user
                    )
            {
                int randomNumber = rand ( ) % 2;  // 生成 0 或 1
                switch ( randomNumber )
                {
                    case 0:
                        * x = i + 3;
                        * y = j + 3;
                        break;
                    case 1:
                        * x = i - 1;
                        * y = j - 1;
                        break;
                }

                if ( * x < 0 || * x >= 20 || * y < 0 || * y >= 20 || array_chessboard[ * x ][ * y ] != '.' )
                {
                    * x = rand ( ) % 20;
                    * y = rand ( ) % 20;
                    AI_chess ( x , y , user , array_chessboard );
                }
                return;
            }

        }
    }
    //判断右往左边斜
    for ( i = 0 ; i < 20 ; i ++ )
    {
        for ( j = 0 ; j < 20 ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i + 1 ][ j - 1 ] == user &&
                 array_chessboard[ i + 2 ][ j - 2 ] == user
                    )
            {
                int randomNumber = rand ( ) % 2;  // 生成 0 或 1
                switch ( randomNumber )
                {
                    case 0:
                        * x = i - 1;
                        * y = j + 1;
                        break;
                    case 1:
                        * x = i - 3;
                        * y = j + 3;
                        break;
                }

                if ( * x < 0 || * x >= 20 || * y < 0 || * y >= 20 || array_chessboard[ * x ][ * y ] != '.' )
                {
                    * x = rand ( ) % 20;
                    * y = rand ( ) % 20;
                    AI_chess ( x , y , user , array_chessboard );
                }
                return;
            }
        }
    }
    //如果不满足随机输入
    generateRandomPosition ( x , y , array_chessboard );


}

//双人模式
void double_game ()
{
    //初始化
    char user;//判断是那个用户
    int bout = 0;//用户输入的回合
    int x;//用户横坐标
    int y;//用户纵坐标
    char array_chessboard[20][20];//初始化棋盘
    initialization ( array_chessboard );//初始化数组里面的数
    while ( bout < 400 )
    {
        print_chessboard ( array_chessboard );//输出当前地图
        bout ++;
        printf ( "第%d回合\n" , ( bout + 1 ) / 2 );
        if ( bout % 2 == 1 )
        {
            user = 'X';
        } else
        {
            user = 'Y';
        }
        printf ( "轮到用户%c \n" , user );
        printf ( "请输入横坐标:" );
        while ( scanf ( "%d" , & x ) != 1 )
        {
            while ( getchar ( ) != '\n' );
            printf ( "请输入合法数组:" );
        }
        printf ( "请输入纵坐标:" );
        while ( scanf ( "%d" , & y ) != 1 )
        {
            while ( getchar ( ) != '\n' );
            printf ( "请输入合法数字:" );
        }
        credited ( x , y , array_chessboard , user );//存入用户输入的数字
        if ( judgment ( user , array_chessboard ) == user )//判断用户是否胜利
        {
            printf ( "用户%c胜利\n" , user );
            break;
        }
    }

    if ( bout == 400 )//平局判断
    {
        printf ( "平局\n" );
    }
    print_chessboard ( array_chessboard ); //输出棋盘
    while ( getchar ( ) != '\n' );//清除缓存
    home ( );//返回主页
}

//单人模式
void single_game ()
{
    //初始化
    char user;//判断是那个用户
    int bout = 0;//用户输入的回合
    int x;//横坐标
    int y;//纵坐标
    char array_chessboard[20][20];//初始化棋盘
    initialization ( array_chessboard );//初始化数组里面的数
    while ( bout < 200 )
    {
        bout ++;
        printf ( "第%d回合\n" , bout );
        user = 'X';
        printf ( "轮到用户 \n" );
        printf ( "请输入横坐标:" );
        while ( scanf ( "%d" , & x ) != 1 )
        {
            while ( getchar ( ) != '\n' );
            printf ( "请输入合法数组:" );
        }
        printf ( "请输入纵坐标:" );
        while ( scanf ( "%d" , & y ) != 1 )
        {
            while ( getchar ( ) != '\n' );
            printf ( "请输入合法数字:" );
        }
        credited ( x , y , array_chessboard , user );//存入用户输入的数字
        if ( judgment ( user , array_chessboard ) == user )//判断用户是否胜利
        {
            printf ( "用户胜利\n" );
            break;
        }

        printf ( "轮到AI \n" );
        AI_chess ( & x , & y , user , array_chessboard );//获取ai判断输出的数

        user = 'Y';
        credited ( x , y , array_chessboard , user );//存入AI输入的数字
        if ( judgment ( user , array_chessboard ) == user )//判断用户是否胜利
        {
            printf ( "AI胜利\n" );
            break;
        }
        print_chessboard ( array_chessboard );//输出当前地图

    }

    if ( bout == 200 )//平局判断
    {
        printf ( "平局\n" );
    }
    print_chessboard ( array_chessboard ); //输出棋盘
    while ( getchar ( ) != '\n' );//清除缓存
    home ( );
}

//菜单
void home ()
{
    int pick;//判断进入什么模式
    printf ( "————主页————\n" );
    printf ( "0.退出程序\n" );
    printf ( "1.单人模式\n" );
    printf ( "2.双人模式\n" );
    printf ( "请输入:" );
    while ( scanf ( "%d" , & pick ) != 1 )
    {
        while ( getchar ( ) != '\n' );//清除缓存
        printf ( "请输入合法数字:" );
    }
    switch ( pick )
    {
        case 0:
        {
            printf ( "欢迎下次使用" );
            return;
            break;
        }
        case 1:
        {
            while ( getchar ( ) != '\n' );//清除缓存
            single_game ( );
            break;
        }
        case 2:
        {
            while ( getchar ( ) != '\n' );//清除缓存
            double_game ( );
            break;
        }
        default:
        {
            while ( getchar ( ) != '\n' );//清除缓存
            printf ( "输入错误 \n" );
            home ( );
        }
    }
}

int main ()
{
    srand ( time ( NULL ) );// 设置种子，可以让每次运行程序时得到不同的随机数序列
    home ( );
    return 0;
}