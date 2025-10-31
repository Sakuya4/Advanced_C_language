#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/* Function prototypes */
tNumStorage *create_node(int num)
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

tNumStorage *get_node_at(const tNumStoreHead *list_head, int position)
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

void insert_before(tNumStoreHead *list_head, tNumStorage *target, tNumStorage *node)
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

void insert_after(tNumStoreHead *list_head, tNumStorage *target, tNumStorage *node)
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
/* Function prototypes def done */



