/* ENTER */
#include <algorithm>
bool onlyspaces(std::string s) {return std::all_of(s.begin(), s.end(), [](uchar c) { return std::isspace(c); });}

#define enter(lines, x, y)																														\
	/* MAKING NEW LINE */																																\
	lines.insert(lines.begin() + y + 1, "");																						\
																																											\
	/* GET FORWARD TEXT IN LINE */																											\
	std::string nexttext = "";																													\
	if (x < lines[y].length()) { /* IF NOT END OF LINE AND ENTERED */										\
		nexttext = lines[y].substr(x, lines[y].length());																	\
		lines[y].erase(x); /* ERASE ALL FROM STARTED CURRENT X POS IN LINES */						\
	}																																										\
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
	lines[y+1].append(nexttext);																												\
																																											\
	++y; /* NEW LINE */																																	\
																																											\






/* BACKSPACE */
#define backspace(lines, x, y)																												\
if (x == 0 && y > 0) { /* IF IN START THEN MOVE LINE UP */														\
	x = lines[y-1].length();																														\
	lines[y-1].append(lines[y]);																												\
	lines.erase(lines.begin() + y--);																										\
} else if (x > 0) {																																		\
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
	
