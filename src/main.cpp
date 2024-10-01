#include <ncurses.h>
#include <vector>
#include <string>

#include "macros.h"

/* VILD */
extern int init_ncurses(void);
extern int check_sym(vec_str &lines, int &c, uint &x, uint &y);
extern int draw_text(const char *filename, vec_str &lines, size_t &start, size_t &end, uint x, uint y);

/* FILEWORKING */
extern int			save(const char *filename, vec_str &lines);
extern vec_str	read_info(const char *);

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
	uint				x, y;
	int					c;

	/* MAIN PROCCESS */
	lines = read_info(*argv);
	for (x = 0, y = 0, start = 0, end = LINES-1; c != KEY_ESC ;) {
		draw_text(*argv, lines, start, end, x, y);
		check_sym(lines, c, x, y);	
	}

	/* SAVE INFO AND QUIT */
	endwin();
	save(*argv, lines);
	return 0;
}
