#include <malloc.h>

#include "../../libs/terminal/terminal.h"
#include "../../libs/strings/strings.h"
#include "../appvars.h"

static int print(geometry *win);
int 
render(geometry *win) 
{
  tabs_to_spaces(win->entry, TABLEN);

 
  /* UP-DOWN SCREEN(USE CYCLE BECAUSE gg AND G) */
  for (;win->y < win->yst;) /* UPPER SCREEN MOVING */
    win->yst--;
  for (;win->y > win->yst+ROWS-1;) /* IF END OF SCREEN */
    win->yst++; 
  
  /* IF LONG LINE */
  for (;win->x > win->xst + COLS - 1;)
    win->xst++;
  for (;win->x < win->xst;)
    win->xst--;


  /* PRINT */
  clear();
  print(win);
  move(win->x - win->xst, win->y - win->yst);

  return 0;
}







#include <string.h>
static int info_puts(geometry *, FILE *, size_t);
static int wputs(const char *, size_t, size_t);
static int 
print(geometry *win)
{
  size_t i, end;

  if (!win->entry)
    return 0;

  end = win->yst + ROWS;
  for (i = win->yst; *(win->entry+i) && i < end; i++)
    wputs(*(win->entry+i), win->xst, win->xst + COLS - 1);
  info_puts(win, stdout, ROWS);

  return 1;
}



static int wputs(const char *s, size_t st, size_t end)
{
  size_t i;

  if (st >= strlen(s)) {
    fputc('\n', stdout);
    return 0;
  }
  
  for (i = st; *(s+i) && i < end; i++)
    putc(*(s+i), stdout);

  return 0;
}



/* |                 filename, NUMc NUMl| */
static int info_puts(geometry *win, FILE *stream, size_t y) {
  static size_t i;

  move(0, y);
  sprintf(win->info, "%d %s, %zdc %zdl", win->mode, win->fn, win->x+1, win->y+1);
  for (i = 0; i < COLS-strlen(win->info); i++)
    fputc(' ', stream);
  fputs(win->info, stream); 

  return 0;
}
