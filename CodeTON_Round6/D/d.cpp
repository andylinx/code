#include<bits/stdc++.h>
typedef long long ll;
#define fi first
#define se second
using namespace std;
const int maxn=2e5+5;
int n,k,c[maxn],mn[maxn],mnpos[maxn];
int ans[maxn];
int main()
{
    int T; scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&c[i]);
        scanf("%d",&k);
        mn[n+1]=0x3f3f3f3f;
        memset(ans,0,sizeof(ans));
        for(int i=n;i>=1;i--)
        {
            mn[i]=mn[i+1];
            mnpos[i]=mnpos[i+1];
            if(c[i]<mn[i])
            {
                mn[i]=c[i];
                mnpos[i]=i;
            }
        }
        int lst=0,gss=k+1;
        for(int i=1;i<=n;i++)
        {
            int gs=min(gss,k/(mn[i]-lst));
            k-=gs*(mn[i]-lst);
            ans[mnpos[i]]+=gs;
            lst=mn[i]; gss=gs;
            i=mnpos[i];
        }
        for(int i=n-1;i>=1;i--)
            if(!ans[i]) ans[i]+=ans[i+1];
        for(int i=1;i<=n;i++) printf("%d ",ans[i]);
        printf("\n");
    }
    return 0;
}