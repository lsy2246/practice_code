#include<stdio.h>
#include <time.h>
#include <stdlib.h>

//声明主页
void home_procedure ( int figure );

//打印界面
void print_interface ( int size , char array[size][size] )
{
    for ( int i = 0 ; i < size ; i ++ )
    {
        for ( int j = 0 ; j < size ; j ++ )
        {
            printf ( " %c " , array[ i ][ j ] );
        }
        printf ( "\n" );
    }
}

//初始化显示界面
char initialization_appear_map ( int size , char appear_map[size][size] )
{
    for ( int i = 0 ; i < size ; i ++ )
    {
        for ( int j = 0 ; j < size ; j ++ )
        {
            appear_map[ i ][ j ] = '#';
        }
    }
}

//初始化结果界面
char initialization_result_map ( int size , int bomb , char result_map[size][size] )
{
    //将界面全部初始化为空
    for ( int i = 0 ; i < size ; i ++ )
    {
        for ( int j = 0 ; j < size ; j ++ )
        {
            result_map[ i ][ j ] = '-';
        }
    }

    //随机生成炸弹
    int i = 1;//需要生成的炸弹自增
    while ( i <= bomb )
    {
        int x = rand ( ) % size;//获随机取炸弹横坐标
        int y = rand ( ) % size;//获随机取炸弹纵坐标
        if ( result_map[ y ][ x ] == '-' )
        {
            result_map[ y ][ x ] = '*';
            ++ i;
        }
    }

    //生成数字
    for ( i = 0 ; i < size ; i ++ )
    {
        for ( int j = 0 ; j < size ; j ++ )
        {
            if ( result_map[ i ][ j ] == '-' )
            {
                char integral = '0';//初始化积分
                if ( result_map[ i ][ j + 1 ] == '*' && j < size && j + 1 < size )//判断右边的雷
                {
                    integral += 1;
                }
                if ( result_map[ i ][ j - 1 ] == '*' && j > 0 & j - 1 >= 0 )//判断左边的雷
                {
                    integral += 1;
                }
                if ( result_map[ i + 1 ][ j ] == '*' && i > 0 &&i+1<size)//判断上边的雷
                {
                    integral += 1;
                }
                if ( result_map[ i - 1 ][ j ] == '*' && i < size &&i-1>=0)//判断下边的雷
                {
                    integral += 1;
                }
                if ( result_map[ i - 1 ][ j + 1 ] == '*' && i > 0 &&i-1>=0&& j+1 < size  )//判断右上的雷
                {
                    integral += 1;
                }
                if ( result_map[ i + 1 ][ j + 1 ] == '*' && i+1 < size && j+1 < size )//判断右下的雷
                {
                    integral += 1;
                }
                if ( result_map[ i + 1 ][ j - 1 ] == '*' && i+1 < size && j-1 >= 0 )//判断左下的雷
                {
                    integral += 1;
                }
                if ( result_map[ i - 1 ][ j - 1 ] == '*' && i-1 >= 0 && j-1 >= 0 )//判断左上的雷
                {
                    integral += 1;
                }

                if ( integral != '0' )
                {
                    result_map[ i ][ j ] = integral;
                }
            }
        }
    }
}

//复制数组
void copy_array ( int size , char array_a[size][size] , char array_b[size][size] )
{
    for ( int i = 0 ; i < size ; i ++ )
    {
        for ( int j = 0 ; j < size ; j ++ )
        {
            array_a[ i ][ j ] = array_b[ i ][ j ];
        }
    }
}

//储存和判断
int replace_appear_map ( int integral , int size , int coordinate_y , int coordinate_x , char appear_map[size][size] ,
                         char copy_appear_map[size][size] , char result_map[size][size]
                       )
{
    int copy_coordinate_x = coordinate_x;//备份x
    int copy_coordinate_y = coordinate_y;//备份y
    if ( result_map[ coordinate_y ][ coordinate_x ] == '*' )//判断有没有雷
    {
        while ( getchar ( ) != '\n' );//清除缓存
        print_interface ( size , result_map );//输出原版地图
        printf ( "——踩到地雷了——\n" );
        printf ( "   *****   \n" );
        printf ( " *       * \n" );
        printf ( "*  O   O  *\n" );
        printf ( "*    ^    *\n" );
        printf ( " * /___\\  \n" );
        printf ( "   *****   \n" );
        home_procedure ( 1 );//返回主页
    }
    else if ( appear_map[ coordinate_y ][ coordinate_x ] == '&' )//判断有无旗
    {
        while ( getchar ( ) != '\n' );//清除缓存
        printf ( "此处有旗\n" );
    }
    else//点开
    {
        copy_appear_map[ coordinate_y ][ coordinate_x ] = result_map[ coordinate_y ][ coordinate_x ];//替换备份地图
        appear_map[ coordinate_y ][ coordinate_x ] = result_map[ coordinate_y ][ coordinate_x ];//替换显示地图
        if ( result_map[ coordinate_y ][ coordinate_x ] == '-' )//空白情况
        {
            while ( result_map[ coordinate_y ][ coordinate_x - 1 ] == '-' )
            {
                integral += 1;
                -- coordinate_x;
                copy_appear_map[ coordinate_y ][ coordinate_x ] = result_map[ coordinate_y ][ coordinate_x ];//替换备份地图
                appear_map[ coordinate_y ][ coordinate_x ] = result_map[ coordinate_y ][ coordinate_x ];//替换显示地图
            }
            coordinate_x = copy_coordinate_x;//还原x
            while ( result_map[ coordinate_y ][ coordinate_x + 1 ] == '-' )
            {
                integral += 1;
                ++ coordinate_x;
                copy_appear_map[ coordinate_y ][ coordinate_x ] = result_map[ coordinate_y ][ coordinate_x ];//替换备份地图
                appear_map[ coordinate_y ][ coordinate_x ] = result_map[ coordinate_y ][ coordinate_x ];//替换显示地图
            }
            coordinate_x = copy_coordinate_x;//还原x
            while ( result_map[ coordinate_y - 1 ][ coordinate_x ] == '-' )
            {
                integral += 1;
                -- coordinate_y;
                copy_appear_map[ coordinate_y ][ coordinate_x ] = result_map[ coordinate_y ][ coordinate_x ];//替换备份地图
                appear_map[ coordinate_y ][ coordinate_x ] = result_map[ coordinate_y ][ coordinate_x ];//替换显示地图
            }
            coordinate_x = copy_coordinate_x;//还原x
            while ( result_map[ coordinate_y + 1 ][ coordinate_x ] == '-' )
            {
                integral += 1;
                ++ coordinate_y;
                copy_appear_map[ coordinate_y ][ coordinate_x ] = result_map[ coordinate_y ][ coordinate_x ];//替换备份地图
                appear_map[ coordinate_y ][ coordinate_x ] = result_map[ coordinate_y ][ coordinate_x ];//替换显示地图
            }
            coordinate_x = copy_coordinate_y;//还原y
        }
        return integral + 1;//增加一个回合
    }
}

//扫雷程序
void mode_procedure ( int size , int bomb )
{
    int integral = 0;//判断下了多少次
    int coordinate_x = 0;//为储存横坐标申请内存空间
    int coordinate_y = 0;//为储存纵坐标申请内存空间
    char result_map[size][size];//为结果界面申请内存空间
    char appear_map[size][size];//为显示界面申请内存空间
    char copy_appear_map[size][size];//为显示界面的复制申请内存空间
    initialization_appear_map ( size , appear_map );//初始化显示界面
    initialization_result_map ( size , bomb , result_map );//初始化结果界面
    copy_array ( size , copy_appear_map , appear_map );//复制显示数组
    copy_appear_map[ coordinate_y ][ coordinate_x ] = '@';//设置备份数组第一次显示
    while ( 1 )
    {
        if ( integral == size * size - bomb )
        {
            while ( getchar ( ) != '\n' );//清除缓存
            printf ( "——扫雷成功———" );
            printf ( "   *****   \n" );
            printf ( " *       * \n" );
            printf ( "*  O   O  *\n" );
            printf ( "*    ∇    *\n" );
            printf ( " * \\___/  \n" );
            printf ( "   *****   \n" );
            home_procedure ( 1 );//返回主页
        }
        char pick;//初始化用户的选择
        print_interface ( size , copy_appear_map );//打印当前界面
        printf ( "输入W,S,A,D进行上下左右移动\n" );
        printf ( "输入Q确认选择,输入E插旗\n" );
        printf ( ":" );
        while ( getchar ( ) != '\n' );//清除缓存
        scanf ( "%c" , & pick );//获取用户的选择
        if ( pick == 'W' || pick == 'w' )//判断向上
        {
            if ( coordinate_y <= 0 )
            {
                coordinate_y = 0;
            }
            else
            {
                copy_appear_map[ coordinate_y ][ coordinate_x ] = appear_map[ coordinate_y ][ coordinate_x ];
                coordinate_y -= 1;
                copy_appear_map[ coordinate_y ][ coordinate_x ] = '@';
            }
        }
        if ( pick == 'S' || pick == 's' )//判断向下
        {
            if ( coordinate_y >= size - 1 )
            {
                coordinate_y = size - 1;
            }
            else
            {
                copy_appear_map[ coordinate_y ][ coordinate_x ] = appear_map[ coordinate_y ][ coordinate_x ];
                coordinate_y += 1;
                copy_appear_map[ coordinate_y ][ coordinate_x ] = '@';
            }
        }
        if ( pick == 'A' || pick == 'a' )//判断向左
        {
            if ( coordinate_x <= 0 )
            {
                coordinate_x = 0;
            }
            else
            {
                copy_appear_map[ coordinate_y ][ coordinate_x ] = appear_map[ coordinate_y ][ coordinate_x ];
                coordinate_x -= 1;
                copy_appear_map[ coordinate_y ][ coordinate_x ] = '@';
            }
        }
        if ( pick == 'D' || pick == 'd' )//判断向右
        {
            if ( coordinate_x >= size - 1 )
            {
                coordinate_x = size - 1;
            }
            else
            {
                copy_appear_map[ coordinate_y ][ coordinate_x ] = appear_map[ coordinate_y ][ coordinate_x ];
                coordinate_x += 1;
                copy_appear_map[ coordinate_y ][ coordinate_x ] = '@';
            }
        }
        if ( pick == 'Q' || pick == 'q' )//判断确定
        {
            integral = replace_appear_map ( integral , size , coordinate_y , coordinate_x , appear_map ,
                                            copy_appear_map , result_map );
        }
        if ( pick == 'E' || pick == 'e' )//判断插旗
        {
            if ( appear_map[ coordinate_y ][ coordinate_x ] == '&' )
            {
                appear_map[ coordinate_y ][ coordinate_x ] = '#';
                copy_appear_map[ coordinate_y ][ coordinate_x ] = '#';
            }
            else if ( appear_map[ coordinate_y ][ coordinate_x ] == '#' )
            {
                appear_map[ coordinate_y ][ coordinate_x ] = '&';
                copy_appear_map[ coordinate_y ][ coordinate_x ] = '&';
            }
        }
    }
}

//选择难度
void difficulty_procedure ( int length , int mode )
{
    char pick;//接收用户的选择
    char mode_a[] = "简单模式 \n";
    char mode_b[] = "困难模式 \n";
    char mode_c[] = "地狱模式 \n";
    char mode_n[] = "返回上级 \n";
    char mode_e[] = "简答模式←\n";
    char mode_f[] = "困难模式←\n";
    char mode_g[] = "地狱模式←\n";
    char mode_m[] = "返回上级←\n";
    printf ( "——模式选择——\n" );
    switch ( mode )
    {
        case 1:
        {
            printf ( "%s" , mode_e );
            printf ( "%s" , mode_b );
            printf ( "%s" , mode_c );
            printf ( "%s" , mode_n );
            break;
        }
        case 2:
        {
            printf ( "%s" , mode_a );
            printf ( "%s" , mode_f );
            printf ( "%s" , mode_c );
            printf ( "%s" , mode_n );
            break;
        }
        case 3:
        {
            printf ( "%s" , mode_a );
            printf ( "%s" , mode_b );
            printf ( "%s" , mode_g );
            printf ( "%s" , mode_n );
            break;
        }
        case 4:
        {
            printf ( "%s" , mode_a );
            printf ( "%s" , mode_b );
            printf ( "%s" , mode_n );
            printf ( "%s" , mode_m );
            break;
        }
    }
    printf ( "输入W,S进行上下移动\n" );
    printf ( "输入Q确认\n" );
    printf ( ":" );
    while ( getchar ( ) != '\n' );//清除缓存
    scanf ( "%c" , & pick );
    if ( pick == 'q' || pick == 'Q' )
    {
        switch ( mode )
        {
            case 1:
            {
                mode_procedure ( length , length * length / 5 );
                break;
            }
            case 2:
            {
                mode_procedure ( length , length * length / 3 );
                break;
            }
            case 3:
            {
                mode_procedure ( length , length * length / 2 );
                break;
            }
            case 4:
            {
                home_procedure ( 1 );
                break;
            }
        }
    }
    else if ( pick == 'W' || pick == 'w' )
    {
        mode -= 1;
        if ( mode <= 1 )
        {
            mode = 1;
        }
        difficulty_procedure ( length , mode );//返回主页
    }
    else if ( pick == 'S' || pick == 's' )
    {
        mode += 1;
        if ( mode >= 4 )
        {
            mode = 4;
        }
        difficulty_procedure ( length , mode );//返回主页
    }
    else
    {
        difficulty_procedure ( length , mode );//返回主页
    }
}

//主页
void home_procedure ( int figure )
{
    char pick;//接收用户的选择
    char mode_a[] = "初级模式 \n";
    char mode_b[] = "中级模式 \n";
    char mode_c[] = "高级模式 \n";
    char mode_n[] = "退出游戏 \n";
    char mode_e[] = "初级模式←\n";
    char mode_f[] = "中级模式←\n";
    char mode_g[] = "高级模式←\n";
    char mode_m[] = "退出游戏←\n";
    printf ( "——扫雷——\n" );
    switch ( figure )
    {
        case 1:
        {
            printf ( "%s" , mode_e );
            printf ( "%s" , mode_b );
            printf ( "%s" , mode_c );
            printf ( "%s" , mode_n );
            break;
        }
        case 2:
        {
            printf ( "%s" , mode_a );
            printf ( "%s" , mode_f );
            printf ( "%s" , mode_c );
            printf ( "%s" , mode_n );
            break;
        }
        case 3:
        {
            printf ( "%s" , mode_a );
            printf ( "%s" , mode_b );
            printf ( "%s" , mode_g );
            printf ( "%s" , mode_n );
            break;
        }
        case 4:
        {
            printf ( "%s" , mode_a );
            printf ( "%s" , mode_b );
            printf ( "%s" , mode_c );
            printf ( "%s" , mode_m );
            break;
        }
    }
    printf ( "输入W,S进行上下移动\n" );
    printf ( "输入Q进入\n" );
    printf ( ":" );
    scanf ( "%c" , & pick );
    if ( pick == 'q' || pick == 'Q' )
    {
        switch ( figure )
        {
            case 1:
            {
                difficulty_procedure ( 9 , 1 );
            }
            case 2:
            {
                difficulty_procedure ( 12 , 1 );
            }
            case 3:
            {
                difficulty_procedure ( 15 , 1 );
            }
            case 4:
            {
                printf ( "欢迎下次使用\n" );
                exit ( 0 );
            }
        }
    }
    else if ( pick == 'W' || pick == 'w' )
    {
        figure -= 1;
        if ( figure <= 1 )
        {
            figure = 1;
        }
        home_procedure ( figure );//返回主页
    }
    else if ( pick == 'S' || pick == 's' )
    {
        figure += 1;
        if ( figure >= 4 )
        {
            figure = 4;
        }
        home_procedure ( figure );//返回主页
    }
    else
    {
        home_procedure ( figure );
    }
}

//主函数
int main ()
{
    srand ( ( unsigned ) time ( NULL ) );//将当前时间戳设置为随机种子
    home_procedure ( 1 );//进入主页
    return 0;
}
