#include <ncurses.h>
#include <vector>
#include <string>

#include "macros.h"

/* VILD */
extern int init_ncurses(void);
extern int check_sym(vec_str &lines, int &c, uint &x, uint &y, bool &is_saved, const char *filename);
extern int draw_text(const char *filename, vec_str &lines, size_t &start, size_t &end, uint x, uint y);

/* FILEWORKING */
extern vec_str	read_info(const char *);

/* MAIN */
int main(int argc, const char **argv)
{
	/* INIT PROGRAMM */
	if (argc == 1)
		return 1;
	++argv;
	init_ncurses();

	/* INIT ALL WORKING VARS */
	vec_str			lines;
	size_t			start, end;
	bool				is_saved;
	uint				x, y;
	int					c;

	/* MAIN PROCCESS */
	lines = read_info(*argv);
	for (x = 0, y = 0, start = 0, end = LINES-1, is_saved = false;;) {
		for (; c != KEY_ESC ;) {
			draw_text(*argv, lines, start, end, x, y);
			check_sym(lines, c, x, y, is_saved, *argv);
		}

		if (is_saved == false) {
			mvprintw(LINES-1, 1, "File not saved!");
			c = 500; /* NEED BECAUSE C = ESC SKIPPING FIRST CYCLE -> INFINITY CYCLE */
		} else
			break;
	}

	/* SAVE INFO AND QUIT */
	endwin();
	return 0;
}
