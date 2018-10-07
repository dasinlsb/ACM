/*
肯定1,2...m,n/m,n/(m-1)...n/2,n/1的形式
左边值连续，右边分母连续，判一下在哪边然后可以O(1)算
*/
#include <bits/stdc++.h>
using namespace std;
int main(){
    int _;scanf("%d",&_);
    for(;_--;){
        long long n,kk;
        scanf("%lld%lld",&n,&kk);
        long long m=(long long)sqrt(1.0*n);
        for(;m*m<=n;m++);
        for(;m*m>n;m--);
        long long all=2LL*m-(n/m==m);
        printf("%lld ",all);
        if(kk>=m)printf("%lld\n",all-kk+1);
        else printf("%lld\n",n/kk);
    }
    return 0;
}