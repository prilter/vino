#define init()										\
	initscr();									\
	raw();										\
	noecho();									\
	keypad(stdscr, TRUE);								\
	start_color();									\
	init_pair(1, COLOR_WHITE, COLOR_BLACK);						\
	bkgd(COLOR_PAIR(1));								\

int getinfolen(const char *filename, int cx, int cy)
{
	int r;
    	r = 0;

       	/* + cxlen */
	if (!cx)  ++r;
	else	  for (;cx; cx/=10, ++r);

	/* + cxlen */
	if (!cy)  ++r;
	else      for (;cy; cy/=10, ++r);

	/* + filenamelen */
	r += ((std::string)filename).len();

	/* + another syms inc */
	r += 7;
	return r;
}

#define draw_text(filename, lines, cx, cy)						\
	clear();									\
											\
	int infolen;									\
	infolen = getinfolen(filename, cx, cy);						\
											\
	mvprintw(LINES-1, COLS-infolen, "%s: %dl, %ds", filename, cy+1, cx+1);		\
	for (size_t i = 0; i < lines.size(); ++i)					\
		mvprintw(i, 0, "%s", lines[i].c_str());					\
		  									\
	move(cy, cx);									\
	refresh();									\

/* FUCK THAT MACRO AND BACKSPACE */
#define curlinelen lines[cy].len()
#define analize_input(lines, sym, cx, cy) 						\
	if ((sym = getch()) != ESC) {							\
		switch(sym) {								\
			case KEY_UP:							\
				cy -= (cy > 0);						\
				if (cx > curlinelen)					\
					cx = curlinelen;				\
				break;							\
			case KEY_DOWN:							\
				cy += (cy < lines.size()-1); /* MOVE Y POS DOWN */	\
				if (cx > curlinelen)					\
		       			cx = curlinelen;				\
				break;							\
			case KEY_LEFT:							\
				cx -= (cx > 0);						\
				break;							\
			case KEY_RIGHT:							\
				cx += (cx < curlinelen);				\
				break;							\
			case KEY_BACKSPACE:						\
				if (cx > 0) {						\
					lines[cy].erase(cx-- - 1, 1); /* ERASE SYM */	\
				} else if (cy > 0) {					\
					cx = lines[cy - 1].len();;			\
					lines[cy - 1] += lines[cy];			\
					lines.erase(lines.begin() + cy--);		\
				}							\
				break;							\
			case '\n':							\
			case KEY_ENTER:							\
				lines.insert(lines.begin()+cy+1, lines[cy].substr(cx));	\
				lines[cy] = lines[cy].substr(0, cx);			\
				cy++; /*MOVE TO NEW LINE*/				\
				cx = 0;/*MOVE TO START OF NEW LINE*/			\
				break;							\
			case KEY_TAB:							\
				lines[cy].insert(cx, 2, ' ');				\
				cx += 0x2;						\
				break;							\
			default: /* SIMPLE PRINT SYMBOL */				\
				if (sym >= 32 && sym <= 126)				\
					lines[cy].insert(cx++, 1, sym);			\
				break;							\
		}									\
	}										\

