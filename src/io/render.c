#include <malloc.h>
#include <stdio.h>

#include "../../libs/terminal/terminal.h"
#include "../../libs/descriptors/descriptors.h"
#include "../../libs/strings/strings.h"
#include "../appvars.h"

static int hello_menu(const char *, const char);
static int print(geometry *win);
int 
render(geometry *win) 
{
  clear();
  if (size(win->entry) == 1 && **win->entry == '\n')
    hello_menu("===== WELCOME TO VINO =====", '='); 
  tabs_to_spaces(win->entry, TABLEN);
 
  /* UP-DOWN SCREEN(USE CYCLE BECAUSE gg AND G) */
  for (;win->y < win->yst;) /* UPPER SCREEN MOVING */
    win->yst--;
  for (;win->y > win->yst+ROWS-1;) /* IF END OF SCREEN */
    win->yst++; 
  
  /* IF LONG LINE */
  win->xst = 0;
  if (win->x > COLS - 1) {
    for (;win->x > win->xst + COLS - 1;)
      win->xst++;
    for (;win->x < win->xst;)
      win->xst--;
  }

  /* PRINT */
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


__attribute__((hot))
static int wputs(const char *s, size_t st, size_t end)
{
  const size_t len = strlen(s);

  if(st >= len) {
    return fputc('\n', stdout);  // Возвращаем результат fputc
  }

  // Рассчитываем длину для вывода
  const size_t print_len = (end > len) ? len - st : end - st;

  // Используем fwrite для эффективного вывода части строки
  return fwrite(s + st, 1, print_len, stdout) != print_len;
}

/* |                 filename, NUMc NUMl| */
static int info_puts(geometry *win, FILE *stream, size_t y) {
  static size_t i;
  char *info;

  move(0, y);
  sprintf(win->info, "%d %s, %zdc %zdl", win->mode, win->fn, win->x+1, win->y+1);
  for (i = 0; i < COLS-strlen(win->info); i++)
    fputc(' ', stream);
  fputs(win->info, stream); 

  return 0;
}



static int 
hello_menu(const char *s, const char sep)
{
  char *b;

  if (!(b = malloc(BUFLEN)))
    return 0;
  memset(b, sep, strlen(s));

  /* 1 LINE */
  move((COLS - strlen(s)) >> 1, (ROWS >> 1) - 1);
  puts(b);

  /* 2 LINE */
  move((COLS - strlen(s)) >> 1, ROWS >> 1);
  puts(s);

  /* 3 LINE */
  move((COLS - strlen(s)) >> 1, (ROWS >> 1) + 1);
  puts(b);

  free(b);
  return 1;
}
