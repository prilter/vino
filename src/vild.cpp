#include <ncurses.h>
#include <string>
#include <vector>

#define vec_str std::vector<std::string>
#define uint	unsigned int

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
	if (!y)  ++r;
	else      for (;y; y/=10, ++r);

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

	for (size_t i = 0; i < lines.size(); ++i)
		mvprintw(i, 0, "%s", lines[i].c_str());

	move(y, x);
	refresh();
	return 1;	
}

void check_sym(vec_str &lines, int &c, uint &x, uint &y)
{
	switch ((c = wgetch(stdscr))) {
		case KEY_UP:
			if (y > 0)
				--y;
			break;
		case KEY_DOWN:
			if (y < lines.size()-1)
				++y;
			break;
		case KEY_RIGHT:
			if (x < lines[y].length()-1)
				++x;
			else if (y < lines.size()-1)
				++y;
			break;
		case KEY_LEFT:
			if (x > 0)
				--x;
			else if (y > 0)
				--y;
			break;

		case ENTER:
			lines.push_back("");
			++y;
			x = 0;
			break;
		case KEY_BACKSPACE:
			if (x > 0)
				lines[y].erase(x-- - 1, 1); /* ERASE SYM */
			else if (y > 0) {
				lines.erase(lines.begin() + y);
				x = lines[-1 + y--].length();
			}
			break;
		case KEY_ESC:
			break;

		case KEY_TAB:
			lines[y].insert(x, "  ");
			x+=2;
			break;
		default:
			if (c >= 32 && c <= 126 && c != KEY_BACKSPACE && c != KEY_TAB)
				lines[y].insert(x++, 1, c);
			break;
	}
}
