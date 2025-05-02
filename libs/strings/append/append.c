/* APPEND CONST CHAR * TO THE END OF CHAR ** */
#include <string.h>

#if defined(__FreeBSD__)
  #include <malloc_np.h>
#elif defined(__linux__)
  #include <malloc.h>
#endif


extern size_t size(char **);

char **
_append(char **ss, const char *s)
{
	size_t sz;

  sz = size(ss);
    
  if (!( ss = realloc(ss, (sz+2)*sizeof(char *)) )) /* CAN NOT REALLOC */
		return ss;
  if (!( ss[sz] = malloc(strlen(s) + 1) )) /* CAN NOT APPEND NEW LINE */
		return ss;
    
	strcpy(ss[sz], s);
	ss[sz + 1] = NULL;

  return ss;
}
