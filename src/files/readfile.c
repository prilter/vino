#include <stdio.h>

#if defined(__FreeBSD__)
  #include <malloc_np.h>
#elif defined(__linux__)
  #include <malloc.h>
#endif


#include "../../libs/descriptors/descriptors.h"
#include "../../libs/strings/strings.h"
#include "../appvars.h"

#define make(dir) (fclose(fopen(dir, "w")))

char **readfile(char **ss, const char *fn)
{
  /* INIT */
  FILE *read;
  char *buf;

  /* IS EXIST? */
  if (!is_exist(fn))
    make(fn);

  /* MALLOC */
  read = fopen(fn, "r");
  buf  = malloc(BUFLEN);

  /* GET SS */
  puts("Reading...");
  if (is_empty(fn))
    {append(ss, "\n"); return ss;}
  for (;fgets(buf, BUFLEN, read);)
    append(ss, buf);

  /* FREE */
  fclose(read);
  free(buf);

  /* END */
  return ss;
}
