#include <ncurses.h>
#include <vector>
#include <string>
#include <fstream>

#define vec_str 	std::vector<std::string>
#define uint		unsigned int

#define KEY_ESC 27

/* VILD */
extern void init_ncurses();
extern void check_sym(vec_str &lines, int &c, uint &x, uint &y);
extern int  draw_text(const char *filename, vec_str lines, uint x, uint y);

/* FILEWORKING */
extern int  save(const char *filename, vec_str lines);
extern int  read_info(const char *filename, vec_str &lines);

int main(int argc, const char **argv)
{
	if (argc == 1)
		return 1;
	++argv;
	init_ncurses();

	vec_str lines(1);
	uint x, y;
	int c;

	read_info(*argv, lines);
	for (x = 0, y = 0; c != KEY_ESC ;) {
		draw_text(*argv, lines, x, y);
		check_sym(lines, c, x, y);	
	}

	save(*argv, lines);
	endwin();
	return 0;	
}
