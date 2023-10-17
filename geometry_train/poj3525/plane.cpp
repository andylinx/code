#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
const int maxn = 1005;
const double eps = 1e-7;
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
	point operator +(const point &oth) const
	{
		return point(x + oth.x, y + oth.y);
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
struct Hplane {
	point	p, d;
	double	ang;
	Hplane ()
	{
	}
	Hplane(point _p, point _d) : p(_p), d(_d)
	{
		ang = atan2(_d.y, _d.x);
	}
	bool operator <(Hplane &oth) const
	{
		return ang < oth.ang;
	}
} b[maxn], tmp[maxn];
bool onleft(Hplane L, point P)
{
	return sgn(L.d ^ (P - L.p)) > 0;
}
point intersect(Hplane a, Hplane b)
{
	point u = a.p - b.p;
	double t = (b.d ^ u) / (a.d ^ b.d);

	return a.p + (a.d * t);
}
bool cmp(Hplane x, Hplane y)
{
	return x.ang < y.ang;
}
vector <point> HPI(Hplane *L, int n)
{
	sort(L, L + n, cmp);
	int st, ed;
	vector <point> p(n), ans;
	vector <Hplane> q(n);
	q[st = ed = 0] = L[0];
	for (int i = 1; i < n; i++) {
		while (st < ed && !onleft(L[i], p[ed - 1])) ed--;
		while (st < ed && !onleft(L[i], p[st])) st++;
		q[++ed] = L[i];
		if (!sgn((q[ed].d ^ q[ed - 1].d))) {
			ed--;
			if (onleft(q[ed], L[i].p)) q[ed] = L[i];
		}
		if (st < ed) p[ed - 1] = intersect(q[ed - 1], q[ed]);
	}
	while (st < ed && !onleft(q[st], p[ed - 1])) ed--;
	if (ed - st <= 1) return ans;
	p[ed] = intersect(q[st], q[ed]);
	for (int i = st; i <= ed; i++) ans.push_back(p[i]);
	return ans;
}
int n;
point a[maxn];
point Normal(point x) // 左转90度的单位法向量
{
	double len = x.len();

	return (point){ -x.y / len, x.x / len };
}
bool check(double mid)
{
	for (int i = 0; i < n; i++) {
		tmp[i].d = b[i].d;
		tmp[i].p = b[i].p + Normal(b[i].d) * mid;
	}
	return HPI(tmp, n).size() > 0;
}
int main()
{
	freopen("a.in", "r", stdin);
	while (scanf("%d", &n) && n) {
		for (int i = 0; i < n; i++) scanf("%lf%lf", &a[i].x, &a[i].y);
		for (int i = 0; i < n; i++) b[i] = { a[i], a[(i + 1) % n] - a[i] };
		double l = 0, r = 20000.0;
		while (r - l > eps) {
			double mid = (l + r) / 2;
			if (check(mid)) l = mid;
			else r = mid;
		}
		printf("%.6lf\n", l);
	}
	return 0;
}
