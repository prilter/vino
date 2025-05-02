/* CHECK IS EXIST FILE */
#include <unistd.h>

__attribute__((hot))
int 
is_exist(const char *path) {
	return (access(path, F_OK) != -1);
}
