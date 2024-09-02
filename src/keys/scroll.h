/* UP */
#define up(lines, x, y)																							\
if (y == 0) /* Y = 0 */																							\
	x = 0;																														\
else if (y > 0) /* DEFAULT */																				\
	--y;																															\
if (x > lines[y].length()) /* IF STRLEN CUR Y > STRLEN FUTURE Y */	\
	x = lines[y].length();																						\







/* DOWN */
#define down(lines, x, y)																						\
if (y == lines.size()-1)	/* LAST */																\
	x = lines[y].length();																						\
else if (y < lines.size()-1) /* DEFAULT */													\
	++y;																															\
if (x > lines[y].length()) /* IF STRLEN CUR Y > STRLEN FUTURE Y */	\
	x = lines[y].length();







/* RIGHT */
#define right(lines, x, y)																					\
if (lines[y][x] == ' ' && x < lines[y].length()) /*TABS AND SPACES*/\
	for (;lines[y][x] == ' ' && x < lines[y].length(); x++);					\
else if (x < lines[y].length()) /* DEFAULT */												\
	++x;																															\
else if (y < lines.size()-1) /* MOVE TO NEXT LINE IF END */					\
	++y, x = 0;																												\








/* LEFT */
#define left(lines, x , y)																					\
if (x > 0)																													\
	--x;																															\
else if (y > 0) /* MOVE UP(x IN END) */															\
	x = lines[--y].length();																					\

