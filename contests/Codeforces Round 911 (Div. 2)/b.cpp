    #include<bits/stdc++.h>
    using namespace std;
    const int maxn=105;
    char s[maxn];
    int n;
    bool check(int a,int b,int c)
    {
        if((a+b)&1) return false;
        int mn=min(a,b);
        a-=mn,b-=mn;
        c+=mn;
        if(a) return c;
        if(b) return c;
        if(c) return true;
        return true;
    }
    int main()
    {
        freopen("a.in","r",stdin);
        freopen("a.out","w",stdout);
        int T; scanf("%d",&T);
        while(T--)
        {
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            if(check(b,c,a))
                printf("%d ",1);
            else printf("%d ",0);
            if(check(a,c,b))
                printf("%d ",1);
            else printf("%d ",0);
            if(check(a,b,c))
                printf("%d\n",1);
            else printf("%d\n",0);
            printf("\n");
        }
        return 0;
    }