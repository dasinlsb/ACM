#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
const int mod=1e9+7;
inline void up(int&x,int y){
  if(x+=y,x>=mod)x-=mod;
}
int w[maxn],f[maxn];
int main(){
  freopen("aa.in","r",stdin);
  w[1]=1;
  w[2]=2;
  w[3]=5;
  w[4]=7;
  for(int i=5;i<maxn;i++)w[i]=3+2*w[i-2]-w[i-4];
  f[0]=1;
  for(int i=1;i<maxn;i++){
    for(int j=1;w[j]<=i;j++){
      if(j+1>>1&1)up(f[i],f[i-w[j]]);
      else up(f[i],mod-f[i-w[j]]);
    }
  }
  int _;scanf("%d",&_);
  for(;_--;){
    int n,kk;scanf("%d%d",&n,&kk);
    int ans=0;
    for(int i=0;w[i]*kk<=n;i++){
      if(i+1>>1&1)up(ans,mod-f[n-w[i]*kk]);
      else up(ans,f[n-w[i]*kk]);
    }
    printf("%d\n",ans);
  }
  return 0;
}