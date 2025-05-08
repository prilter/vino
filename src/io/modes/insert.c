#include <string.h>
#include <unistd.h>

#include "../../../libs/terminal/terminal.h"
#include "../../../libs/strings/strings.h"
#include "../../appvars.h"
#define CURL *(win->entry + win->y)
#define LAST *(win->entry + win->y - 1)

extern int save(char **, const char *);

int 
insert_mode(geometry *win) 
{
  win->sym = getkey();
  switch (win->sym) {
    case ESC:
      win->mode = CONSOLE;
      break;
    case ENTER: /* ENTER */
      insert(win->entry, ++win->y, substr(CURL, win->x));
      insert_s(LAST, win->x++, '\n'); insert_s(LAST, win->x, '\0');
      win->x = 0;
      break;
    case UP:
      if (!USE_ARROWS) /* CAN USER USE IT? */
        break;
      if (win->y > 0) { /* START CHECKING */
        win->y--;
        if (win->x >= strlen(CURL)) /* MOVE TO THE END LINE IF LINE-1 BIGGER */
          win->x = strlen(CURL)-1;
      }
      break;
    case DOWN: // issue 1
      if (!USE_ARROWS) /* CAN USER USE IT? */
        break;
      
      if (win->y < size(win->entry)-1) { /* CHECK END OF FILE */
        win->y++; /* MOVE DOWN CURSOR */
        /* IF X > LEN OF NEXT LINE THEN MOVE CURSOR LEFT */
        if (win->x >= strlen(CURL))
          win->x = strlen(CURL)-1;
      }
      break;
    case RIGHT:
      if (!USE_ARROWS) /* CAN USER USE IT? */
        break;
 
      if (win->x < (strlen(CURL)-1))
        win->x++;
     break;
    case LEFT:
      if (!USE_ARROWS) /* CAN USER USE IT? */
        break;
 
      if (win->x > 0)
        win->x--; 
      break;
    case TAB:
      for (size_t i = 0; i < TABLEN; i++)
        insert_s(CURL, win->x++, ' ');
      break;
    case DELETE:
      break;
    case BACKSPACE:
      if (win->x > 0) /* DON'T DELETING \N */
        erase_s(CURL, --win->x);
      else if (win->x == 0 && win->y != 0) { /* DELETING \N AND NOT START */
        win->x = strlen(LAST)-1;
        erase_s(LAST, strcspn(LAST, "\n")); /* ERASE \n FROM LINE */
        append_s(LAST, CURL); /* ADD LINE UP TO THE END */
        erase(win->entry, win->y--); /* DELETE CURRENT LINE AND MOVE UP */
      }
      break;
    case C_s:
      save(win->entry, win->fn);
      break;
    default:
      if (win->sym >= 32 && win->sym <= 126)
        insert_s(CURL, win->x++, (char)win->sym);
//      win->saved = 0;
      break;
  }

  return 0;
}
