#ifndef __QUEUE__
#define __QUEUE__

typedef struct type_small {
  int id;
  int score;
  int location;
  int data_type;
  struct type_small *next;
  struct type_small *prev;
} tQueueSmall;

typedef struct {
  tQueueSmall *type_small_front;
  tQueueSmall *type_small_rear;
  int type_small_count;
} tQueue;

tQueue* createQueue(void);

int enqueue_type_small(tQueue *queue, int id, int score, int data_type);
int dequeue_type_small(tQueue *queue, tQueueSmall *target, int data_type);
tQueueSmall *find_target_small_node(tQueue *queue, int id, int data_type);

void print_queue(tQueue *queue);

#endif
