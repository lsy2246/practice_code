#include <stdio.h>
#include <stdlib.h>

int main()
{
    //初始化
    unsigned int time_down; //关机时间
    int pick_home;//主页选择
    char shutdown_commend[100];//初始化储存关机字符

    printf ("0.取消关机 \n");
    printf ("1.强制关机 \n");
    printf ("2.立即注销 \n");
    printf ("3.定时关机 \n");
    printf ("4.定时重启 \n");
    printf ("请输入你需要执行的操作:");
    scanf ("%d",&pick_home);
    switch ( pick_home )
    {
        case 0:
        {
            system ("shutdown -a");
            break;
        }
        case 1:
        {
            system ("shutdown -p");
            break;
        }
        case 2:
        {
            system ("shutdown -l");
            break;
        }
        case 3:
        {
            pick_down:
            printf ("请输入你需要多少分钟之后关机:");
            while ( scanf ("%u",&time_down) != 1 || time_down < 0 )
            {
                printf ( "请输入合法的数字 \n" );
                while ( getchar ( ) != '\n' );  //清楚缓存
                goto pick_down;  //重新开始
            }

            time_down = time_down * 60; //默认秒换分钟
            sprintf (shutdown_commend,"shutdown -s -t %u",time_down);
            system (shutdown_commend);
            break;
        }

        case 4:
        {
            pick_reboot:
            printf ("请输入你需要多少分钟之后重启:");
            while ( scanf ("%u",&time_down) != 1 || time_down < 0 )
            {
                printf ( "请输入合法的数字 \n" );
                while ( getchar ( ) != '\n' );  //清楚缓存
                goto pick_reboot;  //重新开始
            }

            time_down = time_down * 60; //默认秒换分钟
            sprintf (shutdown_commend,"shutdown -r -t %u",time_down);
            system (shutdown_commend);
            break;
        }
    }
    return 0;
}
