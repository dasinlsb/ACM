/*
正面dp可以设f[i][j][k]表示i子树保留j个点(包括i)且保留连通块向下的最长链是k的最小直径
在转移时题目给出的生成方式对于第二维的关于size的卷积没有有效的优化帮助
考虑题中生成树的方式可以保证的是以1为根时树高大概只有log(n)
可以反向dp，f[i][j][k]表示i子树向下最长链为j连通块的直径<=k时可以保留的最多的点数
第三维可以直接用全局变量枚举而不用记到状态里面去，此外后两维的上界都可以直接设25左右，复杂度就是对了
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
const int maxk=38;
int n,Diameter;
int fa[maxn],down[maxn];
int f[maxn][maxk],g[maxk];
int ans[maxn];
vector<int>G[maxn];
void cmax(int&x,int y){if(y>x)x=y;}
void cmin(int&x,int y){if(y<x)x=y;}
void dp(int x){
  f[x][1]=1;
  down[x]=1;
  for(int v:G[x]){
    if(v==fa[x])continue;
    fa[v]=x;
    dp(v);
    for(int i=1;i<=down[x];i++){
      for(int j=0;j<=down[v] && i+j<=Diameter;j++){
        cmax(g[max(i,j+1)],f[x][i]+f[v][j]);
      }
    }
    cmax(down[x],down[v]+1);
    for(int i=1;i<=down[x];i++){
      cmax(f[x][i],g[i]);
      g[i]=0;
    }
  }
  for(int i=1;i<=down[x];i++){
    cmin(ans[f[x][i]],Diameter);
  }
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d",&n);
  for(int i=1;i<n;i++){
    int x,y;
    scanf("%d%d",&x,&y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  for(int i=1;i<=n;i++)ans[i]=n+1;
  for(Diameter=1;Diameter<=maxk*2;Diameter++){
    memset(f,0,sizeof f);
    dp(1);
  }
  for(int i=n-1;i>0;i--)cmin(ans[i],ans[i+1]);
  for(int i=n;i>0;i--){
    assert(ans[i]<=n);
    printf("%d ",ans[i]-1);
  }
  return 0;
}