#include<bits/stdc++.h>
using namespace std;
int main()
{
    for(int i=1;i<=4;i++)    
    {        
        for(int j=1;j<=4-i;j++) printf(" ");
        for(int j=1;j<i;j++) printf("*");
        printf("*");
        for(int j=1;j<i;j++) printf("*");
        for(int j=1;j<=4-i;j++) printf(" ");
        printf("\n");
    }
    for(int i=1;i<=3;i++)
    {
        for(int j=1;j<=2;j++) printf(" ");
        for(int j=1;j<=3;j++) printf("*");
        for(int j=1;j<=2;j++) printf(" ");
        if(i!=3) printf("\n");
    }
    return 0;
}









































