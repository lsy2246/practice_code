#include<stdio.h>
#include<stdlib.h>

int main ()
{
    double a , b , c , e , f , g , h; ///本金,年利率.年份,利息,本利,取钱,case里面的变量,i
    int d; //获取用户需要进入的模式

    //开始界面
    printf ( "简易atm机 \n" );
    printf ( "--------------------- \n" ); //用于分割
    //本金
    printf ( "请输入你的本金:" );
    while ( scanf ( "%lf" , & a ) != 1 )  //判断是否为合法数字
    {
        printf ( "请输入合法的数字:" );
        while ( getchar ( ) != '\n' );
    }

    //年利率
    printf ( "请输入你的年利率(不用输入%%):" );
    while ( scanf ( "%lf" , & b ) != 1 || b <= 0 )  //判断是否为合法数字
    {
        printf ( "请输入合法的年利率:" );
        while ( getchar ( ) != '\n' );
    }


    //年份
    printf ( "请输入你的年份:" );
    while ( scanf ( "%lf" , & c ) != 1 || c <= 0 )  //判断是否为合法数字
    {
        printf ( "请输入合理的年份:" );
        while ( getchar ( ) != '\n' );
    }

    system ( "cls" ); // windows清屏命令,如果其他系统报错删除此行或注释掉
    //system("clear"); //Linux和macOS清屏命令

    while ( 1 )
    {
        e = a * b * c / 100; //利息
        f = a + e; //本利
        printf ( "存入本金为%.3lf \n" , a );
        printf ( "当前利率为%.3lf%% \n" , b );
        printf ( "当前存了%.0lf年 \n" , c );
        printf ( "获得的利息为%.3lf \n" , e );
        printf ( "余额为%.3lf \n" , f );

        printf ( "--------------------- \n" ); //用于分割

        printf ( "请输入对应的数字进入对应的模式 \n" );
        printf ( "0.退出 \n" );
        printf ( "1.存钱 \n" );
        printf ( "2.取钱 \n" );
        printf ( "3.增加年份 \n" );
        printf ( "4.减少年份 \n" );
        printf ( "5.增加年利率 \n" );
        printf ( "6.减少年利率 \n" );

        printf ( "请输入对应的数字进入需要的模式:" );
        while ( scanf ( "%d" , & d ) < 0 || d > 4 )  //判断是否为合适数字
        {
            printf ( "请输入对应的数字:" );
            while ( getchar ( ) != '\n' );
        }

        switch ( d )
        {
            case 0:
            {
                return 1;
            }
            case 1:
            {
                printf ( "请输入你需要存入多少钱:" );
                while ( scanf ( "%lf" , & h ) != 1 || h < 0 )  //判断是否为合法数字
                {
                    printf ( "请输入合法的数字:" );
                    while ( getchar ( ) != '\n' );
                }
                a += h;
                system ( "cls" ); // windows清屏命令
                break;
            }
            case 2:
            {
                printf ( "请输入你需要取出多少钱:" );
                while ( scanf ( "%lf" , & h ) != 1 || h < 0 || h > a )  //判断是否为合法数字
                {
                    printf ( "请输入合法的数字:" );
                    while ( getchar ( ) != '\n' );
                }
                a -= h;
                system ( "cls" ); // windows清屏命令
                break;
            }

            case 3:
            {
                printf ( "请输入你需要增加多少年:" );
                while ( scanf ( "%lf" , & h ) != 1 || h < 0 )  //判断是否为合法数字
                {
                    printf ( "请输入合法的数字:" );
                    while ( getchar ( ) != '\n' );
                }
                c += h;
                system ( "cls" ); // windows清屏命令
                break;
            }
            case 4:
            {
                printf ( "请输入你需要减少多少年:" );
                while ( scanf ( "%lf" , & h ) != 1 || h < 0 || h > a )  //判断是否为合法数字
                {
                    printf ( "请输入合法的数字:" );
                    while ( getchar ( ) != '\n' );
                }
                c -= h;
                system ( "cls" ); // windows清屏命令
                break;
            }

            case 5:
            {
                printf ( "请输入你需要增加多少年利率(不用输入%%):" );
                while ( scanf ( "%lf" , & h ) != 1 || h < 0 )  //判断是否为合法数字
                {
                    printf ( "请输入合法的数字:" );
                    while ( getchar ( ) != '\n' );
                }
                b += h;
                system ( "cls" ); // windows清屏命令
                break;
            }
            case 6:
            {
                printf ( "请输入你需要减少多少年利率(不用输入%%):" );
                while ( scanf ( "%lf" , & h ) != 1 || h < 0 || h > a )  //判断是否为合法数字
                {
                    printf ( "请输入合法的数字:" );
                    while ( getchar ( ) != '\n' );
                }
                b -= h;
                system ( "cls" ); // windows清屏命令
                break;
            }

        }

    }
    return 0;
}
