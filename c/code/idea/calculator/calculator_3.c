#include<stdio.h>
#include<stdlib.h>

int main ()
{
    double x , y;//需要计算的数字
    int a;//选择进入模式的数字
    while ( 1 )
    {
        //计算机界面
        printf ( "计算器 \n" );
        printf ( "1.加法模式 \n" );
        printf ( "2.减法模式 \n" );
        printf ( "3.乘法模式 \n" );
        printf ( "4.除法模式 \n" );
        printf ( "5.退出程序 \n" );

        //获取用户输入模式的数字
        printf ( "请输入对应的数字进入:" );
        if ( scanf ( "%d" , & a ) < 1 || a > 5 )
        {
            printf ( "请输入正确的数字 \n" );
            while ( getchar ( ) != '\n' ); //表示循环读入字符，直到读到回车符结束循环
            continue;
        }

        //模式5
        if ( a == 5 )
        {
            exit ( 0 );
        }

        //获取用户需要计算的第一位数字
        printf ( "请输入第一位数:" );
        scanf ( "%lf" , & x );

        //获取用户需要计算的第二位数字
        printf ( "请输入第二位数:" );
        scanf ( "%lf" , & y );


        //计算程序
        switch ( a )
        {
            //加法
            case 1:
                printf ( "相加结果为%lf \n" , x + y );
                break;
                //减法
            case 2:
                printf ( "相减结果为%lf \n" , x - y );
                break;
                //乘法
            case 3:
                printf ( "相乘结果为%lf \n" , x * y );
                break;
                //除法
            case 4:
                if ( y == 0 )
                {
                    printf ( "除数不能为0" ); //除数不能为0
                    continue;
                }
                printf ( "相除结果为%lf \n" , x / y );
                break;
        }

    }
    return 0;
}
