#include "main.h"
#include "queue.h"
#include "space.h"

int main(void)
{
  tQueue *queue;
  int operation;
  tQueueNode *target;
  int id, score = 0, ret, type;

  queue = createQueue();

  while (1)
  {
    printf("Which type you are going to operate? \n");
    printf("1. Add a type 1 item\n");
    printf("2. Add a type 2 item\n");
    printf("3. remove a type 1 item with a specific Id\n");
    printf("4. remove a type 2 item with a specific Id\n");

    scanf("%d", &operation);

    if (operation == 1 || operation == 2)
    {
      printf("  enter id and score: ");
      scanf("%d %d", &id, &score);

      type = (operation == 1) ? TYPE_SMALL : TYPE_LARGE;
      ret = tqueue_enqueue(queue, id, score, type);
      if (ret == 0)
        printf("    Cannot enter to the queue\n");
    }
    else if (operation == 3 || operation == 4)
    {
      printf("  enter an ID to remove \n");
      scanf("%d", &id);

      type = (operation == 3) ? TYPE_SMALL : TYPE_LARGE;
      target = find_target_node(queue, id, type);
      if (target == NULL)
      {
        printf("    cannot find the target node \n");
      }
      else
      {
        printf("target type: %d, location: %d, id: %d\n", target->type, target->location, target->id);
        if (target->next != NULL)
        {
          printf("target next type: %d, location: %d, id: %d\n",
            target->next->type,
            target->next->location,
            target->next->id);
        }
        tqueue_dequeue(queue, target);
      }
    }
    else
    {
      printf("    no such operation \n");
    }

    print_buffer_status();
    print_queue(queue);
  }

  return 0;
}
