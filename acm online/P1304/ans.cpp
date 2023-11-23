//test
#include <bits/stdc++.h>
#define pi pair<int, int>
#define x first
#define y second
#define ll long long
using namespace std;
const int N = 4e5 + 5;
int n;
pi a[N], b[N];
inline double dis(pi i, pi j)
{
	return sqrt((ll)(i.x - j.x) * (i.x - j.x) + (ll)(i.y - j.y) * (i.y - j.y));
}//�������
inline bool cmp(pi i, pi j)
{
	return i.y < j.y;
}
inline double solve(int l, int r)
{
	if (l == r) return 1e9;
	int mid = (l + r) >> 1;
	double d = 1e9;
	d = min(solve(l, mid), solve(mid + 1, r));      //���μ���
	int cnt = 0;
	for (int i = l; i <= r; i++)                    //ȡ�����õĵ�
		if (fabs(a[mid].x - a[i].x) < d) b[++cnt] = a[i];
	sort(b + 1, b + 1 + cnt, cmp);                  //�� y ����
	for (int i = 1; i <= cnt; i++) {                //�����ϲ�
		for (int j = i + 1; j <= cnt; j++) {
			if (b[j].y - b[i].y >= d) break;
			d = min(d, dis(b[i], b[j]));
		}
	}
	return d;
}
int main()
{
	freopen("a.out", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &a[i].x, &a[i].y);
	sort(a + 1, a + 1 + n);         //�� x ����
	double ans = solve(1, n);
	printf("%.0lf\n", ans * ans);   //������ƽ��
	return 0;
}
