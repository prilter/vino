#include <stddef.h>

#include <malloc.h>
#include <string.h>

extern char *_insert_s(char *, size_t, char);
char **_tabs_to_spaces(char **ss, size_t n) {
  size_t i, j, k;
  char *buf;

  if (!ss || n == 0)
    return ss;

  for (i = 0; *(ss+i); i++) {
    buf = ss[i];
    size_t len = strlen(buf);
    size_t tab_count = 0;

    // Сначала подсчитываем количество табов
    for (j = 0; j < len; j++)
      if (*(buf+j) == '\t') 
        tab_count++;

    if (!tab_count) continue;

    // Вычисляем новую длину строки
    size_t new_len = len + tab_count * (n - 1);
    char *snew = malloc(new_len + 1); // +1 для нуль-терминатора
    size_t pos = 0;

    // Заполняем новую строку
    for (j = 0; j < len; j++) {
      if (buf[j] == '\t')
        for (k = 0; k < n; k++)
          snew[pos++] = ' ';
      else
        snew[pos++] = buf[j];
    }
    snew[pos] = '\0';

    // Заменяем старую строку новой
    free(buf);
    ss[i] = snew;
  }
  return ss;
}



/*  
char 
**_tabs_to_spaces(char **ss, size_t n)
{
  size_t i, j;

  for (i = 0; *(ss+i); i++)
    for (j = 0; *(*(ss+i) + j); j++)
      if (*(*(ss+i) + j) == '\t') {
        *(*(ss+i) + j) = ' ';
        for (;--n;)
          *(ss+i) = _insert_s(*(ss+i), j, ' ');
      }
  
  return ss;
}*/
