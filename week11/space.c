#include "space.h"

unsigned char buffer[UNIT_ELEMENT_SIZE * NUM_BYTE_BUF];
unsigned int buffer_mask = 0;

void print_buffer_status(void)
{
  int i;
  unsigned int mask = 1u << (NUM_BYTE_BUF - 1);
  printf("      buffer_mask: ");
  for (i = 0; i < NUM_BYTE_BUF; i++)
  {
    printf("%d ", (buffer_mask & mask) ? 1 : 0);
    mask >>= 1;
    if (i == 6 || i == 14 || i == 22)
      printf(", ");
  }
  printf("\n");
}

int get_remaining_space(void)
{
  int used = 0;
  unsigned int mask = 1u;
  int i;
  for (i = 0; i < NUM_BYTE_BUF; i++)
  {
    if (buffer_mask & mask)
      used++;
    mask <<= 1;
  }
  return NUM_BYTE_BUF - used;
}

void our_malloc(int units, void **target, int *mem_location)
{
  int i;
  int location = -1;
  *target = NULL;
  if (units <= 0 || units > NUM_BYTE_BUF)
    return;
  for (i = 0; i <= NUM_BYTE_BUF - units; i++)
  {
    unsigned int block = ((1u << units) - 1u) << i;
    if ((buffer_mask & block) == 0u)
    {
      location = i;
      buffer_mask |= block;
      break;
    }
  }
  if (location < 0)
    return;
  *target = &buffer[UNIT_ELEMENT_SIZE * location];
  *mem_location = location;
}

void our_free(int units, int mem_location)
{
  unsigned int block;
  if (units <= 0)
    return;
  if (mem_location < 0)
    return;
  if (mem_location + units > NUM_BYTE_BUF)
    return;
  block = ((1u << units) - 1u) << mem_location;
  buffer_mask &= ~block;
}
