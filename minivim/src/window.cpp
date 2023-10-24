#include "virable.h"
#define REG_COLOR_NUM 1
#define CUS_COLOR_NUM 2
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
	maxline = 10;
	if (LINES < maxline) {
		fprintf(stderr, "window line size is small than %d", maxline);
		endwin();
		return;
	}
	// create customized window
	/*create a 5*10 window in (0, 0)*/
	win = newwin(maxline, COLS, 0, 0);
	keypad(win, true);
	wbkgd(win, COLOR_PAIR(CUS_COLOR_NUM));  /*set customized window color*/
	wrefresh(win);

	wmove(win, 0, 0);
	cursor_pos = { 0, 0 };
	nowline = 0;
	return;
}

void move_upward_a_line()
{
	wmove(win, 0, 0);
	wdeleteln(win);
	wmove(win, maxline - 1, 0);
	wrefresh(win);
}
void move_downward_a_line()
{
	for (int i = 0; i < maxline; i++) wmove(win, 0, 0), wdeleteln(win);
	for (int i = 0; i < min(maxline, (int)text.size() - stline); i++)
		wmove(win, i, 0), wprintw(win, "%s", text[stline + i].c_str());
	wrefresh(win);
}
