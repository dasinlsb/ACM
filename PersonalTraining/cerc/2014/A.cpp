/*
对于每条给出的路径只在lca处决定是否选取
f[x][i]表示x子树，第i个儿子未选的方案数
对于一条给出的路径(x,y)，假设z=lca(x,y)，这条路径的贡献就可以在f[z][S]中统计到，转移是z-x,z-y两条路径上的f和，可以O(n)暴力转移
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=1005;
const int maxdeg=10;
int n,m,fa[maxn],dep[maxn],to_root[maxn],used[maxn][1<<maxdeg];
int pos_in_sons[maxn],nextv[maxn][maxn],alls[maxn];
vector<int> G[maxn],another[maxn],sub_status[1<<maxdeg];
vector< pair<int,int> > qry[maxn];
void cmax(int&x,int y){
  if(y>x)x=y;
}
void dfs_init(int x){
  for(int i=0;i<G[x].size();i++){
    int v=G[x][i];
    if(v==fa[x]){
      swap(G[x][i],G[x].back());
      G[x].pop_back();
      i--;continue;
    }
    pos_in_sons[v]=i;
    fa[v]=x;
    dep[v]=dep[x]+1;
    dfs_init(v);
  }
  alls[x]=(1<<G[x].size())-1;
}
void calc_path(int x,int y,int&value,int&status){
  if(x==y)return;
  int z=nextv[x][y];
  status|=1<<pos_in_sons[z];
  value+=used[y][alls[y]]+to_root[y];
}
void update_to_root(int x,int s){
  to_root[x]+=s;
  for(auto v:G[x]){
    update_to_root(v,s);
  }
}
void calc_dp(int x){
  for(int i=0;i<=alls[x];i++){
    used[x][i]=0;
  }
  for(int i=0;i<G[x].size();i++){
    int v=G[x][i];
    calc_dp(v);
    cmax(used[x][1<<i],used[v][alls[v]]);
  }
  for(auto p:qry[x]){
    int value=1,status=0;
    calc_path(x,p.first,value,status);
    calc_path(x,p.second,value,status);
    cmax(used[x][status],value);
  }
  for(int s=0;s<=alls[x];s++){
    for(auto _s:sub_status[s]){
      cmax(used[x][s],used[x][s^_s]+used[x][_s]);
    }
  }
  for(int i=0;i<G[x].size();i++){
    update_to_root(G[x][i],used[x][alls[x]^1<<i]);
  }
}
void calc_nextv(int x,int y,int fst,int snd){
  nextv[fst][x]=snd;
  for(auto v:G[x]){
    if(v==y)continue;
    calc_nextv(v,x,fst,snd);
  }
}
int vis[maxn],anc[maxn];
int ask_anc(int x){
  return x==anc[x]?x:anc[x]=ask_anc(anc[x]);
}
void tarjan(int x){
  for(int v:G[x]){
    tarjan(v);
    anc[ask_anc(v)]=ask_anc(x);
  }
  for(int y:another[x]){
    if(vis[y]){
      qry[ask_anc(y)].push_back(make_pair(x,y));
    }
  }
  vis[x]=1;
}
int main(){
  freopen("aa.in","r",stdin);
  for(int i=0;i<1<<maxdeg;i++){
    for(int j=0;j<=i;j++){
      if((j&i)==j && __builtin_popcount(j)<=2){
        sub_status[i].push_back(j);
      }
    }
  }
  int _;scanf("%d",&_);
  for(;_--;){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
      G[i].clear();
      qry[i].clear();
      another[i].clear();
      to_root[i]=0;
      vis[i]=0;
      anc[i]=i;
    }
    for(int i=2;i<=n;i++){
      int x,y;scanf("%d%d",&x,&y);
      G[x].push_back(y);
      G[y].push_back(x);
    }
    for(int x=1;x<=n;x++){
      for(auto v:G[x]){
        calc_nextv(v,x,x,v);
      }
    }
    dfs_init(1);
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
      int x,y;
      scanf("%d%d",&x,&y);
      another[x].push_back(y);
      another[y].push_back(x);
    }
    tarjan(1);
    calc_dp(1);
    int ans=used[1][alls[1]];
    printf("%d\n",ans);
  }
  return 0;
}