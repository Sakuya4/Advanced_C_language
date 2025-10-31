#ifndef LIST_H
#define LIST_H
typedef struct num_storage
{
  int number;
  struct num_storage *next;
  struct num_storage *previous;
} tNumStorage;

typedef struct num_stor_head
{
  int counts;
  tNumStorage *head;
  tNumStorage *tail;
} tNumStoreHead;

/* Function prototypes */
tNumStorage *create_node(int num);
tNumStorage *get_node_at(const tNumStoreHead *list_head, int position); //week 6
void insert_before(tNumStoreHead *list_head, tNumStorage *target, tNumStorage *node); //week 6
void insert_after(tNumStoreHead *list_head, tNumStorage *target, tNumStorage *node); //week 6
void insertNum(tNumStoreHead *list_head, int num);
void delete_at(tNumStoreHead *list_head, int position);
/* Function prototypes def done */


#endif