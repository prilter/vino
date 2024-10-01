/* ENTER */
#include <algorithm>
bool onlyspaces(std::string &s) {return std::all_of(s.begin(), s.end(), [](uchar c) { return std::isspace(c); });}

#define enter(lines, x, y)																															\
	if (x == 0) {/* START LINE  */																												\
		lines.insert(lines.begin()+y+1, "");																								\
		if (!lines.empty()) {	/* IF HAVE ANY TEXT IN LINE */																\
			lines[y+1].append(lines[y].substr(x, lines[y].length()));													\
			lines[y++].erase(x);																															\
		}																																										\
	} else {																																							\
		/* MAKING NEW LINE */																																\
		lines.insert(lines.begin() + y + 1, "");																						\
																																												\
		/* GET FORWARD TEXT IN LINE */																											\
		std::string nexttext = "";																													\
		nexttext = lines[y].substr(x, lines[y].length());																		\
		lines[y].erase(x); /* ERASE ALL FROM STARTED CURRENT X POS IN LINES */							\
																																												\
		/* AUTO COMPLETER(TABS) */																													\
		x = 0;																																							\
		for (size_t i = 0; lines[y][i] == ' '; i++) {																				\
			lines[y+1].append(" ");																														\
			x++;																																							\
		}																																										\
																																												\
		/* IF NOT ; IN END OF LINE THEN AUTO TAB */																					\
		if (lines[y][lines[y].length()-1] != ';' && !onlyspaces(lines[y]) && nexttext=="") {\
			lines[y+1].append("  ");																													\
			x += 2;																																						\
		}																																										\
																																												\
		/* EMPTY APPENDING IF CUR X NOT IN END */																						\
		lines[y++ + 1].append(nexttext);																										\
	}																																											\






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
