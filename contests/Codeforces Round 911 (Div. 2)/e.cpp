#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2e5+5;
const ll inf=1e18;
int n,m;
int dfn[maxn],low[maxn],mk[maxn],s[maxn],typ[maxn],tot,top,cntco;
vector <int> G[maxn],GG[maxn];
ll val[maxn],org_val[maxn];
int ex[maxn],ey[maxn],du[maxn],sz[maxn];
map <pair<int,int>,int> Map;
void tarjan(int u)
{
    s[++top]=u;
    mk[u]=1;
    dfn[u]=low[u]=++tot;
    for(int to:G[u])
    {
        if(!dfn[to]) tarjan(to),low[u]=min(low[to],low[u]);
        else if(mk[u]) low[u]=min(low[u],dfn[to]);
    }
    if(dfn[u]==low[u])
    {
        ++cntco;
        int p;
        do{
            p=s[top--];
            mk[p]=0;
            typ[p]=cntco;
            val[cntco]+=org_val[p];
            sz[cntco]++;
        }while(p!=u);
    }
}
ll f[maxn],g[maxn];
void topo()
{
    queue <int> q;
    for(int i=1;i<=cntco;i++)
    {
        if(!du[i]) q.push(i);
        f[i]=0; g[i]=0;
    }
    ll ans1=0,ans2=inf;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        f[u]+=sz[u]; g[u]+=val[u];
        if(f[u]>ans1) ans1=f[u],ans2=g[u];
        else if(f[u]==ans1) ans2=min(ans2,g[u]);
        for(int to:GG[u])
        {
            if(f[to]<f[u]) f[to]=f[u],g[to]=g[u];
            else if(f[to]==f[u]) g[to]=min(g[to],g[u]);
            du[to]--;
            if(!du[to]) q.push(to);
        }
    }
    printf("%lld %lld\n",ans1,ans2);
}
void clr()
{
    for(int i=1;i<=n;i++) dfn[i]=low[i]=mk[i]=typ[i]=0,G[i].clear();
    for(int i=1;i<=cntco;i++) val[i]=0,GG[i].clear(),du[i]=0,sz[i]=0;
    tot=top=cntco=0;
}
int main()
{
    freopen("a.in","r",stdin);
    int T; scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) scanf("%lld",&org_val[i]);
        for(int i=1;i<=m;i++)
        {
            int x,y; scanf("%d%d",&x,&y);
            if(x!=y) G[x].push_back(y),ex[i]=x,ey[i]=y;
        }
        for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
        Map.clear();
        for(int i=1;i<=m;i++) if(typ[ex[i]]!=typ[ey[i]]) 
        {
            int x=typ[ex[i]],y=typ[ey[i]];
            if(Map.find({x,y})!=Map.end())
            {
                GG[x].push_back(y);
                du[y]++;
            }
        }
        topo();
        clr();
    }
    return 0;
}