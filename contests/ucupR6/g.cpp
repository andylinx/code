#include <bits/stdc++.h>
using namespace std;
const int maxn = 2005;
typedef long long ll;
const ll mod = 1e9 + 7;
int n, k;
ll A[maxn][maxn], C[maxn][maxn];
ll rnd[maxn], res[maxn], init[maxn];
int tag[maxn][maxn], wr[maxn];
ll ans[maxn][maxn];
ll qpow(ll a, ll b)
{
	ll res = 1;

	while (b) {
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}
ll Ans[maxn];
struct out {
	int	x, y;
	ll	z;
} tt[50];
bool cmp(out x, out y)
{
	if (x.x != y.x) return x.x < y.x;
	return x.y < y.y;
}
vector <int> xx[maxn];
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%lld", &A[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%lld", &C[i][j]), C[i][j] = (C[i][j] + mod) % mod;
	srand(time(0) + clock() + 20050302);
	for (int i = 1; i <= n; i++) rnd[i] = rand() % mod, init[i] = rnd[i];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			res[i] = (res[i] + rnd[j] * A[j][i] % mod) % mod;
	for (int i = 1; i <= n; i++) rnd[i] = res[i], res[i] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			res[i] = (res[i] + rnd[j] * C[j][i] % mod) % mod;
	vector <int> err;
	vector <pair<int, int> > pos;
	for (int i = 1; i <= n; i++) if (init[i] != res[i]) wr[i]++;
	for (int i = 1; i <= n; i++) rnd[i] = rand() % mod, init[i] = rnd[i], res[i] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			res[i] = (res[i] + rnd[j] * A[j][i] % mod) % mod;
	for (int i = 1; i <= n; i++) rnd[i] = res[i], res[i] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			res[i] = (res[i] + rnd[j] * C[j][i] % mod) % mod;
	for (int i = 1; i <= n; i++) if (init[i] != res[i] || wr[i]) err.push_back(i);
	assert(err.size() <= 12);
	for (int i = 1; i <= n; i++) rnd[i] = rand() % mod, init[i] = rnd[i], wr[i] = 0;
	for (int i = 1; i <= n; i++) {
		res[i] = 0;
		for (int j = 1; j <= n; j++)
			res[i] = (res[i] + A[i][j] * rnd[j]) % mod;
	}
	for (int i = 1; i <= n; i++) rnd[i] = res[i], res[i] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			res[i] = (res[i] + rnd[j] * C[i][j]) % mod;
	for (int i = 1; i <= n; i++) if (res[i] != init[i]) wr[i] = 1;
	for (int i = 1; i <= n; i++) rnd[i] = rand() % mod, init[i] = rnd[i];
	for (int i = 1; i <= n; i++) {
		res[i] = 0;
		for (int j = 1; j <= n; j++)
			res[i] = (res[i] + A[i][j] * rnd[j]) % mod;
	}
	for (int i = 1; i <= n; i++) rnd[i] = res[i], res[i] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			res[i] = (res[i] + rnd[j] * C[i][j]) % mod;
	for (int col:err)
		for (int i = 1; i <= n; i++)
			if (init[i] != res[i] || wr[i])
				pos.push_back({ i, col });
	int cnt = 0;
	for (auto p:pos) xx[p.second].push_back(p.first);
	assert(cnt <= 144);
	int gs = 0;
	for (int ii = 1; ii <= n; ii++) {
		if (!xx[ii].size()) continue;
		int cnt = 0;
		memset(ans, 0, sizeof(ans));
		for (int j:xx[ii])
			tag[j][ii] = ++cnt;
		cerr << cnt << endl;
		for (int j = 1; j <= n; j++) {
			ans[j][cnt + 1] = (ii == j);
			for (int k = 1; k <= n; k++) {
				if (!tag[k][ii]) ans[j][cnt + 1] = (ans[j][cnt + 1] + mod - A[j][k] * C[k][ii] % mod) % mod;
				else ans[j][tag[k][ii]] = A[j][k];
			}
		}
		for (int i = 1; i <= cnt; i++) {
			if (!ans[i][i]) {
				int j = i + 1;
				while (!ans[j][i] && j < n) j++;
				for (int k = 1; k <= cnt + 1; k++) swap(ans[i][k], ans[j][k]);
			}
			assert(ans[i][i]);
			ll inv = qpow(ans[i][i], mod - 2);
			for (int j = i + 1; j <= n; j++) {
				ll xs = ans[j][i] * inv % mod;
				for (int k = i; k <= cnt + 1; k++)
					ans[j][k] = (ans[j][k] + mod - xs * ans[i][k] % mod) % mod;
			}
		}
		for (int i = cnt; i >= 1; i--) {
			for (int j = cnt; j > i; j--) ans[i][cnt + 1] = (ans[i][cnt + 1] + mod - Ans[j] * ans[i][j] % mod) % mod;
			Ans[i] = ans[i][cnt + 1] * qpow(ans[i][i], mod - 2) % mod;
		}
		for (int i = 1; i <= cnt; i++) {
			int j = xx[ii][i - 1];
			if (C[j][ii] != Ans[i])
				tt[++gs] = { j, ii, Ans[i] };
		}
	}
	sort(tt + 1, tt + gs + 1, cmp);
	printf("%d\n", gs);
	for (int i = 1; i <= gs; i++) printf("%d %d %lld\n", tt[i].x, tt[i].y, (tt[i].z % mod + mod) % mod);
	return 0;
}
