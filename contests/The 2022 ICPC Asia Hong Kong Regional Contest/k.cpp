#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
int n;
ll a[maxn];
int main()
{
	scanf("%d", &n);
	ll mn = 1e9;
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]), mn = min(mn, a[i]);
	int flag = 0;
	for (int i = 1; i <= n; i++) {
		if (a[i] % mn == 0) continue;
		if (mn <= (a[i] - 1) / 2) continue;
		flag = 1;
	}
	if (flag) printf("%lld\n", mn / 2);
	else printf("%lld\n", mn);
	return 0;
}
