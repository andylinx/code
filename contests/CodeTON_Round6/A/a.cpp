#include<bits/stdc++.h>
typedef long long ll;
#define fi first
#define se second
using namespace std;
int main()
{
    int T; scanf("%d",&T);
    while(T--)
    {
        int n,k,x;
        scanf("%d%d%d",&n,&k,&x);
        if(n<k || k>x+1)
        {
            printf("-1\n");
            continue;
        }
        int ans=0;
        for(int i=0;i<k;i++) ans+=i;
        if(k!=x) ans+=x*(n-k);
        else ans+=(x-1)*(n-k);
        printf("%d\n",ans);
    }
    return 0;
}