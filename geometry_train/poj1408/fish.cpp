#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn = 35;
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
	point operator *(const double t) const
	{
		return point(t * x, t * y);
	}
	point operator -(const point &oth) const
	{
		return point(x - oth.x, y - oth.y);
	}
};
struct line {
	point s, e;
	line()
	{
	}
	line(point _s, point _e) : s(_s), e(_e)
	{
	}
};
point get_intersect(line A, line B)
{
	double S1 = (B.e - A.s) ^ (A.e - A.s);
	double S2 = (B.s - A.s) ^ (A.e - A.s);

	return point((S1 * B.s.x - S2 * B.e.x) / (S1 - S2), (S1 * B.s.y - S2 * B.e.y) / (S1 - S2));
}
int n;
point a[maxn], b[maxn], c[maxn], d[maxn];
point G[maxn][maxn];
line lx[maxn], ly[maxn];
int main()
{
	scanf("%d", &n);
	while (n) {
		for (int i = 1; i <= n; i++) scanf("%lf", &a[i].x), a[i].y = 0;
		for (int i = 1; i <= n; i++) scanf("%lf", &b[i].x), b[i].y = 1;
		for (int i = 1; i <= n; i++) scanf("%lf", &c[i].y), c[i].x = 0;
		for (int i = 1; i <= n; i++) scanf("%lf", &d[i].y), d[i].x = 1;
		for (int i = 1; i <= n; i++) lx[i].s = a[i], lx[i].e = b[i];
		for (int i = 1; i <= n; i++) ly[i].s = c[i], ly[i].e = d[i];
		for (int i = 0; i <= n; i++) G[i][0] = a[i], G[0][i] = c[i], G[n + 1][i] = d[i], G[i][n + 1] = b[i];
		G[0][0] = { 0, 0 }; G[n + 1][0] = { 1, 0 }; G[0][n + 1] = { 0, 1 }; G[n + 1][n + 1] = { 1, 1 };
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				G[i][j] = get_intersect(lx[i], ly[j]);
		double ans = 0;
		for (int i = 1; i <= n + 1; i++)
			for (int j = 1; j <= n + 1; j++) {
				double res = fabs((G[i][j] - G[i][j - 1]) ^ (G[i][j] - G[i - 1][j])) + fabs((G[i - 1][j - 1] - G[i][j - 1]) ^ (G[i - 1][j - 1] - G[i - 1][j]));
				res /= 2; ans = max(ans, res);
			}
		printf("%.6f\n", ans);
		scanf("%d", &n);
	}

	return 0;
}
