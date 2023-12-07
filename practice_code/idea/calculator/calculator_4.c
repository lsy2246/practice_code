#include<stdio.h>
#include<stdlib.h>

int main ()
{
    int d , e , g; //需要计算的模式,需要计算的数量,判断循环几次,标记是否进行了循环
    double a , b , c; //初始化的数字
    int f = 1;

    while ( 1 )
    {
        //获取用户需要计算的模式
        printf ( " \n" );
        printf ( "0.退出计算机 \n" );
        printf ( "1.加法模式 \n" );
        printf ( "2.减法模式 \n" );
        printf ( "3.乘法模式 \n" );
        printf ( "4.除法模式 \n" );

        //获取用户输入的字符
        printf ( "请输入对应的数字进入: " );
        scanf ( "%d" , & d );

        if ( d > 4 || d < 0 ) //判断数字是否符合条件
        {
            printf ( "请输入符合条件的数字 \n" );
            while ( getchar ( ) != '\n' );
            continue;
        }

        //输入0退出
        if ( d == 0 )
        {
            exit ( 0 );
        }

        //获取用户需要计算的个数
        printf ( "请输入需要的个数:" );
        scanf ( "%d" , & e );
        if ( e <= 0 ) //判断数字是否合法
        {
            printf ( "请输入合法的数字 \n" );
            while ( getchar ( ) != '\n' );
            continue;
        }

        //加法模式
        if ( d == 1 )
        {
            for ( g = 1 ; g <= e ; g ++ )
            {
                printf ( "请输入第%d位数:" , f );
                ++ f;
                scanf ( "%lf" , & a );
                b += a;
            }
            printf ( "结果为:%lf \n \n" , b );
            while ( getchar ( ) != '\n' ); //读取字符到回车结束
        }

        //减法模式
        if ( d == 2 )
        {
            for ( g = 1 ; g <= e ; g ++ )
            {
                printf ( "请输入第%d位数:" , f );
                scanf ( "%lf" , & a );
                if ( f == 1 )
                {
                    b = a;
                } else
                {
                    b -= a;
                }
                ++ f;
            }
            printf ( "结果为:%lf \n \n" , b );
            while ( getchar ( ) != '\n' ); //读取字符到回车结束
        }

        //乘法模式
        if ( d == 3 )
        {
            for ( g = 1 ; g <= e ; g ++ )
            {
                printf ( "请输入第%d位数:" , f );

                scanf ( "%lf" , & a );
                if ( f == 1 )
                {
                    b = a;
                } else
                {
                    b *= a;
                }
                ++ f;
            }
            printf ( "结果为:%lf \n \n" , b );
            while ( getchar ( ) != '\n' ); //读取字符到回车结束
        }

        //除法模式
        if ( d == 4 )
        {
            for ( g = 1 ; g <= e ; g ++ )
            {
                printf ( "请输入第%d位数:" , f );

                scanf ( "%lf" , & a );
                if ( f == 1 )
                {
                    if ( a == 0 ) //判断分母是否为0
                    {
                        printf ( "分母不能为0 \n" );
                        while ( getchar ( ) != '\n' );
                        c = 1;  //循环标识
                        continue;
                    } else
                    {
                        b = a;
                    }
                } else
                {
                    b /= a;
                }

                //判断有没有进行错误输入循环
                if ( a == 1 )
                {
                    f = 1;
                } else
                {
                    ++ f;
                }
            }
            printf ( "结果为:%lf \n \n" , b );
            while ( getchar ( ) != '\n' ); //读取字符到回车结束
        }
    }
    return 0;

}
