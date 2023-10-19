#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int MAXN = 1e5 + 5;
const int MAXP = MAXN * 18 * 2 + 5;

int n, pcnt;
array<int, 2> p[MAXN];
vector<int> g[MAXP];

int dfn[MAXP], low[MAXP], curdfn, clr[MAXP], ccnt;
stack<int> sta; bool insta[MAXP];
void tarjan(int u)
{
	dfn[u] = low[u] = ++curdfn;
	sta.push(u); insta[u] = 1;
	for (int v: g[u]) {
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (insta[v]) low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		++ccnt;
		int v; do{
			v = sta.top(); sta.pop();
			insta[v] = 0; clr[v] = ccnt;
		}while (v != u);
	}
}

int new_Node(void)
{
	int u = ++pcnt;

	g[u << 1].clear();
	g[u << 1 | 1].clear();
	return u;
}
void add_edge(int u, int v)
{
	printf("%d %d\n", u, v);
	g[u].emplace_back(v);
	g[v ^ 1].emplace_back(u ^ 1);
}

int dsc[MAXN], dcnt;
int tree[MAXN];

#define lowbit(x) ((x) & -(x))

void insert(int x, int i)
{
	printf("[%d %d]\n", x, i);
	while (x <= dcnt) {
		int u = new_Node();
		add_edge(u << 1 | 1, i << 1);
		if (tree[x]) add_edge(u << 1 | 1, tree[x] << 1 | 1);
		tree[x] = u;
		x += lowbit(x);
	}
}
void query(int x, int i)
{
	while (x) {
		if (tree[x]) add_edge(i << 1 | 1, tree[x] << 1 | 1);
		x ^= lowbit(x);
	}
}

void solve(void)
{
	int m;

	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%d%d", &p[i][0], &p[i][1]);

	pcnt = 0;
	for (int i = 1; i <= n; ++i)
		new_Node();

	for (int i = 1; i <= m; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		// printf("[%d %d]\n", u, v);
		add_edge(u << 1, v << 1 | 1);
	}

	dcnt = 0;
	for (int i = 1; i <= n; ++i)
		dsc[++dcnt] = p[i][0];
	sort(dsc + 1, dsc + dcnt + 1);
	dcnt = unique(dsc + 1, dsc + dcnt + 1) - dsc - 1;

	vector<int> id(n);
	iota(id.begin(), id.end(), 1);
	sort(id.begin(), id.end(), [&] (int i, int j){
		return p[i][0] > p[j][0];
	});

	fill(tree + 1, tree + dcnt + 1, 0);
	for (int i: id) {
		int l = lower_bound(dsc + 1, dsc + dcnt + 1, p[i][0]) - dsc;
		int r = upper_bound(dsc + 1, dsc + dcnt + 1, p[i][1]) - dsc - 1;
		query(r, i);
		insert(l, i);
	}

	fill(dfn + 1, dfn + pcnt * 2 + 2, 0);
	curdfn = ccnt = 0;
	for (int i = 2; i <= pcnt * 2 + 1; ++i)
		if (!dfn[i]) tarjan(i);

	for (int i = 2; i <= pcnt * 2 + 1; ++i)
		if (clr[i] == clr[i ^ 1]) {
			printf("NO\n");
			return;
		}
	printf("YES\n");
}

int main(void)
{
	freopen("a.in", "r", stdin);
	freopen("a.ans", "w", stdout);
	int T;

	scanf("%d", &T);
	while (T--) solve();
	return 0;
}
