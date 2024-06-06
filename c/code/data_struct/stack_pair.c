#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Stack
{
    struct Stack * back;
    char symbol;
};

int In_Stack ( struct Stack ** current_node , char symbol )
{
    struct Stack * tmp_node = ( struct Stack * ) malloc ( sizeof ( struct Stack ) );
    tmp_node -> symbol = symbol;
    tmp_node -> back = * current_node;
    * current_node = tmp_node;
    return 0;
}

int Out_stack ( struct Stack ** current_node , char symbol )
{
    if ( * current_node == NULL )
    {
        return - 2;
    }
    struct Stack * tmp_node = * current_node;
    if ( tmp_node -> symbol != symbol )
    {
        return - 1;
    }
    * current_node = tmp_node -> back;
    free ( tmp_node );
    return 0;
}

void Free_stack ( struct Stack ** current_node )
{
    if ( * current_node != NULL )
    {
        struct Stack * tmp_node = * current_node;
        * current_node = tmp_node -> back;
        free ( tmp_node );
        Free_stack ( current_node );
    }
}

int main ()
{
    struct Stack * current_node = NULL;
    char symbol_s[] = "({[{()}]}";
    for ( int index = 0 ; index < strlen ( symbol_s ) ; index ++ )
    {
        switch ( symbol_s[ index ] )
        {
            case '[':
            case '{':
            case '(':
                In_Stack ( & current_node , symbol_s[ index ] );
                break;
            case ']':
                if ( Out_stack ( & current_node , '[' ) != 0 )
                {
                    printf ( "匹配错误\n" );
                    return - 1;
                }
                break;
            case '}':
                if ( Out_stack ( & current_node , '{' ) != 0 )
                {
                    printf ( "匹配错误\n" );
                    return - 1;
                }
                break;
            case ')':
                if ( Out_stack ( & current_node , '(' ) != 0 )
                {
                    printf ( "匹配错误\n" );
                    return - 1;
                }
                break;
        }
    }
    if ( current_node == NULL )
    {
        printf ( "全部正确\n" );
        return 0;
    }
    else
    {
        printf ( "有些符合未闭合\n" );
        return - 1;
    };
}