#include <string.h>

#if defined(__FreeBSD__)
  #include <malloc_np.h>
#elif defined(__linux__)
  #include <malloc.h>
#endif


char *
_erase_s(char *s, size_t x) 
{
  size_t len;
  len = strlen(s);

  if (x > len)
	  return s;

  memmove(s+x, s+x+1, len - x + 1);
	if (!(s = realloc(s, len)))
	  return s;

	return s;
}
