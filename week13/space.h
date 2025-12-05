#ifndef __SPACE__
#define __SPACE__

#include "main.h"

#define NUM_SMALL_BYTE_BUF 8
#define NUM_LARGE_BYTE_BUF 8

#define SMALL_ELEMENT_SIZE 32
#define LARGE_ELEMENT_SIZE 64
#define LARGE_START        (NUM_SMALL_BYTE_BUF)

void print_buffer_status(void);
void our_malloc(int type, void **target, int *mem_location);
void our_free(int type, int mem_location);
int get_remaining_space(void);

#endif


