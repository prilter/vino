/*  NEED TO CHECK IS FILE EMPTY */

/* LIBS */
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

/* FUNCTION */
int 
is_empty(const char *fn) 
{
	/* INIT */
	struct stat st;
	int fd;

	/* IS EXIST */
	if (access(fn, F_OK) == -1)
		return 1;

	/* CHECK IS EMPTY */
	fd = open(fn, O_RDONLY);
	if (!fstat(fd, &st))
		if (st.st_size == 0)
			{close(fd); return 1;}
	close(fd);

	/* IF NOT EMPTY */
	return 0;
}
