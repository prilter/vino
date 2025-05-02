#include <stdio.h>

int 
save(char **ss, const char *dir)
{
  FILE *write;

  remove(dir);
  for (write = fopen(dir, "w"); *ss; ss++)
    fputs(*ss, write);

  fclose(write);
  return 0;
}
