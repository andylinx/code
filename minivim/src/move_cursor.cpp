void move(char cc)
{
	//move the cursor
	now = st + cur;
	if (cc == 2) {                  //down
		if (now.x == text.size() - 1) return;
		now.y = min((int)text[now.x + 1].length(), lst.y);
		cur.y = min(now.y, mx.y);
		st.y = now.y - cur.y;
		if (cur.x == mx.x) st.x++;
		else cur.x++;
		print(0);
	}
	if (cc == 3) {                  //up
		if (!now.x) return;
		now.y = min((int)text[now.x - 1].length(), lst.y);
		cur.y = min(now.y, mx.y);
		st.y = now.y - cur.y;
		if (!cur.x) st.x--;
		else cur.x--;
		print(0);
	}
	if (cc == 5) {                  // right
		if (now.x == text.size() - 1 && now.y == text[now.x].length()) return;
		if (now.y != text[now.x].length()) {
			if (cur.y == mx.y) st.y++;
			else cur.y++;
		} else {
			cur.y = 0;
			if (cur.x == mx.x) st.x++;
			else cur.x++;
		}
		print();
	}
	if (cc == 4) {                  //left
		if (!now.x && !now.y) return;
		if (now.y) {
			if (!cur.y) st.y--;
			else cur.y--;
		} else {
			now.y = text[now.x - 1].length();
			cur.y = min(now.y, mx.y);
			st.y = now.y - cur.y;
			cur.x--;
		}
		print();
	}
}
