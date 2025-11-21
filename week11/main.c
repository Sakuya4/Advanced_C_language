#include "main.h"
#include "queue.h"
#include "space.h"

int main(void)
{
  tQueue *queue;
  int operation;
  tQueueSmall *target_type_small;
  int id, score = 0, ret, data_type;

  queue = createQueue();

  while (1)
  {
    printf("\nRemaining memory space %d\n", get_remaining_space());
    printf("Which type you are going to operate? \n");
    printf("1. Add an item\n");
    printf("2. remove an item with a specific Id\n");

    scanf("%d", &operation);

    if (operation == 1)
    {
      printf("  enter id: ");
      scanf("%d", &id);

      printf("  specify data type (units) you want: ");
      scanf("%d", &data_type);

      ret = enqueue_type_small(queue, id, score, data_type);
      if (ret == 0)
        printf("    Cannot enter to the queue\n");

      print_buffer_status();
    }
    else if (operation == 2)
    {
      printf("  enter an ID to remove \n");
      scanf("%d", &id);

      target_type_small = find_target_small_node(queue, id, TYPE_SMALL);
      if (target_type_small == NULL)
      {
        printf("    cannot find the target node \n");
      }
      else
      {
        dequeue_type_small(queue, target_type_small, TYPE_SMALL);
      }

      print_buffer_status();
    }
    else
    {
      printf("    no such operation \n");
    }

    print_queue(queue);
  }

  return 0;
}
