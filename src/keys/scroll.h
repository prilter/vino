/* UP */
#define up(lines, x, y)																							\
if (y > 0) /* DEFAULT */																						\
	--y;																															\
if (x > lines[y].length()) /* IF STRLEN CUR Y > STRLEN FUTURE Y */	\
	x = lines[y].length();																						\







/* DOWN */
#define down(lines, x, y)																						\
if (y < lines.size()-1) /* DEFAULT */																\
	++y;																															\
if (x > lines[y].length()) /* IF STRLEN CUR Y > STRLEN FUTURE Y */	\
	x = lines[y].length();







/* RIGHT */
#define right(lines, x, y)																					\
if (lines[y][x] == ' ') /*TABS AND SPACES*/													\
	for (;lines[y][x] == ' '; x++);																		\
else if (x < lines[y].length()) /* DEFAULT */												\
	++x;																															\
else if (y < lines.size()-1) /* MOVE TO NEXT LINE IF END */					\
	++y, x = 0;																												\








/* LEFT */
#define left(lines, x , y)																					\
if (x > 0) {																												\
	for (;lines[y][x-- - 1] == ' ' && x > 0;)													\
			;																															\
} else if (y > 0) /* MOVE UP(x IN END) */														\
	x = lines[--y].length();																					\

