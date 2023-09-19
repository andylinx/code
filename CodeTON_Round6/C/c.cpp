#include<bits/stdc++.h>
typedef long long ll;
#define fi first
#define se second
using namespace std;
const int maxn=1e5+5;
int n,k;
vector <int> pos[maxn];
int main()
{
    int T; scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&k);
        for(int i=1;i<=k;i++) pos[i].clear();
        for(int i=1;i<=n;i++)
        {
            int x; scanf("%d",&x);
            pos[x].push_back(i);
        }
        set <int> a,b;
        int up=1,dw=n;
        for(int i=1;i<=k;i++)
        {
            while(a.size() && *(a.begin())==up) up++,a.erase(a.begin());
            while(b.size() && *(b.begin())==-dw) dw--,b.erase(b.begin());
            if(!pos[i].size())
            {
                printf("0 ");
                continue;
            }
            printf("%d ",2*(dw-up+1));
            for(int j:pos[i]) a.insert(j),b.insert(-j);
        }
        printf("\n");
    }
    return 0;
}