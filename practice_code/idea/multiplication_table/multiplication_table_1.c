#include<stdio.h>

int main ()
{
    int figure_1 = 1;
    int figure_2 = 1;
    int result;
    while ( figure_1 <= 9 )
    {
        for ( figure_2 = 1 ; figure_2 <= figure_1 ; figure_2 ++ )
        {
            result = figure_1 * figure_2;
            printf ( "%d*%d=%d " , figure_1 , figure_2 , result );
            if ( figure_1 == figure_2 )
            {
                printf ( "\n" );
                ++ figure_1;
                break;
            }
        }

    }
    return 0;
}