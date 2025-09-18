// converting a string to uppercase using a non-constant pointer to non-constant data
#include <ctype.h>
#include <stdio.h>

void convertToUppercase(char *sPtr);

int main(void)
{
  char string[]="cHaRaCters and $32.98"; // init char array 
  printf("The string before conversion is: %s\n", string);
  convertToUppercase(string);
  printf("The string after conversion is: %s\n", string);
}


void convertToUppercase(char *sPtr)
{
  while(*sPtr!= '\0') // current character is not 
  {
    *sPtr=toupper(*sPtr);
    ++sPtr;
  }
}


/*


(base) PS C:\Users\user\adv_C> .\train4_convertionUpper.exe
The string before conversion is: cHaRaCters and $32.98
The string after conversion is: CHARACTERS AND $32.98

*/
