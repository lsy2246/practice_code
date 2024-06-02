#include <stdio.h>
#include <malloc.h>

struct Link_queue{
    int content;
    struct Link_queue* _last;
};

int In_queue(struct Link_queue **_head, struct Link_queue **_tail){
    int content;
    printf ("请输入要添加的内容:");
    scanf_s ("%d",&content);
    struct Link_queue *_new_node = ( struct Link_queue * ) malloc(sizeof(struct Link_queue ));
    _new_node->content = content;
    if(*_tail == NULL){
        _new_node->_last = NULL ;
        *_tail = _new_node;
        *_head = *_tail;
    }
    else{
        struct Link_queue *_temp_node = *_tail;
        *_tail = _new_node;
        _temp_node ->_last = *_tail;
    }
    return true;
};

int Out_queue(struct Link_queue **_head, struct Link_queue **_tail){
    if(*_head == NULL){
        printf ("没有元素\n");
        return false;
    }

    struct Link_queue*temp = *_head ;
    printf ("元素:%d\n",temp ->content);

    *_head = temp->_last;
    if (*_head == NULL){
        *_tail =NULL;
        return true;
    }

    free(temp);


}

int main()
{
    struct Link_queue *_head=NULL,*_tail=NULL;
    while ( true){
        int pick;
        printf ("1.入队\n");
        printf ("2.出队\n");
        printf (("请输入:"));
        scanf_s ("%d",&pick);
        if(pick==1){
            In_queue (&_head,&_tail);
        }
        else if(pick==2){
            Out_queue (&_head,&_tail);
        }
    }
}