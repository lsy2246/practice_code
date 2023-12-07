#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//声明
void home ();

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
        } else
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
        } else
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
        } else
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
        } else
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

//生成随机数
void generateRandomPosition ( int * figure , int array , int * x , int * y , char array_chessboard[array][array] )
{
    int randomNumber = rand ( ) % 8;
    switch ( randomNumber )
    {
        case 0:
        {
            * y += 1;
            * figure = 1;
            break;
        }
        case 1:
        {
            * x += 1;
            * figure = 1;
            break;
        }
        case 2:
        {
            * x += 1;
            * y += 1;
            * figure = 1;
            break;
        }
        case 3:
        {
            * x -= 1;
            * figure = 1;
            break;
        }
        case 4:
        {
            * y -= 1;
            * figure = 1;
            break;
        }
        case 5:
        {
            * x -= 1;
            * y -= 1;
            * figure = 1;
            break;
        }
        case 6:
        {
            * x -= 1;
            * y += 1;
            * figure = 1;
            break;
        }
        case 7:
        {
            * x += 1;
            * y -= 1;
            * figure = 1;
            break;
        }
    }
    while ( * x < 0 || * x >= array || * y < 0 || * y >= array || array_chessboard[ * x ][ * y ] != '.' )
    {
        generateRandomPosition (  figure , array ,  x ,  y , array_chessboard );
    }
}

//判断用户位置
void user_chess ( int * figure , int array , int * x , int * y , char user , char array_chessboard[array][array] )
{
    int i;//初始化横排
    int j;//初始化竖排

    //如果横向有四个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i ][ j + 1 ] == user &&
                 array_chessboard[ i ][ j + 2 ] == user &&
                 array_chessboard[ i ][ j + 3 ] == user
                    )
            {
                if ( array_chessboard[ i ][ j - 1 ] == '.' )
                {
                    * x = i;
                    * y = j - 1;
                    * figure = 4;
                } else if ( array_chessboard[ i ][ j + 4 ] == '.' )
                {
                    * x = i;
                    * y = j + 4;
                    * figure = 4;
                } else if ( * x < 0 || * x >= array || * y < 0 || * y >= array ||
                            array_chessboard[ * x ][ * y ] != '.' )
                {
                    continue;
                }
                return;
            }

        }
    }
    //判断纵向有四个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i + 1 ][ j ] == user &&
                 array_chessboard[ i + 2 ][ j ] == user &&
                 array_chessboard[ i + 3 ][ j ] == user

                    )
            {
                if ( array_chessboard[ i - 1 ][ j ] == '.' )
                {
                    * x = i - 1;
                    * y = j;
                    * figure = 4;
                } else if ( array_chessboard[ i + 4 ][ j ] == '.' )
                {
                    * x = i + 4;
                    * y = j;
                    * figure = 4;
                } else if ( * x < 0 || * x >= array || * y < 0 || * y >= array ||
                            array_chessboard[ * x ][ * y ] != '.' )
                {
                    continue;
                }
                return;
            }

        }
    }
    //判断左往右边斜有四个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i + 1 ][ j + 1 ] == user &&
                 array_chessboard[ i + 2 ][ j + 2 ] == user &&
                 array_chessboard[ i + 3 ][ j + 3 ] == user
                    )
            {
                if ( array_chessboard[ i - 1 ][ j - 1 ] == '.' )
                {
                    * x = i - 1;
                    * y = j - 1;
                    * figure = 4;
                } else if ( array_chessboard[ i + 4 ][ j + 4 ] == '.' )
                {
                    * x = i + 4;
                    * y = j + 4;
                    * figure = 4;
                } else if ( * x < 0 || * x >= array || * y < 0 || * y >= array ||
                            array_chessboard[ * x ][ * y ] != '.' )
                {
                    continue;
                }
                return;
            }

        }
    }
    //判断右往左边斜四个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i + 1 ][ j - 1 ] == user &&
                 array_chessboard[ i + 2 ][ j - 2 ] == user &&
                 array_chessboard[ i + 3 ][ j - 3 ] == user
                    )
            {
                if ( array_chessboard[ i - 1 ][ j + 1 ] == '.' )
                {
                    * x = i - 1;
                    * y = j + 1;
                    * figure = 4;
                } else if ( array_chessboard[ i + 4 ][ j - 4 ] == '.' )
                {
                    * x = i + 4;
                    * y = j - 4;
                    * figure = 4;
                } else if ( * x < 0 || * x >= array || * y < 0 || * y >= array ||
                            array_chessboard[ * x ][ * y ] != '.' )
                {
                    continue;
                }
                return;
            }

        }
    }

    //如果横向有三个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i ][ j + 1 ] == user &&
                 array_chessboard[ i ][ j + 2 ] == user
                    )
            {

                if ( array_chessboard[ i ][ j - 1 ] == '.' && array_chessboard[ i ][ j + 3 ] == '.' )
                {
                    * x = i;
                    * y = j - 1;
                    * figure = 3;
                } else if ( array_chessboard[ i ][ j + 3 ] == '.' && array_chessboard[ i ][ j - 1 ] == '.' )
                {
                    * x = i;
                    * y = j + 3;
                    * figure = 3;
                } else if ( * x < 0 || * x >= array || * y < 0 || * y >= array ||
                            array_chessboard[ * x ][ * y ] != '.' )
                {
                    continue;
                }
                return;
            }

        }
    }
    //判断纵向有三个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i + 1 ][ j ] == user &&
                 array_chessboard[ i + 2 ][ j ] == user

                    )
            {
                if ( array_chessboard[ i - 1 ][ j ] == '.' && array_chessboard[ i + 3 ][ j ] == '.' )
                {
                    * x = i - 1;
                    * y = j;
                    * figure = 3;
                } else if ( array_chessboard[ i + 3 ][ j ] == '.' && array_chessboard[ i - 1 ][ j ] == '.' )
                {
                    * x = i + 3;
                    * y = j;
                    * figure = 3;
                } else if ( * x < 0 || * x >= array || * y < 0 || * y >= array ||
                            array_chessboard[ * x ][ * y ] != '.' )
                {
                    continue;
                }
                return;
            }

        }
    }
    //判断左往右边斜有三个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i + 1 ][ j + 1 ] == user &&
                 array_chessboard[ i + 2 ][ j + 2 ] == user
                    )
            {
                if ( array_chessboard[ i - 1 ][ j - 1 ] == '.' && array_chessboard[ i + 3 ][ j + 3 ] == '.' )
                {
                    * x = i - 1;
                    * y = j - 1;
                    * figure = 3;
                } else if ( array_chessboard[ i + 3 ][ j + 3 ] == '.' && array_chessboard[ i - 1 ][ j - 1 ] == '.' )
                {
                    * x = i + 3;
                    * y = j + 3;
                    * figure = 3;
                } else if ( * x < 0 || * x >= array || * y < 0 || * y >= array ||
                            array_chessboard[ * x ][ * y ] != '.' )
                {
                    continue;
                }
                return;
            }

        }
    }
    //判断右往左边斜三个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i + 1 ][ j - 1 ] == user &&
                 array_chessboard[ i + 2 ][ j - 2 ] == user
                    )
            {
                if ( array_chessboard[ i - 1 ][ j + 1 ] == '.' && array_chessboard[ i + 3 ][ j - 3 ] == '.' )
                {
                    * x = i - 1;
                    * y = j + 1;
                    * figure = 3;
                } else if ( array_chessboard[ i + 3 ][ j - 3 ] == '.' && array_chessboard[ i - 1 ][ j + 1 ] == '.' )
                {
                    * x = i + 3;
                    * y = j - 3;
                    * figure = 3;
                } else if ( * x < 0 || * x >= array || * y < 0 || * y >= array ||
                            array_chessboard[ * x ][ * y ] != '.' )
                {
                    continue;
                }
                return;
            }

        }
    }
    //如果横向有两个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i ][ j + 1 ] == user
                    )
            {
                if ( array_chessboard[ i ][ j - 1 ] == '.' && array_chessboard[ i ][ j + 2 ] == '.' )
                {
                    * x = i;
                    * y = j - 1;
                    * figure = 2;
                } else if ( array_chessboard[ i ][ j + 2 ] == '.' && array_chessboard[ i ][ j - 1 ] == '.' )
                {
                    * x = i;
                    * y = j + 2;
                    * figure = 2;
                } else if ( * x < 0 || * x >= array || * y < 0 || * y >= array ||
                            array_chessboard[ * x ][ * y ] != '.' )
                {
                    continue;
                }
                return;
            }

        }
    }
    //判断纵向有两个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i + 2 ][ j ] == '.' && array_chessboard[ i - 1 ][ j ] == '.' )
            {
                if ( array_chessboard[ i ][ j ] == user &&
                     array_chessboard[ i + 1 ][ j ] == user
                        )
                {
                    if ( array_chessboard[ i + 2 ][ j ] == '.' && array_chessboard[ i - 1 ][ j ] == '.' )
                    {
                        * x = i + 2;
                        * y = j;
                        * figure = 2;
                    } else if ( array_chessboard[ i - 1 ][ j ] == '.' && array_chessboard[ i + 2 ][ j ] == '.' )
                    {
                        * x = i - 1;
                        * y = j;
                        * figure = 2;
                    } else if ( * x < 0 || * x >= array || * y < 0 || * y >= array ||
                                array_chessboard[ * x ][ * y ] != '.' )
                    {
                        continue;
                    }
                    return;
                }
            }
        }
    }
    //判断左往右边斜有两个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i + 1 ][ j + 1 ] == user
                    )
            {
                if ( array_chessboard[ i - 1 ][ j - 1 ] == '.' && array_chessboard[ i + 2 ][ j + 2 ] == '.' )
                {
                    * x = i - 1;
                    * y = j - 1;
                    * figure = 2;
                } else if ( array_chessboard[ i + 2 ][ j + 2 ] == '.' && array_chessboard[ i - 1 ][ j - 1 ] == '.' )
                {
                    * x = i + 2;
                    * y = j + 2;
                    * figure = 2;
                } else if ( * x < 0 || * x >= array || * y < 0 || * y >= array ||
                            array_chessboard[ * x ][ * y ] != '.' )
                {
                    continue;
                }
                return;
            }


        }
    }
    //判断右往左边斜两个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i + 1 ][ j - 1 ] == user
                    )
            {
                if ( array_chessboard[ i + 2 ][ j - 2 ] == '.' && array_chessboard[ i - 1 ][ j + 1 ] == '.' )
                {
                    * x = i + 2;
                    * y = j - 2;
                    * figure = 2;
                } else if ( array_chessboard[ i - 1 ][ j + 1 ] == '.' && array_chessboard[ i + 2 ][ j - 2 ] == '.' )
                {
                    * x = i - 1;
                    * y = j + 1;
                    * figure = 2;
                } else if ( * x < 0 || * x >= array || * y < 0 || * y >= array ||
                            array_chessboard[ * x ][ * y ] != '.' )
                {
                    continue;
                }
                return;
            }

        }
    }
    //如果不满足随机输入
    generateRandomPosition ( figure , array , x , y , array_chessboard );


}

//判断AI位置
void AI_chess ( int * figure , int array , int * x_1 , int * y_1 , char user , char array_chessboard[array][array] )
{
    int i;//初始化横排
    int j;//初始化竖排

    //如果横向有四个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i ][ j + 1 ] == user &&
                 array_chessboard[ i ][ j + 2 ] == user &&
                 array_chessboard[ i ][ j + 3 ] == user
                    ) //此if为了判断是否三个一样
            {
                if ( array_chessboard[ i ][ j - 1 ] == '.' )
                {
                    * x_1 = i;
                    * y_1 = j - 1;
                    * figure = 4;
                } else if ( array_chessboard[ i ][ j + 4 ] == '.' )
                {
                    * x_1 = i;
                    * y_1 = j + 4;
                    * figure = 4;
                } else if ( * x_1 < 0 || * x_1 >= array || * y_1 < 0 || * y_1 >= array ||
                            array_chessboard[ * x_1 ][ * y_1 ] != '.' )
                {
                    continue;
                }
                return;
            }

        }
    }
    //判断纵向有四个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i + 1 ][ j ] == user &&
                 array_chessboard[ i + 2 ][ j ] == user &&
                 array_chessboard[ i + 3 ][ j ] == user

                    )
            {
                if ( array_chessboard[ i - 1 ][ j ] == '.' )
                {
                    * x_1 = i - 1;
                    * y_1 = j;
                    * figure = 4;
                } else if ( array_chessboard[ i + 4 ][ j ] == '.' )
                {
                    * x_1 = i + 4;
                    * y_1 = j;
                    * figure = 4;
                } else if ( * x_1 < 0 || * x_1 >= array || * y_1 < 0 || * y_1 >= array ||
                            array_chessboard[ * x_1 ][ * y_1 ] != '.' )
                {
                    continue;
                }
                return;
            }

        }
    }
    //判断左往右边斜有四个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i + 1 ][ j + 1 ] == user &&
                 array_chessboard[ i + 2 ][ j + 2 ] == user &&
                 array_chessboard[ i + 3 ][ j + 3 ] == user
                    )
            {
                if ( array_chessboard[ i - 1 ][ j - 1 ] == '.' )
                {
                    * x_1 = i - 1;
                    * y_1 = j - 1;
                    * figure = 4;
                } else if ( array_chessboard[ i + 4 ][ j + 4 ] == '.' )
                {
                    * x_1 = i + 4;
                    * y_1 = j + 4;
                    * figure = 4;
                } else if ( * x_1 < 0 || * x_1 >= array || * y_1 < 0 || * y_1 >= array ||
                            array_chessboard[ * x_1 ][ * y_1 ] != '.' )
                {
                    continue;
                }
                return;
            }

        }
    }
    //判断右往左边斜四个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i + 1 ][ j - 1 ] == user &&
                 array_chessboard[ i + 2 ][ j - 2 ] == user &&
                 array_chessboard[ i + 3 ][ j - 3 ] == user
                    )
            {
                if ( array_chessboard[ i - 1 ][ j + 1 ] == '.' )
                {
                    * x_1 = i - 1;
                    * y_1 = j + 1;
                    * figure = 4;
                } else if ( array_chessboard[ i + 4 ][ j - 4 ] == '.' )
                {
                    * x_1 = i + 4;
                    * y_1 = j - 4;
                    * figure = 4;
                } else if ( * x_1 < 0 || * x_1 >= array || * y_1 < 0 || * y_1 >= array ||
                            array_chessboard[ * x_1 ][ * y_1 ] != '.' )
                {
                    continue;
                }
                return;
            }

        }
    }

    //如果横向有三个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i ][ j + 1 ] == user &&
                 array_chessboard[ i ][ j + 2 ] == user
                    ) //此if为了判断是否三个一样
            {

                if ( array_chessboard[ i ][ j - 1 ] == '.' &&  array_chessboard[ i ][ j - 2 ] == '.')
                {
                    * x_1 = i;
                    * y_1 = j - 1;
                    * figure = 3;
                } else if ( array_chessboard[ i ][ j + 3 ] == '.' && array_chessboard[ i ][ j + 4 ] == '.' )
                {
                    * x_1 = i;
                    * y_1 = j + 3;
                    * figure = 3;
                } else if ( * x_1 < 0 || * x_1 >= array || * y_1 < 0 || * y_1 >= array ||
                            array_chessboard[ * x_1 ][ * y_1 ] != '.' )
                {
                    continue;
                }
                return;
            }

        }
    }
    //判断纵向有三个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i + 1 ][ j ] == user &&
                 array_chessboard[ i + 2 ][ j ] == user

                    )
            {
                if ( array_chessboard[ i - 1 ][ j ] == '.' &&array_chessboard[ i - 2 ][ j ] == '.' )
                {
                    * x_1 = i - 1;
                    * y_1 = j;
                    * figure = 3;
                } else if ( array_chessboard[ i + 3 ][ j ] == '.'&&array_chessboard[ i + 4 ][ j ] == '.'  )
                {
                    * x_1 = i + 3;
                    * y_1 = j;
                    * figure = 3;
                } else if ( * x_1 < 0 || * x_1 >= array || * y_1 < 0 || * y_1 >= array ||
                            array_chessboard[ * x_1 ][ * y_1 ] != '.' )
                {
                    continue;
                }
                return;
            }

        }
    }
    //判断左往右边斜有三个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i + 1 ][ j + 1 ] == user &&
                 array_chessboard[ i + 2 ][ j + 2 ] == user
                    )
            {
                if ( array_chessboard[ i - 1 ][ j - 1 ] == '.' && array_chessboard[ i - 2 ][ j - 2 ] == '.' )
                {
                    * x_1 = i - 1;
                    * y_1 = j - 1;
                    * figure = 3;
                } else if ( array_chessboard[ i + 3 ][ j + 3 ] == '.' && array_chessboard[ i + 4 ][ j + 4 ] == '.' )
                {
                    * x_1 = i + 3;
                    * y_1 = j + 3;
                    * figure = 3;
                } else if ( * x_1 < 0 || * x_1 >= array || * y_1 < 0 || * y_1 >= array ||
                            array_chessboard[ * x_1 ][ * y_1 ] != '.' )
                {
                    continue;
                }
                return;
            }

        }
    }
    //判断右往左边斜三个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i + 1 ][ j - 1 ] == user &&
                 array_chessboard[ i + 2 ][ j - 2 ] == user
                    )
            {
                if ( array_chessboard[ i - 1 ][ j + 1 ] == '.' &&array_chessboard[ i - 2 ][ j + 2 ] == '.'  )
                {
                    * x_1 = i - 1;
                    * y_1 = j + 1;
                    * figure = 3;
                } else if ( array_chessboard[ i + 3 ][ j - 3 ] == '.'&& array_chessboard[ i + 4 ][ j - 4 ] == '.' )
                {
                    * x_1 = i + 3;
                    * y_1 = j - 3;
                    * figure = 3;
                } else if ( * x_1 < 0 || * x_1 >= array || * y_1 < 0 || * y_1 >= array ||
                            array_chessboard[ * x_1 ][ * y_1 ] != '.' )
                {
                    continue;
                }
                return;
            }

        }
    }
    //如果横向有两个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i ][ j + 1 ] == user
                    )
            {
                if ( array_chessboard[ i ][ j - 1 ] == '.' )
                {
                    * x_1 = i;
                    * y_1 = j - 1;
                    * figure = 2;
                } else if ( array_chessboard[ i ][ j + 2 ] == '.' )
                {
                    * x_1 = i;
                    * y_1 = j + 2;
                    * figure = 2;
                } else if ( * x_1 < 0 || * x_1 >= array || * y_1 < 0 || * y_1 >= array ||
                            array_chessboard[ * x_1 ][ * y_1 ] != '.' )
                {
                    continue;
                }
                return;
            }

        }
    }
    //判断纵向有两个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i + 2 ][ j ] == '.' && array_chessboard[ i - 1 ][ j ] == '.' )
            {
                if ( array_chessboard[ i ][ j ] == user &&
                     array_chessboard[ i + 1 ][ j ] == user
                        )
                {
                    if ( array_chessboard[ i + 2 ][ j ] == '.' )
                    {
                        * x_1 = i + 2;
                        * y_1 = j;
                        * figure = 2;
                    } else if ( array_chessboard[ i - 1 ][ j ] == '.' )
                    {
                        * x_1 = i - 1;
                        * y_1 = j;
                        * figure = 2;
                    } else if ( * x_1 < 0 || * x_1 >= array || * y_1 < 0 || * y_1 >= array ||
                                array_chessboard[ * x_1 ][ * y_1 ] != '.' )
                    {
                        continue;
                    }
                    return;
                }
            }
        }
    }
    //判断左往右边斜有两个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i + 1 ][ j + 1 ] == user
                    )
            {
                if ( array_chessboard[ i - 1 ][ j - 1 ] == '.' )
                {
                    * x_1 = i - 1;
                    * y_1 = j - 1;
                    * figure = 2;
                } else if ( array_chessboard[ i + 2 ][ j + 2 ] == '.' )
                {
                    * x_1 = i + 2;
                    * y_1 = j + 2;
                    * figure = 2;
                } else if ( * x_1 < 0 || * x_1 >= array || * y_1 < 0 || * y_1 >= array ||
                            array_chessboard[ * x_1 ][ * y_1 ] != '.' )
                {
                    continue;
                }
                return;
            }


        }
    }
    //判断右往左边斜两个一样
    for ( i = 0 ; i < array ; i ++ )
    {
        for ( j = 0 ; j < array ; j ++ )
        {
            if ( array_chessboard[ i ][ j ] == user &&
                 array_chessboard[ i + 1 ][ j - 1 ] == user
                    )
            {
                if ( array_chessboard[ i + 2 ][ j - 2 ] == '.' )
                {
                    * x_1 = i + 2;
                    * y_1 = j - 2;
                    * figure = 2;
                } else if ( array_chessboard[ i - 1 ][ j + 1 ] == '.' )
                {
                    * x_1 = i - 1;
                    * y_1 = j + 1;
                    * figure = 2;
                } else if ( * x_1 < 0 || * x_1 >= array || * y_1 < 0 || * y_1 >= array ||
                            array_chessboard[ * x_1 ][ * y_1 ] != '.' )
                {
                    continue;
                }
                return;
            }

        }
    }
    //如果不满足随机输入
    generateRandomPosition ( figure , array , x_1 , y_1 , array_chessboard );


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

//判断结果输入哪个结果
void judgment_outcome ( int figure_1 , int figure_2 , int array , int * x , int * y , int * x_1 , int * y_1 )
{
    if ( figure_2 >= figure_1 )
    {
        * x = * x_1;
        * y = * y_1;
    }

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
    printf ( "请输入棋盘长度(0开始计算,8<=chess<=25):" );
    while ( scanf ( "%d" , & array ) != 1 || array < 8 || array > 25 )
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
    int x_1;//复制横坐标
    int y_1;//复制纵坐标
    int figure_1;//多少连珠
    int figure_2;//备用多少连珠
    int array;//棋盘长度
    printf ( "请输入棋盘长度(0开始计算,8<=chess<=25):" );
    while ( scanf ( "%d" , & array ) != 1 || array < 8 || array > 25 )
    {
        while ( getchar ( ) != '\n' );//清除缓存
        printf ( "请重新输入棋盘长度:" );
    }
    char array_chessboard[array][array];//初始化棋盘
    char array_chessboard_1[array][array];//初始化备用棋盘
    initialization ( array , array_chessboard );//初始化数组里面的数
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

        copy_array ( array , array_chessboard , array_chessboard_1 );//复制当前棋盘
        x_1=x;//复制用户下的位置
        y_1=y;//复制用户下的位置
        user_chess ( & figure_1 , array , & x , & y , user , array_chessboard );//获取用户判断输出的数
        user = 'Y';
        AI_chess ( & figure_2 , array , & x_1 , & y_1 , user , array_chessboard_1 );//获取ai判断输出的数
        judgment_outcome ( figure_1 , figure_2 , array , & x , & y , & x_1 , & y_1 );//判断输出谁
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