/*
如果点<=20那直接O(n*2^n)状压dp就可以了
现在边<=20，说明单个连通块内点<=21，又由于各个连通块直接独立，分别跑状压dp然后组合数合起来即可
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=41;
const int maxm=21;
const int mod=1e9+7;
int n,m,g[maxn][maxn],vis[maxn],pos[1<<maxm];
int fac[maxn],inv_fac[maxn],f[1<<maxm];
bool can[1<<maxm][maxn];
void up(int&x,int y){
  if(x+=y,x>=mod)x-=mod;
}
void dfs(int x,vector<int>&vertex){
  vis[x]=1;
  vertex.push_back(x);
  for(int i=0;i<n;i++){
    if(g[x][i] && !vis[i]){
      dfs(i,vertex);
    }
  }
}
int main(){
  freopen("aa.in","r",stdin);
  fac[0]=1;
  for(int i=1;i<maxn;i++)fac[i]=1LL*fac[i-1]*i%mod;
  inv_fac[0]=inv_fac[1]=1;
  for(int i=2;i<maxn;i++)inv_fac[i]=mod-1LL*mod/i*inv_fac[mod%i]%mod;
  for(int i=1;i<maxn;i++)inv_fac[i]=1LL*inv_fac[i]*inv_fac[i-1]%mod;
  for(int i=0;i<20;i++)pos[1<<i]=i;
  for(;~scanf("%d%d",&n,&m);){
    memset(g,0,sizeof g);
    memset(vis,0,sizeof vis);
    for(int i=0;i<m;i++){
      int x,y;
      scanf("%d%d",&x,&y);
      x--;y--;
      g[x][y]=1;
      g[y][x]=-1;
    }
    int ans=1;
    for(int root=0;root<n;root++){
      if(vis[root])continue;
      vector<int> vertex;
      dfs(root,vertex);
      for(int s=0;s<1<<vertex.size();s++){
        f[s]=0;
      }
      for(int i=0;i<vertex.size();i++){
        can[0][i]=1;
        f[1<<i]=1;
      }
      for(int s=1;s<1<<vertex.size();s++){
        for(int i=0;i<vertex.size();i++)if(~s>>i&1){
          can[s][i]=can[s^(s&-s)][i]&(g[vertex[pos[s&-s]]][vertex[i]]!=-1);
          if(can[s][i])up(f[s|1<<i],f[s]);
        }
      }
      ans=1LL*ans*f[(1<<vertex.size())-1]%mod*inv_fac[vertex.size()]%mod;
    }
    ans=1LL*ans*fac[n]%mod;
    printf("%d\n",ans);
  }
  return 0;
}