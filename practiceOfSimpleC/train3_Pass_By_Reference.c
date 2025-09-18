#include <stdio.h>

int cubeByReference(int *nPtr);

int main(void)
{
  int number = 5; // init
  printf("The original value is %d\n", number);
  cubeByReference(&number); //pass address of number to cubeByReference
  printf("\nThe new value of number is %d\n", number);
}


int cubeByReference(int *nPtr)
{
  *nPtr= *nPtr * *nPtr * *nPtr;
}


/*

(base) PS C:\Users\user\adv_C> .\train3_Pass_By_Reference.exe   
The original value is 5

The new value of number is 125

*/
