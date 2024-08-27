#include <ncurses.h>
#include <fstream>
#include <vector>

#define len() 	    length()
#define end() 	    endwin()

#define CTRL_KEY(k) ((k) & 0x1f)
#define KEY_DEL	    8 /* UNWORKED */
#define ESC	    27
#define KEY_TAB	    9

#include "vild.hpp"
#include "fileworking.hpp"

int main(int argc, const char **argv)
{
	if (argc == 1)
		return 1;

	std::vector<std::string> lines(1);
	int cx, cy, sym, scroll;

	init(cx, MAX_X, cy, MAX_Y);
	getfiletext(*++argv, lines);
	for (cx = 0, cy = 0, scroll = 0; sym != ESC; ) {
		draw_text(*argv, lines, cx, cy, scroll);
		analize_input(lines, sym, cx, cy, scroll);
	}

	save(*argv, lines);
	end();
	return 0;
}
