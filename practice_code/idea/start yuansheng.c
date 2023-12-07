#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main ()
{
    //生成随机数字
    srand ( ( unsigned int ) time ( NULL ) ); //设置睡觉函数预定值
    int figure_1 = rand ( ) % 100; //接收随机数

    //初始化
    int figure_2; //用户输入的数字
    int number_times = 2; //用户输入的次数
    printf ( "请输入%d开启原神\n" , figure_1 );
    printf ( "请输入:" );
    while ( scanf ( "%d" , & figure_2 ) )
    {
        if ( figure_1 == figure_2 )
        {
            printf ( "智力正常,原神启动\n" );
            system ( "start https://genshin.hoyoverse.com" );
            return 1;
        }
        if ( number_times == 0 )
        {
            printf ( "智力缺陷关闭电脑" );
            system ( "shutdown -s" );
            return 1;
        }

        if ( figure_1 < figure_2 )
        {
            printf ( "还剩%d次机会" , number_times );
            printf ( "数字大了请重新输入:" );
            while ( getchar ( ) != '\n' ); //清除缓存
            -- number_times; //减少次数
            continue;
        }

        if ( figure_1 > figure_2 )
        {
            printf ( "还剩%d次机会" , number_times );
            printf ( "数字小了请重新输入:" );
            while ( getchar ( ) != '\n' ); //清除缓存
            -- number_times; //减少次数
            continue;
        }

    }
}
