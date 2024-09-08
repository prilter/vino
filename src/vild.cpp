#include <ncurses.h>
#include <string>
#include <vector>

#define vec_str std::vector<std::string>
#define uint	 unsigned int
#define ushort unsigned short
#define uchar	 unsigned char

#define KEY_TAB 9
#define KEY_ESC	27
#define ENTER   10




void init_ncurses(void) {
	initscr();
	raw();
	noecho();
	keypad(stdscr, TRUE);
}





#include "keys/scroll.h"
#include "keys/special.h"
void check_sym(vec_str &lines, int &c, uint &x, uint &y)
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

			default:
				if (c >= 32 && c <= 126 && c != KEY_BACKSPACE && c != KEY_TAB)
					lines[y].insert(x++, 1, c);
				break;
		}
	}
}







ushort getinfolen(const char *filename, int x, int y);
int draw_text(const char *filename, vec_str lines, size_t &start, size_t &end, uint x, uint y) {
	wclear(stdscr);

	mvprintw(LINES-1, COLS-getinfolen(filename, x, y)-7, "%s: %dl, %ds", filename, y+1, x+1);

	if (y < start) {--end, --start;} /*UP WIN*/
	if (y > end)   {++end, ++start;} /* DOWN WIN */
	for (size_t i = start, k = 0; i <= end && i < lines.size(); ++i, ++k)
		mvprintw(k, 0, "%s", lines[i].c_str());
	move(y-start, x);
	
	wrefresh(stdscr);
	return 1;	
}







ushort getinfolen(const char *filename, int x, int y)
{
	ushort r = 0;

  /* + cxlen */
	if (!x)  ++r;
	else	  for (;x; x/=10, ++r);

	/* + cxlen */
	if (!y) ++r;
	else    for (;y; y/=10, ++r);

	/* + filenamelen */
	r += ((std::string)filename).length();

	return r;
}
