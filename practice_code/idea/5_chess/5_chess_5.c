#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//声明
void home ( int pick );

//初始化棋盘
char initialization ( int array , char array_chessboard[array][array] )
{
    for ( int i = 0 ; i < array ; i ++ )
    {
        for ( int j = 0 ; j < array ; j ++ ) //填充棋盘横排
        {
            array_chessboard[ i ][ j ] = '.';
        }
    }
    return array_chessboard[ array ][ array ];
}

//输出当前棋盘
void print_chessboard ( int array , char array_chessboard[array][array] )
{
    printf ( "    " );
    for ( int i = 0 ; i < array ; i ++ )
    {
        if ( i < 10 ) //输出第几行
        {
            printf ( " %d  " , i );
        }
        else
        {
            printf ( "%d  " , i );
        }
    }
    printf ( "\n" );
    for ( int i = 0 ; i < array ; i ++ )//输出棋盘竖列
    {
        if ( i < 10 ) //输出第几行
        {
            printf ( " %d" , i );
        }
        else
        {
            printf ( "%d" , i );
        }
        for ( int j = 0 ; j < array ; j ++ ) //输出棋盘横排
        {
            printf ( "   %c" , array_chessboard[ i ][ j ] );
        }
        if ( i < 10 ) //输出第几行
        {
            printf ( "   %d" , i );
        }
        else
        {
            printf ( "   %d" , i );
        }
        printf ( "\n" );//输出完每一排换行
    }
    printf ( "    " );
    for ( int i = 0 ; i < array ; i ++ )
    {
        if ( i < 10 ) //输出第几行
        {
            printf ( " %d  " , i );
        }
        else
        {
            printf ( "%d  " , i );
        }
    }
    printf ( "\n" );
}

//存入用户坐标
char credited ( int array , int x , int y , char array_chessboard[array][array] , char user )
{
    while ( x < 0 || x >= array || y < 0 || y >= array ) //检查坐标是否在棋盘内
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
char judgment ( int array , char user , char array_chessboard[array][array] )
{
    int i;//初始化横排
    int j;//初始化竖排

    //判断横向
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
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
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
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
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
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
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
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

//判断AI位置
void AI_chess ( int array , int * x , int * y , char array_chessboard[array][array] )
{
    int i = 0;//初始化横排
    int j = 0;//初始化竖排
    int figure_i = 0;//临时纵坐标
    int figure_j = 0;//临时横坐标
    int integral = 0;//最高评分
    int integral_a = 0;//评分
    int integral_b = 0;//文件临时备份
    int storage_coordinate[2];//存储坐标
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == '.' )//判断该数是不是空
            {
                //判断用户向右判断
                figure_i = i;
                figure_j = j;
                for ( int k = 1 ; k <= 4 ; ++ k )
                {
                    if ( array_chessboard[ figure_i ][ figure_j + 1 ] == 'X' && figure_j + 1 < array )
                    {
                        figure_j += 1;
                        switch ( k )
                        {
                            case 1:
                            {
                                integral_b = 1;
                                break;
                            }
                            case 2:
                            {
                                integral_b = 5;
                                break;
                            }
                            case 3:
                            {
                                integral_b = 12;
                                break;
                            }
                            case 4:
                            {
                                integral_b = 200;
                                break;
                            }
                        }
                    }
                    else//如果没有就退出循环
                    {
                        break;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //判断用户向左判断
                figure_i = i;
                figure_j = j;
                for ( int k = 1 ; k <= 4 ; ++ k )
                {
                    if ( array_chessboard[ figure_i ][ figure_j - 1 ] == 'X' && figure_j - 1 >= 0 )
                    {
                        figure_j -= 1;
                        switch ( k )
                        {
                            case 1:
                            {
                                integral_b = 1;
                                break;
                            }
                            case 2:
                            {
                                integral_b = 5;
                                break;
                            }
                            case 3:
                            {
                                integral_b = 12;
                                break;
                            }
                            case 4:
                            {
                                integral_b = 200;
                                break;
                            }
                        }
                    }
                    else//如果没有就退出循环
                    {
                        break;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //判断AI向右判断
                figure_i = i;
                figure_j = j;
                for ( int k = 1 ; k <= 4 ; ++ k )
                {
                    if ( array_chessboard[ figure_i ][ figure_j + 1 ] == 'Y' && figure_j + 1 < array )
                    {
                        figure_j += 1;
                        switch ( k )
                        {
                            case 1:
                            {
                                integral_b = 2;
                                break;
                            }
                            case 2:
                            {
                                integral_b = 4;
                                break;
                            }
                            case 3:
                            {
                                integral_b = 11;
                                break;
                            }
                            case 4:
                            {
                                integral_b = 201;
                                break;
                            }
                        }
                    }
                    else//如果没有就退出循环
                    {
                        break;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //判断AI向左判断
                figure_i = i;
                figure_j = j;
                for ( int k = 1 ; k <= 4 ; ++ k )
                {
                    if ( array_chessboard[ figure_i ][ figure_j - 1 ] == 'Y' && figure_j - 1 >= 0 )
                    {
                        figure_j -= 1;
                        switch ( k )
                        {
                            case 1:
                            {
                                integral_b = 2;
                                break;
                            }
                            case 2:
                            {
                                integral_b = 4;
                                break;
                            }
                            case 3:
                            {
                                integral_b = 11;
                                break;
                            }
                            case 4:
                            {
                                integral_b = 201;
                                break;
                            }
                        }
                    }
                    else//如果没有就退出循环
                    {
                        break;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //判断用户向下
                figure_i = i;
                figure_j = j;
                for ( int k = 1 ; k <= 4 ; ++ k )
                {
                    if ( array_chessboard[ figure_i + 1 ][ figure_j ] == 'X' && figure_i + 1 < array )
                    {
                        figure_i += 1;
                        switch ( k )
                        {
                            case 1:
                            {
                                integral_b = 1;
                                break;
                            }
                            case 2:
                            {
                                integral_b = 5;
                                break;
                            }
                            case 3:
                            {
                                integral_b = 12;
                                break;
                            }
                            case 4:
                            {
                                integral_b = 200;
                                break;
                            }
                        }
                    }
                    else//如果没有就退出循环
                    {
                        break;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //判断用户向上
                figure_i = i;
                figure_j = j;
                for ( int k = 1 ; k <= 4 ; ++ k )
                {
                    if ( array_chessboard[ figure_i - 1 ][ figure_j ] == 'X' && figure_i - 1 >= 0 )
                    {
                        figure_i -= 1;
                        switch ( k )
                        {
                            case 1:
                            {
                                integral_b = 1;
                                break;
                            }
                            case 2:
                            {
                                integral_b = 5;
                                break;
                            }
                            case 3:
                            {
                                integral_b = 12;
                                break;
                            }
                            case 4:
                            {
                                integral_b = 200;
                                break;
                            }
                        }
                    }
                    else//如果没有就退出循环
                    {
                        break;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //判断AI向下
                figure_i = i;
                figure_j = j;
                for ( int k = 1 ; k <= 4 ; ++ k )
                {
                    if ( array_chessboard[ figure_i + 1 ][ figure_j ] == 'Y' && figure_i + 1 < array )
                    {
                        figure_i += 1;
                        switch ( k )
                        {
                            case 1:
                            {
                                integral_b = 2;
                                break;
                            }
                            case 2:
                            {
                                integral_b = 4;
                                break;
                            }
                            case 3:
                            {
                                integral_b = 11;
                                break;
                            }
                            case 4:
                            {
                                integral_b = 201;
                                break;
                            }
                        }
                    }
                    else//如果没有就退出循环
                    {
                        break;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //判断AI向上
                figure_i = i;
                figure_j = j;
                for ( int k = 1 ; k <= 4 ; ++ k )
                {
                    if ( array_chessboard[ figure_i - 1 ][ figure_j ] == 'Y' && figure_i - 1 >= 0 )
                    {
                        figure_i -= 1;
                        switch ( k )
                        {
                            case 1:
                            {
                                integral_b = 2;
                                break;
                            }
                            case 2:
                            {
                                integral_b = 4;
                                break;
                            }
                            case 3:
                            {
                                integral_b = 11;
                                break;
                            }
                            case 4:
                            {
                                integral_b = 201;
                                break;
                            }
                        }
                    }
                    else//如果没有就退出循环
                    {
                        break;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //判断用户左下
                figure_i = i;
                figure_j = j;
                for ( int k = 1 ; k <= 4 ; ++ k )
                {
                    if ( array_chessboard[ figure_i + 1 ][ figure_j - 1 ] == 'X' && figure_i + 1 < array &&
                         figure_j - 1 >= 0 )
                    {
                        figure_i += 1;
                        figure_j -= 1;
                        switch ( k )
                        {
                            case 1:
                            {
                                integral_b = 1;
                                break;
                            }
                            case 2:
                            {
                                integral_b = 5;
                                break;
                            }
                            case 3:
                            {
                                integral_b = 12;
                                break;
                            }
                            case 4:
                            {
                                integral_b = 200;
                                break;
                            }
                        }
                    }
                    else//如果没有就退出循环
                    {
                        break;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //判断用户右上
                figure_i = i;
                figure_j = j;
                for ( int k = 1 ; k <= 4 ; ++ k )
                {
                    if ( array_chessboard[ figure_i - 1 ][ figure_j + 1 ] == 'X' && figure_i - 1 >= 0 &&
                         figure_j + 1 < array )
                    {
                        figure_i -= 1;
                        figure_j += 1;
                        switch ( k )
                        {
                            case 1:
                            {
                                integral_b = 1;
                                break;
                            }
                            case 2:
                            {
                                integral_b = 5;
                                break;
                            }
                            case 3:
                            {
                                integral_b = 12;
                                break;
                            }
                            case 4:
                            {
                                integral_b = 200;
                                break;
                            }
                        }
                    }
                    else//如果没有就退出循环
                    {
                        break;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //判断AI左下
                figure_i = i;
                figure_j = j;
                for ( int k = 1 ; k <= 4 ; ++ k )
                {
                    if ( array_chessboard[ figure_i + 1 ][ figure_j - 1 ] == 'Y' && figure_i + 1 < array &&
                         figure_j - 1 >= 0 )
                    {
                        figure_i += 1;
                        figure_j -= 1;
                        switch ( k )
                        {
                            case 1:
                            {
                                integral_b = 2;
                                break;
                            }
                            case 2:
                            {
                                integral_b = 4;
                                break;
                            }
                            case 3:
                            {
                                integral_b = 11;
                                break;
                            }
                            case 4:
                            {
                                integral_b = 201;
                                break;
                            }
                        }
                    }
                    else//如果没有就退出循环
                    {
                        break;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //判断AI右上
                figure_i = i;
                figure_j = j;
                for ( int k = 1 ; k <= 4 ; ++ k )
                {
                    if ( array_chessboard[ figure_i - 1 ][ figure_j + 1 ] == 'Y' && figure_i - 1 >= 0 &&
                         figure_j + 1 < array )
                    {
                        figure_i -= 1;
                        figure_j += 1;
                        switch ( k )
                        {
                            case 1:
                            {
                                integral_b = 2;
                                break;
                            }
                            case 2:
                            {
                                integral_b = 4;
                                break;
                            }
                            case 3:
                            {
                                integral_b = 11;
                                break;
                            }
                            case 4:
                            {
                                integral_b = 201;
                                break;
                            }
                        }
                    }
                    else//如果没有就退出循环
                    {
                        break;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //判断用户右下
                figure_i = i;
                figure_j = j;
                for ( int k = 1 ; k <= 4 ; ++ k )
                {
                    if ( array_chessboard[ figure_i + 1 ][ figure_j + 1 ] == 'X' && figure_i + 1 < array &&
                         figure_j + 1 < array )
                    {
                        figure_i += 1;
                        figure_j += 1;
                        switch ( k )
                        {
                            case 1:
                            {
                                integral_b = 1;
                                break;
                            }
                            case 2:
                            {
                                integral_b = 5;
                                break;
                            }
                            case 3:
                            {
                                integral_b = 12;
                                break;
                            }
                            case 4:
                            {
                                integral_b = 200;
                                break;
                            }
                        }
                    }
                    else//如果没有就退出循环
                    {
                        break;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //判断用户左上
                figure_i = i;
                figure_j = j;
                for ( int k = 1 ; k <= 4 ; ++ k )
                {
                    if ( array_chessboard[ figure_i - 1 ][ figure_j - 1 ] == 'X' && figure_i - 1 >= 0 &&
                         figure_j - 1 >= 0 )
                    {
                        figure_i -= 1;
                        figure_j -= 1;
                        switch ( k )
                        {
                            case 1:
                            {
                                integral_b = 1;
                                break;
                            }
                            case 2:
                            {
                                integral_b = 5;
                                break;
                            }
                            case 3:
                            {
                                integral_b = 12;
                                break;
                            }
                            case 4:
                            {
                                integral_b = 200;
                                break;
                            }
                        }
                    }
                    else//如果没有就退出循环
                    {
                        break;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //判断AI右下
                figure_i = i;
                figure_j = j;
                for ( int k = 1 ; k <= 4 ; ++ k )
                {
                    if ( array_chessboard[ figure_i + 1 ][ figure_j + 1 ] == 'Y' && figure_i + 1 < array &&
                         figure_j + 1 < array )
                    {
                        figure_i += 1;
                        figure_j += 1;
                        switch ( k )
                        {
                            case 1:
                            {
                                integral_b = 2;
                                break;
                            }
                            case 2:
                            {
                                integral_b = 4;
                                break;
                            }
                            case 3:
                            {
                                integral_b = 11;
                                break;
                            }
                            case 4:
                            {
                                integral_b = 201;
                                break;
                            }
                        }
                    }
                    else//如果没有就退出循环
                    {
                        break;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //判断AI左上
                figure_i = i;
                figure_j = j;
                for ( int k = 1 ; k <= 4 ; ++ k )
                {
                    if ( array_chessboard[ figure_i - 1 ][ figure_j - 1 ] == 'Y' && figure_i - 1 >= 0 &&
                         figure_j - 1 >= 0 )
                    {
                        figure_i -= 1;
                        figure_j -= 1;
                        switch ( k )
                        {
                            case 1:
                            {
                                integral_b = 2;
                                break;
                            }
                            case 2:
                            {
                                integral_b = 4;
                                break;
                            }
                            case 3:
                            {
                                integral_b = 11;
                                break;
                            }
                            case 4:
                            {
                                integral_b = 201;
                                break;
                            }
                        }
                    }
                    else//如果没有就退出循环
                    {
                        break;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //用户横向中间空一个
                figure_i = i;
                figure_j = j;
                if ( array_chessboard[ figure_i ][ figure_j + 1 ] == 'X' &&
                     array_chessboard[ figure_i ][ figure_j - 1 ] == 'X' && figure_j + 1 < array && figure_j - 1 >= 0 )
                {
                    integral_b = 5;
                    //判断缺第三个
                    if ( array_chessboard[ figure_i ][ figure_j + 2 ] == 'X' &&
                         array_chessboard[ figure_i ][ figure_j - 2 ] == 'X' && figure_j + 2 < array &&
                         figure_j - 2 >= 0 )
                    {
                        integral_b = 200;
                    }
                        //判断缺第二个
                    else if ( array_chessboard[ figure_i ][ figure_j + 2 ] == 'X' &&
                              array_chessboard[ figure_i ][ figure_j + 3 ] == 'X' && figure_j + 3 < array )
                    {
                        integral_b = 200;
                    }
                        //判断缺第四个
                    else if ( array_chessboard[ figure_i ][ figure_j - 2 ] == 'X' &&
                              array_chessboard[ figure_i ][ figure_j - 3 ] == 'X' && figure_j - 3 >= 0 )
                    {
                        integral_b = 200;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //电脑横向中间空一个
                figure_i = i;
                figure_j = j;
                if ( array_chessboard[ figure_i ][ figure_j + 1 ] == 'Y' &&
                     array_chessboard[ figure_i ][ figure_j - 1 ] == 'Y' && figure_j + 1 < array && figure_j - 1 >= 0 )
                {
                    integral_b = 4;
                    //判断缺第三个
                    if ( array_chessboard[ figure_i ][ figure_j + 2 ] == 'Y' &&
                         array_chessboard[ figure_i ][ figure_j - 2 ] == 'Y' && figure_j + 2 < array &&
                         figure_j - 2 >= 0 )
                    {
                        integral_b = 201;
                    }
                        //判断缺第二个
                    else if ( array_chessboard[ figure_i ][ figure_j + 2 ] == 'Y' &&
                              array_chessboard[ figure_i ][ figure_j + 3 ] == 'Y' && figure_j + 3 < array )
                    {
                        integral_b = 201;
                    }
                        //判断缺第四个
                    else if ( array_chessboard[ figure_i ][ figure_j - 2 ] == 'Y' &&
                              array_chessboard[ figure_i ][ figure_j - 3 ] == 'Y' && figure_j - 3 >= 0 )
                    {
                        integral_b = 201;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //用户纵向中间空一个
                figure_i = i;
                figure_j = j;
                if ( array_chessboard[ figure_i + 1 ][ figure_j ] == 'X' &&
                     array_chessboard[ figure_i - 1 ][ figure_j ] == 'X' && figure_j + 1 < array && figure_j - 1 >= 0 )
                {
                    integral_b = 5;
                    //判断缺第三个
                    if ( array_chessboard[ figure_i + 2 ][ figure_j ] == 'X' &&
                         array_chessboard[ figure_i - 2 ][ figure_j ] == 'X' && figure_i + 2 < array &&
                         figure_i - 2 >= 0 )
                    {
                        integral_b = 200;
                    }
                        //判断缺第二个
                    else if ( array_chessboard[ figure_i + 2 ][ figure_j ] == 'X' &&
                              array_chessboard[ figure_i + 3 ][ figure_j ] == 'X' && figure_i + 3 < array )
                    {
                        integral_b = 200;
                    }
                        //判断缺第四个
                    else if ( array_chessboard[ figure_i - 2 ][ figure_j ] == 'X' &&
                              array_chessboard[ figure_i - 3 ][ figure_j ] == 'X' && figure_i - 3 >= 0 )
                    {
                        integral_b = 200;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //电脑纵向中间空一个
                figure_i = i;
                figure_j = j;
                if ( array_chessboard[ figure_i + 1 ][ figure_j ] == 'Y' &&
                     array_chessboard[ figure_i - 1 ][ figure_j ] == 'Y' && figure_i + 1 < array && figure_i - 1 >= 0 )
                {
                    integral_b = 4;
                    //判断缺第三个
                    if ( array_chessboard[ figure_i + 2 ][ figure_j ] == 'Y' &&
                         array_chessboard[ figure_i - 2 ][ figure_j ] == 'Y' && figure_i + 2 < array &&
                         figure_i - 2 >= 0 )
                    {
                        integral_b = 201;
                    }
                        //判断缺第二个
                    else if ( array_chessboard[ figure_i + 2 ][ figure_j ] == 'Y' &&
                              array_chessboard[ figure_i + 3 ][ figure_j ] == 'Y' && figure_i + 3 < array )
                    {
                        integral_b = 201;
                    }
                        //判断缺第四个
                    else if ( array_chessboard[ figure_i - 2 ][ figure_j ] == 'Y' &&
                              array_chessboard[ figure_i - 3 ][ figure_j ] == 'Y' && figure_i - 3 >= 0 )
                    {
                        integral_b = 201;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //用户右上左下中间空一个
                figure_i = i;
                figure_j = j;
                if ( array_chessboard[ figure_i + 1 ][ figure_j - 1 ] == 'X' &&
                     array_chessboard[ figure_i - 1 ][ figure_j + 1 ] == 'X' && figure_i + 1 < array &&
                     figure_j - 1 >= 0 && figure_i - 1 >= 0 && figure_j + 1 < array )
                {
                    integral_b = 5;
                    //判断缺第三个
                    if ( array_chessboard[ figure_i + 2 ][ figure_j - 2 ] == 'X' &&
                         array_chessboard[ figure_i - 2 ][ figure_j + 2 ] == 'X' && figure_i + 2 < array &&
                         figure_j - 2 >= 0 && figure_i - 2 >= 0 & figure_j + 2 < array )
                    {
                        integral_b = 200;
                    }
                        //判断缺第二个
                    else if ( array_chessboard[ figure_i + 2 ][ figure_j - 2 ] == 'X' &&
                              array_chessboard[ figure_i + 3 ][ figure_j - 3 ] == 'X' && figure_i + 3 < array &&
                              figure_j - 3 >= 0 )
                    {
                        integral_b = 200;
                    }
                        //判断缺第四个
                    else if ( array_chessboard[ figure_i - 2 ][ figure_j + 2 ] == 'X' &&
                              array_chessboard[ figure_i - 3 ][ figure_j + 3 ] == 'X' && figure_j - 3 >= 0 &&
                              figure_j + 3 < array )
                    {
                        integral_b = 200;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //电脑右上左下中间空一个
                figure_i = i;
                figure_j = j;
                if ( array_chessboard[ figure_i + 1 ][ figure_j - 1 ] == 'Y' &&
                     array_chessboard[ figure_i - 1 ][ figure_j + 1 ] == 'Y' && figure_i + 1 < array &&
                     figure_j - 1 >= 0 && figure_i - 1 >= 0 && figure_j + 1 < array )
                {
                    integral_b = 4;
                    //判断缺第三个
                    if ( array_chessboard[ figure_i + 2 ][ figure_j - 2 ] == 'Y' &&
                         array_chessboard[ figure_i - 2 ][ figure_j + 2 ] == 'Y' && figure_i + 2 < array &&
                         figure_j - 2 >= 0 && figure_i - 2 >= 0 && figure_j + 2 < array )
                    {
                        integral_b = 201;
                    }
                        //判断缺第二个
                    else if ( array_chessboard[ figure_i + 2 ][ figure_j - 2 ] == 'Y' &&
                              array_chessboard[ figure_i + 3 ][ figure_j - 3 ] == 'Y' && figure_i + 3 < array &&
                              figure_j - 3 >= 0 )
                    {
                        integral_b = 201;
                    }
                        //判断缺第四个
                    else if ( array_chessboard[ figure_i - 2 ][ figure_j + 2 ] == 'Y' &&
                              array_chessboard[ figure_i - 3 ][ figure_j + 3 ] == 'Y' && figure_i - 3 >= 0 &&
                              figure_j + 3 < array )
                    {
                        integral_b = 201;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //用户左上右下中间空一个
                figure_i = i;
                figure_j = j;
                if ( array_chessboard[ figure_i + 1 ][ figure_j + 1 ] == 'X' &&
                     array_chessboard[ figure_i - 1 ][ figure_j - 1 ] == 'X' && figure_j + 1 < array &&
                     figure_j - 1 >= 0 )
                {
                    integral_b = 5;
                    //判断缺第三个
                    if ( array_chessboard[ figure_i + 2 ][ figure_j + 2 ] == 'X' &&
                         array_chessboard[ figure_i - 2 ][ figure_j - 2 ] == 'X' && figure_i + 2 < array &&
                         figure_j + 2 < array && figure_i - 2 >= 0 && figure_j - 2 >= 0 )
                    {
                        integral_b = 200;
                    }
                        //判断缺第二个
                    else if ( array_chessboard[ figure_i + 2 ][ figure_j + 2 ] == 'X' &&
                              array_chessboard[ figure_i + 3 ][ figure_j + 3 ] == 'X' && figure_i + 3<array&&figure_j + 3 < array )
                    {
                        integral_b = 200;
                    }
                        //判断缺第四个
                    else if ( array_chessboard[ figure_i - 2 ][ figure_j - 2 ] == 'X' &&
                              array_chessboard[ figure_i - 3 ][ figure_j - 3 ] == 'X' && figure_i - 3>=0&&figure_j - 3 >=0 )
                    {
                        integral_b = 200;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //电脑左上右下中间空一个
                figure_i = i;
                figure_j = j;
                if ( array_chessboard[ figure_i + 1 ][ figure_j + 1 ] == 'Y' &&
                     array_chessboard[ figure_i - 1 ][ figure_j - 1 ] == 'Y' && figure_i + 1 < array &&
                     figure_j + 1 <array &&figure_i - 1>=0 && figure_j - 1>=0)
                {
                    integral_b = 4;
                    //判断缺第三个
                    if ( array_chessboard[ figure_i + 2 ][ figure_j + 2 ] == 'Y' &&
                         array_chessboard[ figure_i - 2 ][ figure_j - 2 ] == 'Y' && figure_i + 2 < array &&
                         figure_j + 2 <array&&figure_i - 2 >=0&& figure_j - 2>=0 )
                    {
                        integral_b = 201;
                    }
                        //判断缺第二个
                    else if ( array_chessboard[ figure_i + 2 ][ figure_j + 2 ] == 'Y' &&
                              array_chessboard[ figure_i + 3 ][ figure_j + 3 ] == 'Y' && figure_j + 3 < array )
                    {
                        integral_b = 201;
                    }
                        //判断缺第四个
                    else if ( array_chessboard[ figure_i - 2 ][ figure_j - 2 ] == 'Y' &&
                              array_chessboard[ figure_i - 3 ][ figure_j - 3 ] == 'Y' && figure_j - 3 >=0 )
                    {
                        integral_b = 201;
                    }
                }
                integral_a += integral_b;//增加积分
                integral_b = 0;//重置

                //储存最大坐标
                if ( integral_a > integral )
                {
                    integral = integral_a;//更新最大值
                    storage_coordinate[ 0 ] = i;//更新纵坐标
                    storage_coordinate[ 1 ] = j;//更新横坐标
                }
                //重置所有积分
                integral_a = 0;//重置
                integral_b = 0;//重置
            }
        }

    }
    * x = storage_coordinate[ 0 ];//更新纵坐标
    * y = storage_coordinate[ 1 ];//更新横坐标
    return;
}

//复制数值
char copy_array ( int array , char array_chessboard[array][array] , char array_chessboard_1[array][array] )
{
    for ( int i = 0 ; i < array ; i ++ )
    {
        for ( int j = 0 ; j < array ; j ++ )
        {
            array_chessboard_1[ i ][ j ] = array_chessboard[ i ][ j ];
        }
    }
    return array_chessboard_1[ array ][ array ];
}

//双人模式
void double_game ()
{
    //初始化
    char user;//判断是那个用户
    int bout = 0;//用户输入的回合
    int x;//用户横坐标
    int y;//用户纵坐标
    int array;//棋盘长度
    printf ( "请输入棋盘长度(0开始计算,12<=chess<=25):" );
    while ( scanf ( "%d" , & array ) != 1 || array < 12 || array > 25 )
    {
        while ( getchar ( ) != '\n' );//清除缓存
        printf ( "请重新输入棋盘长度:" );
    }
    char array_chessboard[array][array];//初始化棋盘
    initialization ( array , array_chessboard );//初始化数组里面的数
    while ( bout < array * array )
    {
        print_chessboard ( array , array_chessboard );//输出当前地图
        bout ++;
        printf ( "第%d回合\n" , ( bout + 1 ) / 2 );
        if ( bout % 2 == 1 )
        {
            user = 'X';
        }
        else
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
        credited ( array , x , y , array_chessboard , user );//存入用户输入的数字
        if ( judgment ( array , user , array_chessboard ) == user )//判断用户是否胜利
        {
            printf ( "用户%c胜利\n" , user );
            break;
        }
    }

    if ( bout == array * array )//平局判断
    {
        printf ( "平局\n" );
    }
    print_chessboard ( array , array_chessboard ); //输出棋盘
    while ( getchar ( ) != '\n' );//清除缓存
    home ( 1 );//返回主页
}

//单人模式
void single_game ()
{
    //初始化
    char user;//判断是那个用户
    int bout = 0;//用户输入的回合
    int x;//横坐标
    int y;//纵坐标
    int array;//棋盘长度
    printf ( "请输入棋盘长度(0开始计算,12<=chess<=25):" );
    while ( scanf ( "%d" , & array ) != 1 || array < 12 || array > 25 )
    {
        while ( getchar ( ) != '\n' );//清除缓存
        printf ( "请重新输入棋盘长度:" );
    }
    char array_chessboard[array][array];//初始化棋盘
    initialization ( array , array_chessboard );//初始化数组里面的数
    print_chessboard ( array , array_chessboard );//输出当前地图
    while ( bout < array * array / 2 )
    {
        bout ++;
        printf ( "第%d回合\n" , bout );
        user = 'X';
        printf ( "轮到用户 \n" );
        printf ( "请输入横坐标:" );
        while ( scanf ( "%d" , & x ) != 1 )
        {
            while ( getchar ( ) != '\n' );
            printf ( "请输入合法数字:" );
        }
        printf ( "请输入纵坐标:" );
        while ( scanf ( "%d" , & y ) != 1 )
        {
            while ( getchar ( ) != '\n' );
            printf ( "请输入合法数字:" );
        }
        credited ( array , x , y , array_chessboard , user );//存入用户输入的数字
        if ( judgment ( array , user , array_chessboard ) == user )//判断用户是否胜利
        {
            printf ( "用户胜利\n" );
            break;
        }

        user = 'Y';//更新电脑标识
        AI_chess ( array , & x , & y , array_chessboard );//获取ai判断输出的数
        credited ( array , x , y , array_chessboard , user );//存入AI输入的数字
        if ( judgment ( array , user , array_chessboard ) == user )//判断用户是否胜利
        {
            printf ( "AI胜利\n" );
            break;
        }
        print_chessboard ( array , array_chessboard );//输出当前地图

    }

    if ( bout == array * array / 2 )//平局判断
    {
        printf ( "平局\n" );
    }
    print_chessboard ( array , array_chessboard ); //输出棋盘
    while ( getchar ( ) != '\n' );//清除缓存
    home ( 1 );
}

//菜单
void home ( int pick )
{
    char symbol;//获取用户输入什么
    char array_1[] = "单人模式";
    char array_2[] = "双人模式";
    char array_3[] = "退出游戏";
    char array_4[] = "单人模式←";
    char array_5[] = "双人模式←";
    char array_6[] = "退出游戏←";
    printf ( "————五子棋————\n" );
    switch ( pick ) //输出图像
    {
        case 1:
        {
            printf ( "%s\n" , array_4 );
            printf ( "%s\n" , array_2 );
            printf ( "%s\n" , array_3 );
            break;
        }
        case 2:
        {
            printf ( "%s\n" , array_1 );
            printf ( "%s\n" , array_5 );
            printf ( "%s\n" , array_3 );
            break;
        }
        case 3:
        {
            printf ( "%s\n" , array_1 );
            printf ( "%s\n" , array_2 );
            printf ( "%s\n" , array_6 );
            break;
        }
    }
    printf ( "按WS上下选择\n" );
    printf ( "回车确定选择\n" );
    printf ( ":" );
    scanf ( "%c" , & symbol );
    if ( symbol == '\n' )
    {
        switch ( pick )
        {
            case 1:
            {
                fflush ( stdin );//清除缓存
                single_game ( );
                break;
            }
            case 2:
            {
                fflush ( stdin );//清除缓存
                double_game ( );
                break;
            }
            case 3:
            {
                printf ( "欢迎下次使用" );
                exit ( 0 );
                break;
            }
        }//选择需要进入的模式
    }
    else if ( symbol == 'W' || symbol == 'w' )
    {
        if ( pick <= 1 )
        {
            pick = 1;
            while ( getchar ( ) != '\n' );//清除缓存
            home ( pick );//返回主页
        }
        else
        {
            pick -= 1;
            while ( getchar ( ) != '\n' );//清除缓存
            home ( pick );//返回主页
        }
    }
    else if ( symbol == 'S' || symbol == 's' )
    {
        if ( pick >= 3 )
        {
            pick = 3;
            while ( getchar ( ) != '\n' );//清除缓存
            home ( pick );//返回主页
        }
        else
        {
            pick += 1;
            while ( getchar ( ) != '\n' );//清除缓存
            home ( pick );//返回主页
        }
    }

    while ( getchar ( ) != '\n' );//清除缓存
    home ( pick );//返回主页

}

int main ()
{
    srand ( time ( NULL ) );// 设置种子，可以让每次运行程序时得到不同的随机数序列
    home ( 1 );
    return 0;
}
