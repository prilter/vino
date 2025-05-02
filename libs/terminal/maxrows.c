#include <sys/ioctl.h>
#include <unistd.h>

#define IOCTL_FAILED -1

int 
maxrows(void) 
{
  struct winsize ws;

  /* GET TERMINAL SIZE */
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == IOCTL_FAILED)
    return IOCTL_FAILED;

  return ws.ws_row-1;
}
