#include <malloc.h>
#include <string.h>

extern size_t size(char **);

char 
**_insert(char **ss, size_t y, const char *s) 
{
  size_t sz;

  if (!ss || !s)
    return ss;

  sz = size(ss);
  if (y > sz)
    y = sz;

  if (!(ss = realloc(ss, (sz+2) * sizeof(char*))))
    return ss;
  memmove(ss+y+1, ss+y, (sz - y + 1) * sizeof(char*));
  *(ss+y) = strdup(s);

  return ss;
}
