#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
const int maxn = 6e5 + 5;
int n, m, du[maxn], ex[maxn], ey[maxn];
int tag[maxn], rk[maxn], id[maxn];
vector <int> G[maxn], GG[maxn];
bool cmp(int x, int y)
{
	if (du[x] != du[y]) return du[x] < du[y];
	return x < y;
}
int main()
{
	int T; scanf("%d", &T);

	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) du[i] = 0, G[i].clear(), GG[i].clear();
		for (int i = 1; i <= m; i++) {
			int x, y; scanf("%d%d", &x, &y);
			G[x].push_back(y); G[y].push_back(x);
			du[x]++; du[y]++; ex[i] = x; ey[i] = y;
		}
		for (int i = 1; i <= m; i++) {
			int x = ex[i], y = ey[i];
			if (du[x] < du[y] || (du[x] == du[y] && x < y))
				GG[x].push_back(y);
			else GG[y].push_back(x);
		}
		for (int i = 1; i <= n; i++) id[i] = i;
		sort(id + 1, id + n + 1, cmp);
		for (int i = 1; i <= n; i++) rk[id[i]] = i;
		ll e3 = 0, e4 = 0, ans = 0;
		for (int i = 1; i <= n; i++) {
			for (int v:GG[i]) tag[v] = 1;
			for (int v:GG[i]) for (int w:GG[v]) if (tag[w]) e3++;
			for (int v:GG[i]) tag[v] = 0;
		}
		for (int i = 1; i <= n; i++) {
			for (int u:G[i]) for (int v:GG[u]) if (rk[v] > rk[i]) e4 = (e4 + tag[v]++) % mod;
			for (int u:G[i]) for (int v:GG[u]) if (rk[v] > rk[i]) tag[v] = 0;
		}
		ll res = 0;
		for (int i = 1; i <= n; i++) res += du[i] * (du[i] - 1) / 2;
		// cerr << e3 << " " << e4 << " " << res << endl;
		printf("%lld\n", (3 * e3 + e4 + 1ll * (n + m - 3) * m % mod + res) % mod);
	}
	return 0;
}
