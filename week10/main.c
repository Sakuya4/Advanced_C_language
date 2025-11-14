#include "main.h"
#include "queue.h"
#include "space.h"


int main (void)
{
    tQueue *queue;
    int operation;
    tQueueSmall *target_type_small;
    int id, score=0, ret;
    queue = createQueue();

    while (1)
    {

        printf("\nWhich type you are going to operate? \n");
        printf("1. Add a type 1 (small) item\n");
        printf("2. Add a type 2 (big) item\n");
        printf("3. remove a type 1 item with a specific Id\n");
        printf("4. remove a type 2 item with a specific Id\n");
        
        scanf("%d", &operation);
        
        if (operation == 1 || operation == 2)
        {
            printf("  enter id:");
            scanf("%d", &id);

            ret = enqueue_type_small(queue,id,score,operation-1);
          
            if (ret == 0)
            {
                printf("    Cannot enter to the queue\n");
            }
            print_buffer_status();
        }
        else if (operation == 3 || operation == 4)
        {
            printf ("  enter an ID to remove \n");
            scanf("%d", &id);
            target_type_small = NULL;
            target_type_small = find_target_small_node(queue,id,operation-3);
            if (target_type_small == NULL)
            {
                printf ("    cannot find the target node \n");
            }
            else
            {
                dequeue_type_small(queue, target_type_small, TYPE_SMALL);
            }
            print_buffer_status();

        }
        else
        {
            printf ("    no such operation \n");   
        }
        print_queue(queue);
    }

}
