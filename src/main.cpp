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
	for (vino.x = 0, vino.y = 0, vino.start = 0, vino.is_saved = true;;) {
		draw_text(&vino);
		check_sym(&vino);
	}

	return 0;
}
