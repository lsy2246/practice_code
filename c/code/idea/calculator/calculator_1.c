#include <stdio.h>


int main ()
{
    double x;
    double y;
    double v = 0;
    char z;

    printf ( "两位数计算器\n" );


    printf ( "请输入运算方式 (+ or - or * or /):" );
    scanf ( " %c" , & z );
    if ( z != '+' && z != '-' && z != '*' && z != '/' )
    {
        printf ( "你是脑干缺失,还是不识字,看不到“运算方式”这几个大字？" );
        return 1;
    }


    printf ( "请输入第一位数:" );
    scanf ( " %lf" , & x );
    if ( x == 0 && x != 0 )
    {
        printf ( "不知道什么叫数字？\n" );
        return 1;
    }

    printf ( "请输入第二位数:" );
    scanf ( " %lf" , & y );
    if ( y == 0 && y != 0 )
    {
        printf ( "不知道什么叫数字？\n" );
        return 1;
    }

    if ( z == '+' )
    {
        v = x + y;
    }
    if ( z == '-' )
    {
        v = x - y;
    }
    if ( z == '*' )
    {
        v = x * y;
    }
    if ( z == '/' )
    {
        if ( x != 0 )
        {
            v = x / y;
        } else
        {
            printf ( "分母不能为0 \n" );
            return 1;
        }
    }
    printf ( "计算结果为:%lf: \n" , v );
    return 0;
}

