#include <stdio.h>

int main ()
{
    //定义函数
    int a; //计算模式选择的数字
    double x , y; //计算输入的数字, 第一位数字x,第二位数字y

    //输出主界面
    printf ( "*计算机* \n" );
    printf ( "1.加法模式 \n" );
    printf ( "2.减法模式 \n" );
    printf ( "3.乘法模式 \n" );
    printf ( "4.除法模式 \n" );
    printf ( "5.退出程序 \n" );
    printf ( "输入对应的数字进入对应的模式 \n" );

    //获取需要进入的模式
    printf ( "输入对应的数字:" );
    scanf ( " %d" , & a );    //判断用户输入的数字是否符合条件
    if ( a > 5 || a < 1 )
    {
        printf ( "请输入数字" );
        return 1;
    }


    //计算的第一位数字
    printf ( "输入第一位需要计算的数:" );
    scanf ( " %lf" , & x );    //判断用户输入的数字是否符合条件
    if ( a == 0 && a != 0 )
    {
        printf ( "请输入数字" );
        return 1;
    }

    //计算的第二位数字
    printf ( "输入第二位需要计算的数:" );
    scanf ( " %lf" , & y );    //判断用户输入的数字是否符合条件
    if ( a == 0 && a != 0 )
    {
        printf ( "请输入数字" );
        return 1;
    }

    //计算代码块
    switch ( a )
    {
        //加法
        case 1:
            printf ( "a + b = %lf \n" , x + y );
            break;
            //减法
        case 2:
            if ( y = 0 )  //除数不能为0
            {
                printf ( "除数不能为0" );
                return 0;
            }
            printf ( "a - b = %lf \n" , x - y );
            break;
            //乘法
        case 3:
            printf ( "a * b = %lf \n" , x * y );
            break;
            //除法
        case 4:
            printf ( "a / b= %lf \n" , x / y );
            break;
            //输入错误提示
        default :
            printf ( "请输入正确的数字" );
            return 1;
    }


    return 0;
}
