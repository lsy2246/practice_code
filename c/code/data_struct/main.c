#include <stdio.h>
#include <malloc.h>

struct link_list_struct
{
    struct link_list_struct * back_node;
    int current_data;
};


void add_node ( struct link_list_struct **current_node , int content )
{
    struct link_list_struct *new_node = malloc(sizeof(struct link_list_struct));
    new_node->back_node = *current_node;
    new_node->current_data = content;
    *current_node = new_node;
};

void delete_node(struct link_list_struct **current_node){
    if(*current_node == NULL){
        printf ("当前没有结点\n");
    }
    else{
        struct link_list_struct *tmp_node;
        tmp_node = *current_node;
        *current_node = (*current_node)->back_node;
        free (tmp_node);
    }
}

void view_node(struct link_list_struct *current_node){
    if(current_node == NULL){
        printf ("当前没有结点\n");
    }
    else{
        printf ("%d\n",current_node->current_data);
    }
}

int main ()
{
    enum {add=1,delete,view};
    struct link_list_struct *current_node=NULL;

    while( true){
        printf ("1.增加\n");
        printf ("2.删除\n");
        printf ("3.查看\n");
        printf ("请输入:");
        int pick;
        scanf_s ("%d",&pick);
        if(pick==add)
        {
            int content;
            printf ("请输入要添加的数值:");
            scanf_s ("%d",&content);
            add_node (&current_node,content);
        }
        else if(pick==delete)
        {
            delete_node(&current_node);
        }
        else if(pick==view)
        {
            view_node (current_node);
        }
    }

}