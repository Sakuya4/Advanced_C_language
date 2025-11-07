#include "space.h"

tTypeScore score_buf[N]; //preallocated memory space

void get_score_space(tTypeScore **pp_score)
{
   int Number=0;
   for(int counter=0;counter<N;counter++){
      if(score_buf[counter].used!=1){
        break;
      }else{
        Number++;
      }
   }
   *pp_score=&score_buf[Number];
	printf("     get_score_space(): giving space numbered %d\n",Number);
    return;
}

void return_score_space (int loc)
{
    printf("     return_score_space(): return space numbered %d\n", loc);
}
