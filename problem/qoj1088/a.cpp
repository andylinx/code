#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2005;
int n, m;
char a[2][maxn][maxn];
ll ans;
int L[maxn], R[maxn], U[maxn][maxn], D[maxn][maxn];
ll ul[maxn][maxn], dl[maxn][maxn], ur[maxn][maxn], dr[maxn][maxn];
void calc(int lx, int rx, int ly, int ry, int p)
{
	// cerr<<lx<<" "<<rx<<" "<<ly<<" "<<ry<<endl;
	int mid = ly + ry >> 1;

	// p ^= 1;
	// cerr << p << endl;
	for (int i = lx; i <= rx; i++) {
		L[i] = R[i] = 0;
		while (mid - L[i] > ly && a[p][i][mid - L[i] - 1] == a[p][i][mid - L[i]]) L[i]++;
		while (mid + 1 + R[i] < ry && a[p][i][mid + R[i] + 2] == a[p][i][mid + R[i] + 1]) R[i]++;
		// cerr << L[i] << " " << R[i] << endl;
	}
	for (int i = lx; i <= rx; i++)
		for (int j = ly; j <= ry; j++)
			U[i][j] = D[i][j] = 0;
	for (int i = lx; i <= rx; i++)
		for (int j = ly; j <= ry; j++)
			U[i][j] = (i != lx && a[p][i][j] == a[p][i - 1][j])?U[i - 1][j]:i;
	for (int i = rx; i >= lx; i--)
		for (int j = ly; j <= ry; j++)
			D[i][j] = (i != rx && a[p][i][j] == a[p][i + 1][j])?D[i + 1][j]:i;
	// cerr<<D[1][2]<<endl;
	// for (int i = lx; i <= rx; i++) {
	// 	for (int j = ly; j <= ry; j++)
	// 		cerr << D[i][j] << " ";
	// 	cerr << endl;
	// }
	for (int i = lx - 1; i <= rx + 1; i++) for (int j = lx - 1; j <= rx + 1; j++) ul[i][j] = dl[i][j] = ur[i][j] = dr[i][j] = 0;
	for (int i = lx; i <= rx; i++) {
		for (int j = mid - L[i]; j <= mid; j++)
			ul[i][U[i][j]]++, dl[i][D[i][j]]++;
		for (int j = mid + 1; j <= mid + R[i] + 1; j++)
			dr[i][D[i][j]]++, ur[i][U[i][j]]++;
		for (int j = lx + 1; j <= i; j++)
			ul[i][j] += ul[i][j - 1], ur[i][j] += ur[i][j - 1];
		for (int j = rx - 1; j >= i; j--)
			dl[i][j] += dl[i][j + 1], dr[i][j] += dr[i][j + 1];
	}
	// for (int i = lx; i <= rx; i++) {
	// 	for (int j = ly; j <= ry; j++)
	// 		cerr << dl[i][j] << " ";
	// 	cerr << endl;
	// }
	// cerr<<ul[1][3]<<endl;
	for (int i = lx; i <= rx; i++)
		for (int j = i + 1; j <= rx; j++)
			if (a[p][i][mid] == a[p][j][mid] && a[p][i][mid + 1] == a[p][j][mid + 1] && a[p][i][mid] == a[p][i][mid + 1]) {
				// cerr<<i<<" "<<j<<endl;
				ll gs1, gs2;
				if (L[i] < L[j]) gs1 = dl[i][j];
				else gs1 = ul[j][i];
				if (R[i] < R[j]) gs2 = dr[i][j];
				else gs2 = ur[j][i];
				// cerr<<gs1<<" "<<gs2<<endl;
				ans += gs1 * gs2;
			}
}
void solve(int lx, int rx, int ly, int ry)
{
	if (lx >= rx || ly >= ry) return;
	if (rx - lx >= ry - ly) {
		int mid = rx + lx >> 1;
		calc(ly, ry, lx, rx, 1);
		solve(lx, mid, ly, ry);
		solve(mid + 1, rx, ly, ry);
	} else {
		int mid = ly + ry >> 1;
		// cerr<<mid<<endl;
		// cerr<<ans<<endl;
		calc(lx, rx, ly, ry, 0);
		solve(lx, rx, ly, mid);
		solve(lx, rx, mid + 1, ry);
	}
}
int main()
{
	freopen("2.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%s", a[0][i] + 1);
		for (int j = 1; j <= m; j++)
			a[1][j][i] = a[0][i][j];
	}
	// cerr << (a[0][2][4] == a[0][3][4])?1:0;
	solve(1, n, 1, m);
	printf("%lld\n", ans);
	return 0;
}
