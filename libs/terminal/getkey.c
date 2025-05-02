#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define ESC       27
#define KEY_UP    259
#define KEY_DOWN  258
#define KEY_RIGHT 261
#define KEY_LEFT  260

typedef struct termios term;

int getkey(void) {
  term old, new;
  int flags, ch;

  tcgetattr(STDIN_FILENO, &old);
  new = old;

  new.c_lflag &= ~(ICANON | ECHO | IEXTEN | ISIG);
  new.c_iflag &= ~(IXON | ICRNL);
  new.c_cc[VMIN] = 1;
  new.c_cc[VTIME] = 0;
  tcsetattr(STDIN_FILENO, TCSANOW, &new);

  ch = 0;
  if (read(STDIN_FILENO, &ch, 1) == 1 && ch == ESC) {
    char seq[2];

    flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    if (read(STDIN_FILENO, &seq[0], 1) == 1 && read(STDIN_FILENO, &seq[1], 1) == 1 && seq[0] == '[')
      switch(seq[1]) {
        case 'A': ch = KEY_UP; break;
        case 'B': ch = KEY_DOWN; break;
        case 'C': ch = KEY_RIGHT; break;
        case 'D': ch = KEY_LEFT; break;
      }

    fcntl(STDIN_FILENO, F_SETFL, flags);
  }

  tcsetattr(STDIN_FILENO, TCSANOW, &old);
  return ch;
}

