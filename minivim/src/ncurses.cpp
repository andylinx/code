#include <ncurses.h>
#define REG_COLOR_NUM 1
#define CUS_COLOR_NUM 2
WINDOW *win;
void init_window()
{
	initscr();
	raw();
	noecho();
	keypad(stdscr, true);
	start_color();
	init_pair(REG_COLOR_NUM, COLOR_WHITE, COLOR_BLACK);
	init_pair(CUS_COLOR_NUM, COLOR_YELLOW, COLOR_CYAN);
	wbkgd(stdscr, COLOR_PAIR(REG_COLOR_NUM));
	wrefresh(stdscr);
	if (LINES < 8) {
		fprintf(stderr, "window line size is small than 5");
		endwin();
		return;
	}
	// create customized window
	/*create a 5*10 window in (0, 0)*/
	win = newwin(8, COLS, 0, 0);
	keypad(win, true);
	wbkgd(win, COLOR_PAIR(CUS_COLOR_NUM));  /*set customized window color*/
	wrefresh(win);

	wprintw(win, "Press Esc to Exit");
	wmove(win, 2, 2);
	wprintw(win, "Hello, world!");                                                          /* Print Hello World */
	mvwprintw(win, 3, 2, "This is MiniVim, your input will appear on the next line.");      /*Move and Print*/
	wrefresh(win);                                                                          /* Print it on to the real screen */
	wmove(win, 4, 2);
	return;
}
