#include "virable.h"
void normal_state()
{
	char cc = getch();

	while (cc != 'i' && cc != 27) {
		if (cc >= 2 && cc <= 5)
			move(cc);
		if (cc == 'O') {
			cursor_pos.second = 0;
			wmove(win, cursor_pos.first, 0);
			wrefresh(win);
		}
		if (cc == '$') {
			cursor_pos.second = text[stline + cursor_pos.first].length();
			wmove(win, cursor_pos.first, cursor_pos.second);
			wrefresh(win);
		}
		if (cc == 'w') {
			int flag = 0;
			string ss = text[stline + cursor_pos.first];
			for (int i = cursor_pos.second + 1; i < text[stline + cursor_pos.first].length(); i++)
				if (ss[i] != ' ' && ss[i - 1] == ' ')
					flag = 1, cursor_pos.second = i;
		}
		if (cc == 'b') {
		}
		cc = getch();
	}
	if (cc == 'i') mode_type = 1;
	if (cc == 27) exit_flag = 1;
	return;
}
