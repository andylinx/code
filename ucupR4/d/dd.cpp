# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 4e5 + 5;
const ll mod = 998244353;
const ll inv6 = (mod + 1) / 6;
const int inf = 0x3f3f3f3f;
int n, q;
ll f[4][102][2], a[102], a2[102], a3[102];
int lim[102];
void add(ll &x, ll y)
{
	x += y;
	while (x > mod) x -= mod;
}
vector <ll> calc()
{
	memset(f, 0, sizeof(f));
	f[0][0][1] = 1;
	for (int i = 1; i <= n; i++) {
		// 0
		for (int d = 0; d < 4; d++)
			add(f[d][i][0], f[d][i - 1][0]);
		add(f[0][i][0], f[0][i - 1][0]);
		add(f[1][i][0], f[1][i - 1][0] + f[0][i - 1][0] * a[i] % mod);
		add(f[2][i][0], f[2][i - 1][0] + 2 * f[1][i - 1][0] * a[i] % mod + a2[i] * f[0][i - 1][0] % mod);
		add(f[3][i][0], f[3][i - 1][0] + 3 * a[i] * f[2][i - 1][0] % mod + 3 * a2[i] * f[1][i - 1][0] % mod + a3[i] * f[0][i - 1][0] % mod);
		// 1
		if (!lim[i]) {
			for (int d = 0; d < 4; d++)
				add(f[d][i][1], f[d][i - 1][1]);
		} else {
			for (int d = 0; d < 4; d++)
				add(f[d][i][0], f[d][i - 1][1]);
			// cerr<<f[0][1][0]<<endl;
			add(f[0][i][1], f[0][i - 1][1]);
			add(f[1][i][1], f[1][i - 1][1] + f[0][i - 1][1] * a[i] % mod);
			add(f[2][i][1], f[2][i - 1][1] + 2 * f[1][i - 1][1] * a[i] % mod + a2[i] * f[0][i - 1][1] % mod);
			add(f[3][i][1], f[3][i - 1][1] + 3 * a[i] * f[2][i - 1][1] % mod + 3 * a2[i] * f[1][i - 1][1] % mod + a3[i] * f[0][i - 1][1] % mod);
		}
	}
	vector <ll> ans;
	ans.resize(4);
	for (int d = 0; d < 4; d++)
		ans[d] = (f[d][n][0] + f[d][n][1]) % mod;
	// for(int i=1;i<=n;i++) printf("%d",lim[i]);
	// printf("[%lld]\n",ans[1]);
	return ans;
}
struct oper {
	string	l, r;
	int	opt;
	ll	x;
} Q[maxn];
string pos[maxn];
int cnt;
struct seg {
	ll		tag;
	vector <ll>	g;
} tr[maxn << 2];
vector <ll> delta[maxn], res[maxn], resk[maxn];
void pushup(int now)
{
	tr[now].g.resize(4);
	for (int d = 0; d < 4; d++)
		tr[now].g[d] = (tr[now << 1].g[d] + tr[now << 1 | 1].g[d]) % mod;
}
void build(int now, int l, int r)
{
	// cerr<<now<<" "<<l<<" "<<r<<endl;
	if (l == r) {
		tr[now].g = delta[l];
		return;
	}
	int mid = l + r >> 1;
	build(now << 1, l, mid);
	build(now << 1 | 1, mid + 1, r);
	pushup(now);
}
ll calc_ans(vector <ll> tmp)
{
	ll ans = tmp[1] * tmp[1] % mod * tmp[1] % mod;

	ans = (ans - 3 * tmp[2] * tmp[1] % mod + mod) % mod;
	ans = (ans + 2 * tmp[3]) % mod;
	return ans;
}
void work(int now, ll t)
{
	vector <ll> tmp;

	tmp = tr[now].g;
	add(tr[now].g[1], tmp[0] * t % mod);
	add(tr[now].g[2], 2 * tmp[1] * t % mod + tmp[0] * t % mod * t % mod);
	add(tr[now].g[3], 3 * tmp[2] * t % mod + 3 * tmp[1] * t % mod * t % mod + tmp[0] * t % mod * t % mod * t % mod);
}
void pushdown(int now)
{
	if (!tr[now].tag) return;
	ll t = tr[now].tag; tr[now].tag = 0;
	int ls = now << 1, rs = now << 1 | 1;
	work(ls, t); work(rs, t);
	tr[ls].tag = (tr[ls].tag + t) % mod;
	tr[rs].tag = (tr[rs].tag + t) % mod;
}
void modify(int now, int l, int r, int L, int R, ll x)
{
	// cerr<<L<<" "<<R<<endl;
	// cerr<<x<<endl;
	if (l >= L && r <= R) {
		tr[now].tag += x;
		vector <ll> tmp;
		tmp = tr[now].g;
		ll t = x;
		add(tr[now].g[1], tmp[0] * t % mod);
		add(tr[now].g[2], 2 * tmp[1] * t % mod + tmp[0] * t % mod * t % mod);
		add(tr[now].g[3], 3 * tmp[2] * t % mod + 3 * tmp[1] * t % mod * t % mod + tmp[0] * t % mod * t % mod * t % mod);
		return;
	}
	pushdown(now);
	int mid = l + r >> 1;
	if (L <= mid) modify(now << 1, l, mid, L, R, x);
	if (mid < R) modify(now << 1 | 1, mid + 1, r, L, R, x);
	pushup(now);
}
vector <ll> merge(vector<ll> x, vector <ll> y)
{
	vector <ll> tmp;

	tmp.resize(4);
	for (int d = 0; d < 4; d++) tmp[d] = (x[d] + y[d]) % mod;
	return tmp;
}
vector <ll> query(int now, int l, int r, int L, int R)
{
	if (l >= L && r <= R) return tr[now].g;
	pushdown(now);
	int mid = l + r >> 1;
	if (L > mid) return query(now << 1 | 1, mid + 1, r, L, R);
	if (R <= mid) return query(now << 1, l, mid, L, R);
	return merge(query(now << 1, l, mid, L, R), query(now << 1 | 1, mid + 1, r, L, R));
}
string add1(string s)
{
	string ss = s;

	for (int i = n - 1; i >= 0; i--) {
		if (ss[i] == '0') {
			ss[i] = '1';
			return ss;
		}
		ss[i] = '0';
	}
	return ss;
}
string del1(string s)
{
	string ss = s;

	for (int i = n - 1; i >= 0; i--) {
		if (ss[i] == '1') {
			ss[i] = '0';
			return ss;
		}
		ss[i] = '1';
	}
	return ss;
}
int main()
{
	std::ios::sync_with_stdio(false);
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	cin >> n >> q;
	for (int i = n + 1; i >= 2; i--) cin >> a[i], a2[i] = a[i] * a[i] % mod, a3[i] = a2[i] * a[i] % mod;
	n++;
	for (int i = 1; i <= q; i++) {
		cin >> Q[i].opt;
		cin >> Q[i].l >> Q[i].r;
		Q[i].l = "0" + Q[i].l;
		Q[i].r = "0" + Q[i].r;
		Q[i].l[0] = Q[i].r[0] = '0';
		pos[++cnt] = Q[i].l;
		pos[++cnt] = Q[i].r;
		pos[++cnt] = add1(Q[i].r);
		if (Q[i].opt == 1) cin >> Q[i].x;
	}
	string sss;
	for (int i = 0; i < n; i++) sss.push_back('0');
	pos[++cnt] = sss;
	sort(pos + 1, pos + cnt + 1);
	cnt = unique(pos + 1, pos + cnt + 1) - pos - 1;
	// for (int i = 1; i <= cnt; i++)
	// 	cerr << pos[i] << endl;
	for (int i = 2; i <= cnt; i++) {
		string ss = del1(pos[i]);
		for (int j = 1; j <= n; j++)
			lim[j] = ss[j - 1] - '0';
		resk[i] = calc();
	}
	delta[1] = resk[2];
	for (int i = 2; i < cnt; i++) {
		vector <ll> tmp;
		tmp.resize(4);
		for (int d = 0; d < 4; d++) tmp[d] = (resk[i + 1][d] - resk[i][d] + mod) % mod;
		delta[i] = tmp;
	}
	build(1, 1, cnt - 1);
	for (int i = 1; i <= q; i++) {
		int posl = lower_bound(pos + 1, pos + cnt + 1, Q[i].l) - pos;
		int posr = lower_bound(pos + 1, pos + cnt + 1, Q[i].r) - pos;
		if (Q[i].opt == 1) {
			modify(1, 1, cnt - 1, posl, posr, Q[i].x);
		} else {
			vector <ll> tmp;
			tmp = query(1, 1, cnt - 1, posl, posr);
			printf("%lld\n", (calc_ans(tmp) + mod) % mod * inv6 % mod);
		}
	}
	return 0;
}
