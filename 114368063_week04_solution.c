#include <stdio.h>
#include <stdlib.h>

typedef struct num_storage
{
  int number;
  struct num_storage *next;
} tNumStorage;

typedef struct num_stor_head
{
  int counts;
  tNumStorage *head;
  tNumStorage *tail;
} tNumStoreHead;

/* Function prototypes */
void insertNum(tNumStoreHead *list_head, int num);
void printList(const tNumStoreHead *list_head);
/* Function prototypes def done */

int main(void) {
    tNumStoreHead *list_head;
    int num;

    // init linked list
    list_head=(tNumStoreHead*) malloc(sizeof(tNumStoreHead));
    list_head->counts=0;
    list_head->head=NULL;
    list_head->tail=NULL;

    while(1)
    {
      printf("%s", "Input a number: ");
      scanf("%d", &num);
      if (num==-1) 
      {
        break;
      }  
      insertNum(list_head, num);
      printList(list_head);
    }
  free(list_head);
  return 0;
}

void insertNum(tNumStoreHead *list_head, int num)
{
  tNumStorage *newNode=(tNumStorage*) malloc(sizeof(tNumStorage));
  newNode->number=num;
  newNode->next=NULL;

  // 如果 linked list 是空的
  if(list_head->head==NULL)
  {
    list_head->head=newNode;
    list_head->tail=newNode;
  }
  // front insert
  else if(num<list_head->head->number)
  {
    newNode->next=list_head->head;
    list_head->head=newNode;
  }
  // rear insert
  else if (num>=list_head->tail->number)
  {
    list_head->tail->next=newNode;
    list_head->tail=newNode;
  }
  // middle insert
  else
  {
    tNumStorage *curr=list_head->head;
    while(curr->next!=NULL && curr->next->number < num)
    {
      curr=curr->next;
    }
    
    newNode->next=curr->next;
    curr->next=newNode;
  }
  list_head->counts++;
}

/* 印出 linked list */
void printList(const tNumStoreHead *list_head)
{
  tNumStorage *curr=list_head->head;
  printf("  List->count: %d\n", list_head->counts);
  printf("  The Sorted list: ");
  while(curr!=NULL)
  {
    printf("%d ", curr->number);
    curr=curr->next;
  }
  printf("\n\n");
}
