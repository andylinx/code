#include<bits/stdc++.h>
typedef long long ll;
#define fi first
#define se second
using namespace std;
const int maxn=2e5+5;
int n,m;
int a[maxn],b[maxn];
int main()
{
    int T; scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        int res=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            res^=a[i];
        }
        int now=0;
        for(int i=1;i<=m;i++)
        {
            scanf("%d",&b[i]);
            now|=b[i];
        }
        if(n&1)
        {
            printf("%d %d\n",res,res|now);
        }
        else
        {
            now=~now;
            printf("%d %d\n",res&now,res);
        }
    }
    return 0;
}