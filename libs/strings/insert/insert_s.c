#include <stddef.h>
#include <string.h>

#if defined(__FreeBSD__)
  #include <malloc_np.h>
#elif defined(__linux__)
  #include <malloc.h>
#endif


__attribute__((hot))
char *
_insert_s(char *s, size_t x, char c) 
{
  if (x > strlen(s))
    x = strlen(s);

	if (!(s = realloc(s, strlen(s)+2)))
		return s;
  memmove(s+x+1, s+x, strlen(s) - x + 1);
	*(s+x) = c;

	return s;
}
