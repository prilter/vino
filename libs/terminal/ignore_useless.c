#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

int 
ignore_useless(void) 
{
  signal(SIGINT,  SIG_IGN); /* IGNORE C-c */
  signal(SIGQUIT, SIG_IGN); /* IGNORE C-/ */
  return 0;
}

