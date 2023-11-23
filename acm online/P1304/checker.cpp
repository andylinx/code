#include <bits/stdc++.h>
using namespace std;
const int T = 10;
const int N = 4e5;
const long double pi = acosl(-1);
int n, X[N], Y[N];
struct point {
	long double	x, y;
	int		i;
	bool operator <(const point &a) const
	{
		return x < a.x;
	}
	long long distance_2(const point &a)
	{
		return (long long)(X[a.i] - X[i]) * (X[a.i] - X[i]) + (long long)(Y[a.i] - Y[i]) * (Y[a.i] - Y[i]);
	}
};
int main()
{
	freopen("a.out", "r", stdin);
	cin >> n;
	for (int i = 0; i < n; i++) cin >> X[i] >> Y[i];
	long long ans = LLONG_MAX;
	srand(time(0) + 20050302);
	int SEED = rand();
	mt19937 rng(SEED);
	uniform_real_distribution <long double> distribution(0, pi);
	long double theta = distribution(rng);
	for (int i = 0; i < T; i++) {
		vector < point > a;
		long double angle = theta + pi * i / T;
		for (int j = 0; j < n; j++) {
			long double x = X[j], y = Y[j];
			long double nx = cos(angle) * x + sin(angle) * y, ny = -sin(angle) * x + cos(angle) * y;
			a.push_back({ nx, ny, j });
		}
		sort(a.begin(), a.end());
		for (int j = 1; j < n; j++)
			ans = min(ans, a[j - 1].distance_2(a[j]));
	}
	cout << ans << endl;
}
