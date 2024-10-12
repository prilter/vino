#include <ncurses.h>
#include <vector>
#include <string>

#include "macros.h"

/* VILD */
extern int init_ncurses(void);
extern int check_sym(parms *vino);
extern int draw_text(parms *vino);

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

	/* INIT */
	parms vino;
	vino.filename = *argv;

	/* MAIN PROCCESS */
	vino.lines = read_info(vino.filename);
	for (vino.x = 0, vino.y = 0, vino.start = 0, vino.end = LINES-1, vino.is_saved = false;;) {
		for (; vino.c != KEY_ESC ;) {
			draw_text(&vino);
			check_sym(&vino);
		}

		if (vino.is_saved == false) {
			mvprintw(LINES-1, 1, "File not saved!");
			vino.c = 500; /* NEED BECAUSE C = ESC SKIPPING FIRST CYCLE -> INFINITY CYCLE */
		} else
			break;
	}

	/* SAVE INFO AND QUIT */
	endwin();
	return 0;
}
