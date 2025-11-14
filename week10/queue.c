#include "queue.h"
#include "space.h"

tQueue* createQueue(void)
{    
    tQueue *queue;
    queue = (tQueue *) malloc(sizeof(tQueue));

    if (queue)
    {
        queue->type_small_front = NULL;
        queue->type_small_rear  = NULL;
        queue->type_small_count = 0;
    }

    return queue;
}

int enqueue_type_small(tQueue *queue, int id, int score, int data_type)
{
    tQueueSmall *newptr = NULL;
    int mem_location = -1;

    // allocate from your memory pool
    our_malloc(data_type, (void **)&newptr, &mem_location);

    if (newptr == NULL)
    {
        printf("    Enqueue False!!! \n");
        return 0;
    }

    newptr->id        = id;
    newptr->location  = mem_location;
    newptr->data_type = data_type;
    newptr->next      = NULL;
    newptr->prev      = NULL;

    // If empty queue
    if (queue->type_small_count == 0)
    {
        queue->type_small_front = newptr;
        queue->type_small_rear  = newptr;
    }
    else
    {
        // Attach to rear (FIFO)
        newptr->prev = queue->type_small_rear;
        queue->type_small_rear->next = newptr;
        queue->type_small_rear = newptr;
    }

    queue->type_small_count++;
    return 1;
}

int dequeue_type_small(tQueue *queue, tQueueSmall *target, int data_type)
{
    if (queue == NULL || target == NULL || queue->type_small_count == 0)
        return 0;

    data_type = target->data_type;

    // Remove previous link
    if (target->prev != NULL)
        target->prev->next = target->next;
    else
        queue->type_small_front = target->next; // removed front

    // Remove next link
    if (target->next != NULL)
        target->next->prev = target->prev;
    else
        queue->type_small_rear = target->prev;  // removed rear

    queue->type_small_count--;

    // Free from memory pool
    our_free(data_type, target->location);

    return 1;
}

tQueueSmall *find_target_small_node(tQueue *queue, int id, int data_type)
{
    tQueueSmall *target = queue->type_small_front;

    while (target != NULL)
    {
        if (target->id == id && target->data_type == data_type)
            return target;

        target = target->next;
    }

    return NULL;
}

void print_queue(tQueue *queue)
{
    tQueueSmall *target = queue->type_small_front;

    printf("      type small queue: ");
    
    while (target != NULL)
    {
        printf("%d ", target->id);
        target = target->next;
    }

    printf("\n");
}
