#include "stack.h"

tStack *create_stack(void)
{
    //initial count and head
    tStack *init_Stack=(tStack *)malloc(sizeof(tStack));
    init_Stack->count=0;
    init_Stack->head=NULL;
    return init_Stack;
}

void handle_push_operation(tStack *stack_ptr)
{
    if(stack_ptr->count==N){//if count is N stack space is full
        printf ("[Error]  handle_push_operation(): space full \n");
    }else{
        tNode *NewNode= (tNode *)malloc(sizeof(tNode)); //new tNode
        NewNode->data_ptr=NULL;                         //initial data_ptr to NULL
        NewNode->next=NULL;                             //initial tNode->next to NULL
        int score=0;                                    //score value
        if(stack_ptr->count==0){                        //first tNode
            stack_ptr->head=NewNode;
        }else{                                          //tNodes that are not head
            NewNode->next=stack_ptr->head;
            stack_ptr->head=NewNode;
        }
     printf("  handle_push_operation(): enter score value: ");
     scanf("%d", &score);
     get_score_space(&(NewNode->data_ptr));             //allocate tNode->data_ptr to preallocate score_buf
     NewNode->data_ptr->score=score;                    //store score value
     NewNode->data_ptr->used=1;                         //location is used
     NewNode->data_ptr->loc=stack_ptr->count;           //location=count value
     stack_ptr->count+=1;                               //count value of stack +1
    }
    return; 
}

void handle_pop_operation(tStack *stack_ptr)
{
    if(stack_ptr->count==0){
	   printf ("  [Error]  handle_pop_operation(): nothing in stack \n");
    }else{
	   printf("  handle_pop_operation(): poped value: %d\n",stack_ptr->head->data_ptr->score);
	   return_score_space(stack_ptr->head->data_ptr->loc);
       stack_ptr->head->data_ptr->used=0;
       stack_ptr->head=stack_ptr->head->next;
       stack_ptr->count--;
    }
}

void print_stack_content(tStack *stack_ptr)
{
    tNode *node_ptr;
    node_ptr=stack_ptr->head;
    printf("\n\n   print_stack_content(): stack items ->");
    while(node_ptr!=NULL){
     printf(" %d(%d)",node_ptr->data_ptr->score,node_ptr->data_ptr->loc);
     node_ptr=node_ptr->next;
    }
    printf("\n\n");
}

