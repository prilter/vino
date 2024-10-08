#include <ncurses.h>
#include <string>
#include <vector>

#include "macros.h"



int init_ncurses(void) {
	initscr();
	raw();
	noecho();
	keypad(stdscr, TRUE);

	return 1;
}





#include "keys/scroll.h"
#include "keys/special.h"
#include <cstdlib>
int check_sym(vec_str &lines, int &c, uint &x, uint &y)
{
	if ((c = wgetch(stdscr)) != KEY_ESC) { /* GO NEXT TO WAITING CYCLE CHECKING ESC AS END OF WRITTING */
		switch (c) {
			case KEY_UP:
				up(lines, x, y);
				break;
			case KEY_DOWN:
				down(lines, x, y);
				break;
			case KEY_RIGHT:
				right(lines, x, y);
				break;
			case KEY_LEFT:
				left(lines, x, y);
				break;

			case ENTER:
				{enter(lines, x, y);}
				break;
			case KEY_BACKSPACE:
				backspace(lines, x, y);
				break;
			case KEY_DC:
				dc(lines, x, y);
				break;
			case KEY_TAB:
				tab(lines, x, y);
				break;
			case KEY_SLASH:{
				findline(lines, y);
				break;
			}

			default:
				if (c >= 32 && c <= 126 && c != KEY_BACKSPACE && c != KEY_TAB && c != KEY_SLASH)
					lines[y].insert(x++, 1, c);
				break;
		}
	}

	return 1;
}







int draw_text(const char *filename, vec_str &lines, size_t &start, size_t &end, uint x, uint y) {
	wclear(stdscr);
	
	char info[COLS];
	sprintf(info, "%dl, %ds %.0f%%", y+1, x+1, 100*((float)y+1)/(lines.size()));
	mvprintw(LINES-1, COLS-((str)info).length()-2, "%s", info);
	mvprintw(LINES-1, 2, "%s", filename);
	
	/* UPPING || DOWNING(used for because ctnl + /) */
	if (y < start) for (; y < start; --end, --start); /* UP */
	if (y >= end)	 for (; y >= end ; ++end, ++start); /* DOWN */
	for (size_t i = start, k = 0; i < end && i < lines.size(); ++i, ++k)
		mvprintw(k, 0, "%s", lines[i].c_str());
	move(y-start, x);
	
	wrefresh(stdscr);
	return 1;	
}
