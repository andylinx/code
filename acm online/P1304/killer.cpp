#include <bits/stdc++.h>
using namespace std;
const double PI = acos(-1);
pair<int, int> ans[400005];
int gs = 0;
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	int T; scanf("%d", &T);
	int R = 1e7;
	int n = (4e5 - 1) / T - 1;
	double delta = 2 * PI / n;
	double now = 0;
	int cnt = 0, id = rand() % (n - 1) + 1;
	for (int i = 1; i <= n; i++, now += delta) {
		int px = R * cos(now), py = R * sin(now);
		cnt++;
		if (cnt == id) px--, py--;
		ans[++gs] = { px, py };
	}
	sort(ans + 1, ans + gs + 1);
	gs = unique(ans + 1, ans + gs + 1) - ans - 1;
	printf("%d\n", gs + 1);
	printf("0 0\n");
	for (int i = 1; i <= gs; i++) printf("%d %d\n", ans[i].first, ans[i].second);
	return 0;
}
