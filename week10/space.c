#include "space.h"


unsigned char buffer[SMALL_ELEMENT_SIZE*NUM_SMALL_BYTE_BUF];

unsigned char byte_small_buf_mask = 0;


void print_buffer_status (void)
{
    int i;
    unsigned char mask = 0x80;
    printf ("      byte_small_buf_mask: ");
    for (i = 0; i< NUM_SMALL_BYTE_BUF; i++)
    {
        printf ("%d ", (byte_small_buf_mask & mask) ? 1 : 0);
        mask = mask >> 1;
    }
    printf ("\n");
}

void  our_malloc(int type, void **target, int *mem_location)
{
    int location;
    unsigned char mask = 0x01;
    if (byte_small_buf_mask == SMALL_FULL){
        return;
    }
    else if (type == TYPE_SMALL)
    {
        location = test_single_location(mask,NUM_SMALL_BYTE_BUF);
        set_single_bit(&byte_small_buf_mask,location);
        *target = &buffer[SMALL_ELEMENT_SIZE * location];
        *mem_location = location;
    }
    else
    {
        location = test_dual_location(byte_small_buf_mask,NUM_SMALL_BYTE_BUF-1);
        if (location >= 0)
        {
            set_dual_bit(&byte_small_buf_mask,location);
            *target = &buffer[SMALL_ELEMENT_SIZE*location];
            *mem_location = location;
        }
        else
        {
            return;
        }
    }    
}

int test_single_location(int mask, int mask_length)
{
    int counter = 0;
    for (counter = 0; counter < mask_length; counter++)
    {
        if ((byte_small_buf_mask & mask) == 0)
        {
            return counter;
        }
        mask = mask << 1; 
    }
    return -1;
}


void set_single_bit(unsigned char *mask, int location)
{
    int counter=0;
    unsigned char setmask = 0x01;
    for(counter=0;counter<location;counter++){
        setmask=setmask<<1;
    }
    *mask=*mask|setmask;
    
}

int test_dual_location(int mask, int mask_length)
{
    int counter = 0;
    for (counter = 0; counter < mask_length; counter++)
    {
        if (((byte_small_buf_mask & mask) == 0) &&
            ((byte_small_buf_mask & (mask << 1)) == 0))
        {
            return counter;
        }
        mask = mask << 1;
    }
    return -1;
}


void set_dual_bit(unsigned char *mask, int location)
{
    int counter=0;
    unsigned char setmask = 0x01;
    for(counter=0;counter<location;counter++){
        setmask=setmask<<1;
    }
    *mask=*mask|setmask;
    *mask=*mask|(setmask<<1);
}

void clear_single_bit(unsigned char *mask, int location)
{
    int counter=0;
    unsigned char setmask = 0x01;
    unsigned char clearmask = 0xff;
    for (counter = 0; counter < location ; counter++){
        setmask=setmask<<1;
    }
    *mask = *mask & (setmask ^ clearmask);
}

void clear_dual_bit(unsigned char *mask, int location)
{
    int counter=0;
    unsigned char setmask = 0x01;
    unsigned char clearmask = 0xff;
    for (counter = 0; counter < location ; counter++){
        setmask=setmask<<1;
    }
    *mask = *mask & (setmask ^ clearmask);
    *mask = *mask & ((setmask<<1) ^ clearmask);

}

void  our_free(int type, int mem_location)
{
    if (type == TYPE_SMALL)
    {
        clear_single_bit(&byte_small_buf_mask,mem_location);
    }
    else if (type == TYPE_LARGE)
    {
        clear_dual_bit(&byte_small_buf_mask,mem_location);
    }
}
