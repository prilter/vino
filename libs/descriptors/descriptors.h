#ifdef stddef_h
#else
  #include <stddef.h>
#endif

extern size_t filelen(const char *);
extern int    is_exist(const char *);
extern int    is_empty(const char *);
