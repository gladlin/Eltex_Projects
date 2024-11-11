#include "binaries.h"

void task1()
{
  int n = -1;
  printf("Task 1\nPlease enter positive integer:");
  if(scanf("%d", &n) != 1 || n < 0)
  {  
    printf("You must enter positive integer next time");
    return;
  }
  int temp = n;
  int len_of_number = -1;
  while(temp>0)
  {
    temp >>= 1;
    len_of_number +=1;
  }
  while(len_of_number >= 0)
  {
    printf("%d", n >> len_of_number&1);
    len_of_number--;
  }
}