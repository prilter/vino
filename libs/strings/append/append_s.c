/* APPEND CONST CHAR * TO THE END OF CHAR * */
#include <string.h>

#if defined(__FreeBSD__)
  #include <malloc_np.h>
  #define MALLOCED(p) malloc_size(p)
#elif defined(__linux__)
  #include <malloc.h>
  #define MALLOCED(p) malloc_usable_size(p)
#endif

char *
_append_s(char *dst, const char *src)
{
  size_t malloced_dst;
  malloced_dst = MALLOCED(dst);

  if ((strlen(dst)-1 + strlen(src)) > malloced_dst)
    dst = realloc(dst, strlen(dst)+strlen(src)+3);
  strcat(dst, src);

  return dst;
}
