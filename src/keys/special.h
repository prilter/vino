/* ENTER */
#include <algorithm>
bool onlyspaces(std::string &s) {return std::all_of(s.begin(), s.end(), [](uchar c) { return std::isspace(c); });}

#define have(line, s) (line.find(s) < line.length())
#define enter(lines, x, y)																															\
		/* MAKING NEW LINE */																																\
		lines.insert(lines.begin() + y + 1, "");																						\
																																												\
		/* AUTO COMPLETER(TABS) */																													\
		size_t lx = 0;																																			\
		if (x != 0 && !have(lines[y], "#"))																									\
			for (; lines[y][lx] == ' '; lx++)																									\
				lines[y+1].append(" ");																													\
		if (!have(lines[y], ";") && !onlyspaces(lines[y])) {																\
			lines[y+1].append("  ");																													\
			lx+=2;																																						\
		}																																										\
																																												\
		/* EMPTY APPENDING IF CUR X NOT IN END */																						\
		lines[y + 1].append(lines[y].substr(x, lines[y].length()));													\
		lines[y++].erase(x); /* ERASE ALL FROM STARTED CURRENT X POS IN LINES */						\
		x = lx;																																							\





/* BACKSPACE */
#define backspace(lines, x, y)																												\
if (x == 0 && y > 0) { /* IF IN START THEN MOVE LINE UP */														\
	x = lines[y-1].length();																														\
	lines[y-1].append(lines[y]);																												\
	lines.erase(lines.begin() + y--);																										\
} else if (x > 0) {																																		\
	if (lines[y][x-1] == ' ' && lines[y][x-2] == ' ')	/* IF "TAB" */										\
		lines[y].erase(x-- - 1, 1);																												\
	lines[y].erase(x-- - 1, 1); /* ERASE SYM */																					\
} else if (y > 0) { /* ERASING FROM x = 0 THEN CUR LINE UPPING */											\
	lines.erase(lines.begin() + y);																											\
	x = lines[-1 + y--].length();																												\
}																																											\







/* DC */
#define dc(lines, x, y)																																\
if (x == lines[y].length() && y < lines.size()-1) { /*IF END OF LINE */								\
	lines[y].append(lines[y+1]);																												\
	lines.erase(lines.begin() + y + 1);																									\
} else if (x >= 0 && x < lines[y].length()) { /* DEFAULT */														\
		lines[y][x] = lines[y][x+1];																											\
		lines[y].erase(x + 1, 1);																													\
}																																											\







/* TAB */
#define tab(lines, x, y)																															\
lines[y].insert(x, "  ");																															\
x+=2;																																									\







#define findline(lines, y)																														\
char ln[20];																																					\
size_t num;																																						\
																																											\
echo(); /* TEMPORALY TURN ON THIS TO SEE USER TEXT IN MVGETSTR */											\
mvprintw(LINES-2, 2, "line id: ");																										\
mvgetstr(LINES-2, 2+9, ln); /* 9 - line id len */																			\
noecho();																																							\
num = atoi(ln);																																				\
																																											\
if (num-1 < lines.size()) y = num-1;																									\
else											y = lines.size()-1;																					\
if (x > lines[y].length()) /* MOVE CURSOR TO END IF X > CUR LINE MAX X */							\
		x = lines[y].length();
