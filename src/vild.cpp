#include <ncurses.h>
#include <string>
#include <vector>

#define vec_str std::vector<std::string>
#define uint	unsigned int
#define uchar	unsigned char

#define KEY_TAB 9
#define KEY_ESC	27
#define ENTER   10

void init_ncurses(void) {
	initscr();
	raw();
	noecho();
	keypad(stdscr, TRUE);
}

int getinfolen(const char *filename, int x, int y)
{
	int r;
   	r = 0;

  	/* + cxlen */
	if (!x)  ++r;
	else	  for (;x; x/=10, ++r);

	/* + cxlen */
	if (!y) ++r;
	else    for (;y; y/=10, ++r);

	/* + filenamelen */
	r += ((std::string)filename).length();

	/* + another syms inc */
	r += 7;
	return r;
}

int draw_text(const char *filename, vec_str lines, uint x, uint y) {
	clear();

	int infolen;
	infolen = getinfolen(filename, x, y);
	mvprintw(LINES-1, COLS-infolen, "%s: %dl, %ds", filename, y+1, x+1);

	if (y > LINES - 1)
		for (size_t i = y - LINES + 1, k = 0; i < lines.size(); ++i, ++k) {
			mvprintw(k, 0, "%s", lines[i].c_str());
			move(k, x);
		}
	else {
		for (size_t i = 0; i < lines.size(); ++i)
			mvprintw(i, 0, "%s", lines[i].c_str());	
		move(y, x);
	}
	
	refresh();
	return 1;	
}

#include "keys/scroll.h"
#include "keys/special.h"
void check_sym(vec_str &lines, int &c, uint &x, uint &y)
{
	switch ((c = wgetch(stdscr))) {
		case KEY_ESC: /* GO NEXT TO WAITING CYCLE CHECKING ESC AS END OF WRITTING */
			break;
		
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
		{
			enter(lines, x, y);
			break;
		}
		case KEY_BACKSPACE:
			backspace(lines, x, y);
			break;
		case KEY_DC:
			dc(lines, x, y);
			break;
		case KEY_TAB:
			tab(lines, x, y);
			break;

		default:
			if (c >= 32 && c <= 126 && c != KEY_BACKSPACE && c != KEY_TAB)
				lines[y].insert(x++, 1, c);
			break;
	}
}
