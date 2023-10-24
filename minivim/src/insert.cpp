#include "virable.h"
void insert_mode()
{
	char cc = getch();

	if (!text.size()) text.push_back("");
	while (cc != ':' && cc != 27) {
		if (cc >= 2 && cc <= 5) {                                               //move the cursor
			if (cc == 2) {                                                  //down
				if (stline + cursor_pos.first != text.size() - 1) {     // if there is still text under this line
					if (cursor_pos.first == maxline - 1) {          // need to move downwards a line
						move_upward_a_line();
						stline++;
						cursor_pos.second = min(cursor_pos.second, (int)text[stline + cursor_pos.first].length());
						wmove(win, cursor_pos.first, 0);
						wprintw(win, "%s", text[stline + cursor_pos.first].c_str());
						wmove(win, cursor_pos.first, cursor_pos.second);
						wrefresh(win);
					} else {
						cursor_pos.first++;
						cursor_pos.second = min(cursor_pos.second, (int)text[stline + cursor_pos.first].length());
						wmove(win, cursor_pos.first, cursor_pos.second);
						wrefresh(win);
					}
				}
			}
			if (cc == 3) {                                  //up
				if (stline + cursor_pos.first) {        // if there is still text before this line
					if (!cursor_pos.first) {        // if we need to move upwards a line
						stline--;
						move_downward_a_line();
						cursor_pos.first = 0;
						cursor_pos.second = min(cursor_pos.second, (int)text[stline].length());
						wmove(win, cursor_pos.first, cursor_pos.second);
						wrefresh(win);
					} else {
						cursor_pos.first--;
						cursor_pos.second = min(cursor_pos.second, (int)text[stline + cursor_pos.first].length());
						wmove(win, cursor_pos.first, cursor_pos.second);
						wrefresh(win);
					}
				}
			}
			if (cc == 5) {                                                                                                                  // right
				if (stline + cursor_pos.first != text.size() - 1 || cursor_pos.second != text[stline + cursor_pos.first].length()) {    //still have a charater on the right
					if (cursor_pos.second != text[stline + cursor_pos.first].length()) {
						cursor_pos.second++;
					} else {
						if (cursor_pos.first == maxline - 1) {
							move_upward_a_line();
							stline++;
							wprintw(win, "%s", text[stline + maxline - 1].c_str());
							cursor_pos.first--;
						}
						cursor_pos.first++, cursor_pos.second = 0;
					}
					wmove(win, cursor_pos.first, cursor_pos.second);
					wrefresh(win);
				}
			}
			if (cc == 4) {          //left
				if (stline + cursor_pos.first || cursor_pos.second) {
					if (cursor_pos.second) {
						cursor_pos.second--;
					} else {
						if (!cursor_pos.first) { // if we need to move upwards a line
							stline--;
							move_downward_a_line();
							cursor_pos.first = 1;
						}
						cursor_pos.first--, cursor_pos.second = text[stline + cursor_pos.first].length();
					}
					wmove(win, cursor_pos.first, cursor_pos.second);
					wrefresh(win);
				}
			}
		} else {
			nowline = stline + cursor_pos.first;
			if (cc == 7) {
				if (cursor_pos.second) { // if there is remained charater this line
					text[nowline].erase(text[nowline].begin() + cursor_pos.second - 1);
					// wprintw(win, "%d", cursor_pos.second);
					wmove(win, cursor_pos.first, cursor_pos.second - 1);
					wdelch(win);
					cursor_pos.second--;
					wmove(win, cursor_pos.first, cursor_pos.second);
					wrefresh(win);
				} else { // we need to go upward a line
					if (cursor_pos.first == 0) {
						if (stline) {
							text.erase(text.begin() + nowline);
							move_downward_a_line();
							cursor_pos.first = 0;
							cursor_pos.second = text[stline - 1].length();
							stline--;
						}
					} else {
						text.erase(text.begin() + nowline);
						cursor_pos.first--;
						cursor_pos.second = text[nowline - 1].length();
						wmove(win, cursor_pos.first, cursor_pos.second);
						wrefresh(win);
					}
				}
			} else {
				if (cc == '\n') {
					text.push_back("");
					nowline = stline + cursor_pos.first;
					for (int i = cursor_pos.first; i < min(maxline, (int)text.size() - stline); i++) {
						wmove(win, i, 0);
						for (int j = 0; j < text[stline + i].length(); j++) wdelch(win);
					}
					for (int i = text.size() - 1; i > nowline + 1; i--) text[i] = text[i - 1];
					if (cursor_pos.second < text[nowline].length()) text[nowline + 1] = text[nowline].substr(cursor_pos.second);
					else text[nowline + 1] = "";
					string tmp = text[nowline].substr(0, cursor_pos.second);
					text[nowline] = tmp;
					if (cursor_pos.first == maxline - 1) {
						move_upward_a_line();
						stline++;
						wmove(win, maxline - 2, 0);
						wprintw(win, "%s", text[stline + maxline - 2].c_str());
						wmove(win, maxline - 1, 0);
						wprintw(win, "%s", text[stline + maxline - 1].c_str());
						cursor_pos.first = maxline - 1;
						cursor_pos.second = 0;
						wmove(win, cursor_pos.first, cursor_pos.second);
						wrefresh(win);
					} else {
						for (int i = cursor_pos.first; i < min(maxline, (int)text.size() - stline); i++) {
							wmove(win, i, 0);
							wprintw(win, "%s", text[stline + i].c_str());
						}
						cursor_pos.first++; cursor_pos.second = 0;
						wmove(win, cursor_pos.first, cursor_pos.second);
						wrefresh(win);
					}
				} else {
					text[nowline].insert(cursor_pos.second, 1, cc);
					cursor_pos.second++;
					wmove(win, cursor_pos.first, 0);
					wprintw(win, "%s", text[nowline].c_str());
					wmove(win, cursor_pos.first, cursor_pos.second);
					wrefresh(win);
				}
			}
		}
		cc = getch();
	}
	if (cc == ':') mode_type = 2;
	if (cc == 27) mode_type = 0;
	return;
}
