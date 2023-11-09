#include "virable.h"
#define REG_COLOR_NUM 1
#define CUS_COLOR_NUM 2
void print(int type = 1) // we refresh the whole screen after every operation, including the infomation window
{
	for (int i = 0; i <= mx.x; i++) {
		wmove(line_num, i, 0);
		wdelch(line_num); wdelch(line_num);
	}
	for (int i = 1; i <= mx.x + 1; i++) {
		wmove(line_num, i - 1, 0);
		if (st.x + i < 10) wprintw(line_num, "%c", ' ');
		if (st.x + i < 100) wprintw(line_num, "%c", ' ');
		wprintw(line_num, "%d", st.x + i);
	}
	wrefresh(line_num);
	wmove(win, 0, 0);
	for (int i = 0; i <= mx.x; i++)
		wdeleteln(win);
	for (int i = 0; i < min(mx.x + 1, (int)text.size() - st.x); i++) {
		wmove(win, i, 0);
		int cnt = 0;
		for (int j = st.y; j < text[st.x + i].length(); j++) {
			wprintw(win, "%c", text[st.x + i][j]);
			cnt++;
			if (cnt == mx.y) break;
		}
		wrefresh(win);
	}
	wmove(win, cur.x, cur.y);
	wmove(info, 0, 0);
	wdeleteln(info);
	now = st + cur;
	wprintw(info, "LINE:%d COL:%d", now.x + 1, now.y);
	wmove(info, 0, 45);
	if (mode_type == 0)
		wprintw(info, "~Normal Mode~");
	if (mode_type == 1)
		wprintw(info, "~Insert Mode~");
	if (mode_type == 2)
		wprintw(info, "~Command Mode~");
	string name_of_file;
	int stpos;
	for (stpos = File_name.length() - 1; stpos > 0; stpos--)
		if (File_name[stpos] == '/' || File_name[stpos] == '\\') {
			stpos++;
			break;
		}
	name_of_file = File_name.substr(stpos, File_name.length() - stpos);
	wmove(info, 0, mx.y - name_of_file.length() - 1);
	wprintw(info, "%s", name_of_file.c_str());
	wrefresh(info);
	wrefresh(win);
	if (type) lst = st + cur;
}

void init_window() // we set the size of the window as big as we can
{
	initscr();
	raw();
	noecho();
	mx = { LINES - 2, COLS - 5 };
	keypad(stdscr, true);
	start_color();
	wbkgd(stdscr, COLOR_PAIR(REG_COLOR_NUM));
	wrefresh(stdscr);
	int color1 = 1, color2 = 2, color3 = 3;
	start_color();
	init_pair(color1, COLOR_WHITE, COLOR_BLACK);
	init_pair(color2, COLOR_BLUE, COLOR_YELLOW);
	init_pair(color3, COLOR_MAGENTA, COLOR_BLACK);
	win = newwin(mx.x, mx.y + 1, 0, 4);
	keypad(win, true);
	wbkgd(win, COLOR_PAIR(color1));
	wmove(win, 0, 0);
	wrefresh(win);
	info = newwin(1, mx.y + 1, mx.x, 3);
	wbkgd(info, COLOR_PAIR(color2));
	wmove(info, 0, 0);
	wrefresh(info);
	command = newwin(1, mx.y + 1, mx.x + 1, 3);
	wbkgd(command, COLOR_PAIR(color1));
	wmove(command, 0, 0);
	wrefresh(command);
	line_num = newwin(mx.x, 4, 0, 0);
	wbkgd(line_num, COLOR_PAIR(color3));
	wrefresh(line_num);
	mx.x--;
	print();
	return;
}
