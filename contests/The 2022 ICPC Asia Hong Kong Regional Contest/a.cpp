#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
vector <int> G[maxn];
int n, f[maxn];
void dfs(int u)
{
	f[u] = 0;
	int mx = 0, mxx = 0;
	for (int to:G[u]) {
		dfs(to);
		if (f[to] > mx) mxx = mx, mx = f[to];
		else mxx = max(mxx, f[to]);
	}
	f[u] = max(mx, mxx + 1);
}
int main()
{
	int T; scanf("%d", &T);

	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i <= n; i++) G[i].clear();
		for (int i = 1; i <= n; i++) {
			int x; scanf("%d", &x);
			G[x].push_back(i);
		}
		dfs(1);
		printf("%d\n", f[1]);
	}
}
