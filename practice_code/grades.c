#include <stdio.h>

int main ()
{
    int figure_a;//接收用户输入
    int figure_b;//储存最终结果
    printf ( "请输入数:" );
    scanf ( "%d" , & figure_a );
    if ( figure_a < 5 )
    {
        figure_b = figure_a * 4;
        printf ( "结果为%d" , figure_b );
    }
    else if ( figure_a >= 5 && figure_a < 10 )
    {
        figure_b = figure_a * 3;
        printf ( "结果为%d" , figure_b );
    }
    else if ( figure_a > 10 )
    {
        figure_b = figure_a * 2;
        printf ( "结果为%d" , figure_b );
    }
    return 0;
}