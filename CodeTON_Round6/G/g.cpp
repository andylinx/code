#include<bits/stdc++.h>
typedef long long ll;
#define fi first
#define se second
using namespace std;
const int maxn=2e5+5;
int T,a[maxn],n;
int c[maxn];
int lowbit(int x)
{
    return x&(-x);
}
void add(int x)
{
    while(x<=n)
    {
        c[x]++;
        x+=lowbit(x);
    }
}
int query(int x)
{
    int res=0;
    while(x)
    {
        res+=c[x];
        x-=lowbit(x);
    }
    return res;
}
int tr[maxn<<2],mn[maxn<<2];
void update(int now,int l,int r,int pos)
{
    if(l==r)
    {
        tr[now]++;
        mn[now]++;
        return;
    }
    int mid=l+r>>1;
    if(pos<=mid) update(now<<1,l,mid,pos);
    else update(now<<1|1,mid+1,r,pos);
    tr[now]=tr[now<<1]+tr[now<<1|1];
    mn[now]=min(mn[now<<1],mn[now<<1|1]);
}
int need,gs,pos;
void solve(int now,int l,int r,int L,int R)
{
    int mid=l+r>>1;
    if(l>=L && r<=R)
    {
        if(pos/r<need)
        {
            need=n+1;
            return;
        }
        if(mn[now]>=need)
        {
            gs+=tr[now]-(r-l+1)*need;
            return;
        }
        if(l==r)
        {
            int rest=tr[now]-need;
            if(rest>0) gs+=rest;
            else need-=rest;
            need=min(need,n+1);
            return;
        }
    }
    if(R>mid) solve(now<<1|1,mid+1,r,L,R);
    if(L<=mid) solve(now<<1,l,mid,L,R);   
}
int ans[maxn];
int main()
{
    freopen("1.in","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        int val1=a[1];
        for(int i=1;i<=n;i++) if(a[i]>n) a[i]=0;
        for(int i=1;i<=n;i++) c[i]=0;
        for(int i=1;i<=4*n;i++) tr[i]=mn[i]=0;
        int now=1,gs0=0;
        for(int i=1;i<=n;i++)
        {
            if(a[i]) add(a[i]);
            else gs0++;
            update(1,0,n,a[i]);
            pos=i;
            while(now<=i)
            {
                need=1;
                gs=query(n)-query(now-1)+gs0;
                if(now>1) solve(1,0,n,1,now-1);
                if(need>gs) break;
                now++;
            }
            ans[i]=now-1;
        }
        ans[1]=max(ans[1],val1);
        for(int i=1;i<=n;i++) printf("%d ",ans[i]);
        printf("\n");
    }
    return 0;
}