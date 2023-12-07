#include<stdio.h>

int main ()
{
    for ( ;; )
    {
        double x , y , z; //存款金金，存款年份,年利率
        int g; //获取退出字符
        printf ( "存款本利计算器 \n" );
        printf ( "请输入本金:" );
        scanf ( "%lf" , & x );
        printf ( "请输入年份:" );
        scanf ( "%lf" , & y );
        printf ( "请输入年利率(不用加%%):" );
        scanf ( "%lf" , & z );
        printf ( "利息为%lf,本金加利息为%lf \n" , x * y * z / 100 , x + x * y * z / 100 );

        while ( getchar ( ) != '\n' ); //读取缓存，到回车结束

        printf ( "输入0退出,输入其他继续计算: " );
        g = getchar ( );
        if ( g == '0' )
        {
            break;
        }
        if ( g == '\n' || g != '0' )
        {
            continue;  //重新启动
        }

    }
    return 0;
}
