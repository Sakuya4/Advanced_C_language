#include <stdio.h>
#include <stdlib.h>

typedef struct num_list
{
  int counts;
  int *p_list;
}tNumList;


void swap(int *x, int *y);
void bubble_sort(tNumList *list);
void merge(tNumList *list1, tNumList *list2);
void fill_list(tNumList *list);
void print_list(tNumList *list, int Length);

int main(void)
{
  tNumList *list1;
  tNumList *list2;
  
  list1=(tNumList*) malloc(sizeof(tNumList));
  list2=(tNumList*) malloc(sizeof(tNumList));
  
  printf("please enter how many numbers in list1:");
  fill_list(list1);
  
  printf("please enter how many numbers in list2:");
  fill_list(list2); 

  bubble_sort(list1);
  bubble_sort(list2);
  
  printf("%s", "sorted list1: ");
  print_list(list1, list1->counts);
  printf("%s", "sorted list2: ");
  print_list(list2, list2->counts);

  merge(list1, list2);

  return 0;
  free(list1->p_list);
  free(list2->p_list);

}

void swap(int *x, int *y)
{
  int temp;
  temp=*x;
  *x=*y;
  *y=temp;
}

void bubble_sort(tNumList *list)
{
  int i;
  int j;
  for(i=0;i<list->counts-1;i++)
  {
    for(j=0;j<list->counts-i-1;j++)
    {
      if(list->p_list[j]>list->p_list[j+1]) 
      {
        swap(&list->p_list[j], &list->p_list[j+1]);
      }
    }
  }    
}

void merge(tNumList *list1, tNumList *list2)
{
  int i=0;
  int j=0;
  printf("%s", "Merged list: ");

  while(i<list1->counts&&j<list2->counts)
  {
    if(list1->p_list[i]<=list2->p_list[j])
    {
      printf("%d", list1->p_list[i]);
      i++;   
    }
    else
    {
      printf("%d", list2->p_list[j]);
      j++;
    }
  }
  while(i<list1->counts)
  {
    printf("%d", list1->p_list[i]);
    i++;
  }
    while(j<list2->counts)
  {
    printf("%d", list2->p_list[j]);
    j++;
  }
}

void fill_list(tNumList *list)
{
  int i;
  scanf("%d", &(list->counts)); 
  printf("\tplease input %d numbers:", list->counts);
  list->p_list=(int *)malloc(sizeof(int)*(list->counts));
  for(i=0l;i<list->counts;i++) 
  {
    scanf("%d", &list->p_list[i]);
  }
}

void print_list(tNumList *list, int Length)
{
  int i;
  for(i=0;i<Length;i++)
  {
    printf("%d ", list->p_list[i]);
  }
  puts("");
}
