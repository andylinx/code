#include "virable.h"
int now_command_id;
vector <string> command_history;
void command_mode()
{
	wmove(command, 0, 0);
	wdeleteln(command);
	wprintw(command, "%c", ':');
	wrefresh(command);
	mode_type = 0;
	char cc = getch();
	string com = "";
	now_command_id = command_history.size();
	while (cc != 27 && cc != '\n') {
		if (cc == 3) {
			if (now_command_id - 1 >= 0) {
				wdeleteln(command);
				now_command_id--;
				wmove(command, 0, 0);
				wprintw(command, "%c", ':');
				wprintw(command, "%s", command_history[now_command_id].c_str());
				com = command_history[now_command_id];
				wrefresh(command);
			}
			cc = getch();
			continue;
		}
		if (cc == 2) {
			if (now_command_id + 1 < command_history.size()) {
				wdeleteln(command);
				wmove(command, 0, 0);
				now_command_id++;
				wprintw(command, "%c", ':');
				wprintw(command, "%s", command_history[now_command_id].c_str());
				com = command_history[now_command_id];
				wrefresh(command);
			}
			cc = getch();
			continue;
		}
		if (cc != 7) wprintw(command, "%c", cc);
		else wmove(command, 0, com.size()), wdelch(command);
		wrefresh(command);
		if (cc == 7) {
			if (com.size()) com.erase(com.end() - 1);
		} else {
			com += cc;
		}
		cc = getch();
	}
	if (cc == 27) {
		wdeleteln(command);
		wrefresh(command);
		wmove(win, lst.x, lst.y);
		wrefresh(win);
		return;
	}
	command_history.push_back(com);
	if (com == "w") {
		if (read_only) {
			wdeleteln(command);
			wprintw(command, "%s", "'readonly' option is set (add ! to override)");
			wrefresh(command);
			mode_type = 0;
			return;
		}
		changed = 0;
		out_file(File_name);
		wclear(command);
		wrefresh(command);
		wmove(win, lst.x, lst.y);
		wrefresh(win);
		return;
	}
	if (com == "wq") {
		if (read_only) {
			wdeleteln(command);
			wprintw(command, "%s", "'readonly' option is set (add ! to override)");
			wrefresh(command);
			mode_type = 0;
			return;
		}
		changed = 0;
		wclear(command);
		out_file(File_name);
		exit_flag = 1;
		return;
	}
	if (com == "q") {
		if (changed) {
			wdeleteln(command);
			wprintw(command, "%s", "No write since last change (add ! to override)\n");
			wrefresh(command);
			mode_type = 0;
		} else {
			exit_flag = 1;
		}
		return;
	}
	if (com == "q!") {
		exit_flag = 1;
		return;
	}
	if (com == "w!") {
		changed = 0; read_only = 0;
		out_file(File_name);
		wclear(command);
		wrefresh(command);
		wmove(win, lst.x, lst.y);
		wrefresh(win);
		mode_type = 0;
		return;
	}
	if (com == "wq!") {
		changed = 0;
		wclear(command);
		out_file(File_name);
		exit_flag = 1;
		return;
	}
	if (com[0] == 'j' && com[1] == 'm' && com[2] == 'p') {
		wdeleteln(command);
		wrefresh(command);
		int num = 0;
		for (int i = 4; i < com.size(); i++) num = num * 10 + com[i] - '0';
		st.x = num - 1;
		st.x = max(st.x, 0);
		cur.x = cur.y = 0;
		print();
		return;
	}
	command_history.erase(command_history.end() - 1);
	wdeleteln(command);
	wprintw(command, "Not an editor command:%s", com.c_str());
	wrefresh(command);
}
