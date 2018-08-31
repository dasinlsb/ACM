/*
一种可能的想法是枚举最后筹到了多少钱来计算答案，这样的话就需要知道最后筹x(L<=x<=\sum_{}m_i)元钱的概率和期望分红
f[i][j]表示前i个人一共出j元钱的期望分红
g[i][j]表示前i个人一共出j元钱的概率
dp实际上非常常规，转移的时候注意f内部自带了概率，跑背包的过程中如果放入了物品要对物品的价值额外乘上相应的概率
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=105;
const int maxm=500005;
const int mod=1000*1000*1000+7;
int n,L,M,m[maxn],r[maxn],p[maxn];
int f[maxm],g[maxm];
int inv[105];
inline void up(int&x,int y){
  if(x+=y,x>=mod)x-=mod;
}
int main(){
  freopen("aa.in","r",stdin);
  inv[0]=inv[1]=1;
  for(int i=2;i<105;i++)inv[i]=mod-1LL*mod/i*inv[mod%i]%mod;
  scanf("%d%d%d",&n,&L,&M);
  for(int i=1;i<=n;i++){
    scanf("%d%d%d",m+i,r+i,p+i);
    p[i]=1LL*p[i]*inv[100]%mod;
    r[i]=1LL*r[i]*inv[100]%mod;
  }
  g[0]=1;
  for(int i=1;i<=n;i++){
    for(int j=maxm-1;j>=0;j--){
      f[j]=1LL*(1-p[i]+mod)*f[j]%mod;
      g[j]=1LL*(1-p[i]+mod)*g[j]%mod;
      if(j>=m[i]){
        up(f[j],1LL*p[i]*((f[j-m[i]]+1LL*m[i]*r[i]%mod*g[j-m[i]])%mod)%mod);
        up(g[j],1LL*p[i]*g[j-m[i]]%mod);
      }
    }
  }
  int ans=0;
  for(int i=L;i<maxm;i++){
    up(ans,(1LL*M*g[i]-f[i]+mod)%mod);
  }
  printf("%d\n",ans);
  return 0;
}