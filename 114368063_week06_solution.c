#include <stdio.h>
#include <stdlib.h>

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
static tNumStorage *create_node(int num); //week 6
static tNumStorage *get_node_at(const tNumStoreHead *list_head, int position); //week 6
static void insert_before(tNumStoreHead *list_head, tNumStorage *target, tNumStorage *node); //week 6
static void insert_after(tNumStoreHead *list_head, tNumStorage *target, tNumStorage *node); //week 6
void insertNum(tNumStoreHead *list_head, int num);
void printList(const tNumStoreHead *list_head);
void delete_at(tNumStoreHead *list_head, int position);
/* Function prototypes def done */

int main(void)
{
  tNumStoreHead *list_head;
  int choice;

  list_head = (tNumStoreHead *)malloc(sizeof(tNumStoreHead));
  if (list_head == NULL)
  {
    puts("");
    return 1;
  }
  list_head->counts = 0;
  list_head->head = NULL;
  list_head->tail = NULL;

  while (1)
  {
    printf("%s", "1. Add a number or 2. Delete a number: ");
    if (scanf("%d", &choice) != 1)
    {
      break;
    }
    if(choice == -1)
    {
      break;
    }

    if(choice == 1)
    {
      int value;
      printf("%s", "Add a number: ");
      if(scanf("%d", &value)!=1)
      {
        break;
      }

      if (list_head->counts == 0)
      {
        insertNum(list_head, value);
      }
      else
      {
        int location;
        int mode;
        printf("%s", "  Specify a target location ");
        if(scanf("%d", &location)!=1)
        {
          break;
        }
        if(location<1||location>list_head->counts)
        {
          printf("%s", "error");
          continue;
        }

        printf("%s", "  1. Before or 2. After the location: ");
        if(scanf("%d", &mode)!=1)
        {
          break;
        }
        if(mode!=1&&mode!=2)
        {
          printf("%s", "error");
          continue;
        }

        {
          tNumStorage *target=get_node_at(list_head, location);
          tNumStorage *newNode=create_node(value);
          if (target==NULL||newNode==NULL)
          {
            free(newNode);
            continue;
          }
          if (mode == 1)
          {
            insert_before(list_head, target, newNode);
          }
          else
          {
            insert_after(list_head, target, newNode);
          }
        }
      }
      puts("");
      printList(list_head);
    }
    else if(choice==2)
    {
      int location;
      if(list_head->counts==0)
      {
        printf("%s", "List is empty.");
        continue;
      }
      printf("%s", "  Specify a target location to delete ");
      if(scanf("%d", &location) != 1)
      {
        break;
      }
      if(location< 1||location>list_head->counts)
      {
        printf("%s", "error");
        continue;
      }
      delete_at(list_head, location);
      printList(list_head);
    }
    else
    {
      printf("%s", "No such choose!\n");
      continue;
    }
  }

  while (list_head->head!=NULL)
  {
    tNumStorage *next=list_head->head->next;
    free(list_head->head);
    list_head->head=next;
  }
  free(list_head);
  return 0;
}

void insertNum(tNumStoreHead *list_head, int num)
{
  tNumStorage *newNode=create_node(num);
  if(newNode==NULL)
  {
    return;
  }

  if(list_head->head==NULL)
  {
    list_head->head=newNode;
    list_head->tail=newNode;
  }
  else
  {
    newNode->previous=list_head->tail;
    list_head->tail->next=newNode;
    list_head->tail=newNode;
  }
  list_head->counts++;
}

static tNumStorage *create_node(int num)
{
  tNumStorage *node=(tNumStorage *)malloc(sizeof(tNumStorage));
  if (node==NULL)
  {
    printf("%s", "error");
    return NULL;
  }
  node->number=num;
  node->next=NULL;
  node->previous=NULL;
  return node;
}

static tNumStorage *get_node_at(const tNumStoreHead *list_head, int position)
{
  tNumStorage *curr=list_head->head;
  int index=1;
  while(curr!=NULL&&index<position)
  {
    curr=curr->next;
    index++;
  }
  return curr;
}

static void insert_before(tNumStoreHead *list_head, tNumStorage *target, tNumStorage *node)
{
  node->next=target;
  node->previous=target->previous;
  if (target->previous!=NULL)
  {
    target->previous->next=node;
  }
  else
  {
    list_head->head=node;
  }
  target->previous=node;
  list_head->counts++;
}

static void insert_after(tNumStoreHead *list_head, tNumStorage *target, tNumStorage *node)
{
  node->previous=target;
  node->next=target->next;
  if (target->next!=NULL)
  {
    target->next->previous=node;
  }
  else
  {
    list_head->tail=node;
  }
  target->next=node;
  list_head->counts++;
}

void printList(const tNumStoreHead *list_head)
{
  tNumStorage *curr=list_head->head;
  printf("count: %d\n", list_head->counts);
  printf("%s", "  From head--> ");
  while (curr!=NULL)
  {
    printf("%d ", curr->number);
    curr=curr->next;
  }
  puts("");
  curr=list_head->tail;
  printf("%s", "  From tail--> ");
  while (curr!=NULL)
  {
    printf("%d ", curr->number);
    curr=curr->previous;
  }
  printf("\n\n");
}

void delete_at(tNumStoreHead *list_head, int position)
{
  tNumStorage *target=get_node_at(list_head, position);
  if(target==NULL)
  {
    printf("%s","  Target location not found.\n");
    return;
  }

  if(target->previous != NULL)
  {
    target->previous->next=target->next;
  }
  else
  {
    list_head->head=target->next;
  }

  if (target->next != NULL)
  {
    target->next->previous=target->previous;
  }
  else
  {
    list_head->tail=target->previous;
  }

  free(target);
  list_head->counts--;
}
