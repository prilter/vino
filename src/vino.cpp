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
int term_mode(vec_str &lines, uint &x, uint &y, bool &is_saved, const char *filename);
int check_sym(vec_str &lines, int &c, uint &x, uint &y, bool &is_saved, const char *filename)
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
				is_saved = false;
				break;
			case KEY_BACKSPACE:
				backspace(lines, x, y);
				is_saved = false;
				break;
			case KEY_DC:
				dc(lines, x, y);
				is_saved = false;
				break;
			case KEY_TAB:
				tab(lines, x, y);
				is_saved = false;
				break;
			case KEY_SLASH:{
				term_mode(lines, x, y, is_saved, filename);
				break;
			}

			default:
				if (c >= 32 && c <= 126 && c != KEY_BACKSPACE && c != KEY_TAB && c != KEY_SLASH)
					lines[y].insert(x++, 1, c);
				is_saved = false;
				break;
		}
	}

	return 1;
}







int draw_text(const char *filename, vec_str &lines, size_t &start, size_t &end, uint x, uint y) {
	wclear(stdscr);
	
	char info[COLS];
	sprintf(info, "%dl, %ds %.0f%%", y+1, x+1, 100*((float)y+1)/(lines.size()));
	mvprintw(LINES-1, COLS-((str)info).length()-1, "%s", info);
	mvprintw(LINES-1, 1, "%s", filename);
	
	/* UPPING || DOWNING(used for because ctnl + /) */
	for (; end > lines.size(); --end); /* END > LINES SIZE */
	for (; y < start; --start, --end); /* UP */
	for (; y >= end ; ++end, ++start); /* DOWN */

	for (size_t k = 0; start+k < end; ++k)
		mvprintw(k, 0, "%s", lines[start+k].c_str());
	move(y-start, x);
	
	wrefresh(stdscr);
	return 1;	
}







extern int save(const char *, vec_str &);
extern int f_term_getting_line(str &com);
int term_mode(vec_str &lines, uint &x, uint &y, bool &is_saved, const char *filename) 
{
	str com;

	/* GETTING COMMAND */
	echo();
	move(LINES-1, 1);
	clrtoeol();
	mvgetstr(LINES-1, 2, (char *)(com.c_str()));
	noecho();

	/* ANALIZING */
	for (size_t i = 0; i <= com.length(); i++) {
		switch(com[i]) {
			case 's':
				save(filename, lines);
				is_saved = true;
				break;
			case 'q':
				if (is_saved) {
					endwin();
					exit(0);
				}
				break;
		}
	}

	return 1;
}
