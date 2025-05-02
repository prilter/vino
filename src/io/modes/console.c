#include <string.h>
#include <stdlib.h>
#if defined(__FreeBSD__)
  #include <malloc_np.h>
#elif defined(__linux__)
  #include <malloc.h>
#endif


#include "../../appvars.h"
#include "../../../libs/terminal/terminal.h"
#include "../../../libs/strings/strings.h"

#define CURL *(win->entry + win->y)
#define LAST *(win->entry + win->y - 1)

int 
console_mode(geometry *win) 
{
  char *com;

  switch (win->sym) {
    case COLON_KEY:
      move(0, ROWS);
      com = malloc(BUFLEN);
      fputs("LINE ID: ", stdout);
      fgets(com, BUFLEN, stdin);
      if (atoi(com) <= size(win->entry) && atoi(com) > 0)
        win->y = atoi(com)-1;
      else
        win->y = size(win->entry)-1;
      free(com);
      break;
    /*case C_f:
      move(0, ROWS);
      com = malloc(BUFLEN);
      fgets(com, BUFLEN, stdin);
      for (win->y = 0; (win->y+1) < size(win->entry); win->y++)
        if (strcspn(CURL, com) != strlen(CURL))
          win->x = strcspn(CURL, com);
      free(com);
      break;
    */
    
    case I_KEY:
      win->x = 0;
      if (*CURL == ' ')
        for (;++win->x <= strlen(CURL) && *(CURL+win->x) == ' ';);

      win->mode = INSERT;
      break;
    case i_KEY:
      win->mode = INSERT;
      break;
    
    case A_KEY:
      win->x = strlen(CURL)-1;
      win->mode = INSERT;
      break;
    case a_KEY:
      if (win->x < strlen(CURL)-1)
        win->x++;
      win->mode = INSERT;
      break;

      /* NAVIGATION */
    case DOWN:
      if (!USE_ARROWS)
        break;
    case j_KEY:
      if (win->y < size(win->entry)-1) { /* CHECK END OF FILE */
        win->y++; /* MOVE DOWN CURSOR */
        /* IF X > LEN OF NEXT LINE THEN MOVE CURSOR LEFT */
        if (win->x >= strlen(CURL))
          win->x = strlen(CURL)-1;
      }
      break;
    
    case UP:
      if (!USE_ARROWS)
        break;
    case k_KEY:
      if (win->y > 0) { /* START CHECKING */
        win->y--;
        if (win->x >= strlen(CURL)) /* MOVE TO THE END LINE IF LINE-1 BIGGER */
          win->x = strlen(CURL)-1;
      }
      break;

    case RIGHT:
      if (!USE_ARROWS)
        break;
    case l_KEY:
      if (win->x < (strlen(CURL)-1))
        win->x++;
      break;
    case L_KEY:
      win->y = win->yst + ROWS - 1;
      if (win->x > strlen(CURL)-1)
        win->x = strlen(CURL)-1;
      break;

    case LEFT:
      if (!USE_ARROWS)
        break;
    case h_KEY:
      if (win->x > 0)
        win->x--; 
      break;
    case H_KEY:
      win->y = win->yst;
      if (win->x > strlen(CURL)-1)
        win->x = strlen(CURL)-1;
      break;

    case g_KEY:
      win->sym = getkey();
      if (win->sym == g_KEY)
        win->y = 0;
      else
        console_mode(win);
      break;
    case G_KEY:
      win->y = size(win->entry)-1;
      break;
    
    case w_KEY:
      if (win->x == strlen(CURL)-1 && win->y < size(win->entry)-1)
        win->y++, win->x = 0;
      else {
        for (;*(CURL+win->x) != ' ' && win->x < strlen(CURL)-1; win->x++);
        for (;*(CURL+win->x) == ' ' && win->x < strlen(CURL)-1; win->x++);
      }
      break;
    
    case b_KEY:
      if (win->x == 0 && win->y > 0)
        win->x = strlen(LAST)-1, win->y--;
      else {
        for (;*(CURL+win->x) != ' ' && win->x > 0; win->x--);
        for (;*(CURL+win->x) == ' ' && win->x > 0; win->x--);
        for (;*(CURL+win->x-1) != ' ' && win->x > 0; win->x--);
      }
      break;
    
    case o_KEY:
      win->x = 0;
      insert(win->entry, ++win->y, "\n");
      win->mode = INSERT;
      break;
    case O_KEY:
      win->x = 0;
      insert(win->entry, win->y, "\n");
      win->mode = INSERT;
      break;

    case d_KEY:
      if ((win->sym = getkey()) == d_KEY)
        erase(win->entry, win->y);
      break;
    case D_KEY:
      *(CURL+win->x) = '\n';
      *(CURL+win->x+1) = '\0';
      break;
    
    case s_KEY:
      if (win->x < strlen(CURL)-1)
        erase_s(CURL, win->x);
      win->mode = INSERT;
      break;
    case S_KEY:
      strncpy(CURL, "\n", strlen(CURL));
      if (win->x > strlen(CURL)-1)
        win->x = strlen(CURL)-1;
      win->mode = INSERT;
      break;
  }

  return 1;
}
