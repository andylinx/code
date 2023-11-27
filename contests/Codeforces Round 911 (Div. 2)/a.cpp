#include<bits/stdc++.h>
using namespace std;
const int maxn=105;
char s[maxn];
int n;
int main()
{
    freopen("a.in","r",stdin);
    int T; scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        scanf("%s",s+1);
        int lst=0,mx=0,gs=0;
        for(int i=1;i<=n;i++)
        {
            if(s[i]=='.')
            {
                gs++;
                if(!lst) lst=i;
                else mx=max(i-lst+1,mx);
            }
            else lst=0;
        }
        if(mx>2) printf("%d\n",2);
        else printf("%d\n",gs);
    }
    return 0;
}