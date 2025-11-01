#include <stdio.h>
#include <stdlib.h>
// 0x80040004
// 0x80009000

typedef unsigned int Int32;
Int32 input;
Int32 high;
Int32 low;

int CheckRangeLoop(Int32 input, Int32 high, Int32 low);
int CheckRangeNoLoop(Int32 input, Int32 high, Int32 low);

int main(void)
{
  int flag = 0;
  while(1) 
  {
    printf("%s", "Please specify the input: ");
    scanf("%x", &input);
    printf("%s", "  Please specify the high: ");
    scanf("%u", &high);
    printf("%s", "  Please specify the low: ");
    scanf("%u", &low);
    
    printf("CheckRangeLoop result: %d\n", CheckRangeLoop(input,high,low));
    printf("CheckRangeNoLoop result: %d\n", CheckRangeNoLoop(input,high,low));
    puts("");
    puts("");
    
    puts("Enter 1 to keep trying the next round: ");
    scanf("%d", &flag);
    
    if(flag == 1)
    {
      continue;
    }
  
  return 0;
  }
}

int CheckRangeLoop(Int32 input, Int32 high, Int32 low)
{
  int i;
  int middle=high-low+1;
  Int32 set=0x01;
  input>>=low;
  for(i=0;i<middle;i++)
  {
    if(input&0x00000001)
    {
      return 1;
    }
    input>>=1;
  }
  return 0; 
}

int CheckRangeNoLoop(Int32 input, Int32 high, Int32 low)
{
  input>>=low;
  input<<=(31-high+low);
  if(input&0xffffffff)
  {
    return 1;
  }
  return 0; 
}
