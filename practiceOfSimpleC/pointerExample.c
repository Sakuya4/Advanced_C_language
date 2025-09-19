#include <stdio.h>

int main(void)
{
  int a=5, b=3;
  int *ptr;

  ptr=&a; //ptr 指向 a的address
  printf("ptr=%p, *ptr=%d\n", ptr, *ptr);
  ptr=&b;
  printf("ptr=%p, *ptr=%d\n", ptr, *ptr);
  
  return 0;
}
