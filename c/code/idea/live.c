#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

void live(char symbol[],int length)
{
    printf ("\n\n\n\n");
    system ("color 0c");//改变颜色
    int length_2=length/10;//中间部分长度
    int length_1=length/3+1+length_2-1;//上半部分长度
    int length_3=length-length_2-length_1+4+length_2-1;//下半部分长度
    int length_a=length/5*2;//上半2/5前位置
    int length_a_1=length/5*2+2;//上半2/5后位置
    int length_b=length/5*4;//上半4/5前位置
    int length_b_1=length/5*4+2;//上半4/5后位置
    int size= strlen (symbol);//计算空格需要打多少
    int length_e=1;//下半左面
    int length_f=length/2*3-length_2-1;//下半右面
    //打印上半
    for ( int i = 1 ; i <= length_1 ; i++ )
    {
        for ( int j = 1 ; j <= length_a ; ++ j )
        {
            for ( int k = 1 ; k <= size ; k++ )
            {
                printf (" ");
            }
        }
        for ( int j = length_a ; j <= length_a_1 ;  j++ )
        {
            printf ("%s",symbol);
        }
        for ( int j = length_a_1 ; j <=length_b  ;  j++ )
        {
            for ( int k = 1 ; k <= size ; k++ )
            {
                printf (" ");
            }
        }
        for ( int j = length_b ; j <= length_b_1 ;  j++ )
        {
            printf ("%s",symbol);
        }
        if(length_a_1<length_b)
        {
            ++length_a_1;
            --length_b;
        }
        else if(length_a_1==length_b)
        {
            ++length_a_1;
        }
        --length_a;
        ++length_b_1;

        sleep(1);
        printf ("\n");//输出回车
    }
    //打印中间
    for ( int i = 1 ; i <=length_2  ; i++ )
    {
        for ( int j = 1 ; j <length/4*6; j++ )
        {
            printf ("%s",symbol);
        }
        sleep(1);
        printf ("\n");
    }
    //打印下面
    for ( int i = 1 ; i < length_3 ; i++ )
    {
        for ( int j = 1 ; j <= length_e ; j++ )
        {
            for ( int k = 1 ; k <= size ; k++ )
            {
                printf (" ");
            }
        }
        for ( int j = length_e ; j <= length_f ; j++ )
        {
            printf ("%s",symbol);
        }
        sleep (1);
        ++length_e;
        --length_f;
        printf ("\n");
    }
    exit (0);
}
int main()
{
    tab:
    srand (time(NULL));
    char symbol[99];
    int length;
    printf ("请输入需要打印的长度(8-20):");
    scanf ("%d",&length);
    if(length<8||length>20)
    {
        goto tab;
    }
    printf ("请输入需要填充的符号或者是单词:");
    scanf ("%s",symbol);
    live (symbol,length);
    return 0;
}