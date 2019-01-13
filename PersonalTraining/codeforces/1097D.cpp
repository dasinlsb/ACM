#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
long long n;
int kk,f[10005][70],inv[70];
void up(int&x,int y){
  if(x+=y,x>=mod)x-=mod;
}
int main(){
  freopen("aa.in","r",stdin);
  inv[0]=inv[1]=1;
  for(int i=2;i<70;i++)inv[i]=mod-1LL*mod/i*inv[mod%i]%mod;
  scanf("%lld%d",&n,&kk);
  long long copy=n;
  vector< pair<long long,int> > cut;
  for(int i=2;1LL*i*i<=n;i++){
    if(copy%i)continue;
    cut.push_back(make_pair(1LL*i,0));
    for(;copy%i==0;copy/=i)cut.back().second++;
  }
  if(copy!=1)cut.push_back(make_pair(copy,1));
  int ans=1;
  for(auto&it:cut){
    memset(f[0],0,70*sizeof(int));
    f[0][it.second]=1;
    for(int i=1;i<=kk;i++){
      for(int j=0;j<=it.second;j++){
        f[i-1][j]=1LL*f[i-1][j]*inv[j+1]%mod;
      }
      for(int j=it.second-1;j>=0;j--){
        up(f[i-1][j],f[i-1][j+1]);
      }
      for(int j=0;j<=it.second;j++){
        f[i][j]=f[i-1][j];
      }
    }
    int cur=0;
    int mul=1;
    for(int i=0;i<=it.second;i++){
      up(cur,1LL*f[kk][i]*mul%mod);
      mul=1LL*mul*it.first%mod;
    }
    ans=1LL*ans*cur%mod;
  }
  printf("%d\n",ans);
  return 0;
}