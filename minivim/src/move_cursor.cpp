void move(char cc)
{
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
	}
}
