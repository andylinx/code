#include <bits/stdc++.h>
using namespace std;
const double PI = acos(-1);
typedef long long ll;
const int maxn = 1e5 + 5;
ll px[maxn], py[maxn], R[maxn], v, T;
int n;
ll sqr(ll x)
{
	return x * x;
}
vector <pair<double, int> > G;
int main()
{
	scanf("%lld%lld%lld%lld", &px[0], &py[0], &v, &T);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lld%lld%lld", &px[i], &py[i], &R[i]);
	int flag = 0;
	for (int i = 1; i <= n; i++)
		if (sqr(px[i] - px[0]) + sqr(py[i] - py[0]) <= sqr(R[i]))
			flag = 1;
	if (flag) {
		printf("1.0\n");
		// cerr << "!!" << endl;
		return 0;
	}
	double r = 1.0 * v * T;
	for (int i = 1; i <= n; i++) {
		ll dist = sqr(px[i] - px[0]) + sqr(py[i] - py[0]);
		if (1.0 * R[i] + v * T < sqrt(dist)) continue;
		double angst = atan2(py[i] - py[0], px[i] - px[0]);
		if (angst < 0) angst += 2 * PI;
		double ang;
		if (sqrt(dist - 1.0 * R[i] * R[i]) < r + 1e-6) ang = asin(R[i] / sqrt(1.0 * dist));
		else ang = acos((r * r + dist - 1.0 * R[i] * R[i]) / (2.0 * r * sqrt(1.0 * dist)));
		// cerr << angst << " ";
		double angl = angst - ang, angr = angst + ang;
		// cerr << angl << " " << angr << endl;
		if (angl < 0) {
			G.push_back({ 2 * PI + angl, 1 }); G.push_back({ 2 * PI, -1 });
			G.push_back({ 0, 1 }); G.push_back({ angr, -1 });
		} else if (angr > 2 * PI) {
			G.push_back({ angl, 1 }); G.push_back({ 2 * PI, -1 });
			G.push_back({ 0, 1 }); G.push_back({ angr - 2 * PI, -1 });
		} else {
			G.push_back({ angl, 1 }); G.push_back({ angr, -1 });
		}
	}
	double st = 0, ans = 0;
	int gs = 0;
	sort(G.begin(), G.end());
	for (auto u:G) {
		// cerr << u.first << " " << u.second << endl;
		if (gs > 0) ans += u.first - st;
		gs += u.second;
		st = u.first;
	}
	printf("%.10lf\n", (ans) / (2 * PI));
	return 0;
}
