#include <sys/ioctl.h>
#include <unistd.h>

int 
maxcols(void) 
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}
