#include "space.h"

unsigned char buffer_small[SMALL_ELEMENT_SIZE * NUM_SMALL_BYTE_BUF];
unsigned char buffer_large[LARGE_ELEMENT_SIZE * NUM_LARGE_BYTE_BUF];

static unsigned char buffer_large_buf_mask = 0;
static unsigned char buffer_small_buf_mask = 0;

static int get_first_free_slot(unsigned char mask, int needed, int max_slots)
{
  int i;
  for (i = 0; i <= max_slots - needed; i++)
  {
    unsigned int block = ((1u << needed) - 1u) << i;
    if ((mask & block) == 0u)
      return i;
  }
  return -1;
}

void print_buffer_status(void)
{
  int i;
  unsigned int mask;

  printf("      byte_small_buf_mask: ");
  for (i = NUM_SMALL_BYTE_BUF - 1; i >= 0; i--)
  {
    mask = 1u << i;
    printf("%d ", (buffer_small_buf_mask & mask) ? 1 : 0);
  }
  printf("\n");

  printf("      byte_large_buf_mask: ");
  for (i = NUM_LARGE_BYTE_BUF - 1; i >= 0; i--)
  {
    mask = 1u << i;
    printf("%d ", (buffer_large_buf_mask & mask) ? 1 : 0);
  }
  printf("\n");
}

int get_remaining_space(void)
{
  int i;
  int used = 0;
  unsigned int mask = 1u;

  for (i = 0; i < NUM_SMALL_BYTE_BUF; i++)
  {
    if (buffer_small_buf_mask & mask)
      used++;
    mask <<= 1;
  }

  mask = 1u;
  for (i = 0; i < NUM_LARGE_BYTE_BUF; i++)
  {
    if (buffer_large_buf_mask & mask)
      used += 2; // large buffer equals two small units
    mask <<= 1;
  }

  return NUM_SMALL_BYTE_BUF * 2 - used;
}

void our_malloc(int type, void **target, int *mem_location)
{
  int location = -1;
  *target = NULL;
  *mem_location = -1;

  if (type == TYPE_SMALL)
  {
    location = get_first_free_slot(buffer_small_buf_mask, 1, NUM_SMALL_BYTE_BUF);
    if (location >= 0)
    {
      buffer_small_buf_mask |= (1u << location);
      *target = &buffer_small[SMALL_ELEMENT_SIZE * location];
      *mem_location = location;
    }
  }
  else if (type == TYPE_LARGE)
  {
    location = get_first_free_slot(buffer_large_buf_mask, 1, NUM_LARGE_BYTE_BUF);
    if (location >= 0)
    {
      buffer_large_buf_mask |= (1u << location);
      *target = &buffer_large[LARGE_ELEMENT_SIZE * location];
      *mem_location = LARGE_START + location;
      return;
    }

    // fallback to two consecutive small blocks
    location = get_first_free_slot(buffer_small_buf_mask, 2, NUM_SMALL_BYTE_BUF);
    if (location >= 0)
    {
      unsigned int block = (1u << location) | (1u << (location + 1));
      buffer_small_buf_mask |= block;
      *target = &buffer_small[SMALL_ELEMENT_SIZE * location];
      *mem_location = location;
    }
  }
}

void our_free(int type, int mem_location)
{
  if (mem_location < 0)
    return;

  if (type == TYPE_SMALL)
  {
    if (mem_location >= NUM_SMALL_BYTE_BUF)
      return;
    buffer_small_buf_mask &= ~(1u << mem_location);
  }
  else if (type == TYPE_LARGE)
  {
    if (mem_location >= LARGE_START)
    {
      int large_index = mem_location - LARGE_START;
      if (large_index < 0 || large_index >= NUM_LARGE_BYTE_BUF)
        return;
      buffer_large_buf_mask &= ~(1u << large_index);
    }
    else
    {
      if (mem_location + 1 >= NUM_SMALL_BYTE_BUF)
        return;
      buffer_small_buf_mask &= ~(1u << mem_location);
      buffer_small_buf_mask &= ~(1u << (mem_location + 1));
    }
  }
}
