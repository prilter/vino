#include <string.h>

#include "../../appvars.h"
#include "../../../libs/terminal/terminal.h"
#include "../../../libs/strings/strings.h"

#define CURL *(win->entry + win->y)

int 
replace_mode(geometry *win)
{
  switch (win->sym) {
    /* r */
    case r_KEY:
      win->sym = getkey();
      if (win->sym >= 32 && win->sym <= 126)
        *(*(win->entry+win->y) + win->x) = win->sym;
      win->mode = CONSOLE;
      break;


    /* R */
    case R_KEY:
      win->sym = getkey(); /* GET KEY */
      if (win->sym == ESC) { /* END REPLACE MODE */
        win->mode = CONSOLE; 
        break;
      }

      if (win->x < strlen(CURL)-1) { /* REPLACE SYMBOL */
        if (win->sym >= 32 && win->sym <= 126) /* NORMAL SYMBOL */
          *(*(win->entry+win->y) + win->x) = win->sym;
      } else /* APPEND SYMBOL */
        insert_s(CURL, win->x, win->sym);
      win->x++;
      win->sym = R_KEY;
      break;
  }
  return 0;
}


int 
r(geometry *win)
{
  if (win->sym >= 32 && win->sym <= 126)
    *(*(win->entry+win->y) + win->x) = win->sym;
  return 1;
}
