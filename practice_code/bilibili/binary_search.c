#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>


int main ()
{
    int a;
    int i;
    printf ( "请输入你想查找的数字:" );
    scanf ( "%d" , a );
    int arr[10] = { 0,1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 };
    int k = sizeof ( arr[ 10 ] ) / sizeof ( arr[ 0 ] );
    int left = 0;
    int right = k - 1;
    int mid;
    for ( i = 1 ; i < k ; i ++ )
    {
        mid = ( left + right );
        if ( mid > a )
        {
            left = mid + 1;
        } else if ( mid < a )
        {
            right = mid - 1;
        } else
        {
            printf ( "a的下标为%d" , mid );
            break;
        }
        return 0;
    }
}