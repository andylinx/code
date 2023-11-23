#include "virable.h"
using std::max;
void normal_state()
{
	char cc = getch();
	int flag = 0;

	while (cc != 'i' && cc != ':') {
		changed = 1;
		if (cc >= 2 && cc <= 5)
			move(cc);
		if (cc == '0') {
			cur.y = 0;
			st.y = 0;
			print();
		}
		if (cc == '$') {
			cur.y = text[st.x + cur.x].length();
			st.y = max(0, cur.y - mx.y);
			cur.y = min(mx.y, cur.y);
			print();
		}
		if (cc == 'w') {
			int flag = 0;
			if (text.size()) {
				for (int i = now.y; i < text[now.x].length(); i++) {
					if (text[now.x][i] == ' ') flag = -1;
					if (flag == -1 && text[now.x][i] != ' ') {
						flag = i;
						break;
					}
				}
			}
			if (flag > 0) {
				now.y = flag;
				cur.y = min(mx.y, now.y);
				st.y = max(0, now.y - cur.y);
				print();
			} else {
				if (now.x == text.size() - 1) {
					now.y = text[now.x].length();
					cur.y = min(mx.y, now.y);
					st.y = max(0, now.y - cur.y);
				} else {
					if (now.x < text.size()) {
						now.x++;
						if (cur.x == mx.x) st.x++;
						else cur.x++;
						cur.y = 0;
					}
				}
				print();
			}
		}
		if (cc == 'b') {
			int flag = 0;
			if (!now.y) {
				if (!now.x) {
					cc = getch();
					continue;
				}
				if (now.x) {
					now.x--, now.y = text[now.x].length();
					if (!cur.x) st.x--;
					else cur.x--;
				}
			}
			for (int i = now.y - 1; i > 0; i--) {
				if (text[now.x][i] != ' ' && text[now.x][i - 1] == ' ') {
					flag = i;
					break;
				}
			}

			now.y = flag;
			cur.y = min(mx.y, now.y);
			st.y = max(0, now.y - cur.y);
			print();
		}
		if (cc == 'd') {
			if (!flag) {
				flag = 1;
			} else if (flag == 1) {
				flag = 0;
				now = st + cur;
				text.erase(text.begin() + now.x);
				cur.y = st.y = 0;
				if (now.x == text.size()) {
					if (!cur.x) st.x--;
					else cur.x--;
				}
				print();
			}
		} else {
			flag = 0;
		}
		cc = getch();
	}
	if (cc == 'i') mode_type = 1;
	if (cc == 27) exit_flag = 1;
	if (cc == ':') mode_type = 2;
	print();
	return;
}
