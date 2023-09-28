#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <queue>
#include <ctime>
#include <vector>
#include <set>
#include <map>
#include <stack>
using namespace std;
long long a[100100], b[100100], d[440000], sum, d1[440000];
long long S1[100100], S2[100100], S11[100100], S21[100100];
map<long long, long long>id;
inline void add(long long le, long long ri, long long wh, long long pl, long long k)
{
	d[wh] += k;
	if (le == ri) return;
	long long mid = (le + ri) >> 1;
	if (mid >= pl) add(le, mid, wh << 1, pl, k);
	else add(mid + 1, ri, wh << 1 | 1, pl, k);
	return;
}
inline void add2(long long le, long long ri, long long wh, long long pl, long long k)
{
	d1[wh] += k;
	if (le == ri) return;
	long long mid = (le + ri) >> 1;
	if (mid >= pl) add2(le, mid, wh << 1, pl, k);
	else add2(mid + 1, ri, wh << 1 | 1, pl, k);
	return;
}
inline long long q(long long le, long long ri, long long x, long long y, long long wh)
{
	if (x > y) return 0;
	if (le >= x && ri <= y) return d[wh];
	long long mid = (le + ri) >> 1, ans = 0;
	if (mid >= x) ans += q(le, mid, x, y, wh << 1);
	if (mid < y) ans += q(mid + 1, ri, x, y, wh << 1 | 1);
	return ans;
}
inline long long q2(long long le, long long ri, long long x, long long y, long long wh)
{
	if (x > y) return 0;
	if (le >= x && ri <= y) return d1[wh];
	long long mid = (le + ri) >> 1, ans = 0;
	if (mid >= x) ans += q2(le, mid, x, y, wh << 1);
	if (mid < y) ans += q2(mid + 1, ri, x, y, wh << 1 | 1);
	return ans;
}
int main()
{
	long long n, m, i, j, k, sum1 = 0, sum2 = 0;

	scanf("%lld", &n);
	id.clear();
	for (i = 1; i <= n; i++) scanf("%lld", &a[i]), b[i] = a[i];
	sort(b + 1, b + n + 1);
	for (i = 1; i <= n; i++)
		if (!id[b[i]])
			id[b[i]] = ++sum;
	for (i = 1; i <= n; i++) {
		long long x = q(1, sum, 1, id[a[i]] - 1, 1), y = q(1, sum, id[a[i]] + 1, sum, 1);
		sum1 += x; sum2 += y;
		add(1, sum, 1, id[a[i]], 1);
	}
	long long Ans = (long long)sum1 * sum2;
	memset(d, 0, sizeof(d));
	memset(d1, 0, sizeof(d1));
	for (i = 1; i <= n; i++) {
		S1[i] = q(1, sum, 1, id[a[i]] - 1, 1);
		S11[i] = q(1, sum, id[a[i]] + 1, sum, 1);
		add(1, sum, 1, id[a[i]], 1);
	}
	for (i = n; i > 0; i--) {
		S2[i] = q2(1, sum, 1, id[a[i]] - 1, 1);
		S21[i] = q2(1, sum, id[a[i]] + 1, sum, 1);
		add2(1, sum, 1, id[a[i]], 1);
	}
	for (i = 1; i <= n; i++)
		Ans -= (long long)S1[i] * S2[i] + (long long)S11[i] * S1[i] + (long long)S21[i] * S2[i] + (long long)S21[i] * S11[i];
	printf("%lld\n", Ans);
	return 0;
}
