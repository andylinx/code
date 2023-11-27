#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
const int inf=0x3f3f3f3f;
int ls[maxn],rs[maxn],n,ans,f[maxn];
char s[maxn];
void dfs(int u)
{
    if(ls[u])
    {
        f[ls[u]]=f[u]+(s[u]!='L');
        dfs(ls[u]);
    }
    if(rs[u])
    {
        f[rs[u]]=f[u]+(s[u]!='R');
        dfs(rs[u]);
    }
    if(!ls[u] && !rs[u]) ans=min(ans,f[u]);
}
int main()
{
    freopen("a.in","r",stdin);
    int T; scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        scanf("%s",s+1);
        for(int i=1;i<=n;i++) scanf("%d%d",&ls[i],&rs[i]);
        ans=inf;
        dfs(1);
        printf("%d\n",ans);
    }
    return 0;
}