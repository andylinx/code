#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll l, r, b, k;
int main()
{
	scanf("%lld%lld%lld%lld", &l, &r, &b, &k);
	ll gs = ceil(1.0 * l / b);
	// cerr << gs << endl;
	printf("%lld\n", k * gs * b);
	return 0;
}
