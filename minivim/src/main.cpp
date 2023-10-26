#include <ncurses.h>
#include <fstream>
WINDOW *win, *info, *command, *whole;
std::ifstream File;
#include "window.cpp"
#include "move_cursor.cpp"
#include "normal.cpp"
#include "insert.cpp"
#include "command.cpp"
#include "iofile.cpp"
int mode_type, exit_flag;
int nowline, maxline, stline, rowdelta;
vector <string> text;
pair <int, int> cursor_pos;
int main(int argc, char *argv[])
{
	mode_type = 0;
	// 0 normal 1 insert 2 command
	if (argc >= 2) {
		if (argv[1][0] != '-') {
			init_file(argv[1]);
		} else {
		}
		for (int i = 2; i <= argc; i++) {
			//deal with the command argv
		}
	}
	init_window();
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
