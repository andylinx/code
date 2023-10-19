// This Code was made by Chinese_zjc_.
#include <bits/stdc++.h>
// #define debug
const int MOD = 998244353;
struct mint {
	unsigned v;
	mint(unsigned v_ = 0) : v(v_)
	{
	}
	mint operator-() const
	{
		return v ? MOD - v : *this;
	}
	mint &operator+=(const mint &X)
	{
		return (v += X.v) >= MOD ? v -= MOD : v, *this;
	}
	mint &operator-=(const mint &X)
	{
		return (v += MOD - X.v) >= MOD ? v -= MOD : v, *this;
	}
	mint &operator*=(const mint &X)
	{
		return v = 1llu * v * X.v % MOD, *this;
	}
	mint &operator/=(const mint &X)
	{
		return *this *= X.inv();
	}
	mint pow(long long B) const
	{
		B %= MOD - 1;
		if (B < 0)
			B += MOD - 1;
		mint res = 1, A = *this;
		while (B) {
			if (B & 1)
				res *= A;
			B >>= 1;
			A *= A;
		}
		return res;
	}
	mint inv() const
	{
		return pow(MOD - 2);
	}
	friend mint operator+(const mint &A, const mint &B)
	{
		return mint(A) += B;
	}
	friend mint operator-(const mint &A, const mint &B)
	{
		return mint(A) -= B;
	}
	friend mint operator*(const mint &A, const mint &B)
	{
		return mint(A) *= B;
	}
	friend mint operator/(const mint &A, const mint &B)
	{
		return mint(A) /= B;
	}
	friend std::istream &operator>>(std::istream &A, mint &B)
	{
		return A >> B.v;
	}
	friend std::ostream &operator<<(std::ostream &A, const mint &B)
	{
		return A << B.v;
	}
	friend bool operator==(const mint &A, const mint &B)
	{
		return A.v == B.v;
	}
	explicit operator bool() const {
		return v;
	}
} a[50005], x[50005], tag[1 << 18], fact[4], ifact[4];
int n, m, q, opt[50005];
std::string l[50005], r[50005];
std::vector<std::string> app;
std::string add(std::string &X)
{
	for (int i = n; i--;)
		if (X[i] == '1')
			X[i] = '0';
		else
			return ++X[i], X;
	assert(false);
}
struct node {
	mint v[4];
	friend node operator+(const node &A, const node &B)
	{
		node res;
		res.v[0] = A.v[0] + B.v[0];
		res.v[1] = A.v[1] + B.v[1];
		res.v[2] = A.v[2] + A.v[1] * B.v[1] + B.v[2];
		res.v[3] = A.v[3] + A.v[2] * B.v[1] + A.v[1] * B.v[2] + B.v[3];
		return res;
	}
	node &operator+=(const node &X)
	{
		return *this = *this + X;
	}
	node &operator+=(const mint &X)
	{
		v[3] += v[2] * (v[0] - 2) * X +
			v[1] * (v[0] - 1) * (v[0] - 2) * ifact[2] * X * X +
			v[0] * (v[0] - 1) * (v[0] - 2) * ifact[3] * X * X * X;
		v[2] += v[1] * (v[0] - 1) * X +
			v[0] * (v[0] - 1) * ifact[2] * X * X;
		v[1] += v[0] * X;
		return *this;
	}
} t[1 << 18], dp[105][2][2];
node calc(std::string L, std::string R)
{
	dp[0][0][0] = { 1, 0, 0, 0 };
	dp[0][1][0] = { 1, 0, 0, 0 };
	dp[0][0][1] = { 0, 0, 0, 0 };
	dp[0][1][1] = { 0, 0, 0, 0 };
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j != 2; ++j)
			for (int k = 0; k != 2; ++k) {
				dp[i][j][k] = { 0, 0, 0, 0 };
				for (int l = (j ? L[n - i] - '0' : 0); l <= (k ? R[n - i] - '0' : 1); ++l) {
					node tmp = dp[i - 1][j && l == L[n - i] - '0'][k && l == R[n - i] - '0'];
					if (l)
						tmp += a[i - 1];
					dp[i][j][k] += tmp;
				}
			}
	return dp[n][1][1];
}
#define lson (now << 1)
#define rson (lson | 1)
#define mid ((l + r) >> 1)
void pushdown(int now)
{
	if (mint &v = tag[now]) {
		t[lson] += v;
		t[rson] += v;
		tag[lson] += v;
		tag[rson] += v;
		v = 0;
	}
}
void pushup(int now)
{
	t[now] = t[lson] + t[rson];
}
void build(int now = 1, int l = 0, int r = m)
{
	if (r - l == 1) {
		t[now] = calc(app[l], app[r]);
		return;
	}
	pushdown(now);
	build(lson, l, mid);
	build(rson, mid, r);
	pushup(now);
}
void add(int L, int R, mint v, int now = 1, int l = 0, int r = m)
{
	if (r <= L || R <= l)
		return;
	if (L <= l && r <= R) {
		t[now] += v;
		tag[now] += v;
		return;
	}
	pushdown(now);
	add(L, R, v, lson, l, mid);
	add(L, R, v, rson, mid, r);
	pushup(now);
}
node query(int L, int R, int now = 1, int l = 0, int r = m)
{
	if (r <= L || R <= l)
		return node();
	if (L <= l && r <= R)
		return t[now];
	pushdown(now);
	return query(L, R, lson, l, mid) + query(L, R, rson, mid, r);
}
signed main()
{
	freopen("a.in", "r", stdin);
	freopen("a.ans", "w", stdout);
	std::ios::sync_with_stdio(false);
	fact[0] = 1;
	for (int i = 1; i <= 3; ++i)
		fact[i] = fact[i - 1] * i;
	ifact[3] = fact[3].inv();
	for (int i = 3; i; --i)
		ifact[i - 1] = ifact[i] * i;
	std::cin >> n >> q;
	for (int i = 0; i != n; ++i)
		std::cin >> a[i];
	app.push_back('0' + std::string(n, '0'));
	app.push_back('1' + std::string(n, '0'));
	++n;
	for (int i = 1; i <= q; ++i) {
		std::cin >> opt[i] >> l[i] >> r[i];
		l[i].insert(l[i].begin(), '0');
		r[i].insert(r[i].begin(), '0');
		add(r[i]);
		app.push_back(l[i]);
		app.push_back(r[i]);
		if (opt[i] == 1)
			std::cin >> x[i];
	}
	std::sort(app.begin(), app.end());
	app.erase(std::unique(app.begin(), app.end()), app.end());
	m = app.size() - 1;
	build();
	for (int i = 1; i <= q; ++i) {
		int L = std::lower_bound(app.begin(), app.end(), l[i]) - app.begin(),
		    R = std::lower_bound(app.begin(), app.end(), r[i]) - app.begin();
		if (opt[i] == 1)
			add(L, R, x[i]);
		else
			std::cout << query(L, R).v[3] << '\n';
	}
	return 0;
}
