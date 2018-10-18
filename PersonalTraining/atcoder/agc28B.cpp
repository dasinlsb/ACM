/*
分别对于每个位置i计算a[i]的贡献
考虑在i右边的某个位置j，在j上的操作对i产生贡献当且仅当j在[i,j]上是第一个操作的，左边同理
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
const int mod=1000*1000*1000+7;
int n,a[maxn];
int g[maxn],G[maxn];
int fac[maxn],inv[maxn];
int C(int x,int y){
  if(x<y)return 0;
  return 1LL*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d",&n);
  for(int i=1;i<=n;i++){
    scanf("%d",a+i);
  }
  fac[0]=1;
  for(int i=1;i<maxn;i++)fac[i]=1LL*fac[i-1]*i%mod;
  inv[0]=inv[1]=1;
  for(int i=2;i<maxn;i++)inv[i]=mod-1LL*mod/i*inv[mod%i]%mod;
  for(int i=1;i<maxn;i++)inv[i]=1LL*inv[i]*inv[i-1]%mod;
  for(int i=1;i<=n;i++){
    g[i]=1LL*C(n,i)*fac[i-1]%mod*fac[n-i]%mod;
    // printf("g %d %d\n",i,g[i]);
    g[i]=(g[i]+g[i-1])%mod;
  }
  int ans=0;
  for(int i=1;i<=n;i++){
    ans=(ans+1LL*a[i]*(1LL*g[n-i+1]+g[i]-fac[n]+mod))%mod;
  }
  printf("%d\n",ans);
  return 0;
}