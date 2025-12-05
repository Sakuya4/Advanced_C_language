#ifndef __QUEUE__
#define __QUEUE__

#include "main.h"

typedef struct type_small {
  int id;
  int score;
  int location;
} tQueueSmall;

typedef struct type_large {
  int id;
  int score[8];
  int location;
} tQueueLarge;

typedef struct node_info {
  int type;
  int id;
  int score;
  int location;
  struct node_info *next;
  struct node_info *prev;
} tQueueNode;

typedef struct {
  tQueueNode *front;
  tQueueNode *rear;
  int count;
} tQueue;

tQueue* createQueue(void);
int tqueue_enqueue(tQueue *queue, int id, int score, int type);
tQueueNode *find_target_node(tQueue *queue, int id, int type);
int tqueue_dequeue(tQueue *queue, tQueueNode *target);
void print_queue(tQueue *queue);

#endif
