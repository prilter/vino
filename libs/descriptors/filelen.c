#include <stdio.h>
#include <stdlib.h>

extern int is_exist(const char *);

#define BUFLEN 1024

size_t filelen(const char *path) 
{
	FILE  *r;
	char  *b;
	size_t res;

  if (!is_exist(path))
    {perror(""); exit(1);}
	
	b = malloc(BUFLEN);
	r = fopen(path, "r");

	for (res = 0; fgets(b, BUFLEN, r);)
		res++;

	fclose(r);
	free(b);
	return res;
}
