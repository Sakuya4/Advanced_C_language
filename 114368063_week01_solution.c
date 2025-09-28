#include <stdio.h>
#include <string.h>

void swap(char *x,char *y);

int main(void)
{
  int i=0;
  int j=0;
  int size=0;
  int counter=0;
  char charSequence[10];

  printf("%s", "please input a character sequence:");
  gets(charSequence); //or use scanf("%s", charSequence) or for loop to get each char
  size=strlen(charSequence);
  
  for(i=0;i<size;++i)
  {
    for(j=i+1;j<size;++j)
    {
      if(charSequence[i]>charSequence[j])
      {
        swap(&charSequence[i], &charSequence[j]);
        counter++;
      }
    }
  }
    printf("number of inversions: %d",counter);

  return 0;
}

void swap(char *x,char *y)
{
  char temp;
  temp=*x;
  *x=*y;
  *y=temp;
}
