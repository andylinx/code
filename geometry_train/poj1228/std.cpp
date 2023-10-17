#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
using namespace std;

typedef struct {
	double x, y;
} Point;

Point p[1005];
int ans[1005];
int t, n;

bool cmp(Point a, Point b)
{
	return a.y < b.y || (a.y == b.y && a.x < b.x);
}

double cross(int i, int j, int k)
{
	Point a = p[i];
	Point b = p[j];
	Point c = p[k];

	return (c.x - b.x) * (a.y - b.y) - (c.y - b.y) * (a.x - b.x);
}

int Q[1005], top;
void scan()
{
	sort(p + 1, p + n + 1, cmp);
	Q[1] = 1; Q[2] = 2; top = 2;
	for (int i = 3; i <= n; ++i) {
		while (top > 1 && cross(Q[top - 1], Q[top], i) <= 0) top--;
		Q[++top] = i;
	}

	for (int i = 1; i <= top; ++i)
		ans[i] = Q[i];
	ans[0] = top;

	Q[1] = n; Q[2] = n - 1; top = 2;
	for (int i = n - 2; i >= 1; --i) {
		while (top > 1 && cross(Q[top - 1], Q[top], i) <= 0) top--;
		Q[++top] = i;
	}

	for (int i = 2; i < top; ++i)
		ans[++ans[0]] = Q[i];
}
int main()
{
	//freopen("fc.in","r",stdin);
	//freopen("fc.out","w",stdout);

	cin >> t;
	while (t > 0) {
		t--;
		cin >> n;
		for (int i = 1; i <= n; ++i)
			cin >> p[i].x >> p[i].y;
		scan();
		cerr << ans[0] << endl;
		if (ans[0] < 3) {
			cout << "NO" << endl; continue;
		}


		ans[0]++;
		ans[ans[0]] = 1;
		int i;
		for (i = 1; i < ans[0]; ++i) {
			int j;
			for (j = 1; j <= n; ++j)
				if (j != ans[i] && j != ans[i + 1] && fabs(cross(ans[i], ans[i + 1], j)) < 1e-6)
					break;
			if (j > n) break;
		}
		if (i < ans[0]) cout << "NO" << endl;
		else cout << "YES" << endl;
	}
}
