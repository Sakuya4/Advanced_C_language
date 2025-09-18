#include <stdio.h>

int main()
{
  int a=7;
  int *aPtr=&a;
  printf("address of a is:%p\nvalue of aPtr is:%p\n", &a, aPtr); // addresss and address of pointer
  printf("value of a is %d\nvalue of *aPtr is %d\n", a, *aPtr);
  printf("showing that * and & are inverses of each other\n&*aPtr=%p\n*&aPtr=%p\n", &*aPtr, *&aPtr);

  return 0;
}


/*


(base) PS C:\Users\user\adv_C> .\train1.exe
address of a is:0061FF1C
value of aPtr is:0061FF1C
value of a is 7
value of *aPtr is 7
showing that * and & are inverses of each other
&*aPtr=0061FF1C
*&aPtr=0061FF1C

*/
