/*
直接从左到右递推合法序列比较困难，由于是01序列，LIS肯定是000...111的形式，可以考虑划分成前后两部分dp
枚举分界线mid，假设序列已知，那么[1,mid]要贡献出所有LIS中最多的0
那么在[1,mid]中，可以把1看作-1，0看作1，要保证任一位置处的后缀和都>=0，同时[mid+1,n]如果把1看作1，0看作-1，任一位置的前缀和都要>0，这个可以用O(n^2)的简单dp解决
时间复杂度O(n^3)
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=505;
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
  return t;
}
int n;
int P[maxn],nP[maxn];
int f[maxn][maxn];
int main(){
  freopen("aa.in","r",stdin);
  int inv1k=Pow(1000,mod-2);
  scanf("%d",&n);
  for(int i=1;i<=n;i++){
    scanf("%d",P+i);
    nP[i]=1000-P[i];
  }
  int ans=0;
  for(int mid=0;mid<=n;mid++){
    memset(f,0,sizeof(f));
    f[mid][1]=nP[mid];
    for(int i=mid;i>1;i--){
      for(int j=0;j<=mid+1-i;j++){
        if(!f[i][j])continue;
        up(f[i-1][j+1],1LL*nP[i-1]*f[i][j]%mod);
        if((mid+1-i-j+1)*2<=mid+1-i+1){
          up(f[i-1][j],1LL*P[i-1]*f[i][j]%mod);
        }
      }
    }
    f[mid+1][1]=P[mid+1];
    for(int i=mid+1;i<n;i++){
      for(int j=0;j<=i-mid;j++){
        if(!f[i][j])continue;
        up(f[i+1][j+1],1LL*P[i+1]*f[i][j]%mod);
        if((i-mid-j+1)*2<i-mid+1){
          up(f[i+1][j],1LL*nP[i+1]*f[i][j]%mod);
        }
      }
    }
    for(int pre=0;pre<=mid;pre++){
      for(int suf=0;suf<=n-mid;suf++){
        int prob=1LL*(mid==0?(pre==0):f[1][pre])*(mid==n?(suf==0):f[n][suf])%mod;
        int res=1LL*pre*(pre+suf)%mod*prob%mod;
        up(ans,res);
      }
    }
  }
  printf("%d\n",ans);
  return 0;
}