#include <stdio.h>

int cybeByValue(int n);

int main(void)
{
  int number=5; // init value
  printf("The original value is %d\n", number);
  number=cybeByValue(number); // pass by value to cubeByValue
  printf("\nThe new value of number is %d\n", number);      
}

int cybeByValue(int n)
{
  return n*n*n; //cube local variable n and return result
}

/*

(base) PS C:\Users\user\adv_C> .\trian2_Pass_By_Value.exe
The original value is 5

The new value of number is 125

*/
