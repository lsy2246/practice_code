#include <stdio.h>

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
        for ( j = 0 ; j <  20 ; j ++ )
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
}

int main ()
{
    int pick_home;//判断是否进入程序
    //判断用户是否进入程序
    start:
    printf ("####双击进入程序####\n");
    printf ("#####输入0退出#####\n:");
    pick_home=getchar();
    if(pick_home=='0')
    {
        printf ("欢迎下次使用");
        return 0;
    }
    while (getchar() != '\n' );//清除缓存
    //初始化
    char user;//判断是那个用户
    int bout = 0;//用户输入的回合
    int x;//用户横坐标
    int y;//用户纵坐标
    char array_chessboard[20][20];//初始化棋盘

    for ( int i = 0 ; i < 20 ; i ++ )
    {
        for ( int j = 0 ; j < 20 ; j ++ ) //填充棋盘横排
        {
            array_chessboard[ i ][ j ] = '.';
        }
    }

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
    while (getchar() != '\n' );//清除缓存
    goto start;//回到主页
}