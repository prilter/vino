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
	else
		for (size_t i = 0; i < lines.size(); ++i) {
			mvprintw(i, 0, "%s", lines[i].c_str());	
			move(y, x);
		}
	
	refresh();
	return 1;	
}

void check_sym(vec_str &lines, int &c, uint &x, uint &y)
{
	switch ((c = wgetch(stdscr))) {
		case KEY_UP:
			if (y > 0)
				--y;
			if (x > lines[y].length()) /* IF STRLEN CUR Y > STRLEN FUTURE Y */
				x = lines[y].length();
			break;
		case KEY_DOWN:
			if (y < lines.size()-1)
				++y;
			if (x > lines[y].length()) /* IF STRLEN CUR Y > STRLEN FUTURE Y */
				x = lines[y].length();
			break;
		case KEY_RIGHT:
			if (x < lines[y].length())
				++x;
			else if (y < lines.size()-1) /* MOVE TO NEXT LINE(x = 0) */
				++y, x = 0;
			break;
		case KEY_LEFT:
			if (x > 0)
				--x;
			else if (y > 0) /* MOVE UP(x IN END) */
				x = lines[--y].length();
			break;

		case ENTER:
		{
			/* MAKING NEW LINE */
			lines.insert(lines.begin() + y + 1, "");

			/* GET FORWARD TEXT IN LINE */
			std::string nexttext = "";
			if (x < lines[y].length()) { /* IF NOT END OF LINE AND ENTERED */
							nexttext = lines[y].substr(x, lines[y].length());
							lines[y].erase(x); /* ERASE ALL FROM STARTED CURRENT X POS IN LINES */
			}

			/* AUTO COMPLETER(TABS) */
			x = 0;
			for (size_t i = 0; lines[y][i] == ' '; i++) {
				lines[y+1].append(" ");
				x++;
			}

		 	/* EMPTY APPENDING IF CUR X NOT IN END */
			lines[y+1].append(nexttext);

		 	++y; /* NEW LINE */
			break;
		}
		case KEY_BACKSPACE:
			if (x == 0 && y > 0) { /* IF IN START THEN MOVE LINE UP */
				x = lines[y-1].length();
				lines[y-1].append(lines[y]);
				lines.erase(lines.begin() + y--);
			} else if (x > 0) {
				lines[y].erase(x-- - 1, 1); /* ERASE SYM */
			} else if (y > 0) { /* ERASING FROM x = 0 THEN CUR LINE UPPING */
				lines.erase(lines.begin() + y);
				x = lines[-1 + y--].length();
			}
			break;
		case KEY_DC:
			if (x >= 0 && x < lines[y].length()) { /* DEFAULT */
				lines[y][x] = lines[y][x+1];
				lines[y].erase(x + 1, 1);
			} else if (x == lines[y].length() && y < lines.size()-1) { /*IF END OF LINE AND NEED MOVE NEXT LINE TO CUR LINE*/
				lines[y].append(lines[y+1]);
				lines.erase(lines.begin() + y + 1);
			}

			break;
		case KEY_ESC: /* GO NEXT TO WAITING CYCLE CHECKING ESC AS END OF WRITTING */
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
