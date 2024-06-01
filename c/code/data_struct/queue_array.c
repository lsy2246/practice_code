#include <stdio.h>

struct queue
{
    int _arr[10];
    int _head;
    int _tail;
    int amount;
};

void in_queue ( struct queue * _arr_queue , int _content )
{
    if ( _arr_queue -> amount == 10 )
    {
        printf ( "队列已满\n" );
        return;
    }
    _arr_queue -> _arr[ _arr_queue -> _head ] = _content;
    _arr_queue -> _head = ( _arr_queue -> _head + 1 ) % 10;
    _arr_queue -> amount += 1;
    printf ( "%d,入队成功\n\n",_content );
}

void out_queue ( struct queue * _arr_queue )
{
    if ( _arr_queue->amount == 0 )
    {
        printf ( "队列为空\n\n" );
        return;
    }
    printf ( "%d,出队成功\n" , _arr_queue -> _arr[ _arr_queue -> _tail ] );
    _arr_queue -> _tail = ( _arr_queue -> _tail + 1 ) % 10;
    _arr_queue -> amount -= 1;
}

int main ()
{
    struct queue _arr_queue={0};
    enum {_in=1,_out};
    int pick,_number;
    while(1){
        printf ("1.入站\n");
        printf ("2.出站\n");
        printf ("请输入:");
        scanf_s ("%d",&pick);
        if(pick==_in){
            printf ("请输入数字:");
            scanf_s ("%d",&_number);
            in_queue (&_arr_queue,_number);
        }
        else if(pick==_out){
            out_queue (&_arr_queue);
        }
    }

}