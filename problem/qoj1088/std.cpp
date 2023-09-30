#include <bits/stdc++.h>
using namespace std;
#define N 2010
typedef long long ll;
int n, m;
ll ans;
char a[N][N], _a[N][N];
void calc(int l1, int r1, int l2, int r2, char a[][N])
{
	static int L[N], R[N], D[N][N], U[N][N], slU[N][N], slD[N][N], srU[N][N], srD[N][N];
	int mid = (l2 + r2) >> 1;

	// cerr << a[2][4];
	for (int i = l1; i <= r1; ++i) {
		L[i] = R[i] = 0;
		while (mid - L[i] >= l2 && a[i][mid] == a[i][mid - L[i]]) ++L[i];
		while (mid + R[i] + 1 <= r2 && a[i][mid + 1] == a[i][mid + R[i] + 1]) ++R[i];
		// cerr << L[i] - 1 << " " << R[i] - 1 << endl;
	}
	for (int i = r1; i >= l1; --i)
		for (int j = l2; j <= r2; ++j)
			D[i][j] = (i < r1 && a[i][j] == a[i + 1][j])?D[i + 1][j]:i;
	for (int i = l1; i <= r1; ++i)
		for (int j = l2; j <= r2; ++j)
			U[i][j] = (i > l1 && a[i][j] == a[i - 1][j])?U[i - 1][j]:i;
	for (int i = l1; i <= r1; ++i)
		for (int j = l1; j <= r1; ++j)
			slU[i][j] = slD[i][j] = srU[i][j] = srD[i][j] = 0;
	for (int i = l1; i <= r1; i++) {
		for (int j = l2; j <= r2; j++)
			cerr << D[i][j] << " ";
		cerr << endl;
	}
	for (int i = l1; i <= r1; ++i) {
		for (int j = mid; j >= mid - L[i] + 1; --j)
			++slU[i][U[i][j]], ++slD[i][D[i][j]];
		for (int j = mid + 1; j <= mid + R[i]; ++j)
			++srU[i][U[i][j]], ++srD[i][D[i][j]];
		for (int j = l1 + 1; j <= i; ++j) {
			slU[i][j] += slU[i][j - 1];
			srU[i][j] += srU[i][j - 1];
		}
		for (int j = r1 - 1; j >= i; --j) {
			slD[i][j] += slD[i][j + 1];
			srD[i][j] += srD[i][j + 1];
		}
	}
	// for (int i = l1; i <= r1; i++) {
	// 	for (int j = l2; j <= r2; j++)
	// 		cerr << slD[i][j] << " ";
	// 	cerr << endl;
	// }
	for (int i = l1; i <= r1; ++i) {
		for (int j = i + 1; j <= r1; ++j) {
			if (a[i][mid] == a[j][mid] && a[i][mid] == a[i][mid + 1] && a[i][mid + 1] == a[j][mid + 1]) {
				int lw, rw;
				if (L[i] < L[j]) lw = slD[i][j];
				else lw = slU[j][i];
				if (R[i] < R[j]) rw = srD[i][j];
				else rw = srU[j][i];
				ans += lw * rw;
			}
		}
	}
}
void Solve(int l1, int r1, int l2, int r2)
{
	if (l1 >= r1 || l2 >= r2) return;
	if (r1 - l1 < r2 - l2) {
		int mid = (l2 + r2) >> 1;
		calc(l1, r1, l2, r2, a);
		Solve(l1, r1, l2, mid);
		Solve(l1, r1, mid + 1, r2);
	} else {
		int mid = (l1 + r1) >> 1;
		calc(l2, r2, l1, r1, _a);
		Solve(l1, mid, l2, r2);
		Solve(mid + 1, r1, l2, r2);
	}
}
int main()
{
	freopen("2.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> (a[i] + 1);
		for (int j = 1; j <= m; ++j)
			_a[j][i] = a[i][j];
	}
	Solve(1, n, 1, m);
	cout << ans << '\n';
	return 0;
}
