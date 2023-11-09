#include <bits/stdc++.h>
using namespace std;
int n, m;
vector <vector<int> > G;
int main()
{
	scanf("%d%d", &n, &m);
	G.resize(n);
	for (int i = 0; i < n; i++) G[i].resize(m);
	int ans = min(n, m) - 1;
	for (int i = 0; i <= ans; i++) {
		for (int j = 0; j <= ans - i; j++)
			G[i][j] = j + i;
		int st = ans - i + 1;
		for (int j = 0; j < i; j++)
			G[i][st + j] = j;
	}
	if (m > n) {
		for (int i = ans + 1; i < m; i++)
			for (int j = 0; j < n; j++)
				G[j][i] = i;
	} else {
		for (int i = ans + 1; i < n; i++)
			for (int j = 0; j < m; j++)
				G[i][j] = m - j - 1;
	}
	printf("%d\n", ans + 1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) printf("%d ", G[i][j]);
		printf("\n");
	}
	return 0;
}
