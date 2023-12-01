#include<stdio.h>
#include<stdlib.h>

int main ()
{
    while ( 1 ) //计算器运行
    {
        //初始化
        double result = 0;  //结果
        double array_1[100]; //储存数字的的数组
        char array_2[100]; //储存符号
        double array_3[100]; //储存乘除数字的的数组
        char array_4[100]; //储存乘除符号
        int tab_2 = 0 , tab_3 = 0 , tab_4 = 0 , tab_7 = 0 , tab_8 = 0 , tab_a = 0;//乘除里符号接收的第几位;用于判断接收位数;加减第几位；用获取乘除数字的次数;判断用户是否退出获取加减循环
        int tab_1 = 0 , tab_5 = 0 , tab_6 = 0; //判断用户是否退出获取数字循环,判断用户是否退出获取乘除循环;
        int tab_9; //主页面判断

        //主页面
        printf ( "---主页--- \n" );
        printf ( "输入0退出 \n" );
        printf ( "任意字符或双回车进入计算:" );
        tab_9 = getchar ( );
        if ( tab_9 == '0' )
        {
            printf ( "欢迎下次使用!" );
            return 1;
        }
        while ( getchar ( ) != '\n' );  //清楚缓存
        printf ( "-------- \n" );
        //此层循环计算加减开始
        for ( tab_4 = 0 ; tab_8 == 0 ; tab_4 ++ )
        {
            //此层循环计算乘除开始
            for ( tab_7 = 0 ; tab_5 == 0 ; tab_7 ++ )
            {

                //此循环接收用户输入的数据开始
                for ( ; tab_1 == 0 ; )
                {
                    //获取用户输入的数字
                    printf ( "请输入第%d位数:" , tab_3 + 1 );
                    while ( scanf ( "%lf" , & array_1[ tab_3 ] ) != 1 )
                    {
                        printf ( "请输入合法的数字:" );
                        while ( getchar ( ) != '\n' );  //清楚缓存
                        continue;  //重新开始循环
                    }

                    while ( getchar ( ) != '\n' );  //清楚缓存

                    //获取用户输入的符号
                    printf ( "+ or - or * or / or = \n" );
                    printf ( "请输入第%d位符号:" , tab_3 + 1 );
                    scanf ( " %c" , & array_2[ tab_3 ] );
                    while ( array_2[ tab_3 ] != '+' && array_2[ tab_3 ] != '-' && array_2[ tab_3 ] != '*' &&
                            array_2[ tab_3 ] != '/' && array_2[ tab_3 ] != '=' )
                    {
                        printf ( "请输入正确的符号:" );
                        while ( getchar ( ) != '\n' );  //清楚缓存
                        scanf ( " %c" , & array_2[ tab_3 ] ); //重新获取字符
                    }


                    while ( getchar ( ) != '\n' );  //清楚缓存

                    //分母不能为0
                    if ( tab_3 == 0 && array_1[ tab_3 ] == 0 && array_2[ tab_3 ] == '/' )
                    {
                        printf ( "分母不能为0,请重新输入 \n" );
                        while ( getchar ( ) != '\n' ); //清楚缓存
                        continue;  //重新开始循环
                    }


                    //判断是=结束计算出结果
                    if ( array_2[ tab_3 ] == '=' )
                    {
                        tab_1 = 1;
                        break;
                    }

                    //次数的自增
                    ++ tab_3;
                }
                //此循环接收用户输入的数据结束


                //计算乘法
                if ( array_2[ tab_7 ] == '*' )
                {
                    array_1[ tab_7 + 1 ] = array_1[ tab_7 ] * array_1[ tab_7 + 1 ]; //计算
                }

                //计算除法
                if ( array_2[ tab_7 ] == '/' )
                {
                    array_1[ tab_7 + 1 ] = array_1[ tab_7 ] / array_1[ tab_7 + 1 ]; //计算
                }

                //跳过加法减法
                if ( array_2[ tab_7 ] == '+' || array_2[ tab_7 ] == '-' )
                {
                    array_3[ tab_2 ] = array_1[ tab_7 ]; //储存计算的数
                    array_4[ tab_2 ] = array_2[ tab_7 ]; //储存符号
                    ++ tab_2; //增加符号存储位置
                }

                //退出乘除
                if ( array_2[ tab_7 ] == '=' )
                {
                    array_3[ tab_2 ] = array_1[ tab_7 ]; //储存计算的数
                    array_4[ tab_2 ] = array_2[ tab_7 ]; //储存符号
                    tab_5 = 1; //防止再次进入循环
                    break; //退出循环
                }


            }
            //此层循环计算乘除结束

            if ( tab_4 == 0 )
            {
                result = array_3[ tab_4 ];
            } else
            {
                //加法
                if ( array_4[ tab_a ] == '+' )
                {
                    result += array_3[ tab_4 ];
                }

                //加法
                if ( array_4[ tab_a ] == '-' )
                {

                    result -= array_3[ tab_4 ];
                }

                //计算最终结果
                if ( array_4[ tab_a ] == '=' )
                {
                    printf ( "结果为%lf \n" , result );
                    tab_8 = 1;
                    printf ( "按任意按键返回主菜单 \n" );
                    getchar ( );
                    break;

                }

                //符号的自增
                ++ tab_a;
            }
        }
        //此层循环计算加减结束
    }

    return 0;
}
