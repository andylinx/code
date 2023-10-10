#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn = 1005;
const double eps = 1e-6;
int sgn(double x)
{
	if (fabs(x) < eps) return 0;
	if (x < 0) return -1;
	return 1;
}
struct point {
	double x, y;
	point()
	{
	}
	point(double _x, double _y) : x(_x), y(_y)
	{
	}
	double operator ^(const point &oth) const
	{
		return x * oth.y - y * oth.x;
	}
	double operator *(const point &oth) const
	{
		return x * oth.x + y * oth.y;
	}
	point operator *(const double t) const
	{
		return point(t * x, t * y);
	}
	point operator -(const point &oth) const
	{
		return point(x - oth.x, y - oth.y);
	}
	double len()
	{
		return sqrt(x * x + y * y);
	}
	bool operator ==(const point &oth) const
	{
		return !sgn(x - oth.x) && !sgn(y - oth.y);
	}
};
int n, m;
point a[maxn], c[maxn];
bool cmp(point x, point y)
{
	if (x.x != y.x) return x.x < y.x;
	return x.y < y.y;
}
void convex()
{
	sort(a, a + n, cmp);
	m = 0;
	for (int i = 0; i < n; i++) {
		while (m > 1 && sgn((c[m - 1] - c[m - 2]) ^ (a[i] - c[m - 1])) <= 0) m--;
		c[m++] = a[i];
	}
	int k = m;
	for (int i = n - 2; i >= 0; i--) {
		while (m > k && sgn((c[m - 1] - c[m - 2]) ^ (a[i] - c[m - 1])) <= 0) m--;
		c[m++] = a[i];
	}
	if (n > 1) m--;
}
int main()
{
	int T;

	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%lf%lf", &a[i].x, &a[i].y);
		convex();
		// cerr << m << endl;
		if (m <= 2) {
			printf("NO\n");
			continue;
		}
		// for (int i = 0; i < m; i++) printf("%lf %lf\n", c[i].x, c[i].y);
		int flag = 0;
		// for (int i = 1; i < m - 1; i++)
		// 	if (!sgn((c[i + 1] - c[i]) ^ (c[i - 1] - c[i]))) flag = 1;
		// if (!sgn((c[m - 1] - c[1]) ^ (c[2] - c[1]))) flag = 1;
		// if (!sgn((c[0] - c[m - 1]) ^ (c[m - 2] - c[m - 1]))) flag = 1;
		c[m] = c[1];
		for (int i = 1; i < m; i++) {
			int tag = 0;
			for (int j = 0; j < n; j++) {
				if (a[j] == c[i] || a[j] == c[i - 1]) continue;
				if (!sgn((c[i] - a[j]) ^ (c[i - 1] - a[j])))
					tag = 1;
			}
			if (!tag) flag = 1;
		}
		if (flag) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
