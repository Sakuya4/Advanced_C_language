#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MIN 18 // user input 1+x^2

void swap(int *a, int *b); // swap 1st, 3rd row and 1st, 3rd col
void printMatrix(int *arr, int dimension); // print 2-D Array

int main(int argc, char *argv[])
{
  if(argc<MIN) return 0;
  else
  {
    int i;
    int totalNumber=argc-2;
    int dimension=(int)sqrt(totalNumber);
    int *arr=(int *)malloc(sizeof(int)*totalNumber); // demo 1-D arr
    if(dimension*dimension!=totalNumber)
    {
      puts("Input number error, not a square.\n");
      return 1;    
    }
    if(arr==NULL) return 1; // malloc fail
    for(i=0;i<totalNumber;i++) *(arr+i)=atoi(argv[i+2]);
    
    printf("Original Matrix:\n");
    printMatrix(arr, dimension);
    puts("");
    /*swap logic*/
    puts("swap 1st row and 3rd row:");
    for(int i=0;i<dimension;i++) swap((arr+0*dimension+i),(arr+2*dimension+i));
    {
      printMatrix(arr, dimension);
      puts("");
    }
    puts("swap 1st column and 3rd column:");
    for(int i=0;i<dimension;i++) swap((arr+i*dimension+0),(arr+i*dimension+2));
    {
      printMatrix(arr, dimension);
      puts("");
    }
    free(arr);
    return 0;
  }
}


void swap(int *a, int *b)
{
  int temp;
  temp=*a;
  *a=*b;
  *b=temp;
}

void printMatrix(int *arr, int dimension)
{
  int i, j;
  for(j=0;j<dimension;j++)
  {
    for(i=0;i<dimension;i++) printf("%3d",*(arr+dimension*j+i));
    puts("");
  }    
}



/* 
input 1+x^2 numbers
(the first number is total number, x>3)

After alignment, change first row and third row,
and then first column and third column.

requirements:
Let you know how to get rid of "array accessing"
only one set of brackets,i.e, [], is allowed in your program
that is command line argument -> int main(int argc, char *argv[])

don't use[] to access(read and write)array elements

*/
