#ifdef stddef_h
#else
  #include <stddef.h>
#endif

#define MAXLINES_FAILED -1
#define EMPTY_ARR      0

extern int ignore_useless(void);
extern int clear(void);
extern int maxrows(void);
extern int maxcols(void);
extern int move(size_t, size_t);
extern int getkey(void);

#define ROWS maxrows()
#define COLS maxcols()


