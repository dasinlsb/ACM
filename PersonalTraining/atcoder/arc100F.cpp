/*
如果直接正面dp比较困难，考虑反面，全集很好求，考虑如何求出所有长度为N的not colorful的序列中包含A序列次数的总和
A如果本身是colorful那就答案为0
既然是not colorful那么最终整个序列不存在1-K的排列，由此可以将剩下的情况分成两类
一类是A_i互不相同，这一类比较麻烦，如果我们直接O(n)枚举A放在哪个位置，暴力跑dp，f[i][j]表示前i位其中恰好最后j位互不相同的方案，碰到A的左端点直接往右跳到A的右端点，这样做是O(n^2k)，无法接受
实际上这个答案可以在上述dp中一轮就统计出来，一开始我想如何只用f[i][j](j>=m)计算，后来发现对于中间一段长m的区间，它的右边是必须用类似f的方法递推过去
也就是我们要额外维护一个类似f的dp,记为cnt[i][j]，不断以f[i][j](j>=m)作为种子更新到cnt[i][j],其他转移和f完全相同
另一类是A_i中存在相同的元素，显然这会将A分成左右两段独立的情况，假设A的左边至多L个连续，那么我们可以枚举i使得f[i][j](j>=L)的方案通过一些变换计入答案
时间复杂度O(nk)
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=25005;
const int maxk=405;
const int mod=1000*1000*1000+7;
inline void up(int&x,int y){
  if(x+=y,x>=mod)x-=mod;
}
int Pow(long long x,int y){
  long long t=1;
  for(;y;y>>=1){
    if(y&1)t=t*x%mod;
    x=x*x%mod;
  }
  return (int)t;
}
int n,m,K,a[maxn];
int fac[maxn],fac_inv[maxn];
int f[maxn][maxk],cnt[maxn][maxk],gL[maxn],gR[maxn];
int vis[maxk];
int main(){
  freopen("aa.in","r",stdin);
  fac[0]=1;
  for(int i=1;i<maxn;i++)fac[i]=1LL*fac[i-1]*i%mod;
  fac_inv[maxn-1]=Pow(fac[maxn-1],mod-2);
  for(int i=maxn-1;i;i--)fac_inv[i-1]=1LL*fac_inv[i]*i%mod;
  scanf("%d%d%d",&n,&K,&m);
  for(int i=1;i<=m;i++)scanf("%d",a+i);
  int ans=1LL*Pow(K,n-m)*(n-m+1)%mod;
  int max_len=0;
  int pre_pos=1;
  for(int i=1;i<=m;i++){
    for(;vis[a[i]];pre_pos++){
      vis[a[pre_pos]]--;
    }
    vis[a[i]]++;
    max_len=max(max_len,i-pre_pos+1);
  }
  if(max_len==K)return printf("%d\n",ans),0;
  f[1][1]=K;
  for(int i=1;i<n;i++){
    for(int j=1;j<K;j++){
      up(f[i+1][1],f[i][j]);
      up(f[i+1][j+1],mod-f[i][j]);
    }
    for(int j=1;j<K;j++){
      up(f[i+1][j],f[i+1][j-1]);
    }
    for(int j=1;j<K;j++){
      up(f[i+1][j+1],1LL*f[i][j]*(K-j)%mod);
    }
  }
  int L,R;
  memset(vis,0,sizeof(vis));
  for(L=1;L<=m&&!vis[a[L]];L++)vis[a[L]]=1;L--;
  memset(vis,0,sizeof(vis));
  for(R=1;R<=m&&!vis[a[m-R+1]];R++)vis[a[m-R+1]]=1;R--;
  if(L==m){
    //printf("ans %d\n",ans);
    for(int i=1;i<=n;i++){
      for(int j=1;j<K;j++){
        if(j>=m)up(cnt[i][j],f[i][j]);
        up(cnt[i+1][1],cnt[i][j]);
        up(cnt[i+1][j+1],mod-cnt[i][j]);
      }
      for(int j=1;j<K;j++){
        up(cnt[i+1][j],cnt[i+1][j-1]);
      }
      for(int j=1;j<K;j++){
        up(cnt[i+1][j+1],1LL*cnt[i][j]*(K-j)%mod);
        //if(j>=m)up(cnt[i][j],f[i][j]);
      }
    }
    int res=0;
    for(int i=1;i<K;i++)up(res,cnt[n][i]);
    //printf("res %d\n",res);
    res=1LL*res*fac[K-m]%mod*fac_inv[K]%mod;
    up(ans,mod-res);
  }else{
    for(int i=0;i+L<=n;i++){
      for(int j=L;j<K;j++){
        up(gL[i],1LL*f[i+L][j]*fac[K-L]%mod*fac_inv[K]%mod);
      }
    }
    for(int i=0;i+R<=n;i++){
      for(int j=R;j<K;j++){
        up(gR[i],1LL*f[i+R][j]*fac[K-R]%mod*fac_inv[K]%mod);
      }
    }
    for(int i=0;i+m<=n;i++){
      up(ans,mod-1LL*gL[i]*gR[n-m-i]%mod);
    }
  }
  printf("%d\n",ans);
  return 0;
}