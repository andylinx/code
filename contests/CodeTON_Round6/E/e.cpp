#include<bits/stdc++.h>
typedef long long ll;
#define fi first
#define se second
using namespace std;
const int maxn=5e3+5;
int T,n,a[maxn],cnt[maxn];
int Mex[maxn][maxn],f[maxn][maxn];
int main()
{
    freopen("1.in","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n;i++) for(int k=0;k<maxn;k++) f[i][k]=0;
        for(int i=1;i<=n;i++)
        {
            int now=0;
            for(int j=0;j<=n;j++) cnt[j]=0;
            for(int j=i;j<=n;j++)
            {
                cnt[a[j]]++;
                while(cnt[now]) now++;
                Mex[i][j]=now;
            }
        }
        f[0][0]=1;
        // cerr<<Mex[1][2];
        for(int i=1;i<=n;i++)
        {
            for(int k=0;k<maxn;k++) f[i][k]=f[i-1][k];
            for(int j=i;j>=1;j--)
            {
                if(i==j || (Mex[j][i]!=Mex[j+1][i] && Mex[j][i]!=Mex[j][i-1]))
                    for(int k=0;k<maxn;k++) if(f[j-1][k]) f[i][k^Mex[j][i]]|=1;
            }
        }
        // cerr<<Mex[1][1]<<endl;
        for(int i=maxn-1;i>=0;i--)
        {
            if(f[n][i])
            {
                printf("%d\n",i);
                break;
            }
        }
    }   
    return 0;
}