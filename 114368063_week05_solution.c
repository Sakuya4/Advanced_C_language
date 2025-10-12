#include <stdio.h>
#include <stdlib.h>

typedef struct num_storage  // tNumStorage 雙向LINKED LIST
{
  int number;
  struct num_storage *next;
  struct num_storage *previous;
} tNumStorage;

typedef struct num_stor_head // tNumStoreHead LIINKED LIST 狀態管理，數量、頭、尾，為存取兩端
{
  int counts;
  tNumStorage *head;
  tNumStorage *tail;
} tNumStoreHead;

/* Function prototypes */
void insertNum(tNumStoreHead *list_head, int num);
void printList(const tNumStoreHead *list_head);
void delete_last(tNumStoreHead *list_head); //cannot use while/for/recursive
/* Function prototypes def done */

int main(void)
{
  tNumStoreHead *list_head; // 配置LINKED LIST
  int num;

  // init linked list
  list_head=(tNumStoreHead*) malloc(sizeof(tNumStoreHead));
  list_head->counts=0;
  list_head->head=NULL;
  list_head->tail=NULL;
  while(1) //-1 break, -2 call delete_last(), outher wise: inserNum; every time do printList()
  {
    printf("%s", "Input a number(-1 to exit, -2 to delete last): ");
    if(scanf("%d", &num)!=1)
    {
      break;
    }
    if(num==-1) 
    {
      break;
    }  
    else if(num==-2)
    {
      delete_last(list_head);
      printList(list_head);
    }
    else
    {
      insertNum(list_head, num);
      printList(list_head);
    }
  }
  free(list_head);
  return 0;
}

/* 排序插入，case 4 TYPE */
/* 每次更新NEXT/PREVIOUS、變更HEAD/TAIL，最後COUNTS++ */
void insertNum(tNumStoreHead *list_head, int num)
{
  tNumStorage *newNode=(tNumStorage*) malloc(sizeof(tNumStorage)); //NODE INIT
  newNode->number=num;
  newNode->next=NULL;
  newNode->previous=NULL;
  // IF linked list NULL
  if(list_head->head==NULL)
  {
    list_head->head=newNode;
    list_head->tail=newNode;
  }
  // front insert
  else if(num<list_head->head->number)
  {
    newNode->next=list_head->head;
    list_head->head->previous=newNode;
    list_head->head=newNode;
  }
  // rear insert
  else if (num>=list_head->tail->number)
  {
    newNode->previous=list_head->tail;
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
    newNode->previous=curr;
    if(newNode->next!=NULL)
    {
      newNode->next->previous=newNode;
    }
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


void delete_last(tNumStoreHead *list_head) 
{
  tNumStorage *last=list_head->tail;
  if(last==NULL) //empty 
  {
    return;
  }
  if(last->previous!=NULL) //more than one
  {
    list_head->tail=last->previous;
    list_head->tail->next=NULL;
  }
  else //only one
  {
    list_head->head=NULL;
    list_head->tail=NULL;
  }
  free(last);
  list_head->counts--;
}
