#include <ncurses.h>
#include <fstream>
WINDOW *win, *info, *command, *whole, *line_num;
std::ifstream File;
std::ofstream OFile;
struct point {
	int x, y;     // 0-index
	point()
	{
	}
	point(int _x, int _y) : x(_x), y(_y)
	{
	}
	point operator +(const point &oth) const
	{
		return point(x + oth.x, y + oth.y);
	}
} mx, st, now, cur, lst;
#include "window.cpp"
#include "move_cursor.cpp"
#include "normal.cpp"
#include "insert.cpp"
#include "iofile.cpp"
#include "command.cpp"
int mode_type, exit_flag, changed;
int read_only, tranc_flag;
vector <string> text;
string File_name;
int main(int argc, char *argv[])
{
	mode_type = 0;
	// 0 normal 1 insert 2 command
	if (argc == 1) {
		std::cout << "Please input a file name~" << std::endl;
		return 0;
	}
	if (argc >= 2) {
		if (argc >= 3) {
			if (argv[1][1] == 't')
				tranc_flag = 1;
			if (argv[1][1] == 'R')
				read_only = 1;
			if (argc >= 4) {
				if (argv[2][1] == 't')
					tranc_flag = 1;
				if (argv[2][1] == 'R')
					read_only = 1;
			}
		}
		if (!tranc_flag) init_file(argv[argc - 1]);
		File_name = argv[argc - 1];
	}
	// init part
	st = { 0, 0 }; mx = { 0, 0 }; cur = { 0, 0 };
	init_word_completion();
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
		print();
		wclear(command);
	}
	endwin();
	return 0;
}
