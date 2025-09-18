// error pointer case
#include <stdio.h>

// case 1

void f(const int *xPtr);

int main(void)
{
  int y = 7;
  f(&y); // f attempts illegal modification
}

void f(const int *xPtr)
{
  *xPtr=100;// error: cannot modify a const object
}


// case 2
#include <stdio.h>
int main(void)
{
  int x=0;
  int y=0;
  // ptr is a constant pointer to an integer that can be modified
  // through ptr, but ptr always points to the same memory location
  int *const ptr=&x;
  
  *ptr=7; // allowed: *ptr is not const
   ptr=&y; // error: ptr is const; cannot assign new address

}

// case 3
#include <stdio.h>

int main(void)
{
  int x=5;
  int y=0;

  const int *const ptr=&x; // ptr is a constant pointer to a const int
  *ptr=7; // error: *ptr is const; cannot assign new value
  ptr=&y; // error: ptr is const; cannot assign new address
}
