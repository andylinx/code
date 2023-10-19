#include <bits/stdc++.h>
using namespace std;
int main()
{
	freopen("a.in", "w", stdout);
	srand(clock() + 2626);
	int n = 99, q = 5e4;
	printf("%d %d\n", n, q);
	for (int i = 1; i <= n; i++) printf("%d ", rand());
	printf("\n");
	for (int i = 1; i <= q; i++) {
		string l, r;
		l.clear(); r.clear();
		for (int j = 1; j <= n; j++) l.push_back('0' + (rand() & 1)), r.push_back('0' + (rand() & 1));
		// cerr << l << endl;
		if (l > r) swap(l, r);
		if (rand() & 1) cout << 2 << " " << l << endl << r << endl;
		else cout << 1 << " " << l << endl << r << " " << rand() << endl;
	}
	return 0;
}
