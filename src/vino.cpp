#include <ncurses.h>
#include <string>
#include <vector>

#include "macros.h"



int init_ncurses(void) {
	initscr();
	raw();
	noecho();
	keypad(stdscr, TRUE);

	return 1;
}





#include "keys/scroll.h"
#include "keys/special.h"
int term_mode(parms *vino);
int check_sym(parms *vino)
{
	if ((vino->c = wgetch(stdscr)) != KEY_ESC) { /* GO NEXT TO WAITING CYCLE CHECKING ESC AS END OF WRITTING */
		switch (vino->c) {
			case KEY_UP:
				up((vino->lines), (vino->x), (vino->y));
				break;
			case KEY_DOWN:
				down((vino->lines), (vino->x), (vino->y));
				break;
			case KEY_RIGHT:
				right((vino->lines), (vino->x), (vino->y));
				break;
			case KEY_LEFT:
				left((vino->lines), (vino->x), (vino->y));
				break;

			case ENTER:
				{enter((vino->lines), (vino->x), (vino->y));}
				vino->is_saved = false;
				break;
			case KEY_BACKSPACE:
				backspace((vino->lines), (vino->x), (vino->y));
				vino->is_saved = false;
				break;
			case KEY_DC:
				dc((vino->lines), (vino->x), (vino->y));
				vino->is_saved = false;
				break;
			case KEY_TAB:
				tab((vino->lines), (vino->x), (vino->y));
				vino->is_saved = false;
				break;
			case KEY_SLASH:{
				term_mode(vino);
				break;
			}

			default:
				if (vino->c >= 32 && vino->c <= 126 && vino->c != KEY_BACKSPACE && vino->c != KEY_TAB && vino->c != KEY_SLASH) {
					(vino->lines)[vino->y].insert((vino->x)++, 1, vino->c);
					 vino->is_saved = false;
				}
				break;
		}
	}

	return 1;
}







int draw_text(parms *vino) {
	wclear(stdscr);
	
	char info[COLS];
	sprintf(info, "%dl, %ds %.0f%%", vino->y+1, vino->x+1, 100*((float)(vino->y)+1)/((vino->lines).size()));
	mvprintw(LINES-1, COLS-((str)info).length()-1, "%s", info);
	mvprintw(LINES-1, 1, "%s", vino->filename);
	
	/* UPPING || DOWNING(used for because ctnl + /) */
	for (; vino->y <  vino->start;	--(vino->start), --(vino->end)); /* UP */
	for (; vino->y >= vino->end ;	  ++(vino->end), ++(vino->start)); /* DOWN */

	for (size_t k = 0; vino->start+k < vino->end && vino->start+k < (vino->lines).size(); ++k)
		mvprintw(k, 0, "%s", (vino->lines)[vino->start+k].c_str());
	move(vino->y-vino->start, vino->x);
	
	wrefresh(stdscr);
	return 1;	
}







#define COMLEN 1024
#include <cstdlib>
#include <cstdio>
extern int save(const char *, vec_str &);
extern int f_term_getting_line(str &com);
int term_mode(parms *vino) 
{
	char *com;

	/* GETTING COMMAND */
	echo();
	move(LINES-1, 1);
	clrtoeol();
	mvgetstr(LINES-1, 2, (com = new char[COMLEN]));
	noecho();

	/* ANALIZING */
	for (;*com;) {
		switch(*com++) {
			case 's': /* SAVE */
				save(vino->filename, vino->lines);
				vino->is_saved = true;
				break;
			case 'q': /* QUIT */
				if (vino->is_saved) {
					endwin();
					exit(0);
				}
				break;
			case 'Q': /* FORCED QUIT */
				endwin();
				exit(0);
				break; /* NOT NEEDED FOR PROGRAMM, NEED FOR MYSELF*/
		}
	}

	delete[] com;
	com = nullptr;
	return 1;
}
