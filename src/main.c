#include <stdio.h>
#include <string.h>

#if defined(__FreeBSD__)
  #include <malloc_np.h>
#elif defined(__linux__)
  #include <malloc.h>
#endif


#include "../libs/descriptors/descriptors.h"
#include "../libs/terminal/terminal.h"
#include "io/modes/modes.h"

extern int    render(geometry *);
extern int    input(geometry *);
extern char **readfile(char **, const char *);
extern int    save(char **, const char *);
int
main(int argc, const char **argv) {
  /* INIT */
  geometry win;

  /* ZERO ARGUMENTS */
  if (argc == 1)
    {puts("Usage: vino <filename>"); return 1;}

  /* SET STARTED VALUES */
  win.fn    = malloc(FILENAMELEN);   
  win.info  = malloc(COLS);
  win.x     = 0;
  win.y     = 0;
  win.xst   = 0;
  win.yst   = 0;
  win.saved = 1;
  win.mode  = CONSOLE;
  win.entry = malloc(8); 

  strncpy(win.fn, *(argv+1), FILENAMELEN);
  win.entry = readfile(win.entry, win.fn); /* GET WIN.FN AND WIN.ENTRY */
  /* MAIN */
  ignore_useless();
  for (;win.sym != C_q;) {
    render(&win);
    win.sym = getkey();
    switch (win.mode) {
      case CONSOLE: console_mode(&win); break;
      case INSERT:  insert_mode(&win);  break;
    }
  }
  clear();
  save(win.entry, win.fn);

  /* FREE */
  for (int i = 0;*(win.entry+i); i++)
    free(*(win.entry+i));
  free(win.entry);
  free(win.fn);
  free(win.info);

  return 0;
}

