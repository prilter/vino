#include <stddef.h>

size_t size(char **s) 
{
	size_t r;
	for (r = 0; *s; r++)
		s++;

	return r;
}
