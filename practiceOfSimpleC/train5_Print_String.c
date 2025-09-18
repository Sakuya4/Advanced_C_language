// printing a string one character at a time using a non-constant pointer to constant data
#include <stdio.h>

void printCharacters(const char *sPtr);

int main(void)
{
  char string[] = "print characters of a string"; 
  puts("The string is:");
  printCharacters(string);
  puts("");
}

void printCharacters(const char *sPtr)
{
  for(;*sPtr != '\0'; ++sPtr) printf("%c", *sPtr);
}

/*

(base) PS C:\Users\user\adv_C> .\train5_Print_String.exe
The string is:
print characters of a string

*/
