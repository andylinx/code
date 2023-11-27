#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+5;
int n,suf[maxn];
ll ans[maxn],cnt[maxn];
int main()
{
    int T; scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;i++)
        {
            int x; scanf("%d",&x);
            cnt[x]++;
        }
        for(int i=100000;i>=1;i--)
            suf[i]=suf[i+1]+cnt[i];
        for(int i=1;i<=100000;i++)
        {
            ans[i]=0;
            ll pre=0;
            for(int j=i;j<=100000;j+=i)
            {
                ans[i]+=pre*cnt[j]*suf[j+1];
                ans[i]+=(pre+suf[j+1])*cnt[j]*(cnt[j]-1)/2;
                ans[i]+=cnt[j]*(cnt[j]-1)*(cnt[j]-2)/6;
                pre+=cnt[j];
            }
        }
        for(int i=100000;i>=1;i--)
            for(int j=2*i;j<=100000;j+=i)
                ans[i]-=ans[j];
        ll res=0;
        for(int i=1;i<=100000;i++) res+=i*ans[i];
        printf("%lld\n",res);
    }
    return 0;
}