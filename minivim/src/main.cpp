#include <ncurses.h>
WINDOW *win;
#include "window.cpp"
#include "normal.cpp"
#include "insert.cpp"
#include "command.cpp"

int mode_type, exit_flag;
int nowline, maxline, stline;
vector <string> text;
pair <int, int> cursor_pos;
int main()
{
	init_window();
	mode_type = 0;
	// 0 normal 1 insert 2 command

	exit_flag = 0;
	// 0 running 1 exit
	while (!exit_flag) {
		if (mode_type == 0)
			normal_state();
		if (mode_type == 1)
			insert_mode();
		if (mode_type == 2)
			command_mode();
	}
	endwin();
	return 0;
}
