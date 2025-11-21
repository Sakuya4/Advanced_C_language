#ifndef __SPACE__
#define __SPACE__

#include "main.h"

#define NUM_BYTE_BUF 23
#define UNIT_ELEMENT_SIZE 32

void print_buffer_status(void);
void our_malloc(int units, void **target, int *mem_location);
void our_free(int units, int mem_location);
int get_remaining_space(void);

#endif
