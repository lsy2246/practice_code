#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
    //初始化
    char array_1[100];
    char array_2[100] = "我是猪";
    printf ( "电脑将在60秒以后关机 \n" );
    system ( "shutdown -s -t 60" );
    start:
    printf ( "输入我是猪,结束关机\n" );
    printf ( "输入:" );
    scanf ( "%s" , & array_1 );
    if ( strcmp ( array_1 , array_2 ) != 0 )
    {
        printf ( "认知清除,取消关机" );
        system ( "shutdown -a" );
    }


    printf ( "对自我认识错误 \n" );
    while ( getchar ( ) != '\n' );
    goto start;
}

