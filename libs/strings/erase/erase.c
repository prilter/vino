#include <string.h>

#if defined(__FreeBSD__)
  #include <malloc_np.h>
#elif defined(__linux__)
  #include <malloc.h>
#endif


extern size_t size(char **);

char **
_erase(char **ss, size_t y) 
{
  size_t sz;
  if (!ss)
    return ss;

  sz = size(ss);
  if (y >= sz)
    return ss;

  free(*(ss+y));
  memmove(ss+y, ss+y+1, (sz - y) * sizeof(char*));

  if ( !(ss = realloc(ss, sz * sizeof(char *))) )
    return ss;
  return ss;
}
