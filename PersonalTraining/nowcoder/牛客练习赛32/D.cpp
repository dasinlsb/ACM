/*
考虑Kruscal的过程，肯定是从小到大考虑每种边权，在加入边权较小的边之后，对当前权值的边集一起考虑，必选边肯定是桥
每种边权的边加入后缩点跑下一轮
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=200005;

int n,m,P,ed,T,f[maxn],fir[maxn];
int dfn[maxn],low[maxn],fae[maxn],cut[maxn];
struct Edge{
  int u,v,w,nxt;
  void read(){scanf("%d%d%d",&u,&v,&w);}
}qe[maxn],e[maxn*2];

int F(int x){
  return x==f[x]?x:f[x]=F(f[x]);
}
void adde(int x,int y){
  e[++ed].v=y;e[ed].nxt=fir[x];fir[x]=ed;
}
void tarjan(int x){
  dfn[x]=low[x]=++T;
  for(int i=fir[x];i;i=e[i].nxt){
    if(!dfn[e[i].v]){
      fae[e[i].v]=i/2;
      tarjan(e[i].v);
      low[x]=min(low[x],low[e[i].v]);
    }else if(fae[x]!=i/2){
      low[x]=min(low[x],dfn[e[i].v]);
    }
  }
  if(fae[x] && low[x]==dfn[x])cut[fae[x]]=1;
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d%d%d",&n,&m,&P);
  for(int i=1;i<=m;i++){
    qe[i].read();
  }
  sort(qe+1,qe+1+m,[&](Edge x,Edge y){
    return x.w<y.w;
  });
  for(int i=1;i<=n;i++){
    f[i]=i;
  }
  int ans=0;
  ed=1;
  for(int cur=1;cur<=m;){
    int nxt;
    vector<int> vertex;
    for(nxt=cur;nxt<=m && qe[nxt].w==qe[cur].w;nxt++){
      int x=qe[nxt].u;
      int y=qe[nxt].v;
      int w=qe[nxt].w;
      if(F(x)==F(y))continue;
      adde(f[x],f[y]);
      adde(f[y],f[x]);
      vertex.push_back(f[x]);
      vertex.push_back(f[y]);
    }
    for(int x:vertex){
      if(!dfn[x])tarjan(x);
    }
    for(int i=1;i<=ed/2;i++){
      ans+=cut[i];
      cut[i]=0;
    }
    ed=1;T=0;
    for(int x:vertex){
      fae[x]=0;
      fir[x]=0;
      dfn[x]=0;
      low[x]=0;
    }
    for(;cur<nxt;cur++){
      int x=qe[cur].u;
      int y=qe[cur].v;
      int w=qe[cur].w;
      if(F(x)==F(y))continue;
      f[f[x]]=f[y];
    }
  }
  printf("%d\n",ans);
  return 0;
}