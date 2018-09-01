/*
单独考虑关于某种颜色c的询问，将这种颜色c染成黑色，其他都染成白色，问题转化为询问某个点集中所有点到黑点的最大距离
所有黑点以及使它们联通所必须的点和边共同组成了一个生成树，不妨考虑这棵生成树的直径，显然上述问题的答案必定在直径的两个端点处取到，否则用反证法可推出矛盾
那么也就是说对于同一种颜色，我们只要保留对应直径的端点即可，如果直径有多条，选任意一条都是等价的
求树的直径有个经典的做法，遍历所有点，同时维护距离最远的二元组(x,y)，假设当前在点z，用(x,z)(y,z)更新，也可以很容易看出这样不会丢失答案
询问的时候直接暴力扫四组点对取最优即可
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
const int maxk=18;
int n,qn,cn,c[maxn];
vector<int >que[maxn],G[maxn];
int fa[maxn][maxk],dep[maxn];
tuple<int,int,int >best[maxn];
map<int,int >vis;
void dfs(int x){
  for(int i=1;i<maxk;i++){
    fa[x][i]=fa[fa[x][i-1]][i-1];
  }
  for(int v:G[x])if(v!=fa[x][0]){
    fa[v][0]=x;
    dep[v]=dep[x]+1;
    dfs(v);
  }
}
int ask_lca(int x,int y){
  if(dep[x]<dep[y])swap(x,y);
  for(int i=maxk-1;~i;i--)if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
  if(x==y)return x;
  for(int i=maxk-1;~i;i--)if(fa[x][i]!=fa[y][i]){x=fa[x][i],y=fa[y][i];}
  return fa[x][0];
}
int ask_dist(int x,int y){
  int res=dep[x]+dep[y]-2*dep[ask_lca(x,y)];
  return res;
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d%d",&n,&qn);
  for(int i=1;i<=n;i++){
    scanf("%d",c+i);
    if(!vis.count(c[i]))vis[c[i]]=++cn;
  }
  for(int i=1;i<=n;i++){
    c[i]=vis[c[i]];
    que[c[i]].push_back(i);
  }
  for(int i=1;i<n;i++){
    int x,y;scanf("%d%d",&x,&y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  fa[1][0]=1;
  dfs(1);
  for(int i=1;i<=cn;i++){
    best[i]=make_tuple(0,que[i][0],que[i][0]);
    for(int j:que[i]){
      tuple<int,int,int > p1=make_tuple(ask_dist(j,get<1>(best[i])),j,get<1>(best[i]));
      tuple<int,int,int > p2=make_tuple(ask_dist(j,get<2>(best[i])),j,get<2>(best[i]));
      best[i]=max(best[i],p1);
      best[i]=max(best[i],p2);
    }
  }
  for(;qn--;){
    int x,y;scanf("%d%d",&x,&y);
    if(!vis.count(x)||!vis.count(y)){
      puts("0");
      continue;
    }
    x=vis[x];y=vis[y];
    int res=0;
    res=max(res,ask_dist(get<1>(best[x]),get<1>(best[y])));
    res=max(res,ask_dist(get<1>(best[x]),get<2>(best[y])));
    res=max(res,ask_dist(get<2>(best[x]),get<1>(best[y])));
    res=max(res,ask_dist(get<2>(best[x]),get<2>(best[y])));
    printf("%d\n",res);
  }
  return 0;
}