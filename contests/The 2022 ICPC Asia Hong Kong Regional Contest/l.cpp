#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
int n, m, k;
int ex[maxn], a[maxn], rev[maxn], len[maxn];
set <int> pos;
vector <int> res;
bool cmp(int x, int y)
{
	return x > y;
}
int c[maxn];
int lowbit(int x)
{
	return x & (-x);
}
void add(int x)
{
	while (x <= n + 1) {
		c[x]++;
		x += lowbit(x);
	}
}
int query(int x)
{
	int rres = 0;

	while (x) {
		rres += c[x];
		x -= lowbit(x);
	}
	return rres;
}
int main()
{
	int T; scanf("%d", &T);
	int cnTT = 0, TT = T;

	while (T--) {
		cnTT++;
		scanf("%d%d%d", &n, &m, &k);
		// if (TT == 99 && cnTT == 49) printf("%d %d %d ", n, m, k);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]), rev[a[i]] = i;
			ex[i] = 0; c[i] = 0;
			// if (TT == 99 && cnTT == 49) printf("%d ", a[i]);
		}
		int posi = 0, flag = 0;
		for (int i = 1; i <= m; i++) {
			int x; scanf("%d", &x);

			// if (TT == 99 && cnTT == 49) printf("%d ", x);
			while (posi <= n && a[posi] != x) posi++;
			if (posi > n) flag = 1;
			ex[x] = 1;
		}
		for (int i = 1; i <= k; i++) {
			scanf("%d", &len[i]);

			// if (TT == 99 && cnTT == 49) printf("%d ", len[i]);
		}
		sort(len + 1, len + k + 1, cmp);
		pos.clear(); res.clear();
		pos.insert(0);
		pos.insert(n + 1);
		for (int i = n; i >= 1; i--) {
			int p = rev[i];
			auto pr = pos.lower_bound(p);
			auto pl = pr; pl--;
			// cerr << query(*pr) << endl;
			if (!ex[i])
				res.push_back((*pr) - (*pl) - query(*(pr)) + query(*(pl)) - 1), add(rev[i]);
			else pos.insert(rev[i]);
		}
		sort(res.begin(), res.end(), cmp);
		int now = 1;
		for (int i = 0; i < res.size(); i++) {
			// printf("%d ", res[i]);
			while (now <= k && len[now] > res[i]) now++;
			if (now > k) {
				flag = 1;
				break;
			}
			now++;
		}
		for (int i = 1; i <= n + 1; i++) c[i] = a[i] = rev[i] = 0;
		for (int i = 1; i <= k; i++) len[i] = 0;
		// printf("\n");
		if (!flag) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
