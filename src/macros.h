#include <vector>
#include <string>

#define vec_str std::vector<std::string>
#define str			std::string

#define uint		unsigned int
#define uchar		unsigned char
#define ushort	unsigned short

typedef struct {
	vec_str			lines;
	const char *filename;
	size_t			start, end;
	bool				is_saved;
	uint				x, y;
	int					c;
} parms;

#define KEY_TAB		9
#define KEY_ESC		27
#define ENTER			10
#define KEY_SLASH 31 
#define PASTE_KEY	22
