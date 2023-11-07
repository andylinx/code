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
	wbkgd(stdscr, COLOR_PAIR(REG_COLOR_NUM));
	wrefresh(stdscr);
	maxline = 10;
	if (LINES < maxline + 2) {
		endwin();
		return;
	}
	int color1 = 1, color2 = 2;
	start_color();
// init color pair
	init_pair(color1, COLOR_WHITE, COLOR_BLACK);
	init_pair(color2, COLOR_BLUE, COLOR_YELLOW);
	win = newwin(maxline, COLS, 0, 0);
	keypad(win, true);
	wbkgd(win, COLOR_PAIR(color1));
	wmove(win, 0, 0);
	cursor_pos = { 0, 0 };
	wrefresh(win);
	info = newwin(1, COLS, maxline, 0);
	wbkgd(info, COLOR_PAIR(color2));
	wmove(info, 0, 0);
	wrefresh(info);
	command = newwin(1, COLS, maxline + 1, 0);
	wbkgd(command, COLOR_PAIR(color1));
	wmove(command, 0, 0);
	wrefresh(command);
	if (text.size()) {
		for (int i = 0; i < min(maxline, (int)text.size()); i++)
			wmove(win, i, 0), wprintw(win, "%s", text[i].c_str());
		wmove(win, 0, 0);
	}
	wrefresh(win);
	return;
}
void print_screen()
{
	wclear(win);
	for (int i = 0; i < min(maxline, (int)text.size() - stline); i++) {
		wmove(win, i, 0);
		for (int j = coldelta; j < text[stline + i].length(); j++)
			wprintw(win, "%c", text[stline + i][j]);
	}
	wrefresh(win);
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
