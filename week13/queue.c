#include "queue.h"
#include "space.h"

int tqueue_enqueue(tQueue *queue, int id, int score, int type)
{
  tQueueNode *queue_node;
  void *newptr = NULL;
  int mem_location = -1;

  if (queue == NULL)
    return 0;

  queue_node = (tQueueNode *)malloc(sizeof(tQueueNode));
  if (queue_node == NULL)
    return 0;

  our_malloc(type, (void *)&newptr, &mem_location);

  if (newptr == NULL)
  {
    printf("    Enqueue Failed !!!\n\n");
    free(queue_node);
    return 0;
  }

  queue_node->type = type;
  queue_node->id = id;
  queue_node->score = score;
  queue_node->location = mem_location;
  queue_node->next = NULL;
  queue_node->prev = queue->rear;

  if (type == TYPE_SMALL)
  {
    tQueueSmall *data = (tQueueSmall *)newptr;
    data->id = id;
    data->score = score;
    data->location = mem_location;
  }
  else
  {
    tQueueLarge *data = (tQueueLarge *)newptr;
    data->id = id;
    data->score[0] = score;
    data->location = mem_location;
  }

  if (queue->rear == NULL)
  {
    queue->front = queue_node;
  }
  else
  {
    queue->rear->next = queue_node;
  }
  queue->rear = queue_node;
  queue->count++;

  return 1;
}

tQueue* createQueue(void)
{
  tQueue *queue;
  queue = (tQueue *) malloc(sizeof(tQueue));
  if (queue)
  {
    queue->front = NULL;
    queue->rear = NULL;
    queue->count = 0;
  }
  return queue;
}

tQueueNode *find_target_node(tQueue *queue, int id, int type)
{
  tQueueNode *target = queue->front;
  while (target != NULL)
  {
    if (target->id == id && target->type == type)
      return target;
    target = target->next;
  }
  return NULL;
}

int tqueue_dequeue(tQueue *queue, tQueueNode *target)
{
  if (queue == NULL || target == NULL)
    return 0;

  if (target->prev != NULL)
    target->prev->next = target->next;
  else
    queue->front = target->next;

  if (target->next != NULL)
    target->next->prev = target->prev;
  else
    queue->rear = target->prev;

  queue->count--;
  our_free(target->type, target->location);
  free(target);

  return 1;
}

void print_queue(tQueue *queue)
{
  tQueueNode *target = queue->front;
  printf("      type mixed queue: ");
  while (target != NULL)
  {
    printf("%d,%d(%d,%d) ",
      target->id,
      target->score,
      target->type,
      target->location);
    target = target->next;
  }
  printf("\n\n");
}
