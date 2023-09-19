#include<bits/stdc++.h>
#define L(i, j, k) for(int i = (j); i <= (k); ++i)
#define R(i, j, k) for(int i = (j); i >= (k); --i)
#define ll long long 
#define vi vector < int > 
#define sz(a) ((int) (a).size())
#define ll long long 
#define ull unsigned long long
#define me(a, x) memset(a, x, sizeof(a)) 
using namespace std;
const int N = 1 << 20;

int n;
int a[N];
int ans[N];

int cnt[N];

int mn[N];
ll sum[N];
void modify(int x, int L, int R, int p) {
	sum[x] += 1;
	if(L == R) {
		mn[x] += 1;
		return ;
	}
	int mid = (L + R) >> 1;
	p <= mid ? modify(x * 2, L, mid, p) : modify(x * 2 + 1, mid + 1, R, p);
	mn[x] = min(mn[x * 2], mn[x * 2 + 1]);
}

int need, zero, curp;
void slv(int x, int L, int R, int l, int r) {
	if(l <= L && R <= r) {
		if(need > curp / R) {
			need = n * 2;
			return ;
		}
		if(mn[x] >= need) {
			zero += sum[x] - need * (R - L + 1);
			return ;
		}
		if(L == R) {
			int use = need - mn[x];
			if(use > 0) {
				need += use;
			} else {
				zero += -use;
			}
			need = min(need, n * 2);
			return ;
		}
	}
	int mid = (L + R) >> 1;
	if(r > mid) slv(x * 2 + 1, mid + 1, R, l, r);
	if(l <= mid) slv(x * 2, L, mid, l, r);
}

template < int N > struct fenwt {
	using F = long long ;
	F a[N + 1];
	void add (int x, F w) {
		for (; x <= N; x += x & -x) a[x] += w;
	}
	F query (int x) {
		F ret = 0;
		for (; x; x -= x & -x) ret += a[x];
		return ret;
	}
	F get (int l, int r) {
		if(l > r) return 0;
		return query (r) - query (l - 1);
	}
} ;
fenwt < N > F;

int a1;
void Main() {
	cin >> n;
	L(i, 1, n) {
		cin >> a[i];
	}
	a1 = a[1];
	L(i, 1, n) {
		if(a[i] > n) {
			a[i] = 0;
		}
	}
	L(i, 0, n) {
		cnt[i] = 0;
	}
	
	int ns = 1;
	L(i, 1, n) {
		if(a[i]) F.add(a[i], 1);
		++cnt[a[i]];
		modify(1, 0, n, a[i]);
		curp = i;
		while(ns <= i) {
			need = 1, zero = F.get(ns, n) + cnt[0];
			if(1 < ns) slv(1, 0, n, 1, ns - 1);
			if(zero < need) {
				break;
			}
			++ns;
		}
		ans[i] = ns - 1;
	}
	
	L(i, 1, n) {
		if(a[i]) F.add(a[i], -1);
	}
	
	ans[1] = max(ans[1], a1);
	L(i, 1, n) {
		cout << ans[i] << ' ';
	}
	cout << '\n';
	
	L(i, 1, n * 4) {
		mn[i] = 0;
		sum[i] = 0;
	}
}

int main() {
	ios :: sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; cin >> t; while(t--) Main();
	return 0;
}
