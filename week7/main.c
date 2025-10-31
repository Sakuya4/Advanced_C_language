#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "list.h"

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

  ui_run_menu(list_head);

  while (list_head->head!=NULL)
  {
    tNumStorage *next=list_head->head->next;
    free(list_head->head);
    list_head->head=next;
  }
  free(list_head);
  return 0;
}








