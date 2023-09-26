#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 4002;
ll n, k, lp[maxn], rp[maxn];
int tp;
ll check(ll mid, int cs)
{
	// cerr << mid << " ";
	cs = 1;
	while (mid > rp[cs]) cs++;
	ll res = 1 - mid;
	ll now = 1;

	// cerr << cs << " ";
	for (int i = cs - 1 ; i >= 1; i--)
		now *= k, res += mid / now - lp[i] + 1;
	// cerr << res << " ";
	now = 1;
	for (int i = cs ; i <= tp; i++) {
		res += min((__int128)n, (__int128)mid * now - 1) - lp[i] + 1, now *= k;
		// ans += min((i128)x * mul - 1, (i128)n) - L[i] + 1,
		// cerr << mid * now - 1 << endl;
	}
	// cerr << endl;
	return res;
}
int main()
{
	int T;

	scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld", &n, &k);
		if (n < k) {
			printf("%lld\n", n);
			continue;
		}
		ll now = 1;
		tp = 0;
		__int128 l = 1, r;
		for (; l <= n; l = r + 1) {
			r = l * k - 1;
			r = min((__int128)n, r);
			++tp;
			lp[tp] = l; rp[tp] = r;
		}
		// for (int i = 1; i <= tp; i++) printf("%lld %lld\n", lp[i], rp[i]);
		// continue;
		ll ans = 0;
		// cerr << check(1, 1) << endl;
		for (int i = 1; i <= tp; i++) {
			ll ansl = rp[i] + 1, ansr = rp[i] + 1;
			ll l = lp[i], r = rp[i];

			while (l <= r) {
				ll mid = l + r >> 1;
				if (check(mid, i) >= 0) {
					ansl = mid;
					r = mid - 1;
				} else {
					l = mid + 1;
				}
			}
			l = lp[i], r = rp[i];
			while (l <= r) {
				ll mid = l + r >> 1;
				if (check(mid, i) > 0) {
					ansr = mid;
					r = mid - 1;
				} else {
					l = mid + 1;
				}
			}
			// cerr << ansl << " " << ansr << endl;
			ans += ansr - ansl;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
