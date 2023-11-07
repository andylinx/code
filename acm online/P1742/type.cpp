#include <bits/stdc++.h>
using namespace std;
string type, s;
int n;
void dfs(int l, int r)
{
	// cerr << l << " " << r << endl;
	if (!l && r == n - 1) return;
	if (r + 1 < n) {
		if (s[r + 1] == ')') {
			int i;
			for (i = l - 1; i >= 0; i--) {
				if (s[i] == '*') printf("pointer to ");
				if (s[i] == '(') break;
			}
			dfs(i, r + 1);
		} else {
			printf("array of ");
			dfs(l, r + 2);
		}
	} else if (l - 1 >= 0) {
		if (s[l - 1] == '*') {
			printf("pointer to ");
			dfs(l - 1, r);
		}
	}
}
int main()
{
	cin >> type >> s;
	n = s.length();
	for (int i = 0; i < n; i++) if (s[i] != '[' && s[i] != ']' && s[i] != '*' && s[i] != '(' && s[i] != ')') printf("%c", s[i]);
	printf(" is ");
	int lpos = 2000, rpos = 0;
	for (int i = 0; i < n; i++) if (s[i] >= 'a' && s[i] <= 'z') lpos = min(lpos, i), rpos = max(rpos, i);
	dfs(lpos, rpos);
	cout << type;
	return 0;
}
