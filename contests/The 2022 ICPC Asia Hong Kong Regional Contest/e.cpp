#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 5;
int n, k;
int a[maxn], gs[maxn];
vector <int> pos[maxn];
int tag[maxn << 2], cnt[maxn << 2], mn[maxn << 2];
void pushup(int now)
{
	mn[now] = min(mn[now << 1], mn[now << 1 | 1]);
	if (mn[now << 1] == mn[now << 1 | 1])
		cnt[now] = cnt[now << 1] + cnt[now << 1 | 1];
	if (mn[now << 1] < mn[now << 1 | 1])
		cnt[now] = cnt[now << 1];
	if (mn[now << 1] > mn[now << 1 | 1])
		cnt[now] = cnt[now << 1 | 1];
}
void build(int now, int l, int r)
{
	if (l == r) {
		cnt[now] = 1;
		return;
	}
	int mid = l + r >> 1;
	build(now << 1, l, mid);
	build(now << 1 | 1, mid + 1, r);
	pushup(now);
}
void pushdown(int now)
{
	if (!tag[now]) return;
	tag[now << 1] += tag[now];
	tag[now << 1 | 1] += tag[now];
	mn[now << 1] += tag[now];
	mn[now << 1 | 1] += tag[now];
	tag[now] = 0;
	return;
}
void modify(int now, int l, int r, int L, int R, int v)
{
	// cerr << l << " " << r << " " << tag[now] << endl;

	if (l >= L && r <= R) {
		tag[now] += v;
		mn[now] += v;
		return;
	}
	int mid = l + r >> 1;

	pushdown(now);
	if (L <= mid) modify(now << 1, l, mid, L, R, v);
	if (mid < R) modify(now << 1 | 1, mid + 1, r, L, R, v);
	// cerr << mn[now << 1] << " " << mn[now << 1 | 1] << endl;
	pushup(now);
	// cerr << now << " " << l << " " << r << " " << mn[now << 1] << " " << mn[now << 1 | 1] << " " << mn[now] << endl;
}
int nowgs[maxn];
int main()
{
	// freopen("a.in", "r", stdin);
	scanf("%d%d", &n, &k);
	// n = 1e6; k = 1;
	for (int i = 1; i <= 1e6; i++) pos[i].push_back(0);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		// a[i] = i;
		gs[a[i]]++;
		pos[a[i]].push_back(i);
	}
	for (int i = 1; i <= 1e6; i++) pos[i].push_back(n + 1);
	build(1, 1, n);
	for (int i = 1; i <= 1e6; i++)
		if (gs[i] >= k)
			// cerr << pos[i][k + 1] - 1 << endl;
			modify(1, 1, n, pos[i][k], pos[i][k + 1] - 1, 1);

	// modify(1, 1, n, 1, n, 1);
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		if (!mn[1]) ans += n - cnt[1];
		else ans += n;
		if (nowgs[a[i]] + k <= gs[a[i]])
			modify(1, 1, n, pos[a[i]][nowgs[a[i]] + k], pos[a[i]][nowgs[a[i]] + k + 1] - 1, -1);
		nowgs[a[i]]++;
		if (nowgs[a[i]] + k <= gs[a[i]])
			modify(1, 1, n, pos[a[i]][nowgs[a[i]] + k], pos[a[i]][nowgs[a[i]] + k + 1] - 1, 1);
	}

	printf("%lld\n", 1ll * n * (n + 1) / 2 - ans);
	return 0;
}
