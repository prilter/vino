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
			case KEY_SLASH:
				term_mode(vino);
				break;

			default:
				if (vino->c >= 32 && vino->c <= 126 && vino->c != KEY_TAB && vino->c != KEY_BACKSPACE && vino->c != KEY_TAB) {
					(vino->lines)[vino->y].insert((vino->x)++, 1, vino->c);	
					vino->is_saved = false;
				}
				break;
		}
	}

	return 1;
}







#define end ((vino->start)+LINES-1)
int draw_text(parms *vino) {
	wclear(stdscr);
	
	char *txt = new char[20];
	sprintf(txt, "%dl, %ds", vino->y+1, vino->x+1);

	mvprintw(LINES-1, (COLS-((str)vino->filename).length())/2, vino->filename);
	mvprintw(LINES-1, COLS-((str)txt).length()-1, txt);
	
	delete[] txt;

	/* UPPING || DOWNING */
	if (vino->y < vino->start) /* UP */
		--(vino->start);
	if (vino->y >= end)   /* DOWN */
		++(vino->start);

	for (size_t k = 0; k < LINES-1; ++k)
		mvaddstr(k, 0, (vino->lines)[vino->start+k].c_str());
	move(vino->y-vino->start, vino->x);

	wredrawln(stdscr, vino->y-vino->start, vino->x);
	
	return 1;
}







#define COMLEN  1024
#define SURELEN 3
#define ask(s, s1)															\
	echo();																				\
	move(LINES-1, 1);															\
	clrtoeol();																		\
	mvaddstr(LINES-1, 1, s);											\
	mvgetstr(LINES-1, ((str)(s)).length()+1, s1);	\
	noecho();
extern int save(const char *, vec_str &);
size_t findline(void);
int term_mode(parms *vino) 
{
	char *com, *sure;

	/* GETTING COMMAND */
	ask("", (com = new char[COMLEN]));

	/* ANALIZING */
	for (sure = new char[SURELEN]; *com;) {
		switch(*com++) {
			case 's': /* SAVE */
				save(vino->filename, vino->lines);
				vino->is_saved = true;
				break;
			case 'q': /* QUIT */
				if (vino->is_saved == true) {
					endwin();
					exit(0);
				}
				break;
			case 'Q': /* FORCED QUIT */
				endwin();
				exit(0);
				break; /* NOT NEEDED FOR PROGRAMM, NEED FOR MYSELF*/
			case 'R':
				ask("Are you really want to delete file(Y/N): ", sure)
	
				if (*sure == 'Y' || *sure == 'y') {
					remove(vino->filename);
					endwin();
					exit(0);
				}
				break;
			case 'f':{
				size_t n = findline();
				if (n < (vino->lines).size())
					vino->y = n;
				else
					vino->y = (vino->lines).size()-1;
				
				break;}
		}
	}	

	delete[] com, sure;
	com = nullptr, sure = nullptr;
	return 1;
}

#include <cstdlib> /* FOR atoi */
size_t findline(void)
{
	char  *s;
	size_t r;

	ask("Line: ", (s = new char[COMLEN]));
	r = atoi(s);
	
	delete[] s;
	s = nullptr;
	return r;
}
