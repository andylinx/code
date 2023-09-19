#include <bits/stdc++.h>
#define L(i, j, k) for (int i = (j); i <= (k); ++i)
#define R(i, j, k) for (int i = (j); i >= (k); --i)
#define ll long long
#define vi vector < int >
#define sz(a) ((int)(a).size())
#define ll long long
#define ull unsigned long long
#define me(a, x) memset(a, x, sizeof(a))
using namespace std;
const int N = 5007, S = 8300, M = 8192;
#define i128 __int128
ll n, k;

int top;
ll L[N], R[N];

ll get(ll x)
{
	int cur = 1;

	while (x > R[cur])
		++cur;

	ll ans = -x + 1;
	ll mul = 1;
	R(i, cur - 1, 1) {
		mul *= k, ans += x / mul - L[i] + 1;
	}
	mul = 1;
	L(i, cur, top)
	ans += min((i128)x * mul - 1, (i128)n) - L[i] + 1, mul *= k;
	return ans;
}
void Main()
{
	cin >> n >> k;
	if (n < k) {
		cout << n << '\n';
		return;
	}

	top = 0;
	i128 l = 1, r;
	int cnt = 0;
	for (; l <= n; l = r + 1) {
		r = l * k - 1;
		r = min(r, (i128)n);
		++top;
		L[top] = l;
		R[top] = r;
	}

	ll ans = 0;
	L(i, 1, top) {
		ll ansl = R[i] + 1, ansr = R[i] + 1;
		// go up
		{
			ll l = L[i], r = R[i];
			while (l <= r) {
				ll mid = (l + r) >> 1;
				if (get(mid) >= 0)
					ansl = mid, r = mid - 1;
				else
					l = mid + 1;
			}
		}
		{
			ll l = L[i], r = R[i];
			while (l <= r) {
				ll mid = (l + r) >> 1;
				if (get(mid) > 0)
					ansr = mid, r = mid - 1;
				else
					l = mid + 1;
			}
		}

		ans += ansr - ansl;
	}
	cout << ans << '\n';
}
int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; cin >> t; while (t--) Main();
	return 0;
}
