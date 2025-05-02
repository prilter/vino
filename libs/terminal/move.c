#include <stdio.h>

int
move(size_t x, size_t y) 
{
  printf("\033[%zd;%zdH", y+1, x+1);
  fflush(stdout);

  return 0;
}
