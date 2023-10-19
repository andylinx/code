#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
const int maxm = 4e6 + 5;
int n, m;
struct Line {
	int l, r, id;
} a[maxn];
bool cmp(Line x, Line y)
{
	return x.l > y.l;
}
vector <int> G[maxm];
int ncnt = 1;
void newpoint()
{
	ncnt++; G[ncnt].clear();
	ncnt++; G[ncnt].clear();
}
void add(int x, int y)
{
	// printf("%d %d\n", x, y);
	G[x].push_back(y);
	x ^= 1; y ^= 1;
	G[y].push_back(x);
}
int c[maxn], gs;
int tr[maxn];
int lowbit(int x)
{
	return x & (-x);
}
void query(int x, int i)
{
	while (x) {
		if (tr[x]) add(i << 1 | 1, tr[x]);
		x -= lowbit(x);
	}
}
void modify(int x, int i)
{
	while (x <= gs) {
		newpoint();
		add(ncnt, i << 1);
		if (tr[x]) add(ncnt, tr[x]);
		tr[x] = ncnt;
		x += lowbit(x);
	}
}
int dfn[maxm], low[maxm], in[maxm], st[maxm], top;
int col[maxm], dfstime, colcnt;
void tarjan(int u)
{
	dfn[u] = low[u] = ++dfstime;
	st[++top] = u; in[u] = 1;
	for (int to:G[u])
		if (!dfn[to]) {
			tarjan(to);
			low[u] = min(low[u], low[to]);
		} else if (in[to]) {
			low[u] = min(low[u], dfn[to]);
		}
	if (low[u] == dfn[u]) {
		int v;
		colcnt++;
		do{
			v = st[top--];
			in[v] = 0;
			col[v] = colcnt;
		} while (v != u);
	}
}

int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].l, &a[i].r), a[i].id = i;
		sort(a + 1, a + n + 1, cmp);
		ncnt = 1;
		for (int i = 1; i <= n; i++)
			newpoint();
		for (int i = 1; i <= m; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			// printf("[%d %d]\n", x, y);
			add(x << 1, y << 1 | 1);
		}
		for (int i = 1; i <= n; i++) c[i] = a[i].l;
		sort(c + 1, c + n + 1);
		gs = unique(c + 1, c + n + 1) - c - 1;
		for (int i = 1; i <= gs; i++) tr[i] = 0;
		for (int i = 1; i <= n; i++) {
			int lp = lower_bound(c + 1, c + gs + 1, a[i].l) - c;
			int rp = upper_bound(c + 1, c + gs + 1, a[i].r) - c - 1;
			query(rp, a[i].id); modify(lp, a[i].id);
		}
		dfstime = colcnt = 0;
		for (int i = 1; i <= ncnt; i++) dfn[i] = low[i] = in[i] = 0;
		for (int i = 2; i <= ncnt; i++)
			if (!dfn[i]) tarjan(i);
		int flag = 0;
		for (int i = 2; i <= ncnt; i++)
			if (col[i] == col[i ^ 1]) {
				flag = 1;
				break;
			}
		if (flag) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
