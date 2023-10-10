#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn = 105;
const double eps = 1e-8;
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
int n, flag;
line a[maxn];
void check(point b, point c)
{
	if ((b - c).len() < eps) return;
	int tag = 0;
	for (int i = 1; i <= n; i++)
		if (sgn((c - b) ^ (a[i].s - b)) * sgn((c - b) ^ (a[i].e - b)) > 0) tag = 1;
	if (!tag) flag = 1;
}
int main()
{
	int T;

	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%lf%lf%lf%lf", &a[i].s.x, &a[i].s.y, &a[i].e.x, &a[i].e.y);
		if (n <= 2) {
			printf("Yes!\n");
		} else {
			flag = 0;
			for (int i = 1; i <= n; i++)
				for (int j = i + 1; j <= n; j++) {
					check(a[i].s, a[j].s); check(a[i].s, a[j].e);
					check(a[i].e, a[j].s); check(a[i].e, a[j].e);
				}
			if (flag) printf("Yes!\n");
			else printf("No!\n");
		}
		// return 0;
	}
	return 0;
}
