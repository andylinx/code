#include "virable.h"
#include <trie.h>
using Lexicon = trie::trie_map<char, trie::SetCounter>;
Lexicon Dic;
void init_word_completion() // initialize the word completion
{
	std::ifstream words;

	words.open("words_alpha.txt");
	string ss;
	while (getline(words, ss))
		Dic.insert(ss);
}
void insert_mode()
{
	char cc = getch();

	if (!text.size()) text.push_back("");
	while (cc != 27) {
		changed = 1;
		if (cc >= 2 && cc <= 5) {
			move(cc);       // only move the cursor
		} else {
			now = st + cur; // calculate the position of the absolute position in the text
			if (cc == 7) {  // erase the last character of the current cursor position
				if (now.y) {
					text[now.x].erase(text[now.x].begin() + now.y - 1);
					if (!cur.y) st.y--, print();
					else cur.y--, print();
				} else {
					if (now.x) {
						if (cur.x) cur.x--;
						else st.x--;
						cur.y = min(mx.y, (int)text[now.x - 1].length());
						if (text[now.x - 1].length() > mx.y) st.y = text[now.x - 1].length() - mx.y;
						else st.y = 0;
						text[now.x - 1] += text[now.x];
						for (int i = now.x; i < text.size() - 1; i++)
							text[i] = text[i + 1];
						text.erase(text.begin() + text.size() - 1);
					}
					print();
				}
				cc = getch();
				continue;
			}
			if (cc == '\n') { // pay attention to the scenario when the cursor is in the middle of a line
				text.push_back("");
				for (int i = text.size() - 1; i > now.x + 1; i--)
					text[i] = text[i - 1];
				if (now.y < text[now.x].length())
					text[now.x + 1] = text[now.x].substr(now.y);
				else text[now.x + 1] = "";
				string tmp = text[now.x].substr(0, now.y);
				text[now.x] = tmp;
				if (cur.x == mx.x)
					st.x++;
				else cur.x++;
				st.y = 0;
				cur.y = 0;

				print();
				cc = getch();
				continue;
			}
			if (cc == '\t') {
				wdeleteln(info);
				wmove(info, 0, 0);
				int stpos = 0;
				for (stpos = now.y; stpos > 0; stpos--)
					if (text[now.x][stpos - 1] == ' ')
						break;
				vector <string> list_of_word[21];
				int nowpage = 0;
				if (stpos || (text[now.x][stpos] >= 'a' && text[now.x][stpos] <= 'z')) {
					string pre = text[now.x].substr(stpos, now.y - stpos);
					auto it = Dic.find_prefix(pre);
					int num = 0, nowpos = 0, pages;
					for (pages = 1; pages <= 20; pages++) { // only show the first 200 pages of the dictionary which must be enough.
						list_of_word[pages].clear();
						nowpos = 0; num = 0;
						for (; it != Dic.end(); ++it) {
							if (num == 9) break;
							num++;
							if (nowpos + it.key().length() + 2 >= mx.y) break;
							nowpos += it.key().length() + 2;
							list_of_word[pages].push_back(it.key());
						}
						if (it == Dic.end()) break;
					}
					while (1) {
						if (cc == 3) {
							if (nowpage) nowpage--;
						} else {
							if (nowpage < pages) nowpage++;
						}
						if (nowpage > 20) {
							cc = getch();
							break;
						}
						wdeleteln(info);
						wmove(info, 0, 0);
						nowpos = 0;
						for (int i = 1; i <= list_of_word[nowpage].size(); i++) {
							wmove(info, 0, nowpos);
							wprintw(info, "%d.%s", i, list_of_word[nowpage][i - 1].c_str());
							nowpos += 3 + list_of_word[nowpage][i - 1].length();
						}
						wrefresh(info);
						cc = getch();
						if (cc < 2 || cc > 3) break;
					}
				}
				if (cc == 27) {
					cc = getch();
					print();
					continue;
				}
				if (cc >= '1' && cc <= '0' + list_of_word[nowpage].size()) {
					string temp;
					now = st + cur;
					for (int i = 0; i < stpos; i++) temp.push_back(text[now.x][i]);
					for (int i = 0; i < list_of_word[nowpage][cc - '0' - 1].length() - 1; i++)
						temp.push_back(list_of_word[nowpage][cc - '0' - 1][i]);
					for (int i = now.y; i < text[now.x].length(); i++) temp.push_back(text[now.x][i]);
					text[now.x] = temp;
					cur.y += list_of_word[nowpage][cc - '0' - 1].length() - now.y + stpos - 1;
					if (cur.y > mx.y) st.y += cur.y - mx.y, cur.y = mx.y;
					print();
					cc = getch();
					continue;
				}
				if (cc == '\t') { // if you want to interpret tab as 4 spaces, you should type it twice
					text[now.x].insert(now.y, 4, ' ');
					now.y += 4;
					cur.y = min(mx.y, now.y);
					st.y = max(0, now.y - mx.y);
				}
				print();
			} else {
				text[now.x].insert(now.y, 1, cc);
				if (cur.y == mx.y) st.y++;
				else cur.y++;
				print();
			}
		}
		cc = getch();
	}
	if (cc == 27) mode_type = 0;
	print();
	return;
}
