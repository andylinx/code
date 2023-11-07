#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
typedef long long ll;
int n;
ll s;
pair <ll, ll> a[maxn];
bool check(ll mid)
{
	ll mx = 0, sum = 0;

	for (int i = 1; i <= n; i++) {
		mx = max(mx, max(0ll, mid - a[i].first) * a[i].second);
		sum += max(0ll, mid - a[i].first) * a[i].second;
	}
	return sum <= mx + s;
}
int main()
{
	scanf("%d%lld", &n, &s);
	for (int i = 1; i <= n; i++) scanf("%lld%lld", &a[i].first, &a[i].second);
	sort(a + 1, a + n + 1);
	ll l = 0, r = 4e9 + 5, ans = 4e9 + 5;
	while (l <= r) {
		ll mid = l + r >> 1;
		if (check(mid)) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	// cerr << ans << endl;
	printf("%lld\n", ans == 4e9 + 5?-1:ans + 1);
	return 0;
}
