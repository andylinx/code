#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
int n;
pair <ll, ll> a[maxn];
priority_queue <ll> val;
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld%lld", &a[i].first, &a[i].second);
	sort(a + 1, a + n + 1);
	int now = 0;
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		if (now < a[i].first)
			val.push(-a[i].second), now++, ans += a[i].second;
		else
		if (-val.top() < a[i].second) ans += a[i].second + val.top(), val.pop(), val.push(-a[i].second);
		// cerr << i << ":" << val.top() << " " << ans << endl;
	}
	printf("%lld\n", ans);
	return 0;
}
