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

int w(const char **, size_t *, size_t *);
int b(const char **, size_t *, size_t *);

int 
console_mode(geometry *win) 
{
  win->sym = getkey();
  switch (win->sym) {
    /*-----------------------------------------  COLON  -----------------------------------------*/
    case COLON_KEY:{
      char *com;

      move(0, ROWS);\
      com = malloc(BUFLEN);
      fputs("LINE ID: ", stdout);
      fgets(com, BUFLEN, stdin);

      switch (*com) {
        case '+':
          if (win->y + atoi(com+1) < size(win->entry))
            win->y += atoi(com+1);
          else
            win->y = size(win->entry)-1;

          if (win->x > strlen(CURL)-1)
            win->x = strlen(CURL)-1;
          break;
        case '-':
          if (win->y - atoi(com+1) > 0)
            win->y -= atoi(com+1);
          else {}

          if (win->x > strlen(CURL)-1)
            win->x = strlen(CURL)-1;
          break;
        default:
          if (atoi(com) <= size(win->entry) && atoi(com) > 0)
            win->y = atoi(com)-1;
          else
            win->y = size(win->entry)-1;

          if (win->x > strlen(CURL)-1)
            win->x = strlen(CURL)-1;
          break;
      }
      free(com);
      break;
    }

                   
    /*-------------------------------------------  I  -------------------------------------------*/
    case I_KEY: 
      win->x = 0;
      if (*CURL == ' ')
        for (;++win->x <= strlen(CURL) && *(CURL+win->x) == ' ';);

      win->mode = INSERT;
      break;


    /*-------------------------------------------  i  -------------------------------------------*/
    case i_KEY:
      win->mode = INSERT;
      break;


    /*-------------------------------------------  A  -------------------------------------------*/
    case A_KEY:
        win->x = strlen(CURL)-1;\
        win->mode = INSERT;\
        break;


    /*-------------------------------------------  a  -------------------------------------------*/
    case a_KEY:
        if (win->x < strlen(CURL)-1)
          win->x++;
        win->mode = INSERT;
        break;


    /*----------------------------------------  r and R  ----------------------------------------*/
    case R_KEY:
    case r_KEY:
        win->mode = REPLACE;
        break;


    /*-------------------------------------------  j  -------------------------------------------*/
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
    

    /*-------------------------------------------  k  -------------------------------------------*/
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


    /*-------------------------------------------  l  -------------------------------------------*/
    case RIGHT:
      if (!USE_ARROWS)
        break;
    case l_KEY:
      if (win->x < (strlen(CURL)-1))
        win->x++;
      break;


    /*-------------------------------------------  L  -------------------------------------------*/
    case L_KEY:
      win->y = win->yst + ROWS - 1;
      if (win->x > strlen(CURL)-1)
        win->x = strlen(CURL)-1;
      break;


    /*-------------------------------------------  h  -------------------------------------------*/
    case LEFT:
      if (!USE_ARROWS)
        break;
    case h_KEY:
      if (win->x > 0)
        win->x--; 
      break;
      

    /*-------------------------------------------  H  -------------------------------------------*/
    case H_KEY:
      win->y = win->yst;
      if (win->x > strlen(CURL)-1)
        win->x = strlen(CURL)-1;
      break;


    /*-------------------------------------------  g  -------------------------------------------*/
    case g_KEY:
      win->sym = getkey();
      if (win->sym == g_KEY)
        win->y = 0, win->x = 0;
      else
        console_mode(win);
      break;


    /*-------------------------------------------  G  -------------------------------------------*/
    case G_KEY:
      win->y = size(win->entry)-1;
      if (win->x > strlen(CURL)-1)
        win->x = strlen(CURL)-1;
      break;
    

    /*-------------------------------------------  w  -------------------------------------------*/
    case w_KEY:
      w((const char **)win->entry, &win->y, &win->x);
      break;
    

    /*-------------------------------------------  b  -------------------------------------------*/
    case b_KEY:
      b((const char **)win->entry, &win->y, &win->x);
      break;
    

    /*-------------------------------------------  o  -------------------------------------------*/
    case o_KEY:
      win->x = 0;
      insert(win->entry, ++win->y, "\n");
      win->mode = INSERT;
      break;


    /*-------------------------------------------  O  -------------------------------------------*/
    case O_KEY:
      win->x = 0;
      insert(win->entry, win->y, "\n");
      win->mode = INSERT;
      break;


    /*-------------------------------------------  d  -------------------------------------------*/
    case d_KEY:
      win->sym = getkey();
      switch (win->sym) {
        case d_KEY:                                                                                                       /* -------dd------- */
          if (win->y == 0 && size(win->entry) == 1) /* IF HAVE ONLY 1 LINE */
            strncpy(CURL, "\n", strlen(CURL));
          else
            erase(win->entry, win->y);

          if (win->y == size(win->entry))
            win->y--;
          win->x = 0;
          break;
        case g_KEY:                                                                                                       /* -------dg------- */
          win->sym = getkey();
          if (win->sym == g_KEY) {
            for (;win->y > 0;)
              erase(win->entry, win->y--);
            strncpy(*win->entry, "\n", strlen(*win->entry));
            win->y = 0, win->x = 0;
          }
          break;
        case G_KEY:                                                                                                       /* -------dG------- */
          for (;win->y < size(win->entry);)
            erase(win->entry, win->y);
          if (win->y > 0) win->y--;
          else append(win->entry, "\n");
          win->x = 0;
          break;
        case w_KEY:{                                                                                                      /* -------dw------- */
          size_t yend, xend;
          yend = win->y, xend = win->x;
          w((const char **)win->entry, &yend, &xend);
          if (xend)
            for (;(xend-- - win->x);)
              erase_s(CURL, win->x);
          break;}
        case b_KEY:{                                                                                                      /* -------dw------- */
          size_t yend, xend;
          yend = win->y, xend = win->x;
          b((const char **)win->entry, &yend, &xend);
          if (win->x == 0 && win->y > 0 ) { /* START OF LINE */
            *(LAST + (win->x = strcspn(LAST, "\n"))) = '\0';    /* REMOVE \n IN END OF LAST LINE AND MOVE CURSOR*/
            append_s(LAST, CURL); erase(win->entry, win->y--);  /* MOVE CURRENT LINE UP */
          } else if (xend > 0)
            for (;win->x > 0 && (win->x - xend); win->x--)
              erase_s(CURL, xend);
          break;
        }
      }
      break;
    
      
    /*-------------------------------------------  D  -------------------------------------------*/
    case D_KEY:
      *(CURL+win->x) = '\n';
      *(CURL+win->x+1) = '\0';
      break;
    

    /*-------------------------------------------  s  -------------------------------------------*/
    case s_KEY:
      if (win->x < strlen(CURL)-1)
        erase_s(CURL, win->x);
      win->mode = INSERT;
      break;
      

    /*-------------------------------------------  S  -------------------------------------------*/
    case S_KEY:
      strncpy(CURL, "\n", strlen(CURL));
      if (win->x > strlen(CURL)-1)
        win->x = strlen(CURL)-1;
      win->mode = INSERT;
      break;


    /*-----------------------------------------  SLASH  -----------------------------------------*/
    case SLASH_KEY:{
      size_t i;
      for (i = 0; i < strlen(CURL) && *(CURL+i) == ' ';) /* SKEEP SPACES AT START */
        i++;

      if (i < strlen(CURL)-2) { /* IF "   rgeRg erge" */
        if (*(CURL+i) == '/' && *(CURL+i+1) == '/') { /* UNCOMMENT */
          erase_s(CURL, i);
          erase_s(CURL, i);
        } else { /* COMMENT */
          insert_s(CURL, i, '/');
          insert_s(CURL, i, '/');
        }
        if (win->x > strlen(CURL)-1)
          win->x = strlen(CURL)-1;
      } else {insert_s(CURL, i, '/');insert_s(CURL, i, '/');} /* IF "    " */
      break;}
  }

  return 1;
}





int w(const char **ss, size_t *y, size_t *x)
{
  if (*x == strlen(*(ss+*y))-1 && *y < size((char **)ss)-1)
    (*y)++, *x = 0;
  else {
    for (;ss[*y][*x] != ' ' && *x < strlen(*(ss+*y))-1; (*x)++);
    for (;ss[*y][*x] == ' ' && *x < strlen(*(ss+*y))-1; (*x)++);
  }
  return 0;
}


int b(const char **ss, size_t *y, size_t *x)
{
  if (*x == 0 && *y > 0)
    *x = strlen(*(ss+*y-1))-1, (*y)--;
  else if (*x == strlen(*(ss+*y))-1)
    for (;ss[*y][*x-1] != ' ' && *x > 0; (*x)--);
  else if (*x > 0) {
    for (;ss[*y][*x-1] != ' ' && *x > 0; (*x)--);
    for (;ss[*y][*x-1] == ' ' && *x > 0; (*x)--);
    for (;ss[*y][*x-1] != ' ' && *x > 0; (*x)--);
  }
  return 0;
}
