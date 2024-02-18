#include <stdio.h>

int my_strlen(char* str )
{
    if(*str != '\0')
    {
        return 1+ my_strlen (str+1);
    }
    else
        return 0;
}

int main ()
{
    char arr[99];
    printf("请输入你要计算数字的长度:");
    scanf("%s",arr);
    printf ("%d",my_strlen(arr));
    return 0;
}