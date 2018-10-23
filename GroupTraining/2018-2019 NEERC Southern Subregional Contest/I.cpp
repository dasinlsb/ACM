/*
首先有个性质，每个公司拥有2条路肯定比1条路优，然后这2条路有1个公共点最优
发现这样的性质之后问题就十分简单了，对于每个点根据它的度数是可以直接确定它的出边中有多少对同公司的路，然后就是经典的最大流了
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=605;
const int inf=maxn*4;

int n,m,kk,deg[maxn];
pair<int,int>qe[maxn];
int ed,fir[maxn*2];
struct Edge{int v,w,nxt;}e[maxn*8];
int S,T,tot,h[maxn*2],gap[maxn*2];
int col[maxn];
inline void adde(int x,int y,int z){
  e[++ed].v=y;e[ed].w=z;e[ed].nxt=fir[x];fir[x]=ed;
  e[++ed].v=x;e[ed].w=0;e[ed].nxt=fir[y];fir[y]=ed;
}
int sap(int x,int flow){
  if(x==T)return flow;
  int minh=tot,dec=0;
  for(int i=fir[x];i;i=e[i].nxt)if(e[i].w){
    if(h[x]==h[e[i].v]+1){
      int tmp=sap(e[i].v,min(e[i].w,flow-dec));
      e[i].w-=tmp;
      e[i^1].w+=tmp;
      dec+=tmp;
      if(dec==flow)return flow;
      if(h[S]>=tot)return dec;
    }
    minh=min(minh,h[e[i].v]);
  }
  if(dec==0){
    if(!(--gap[h[x]]))h[S]=tot;
    gap[h[x]=minh+1]++;
  }
  return dec;
}
int max_flow(){
  for(int i=1;i<=tot;i++){
    h[i]=0;
    gap[i]=0;
  }
  int res=0;
  for(gap[0]=tot;h[S]<tot;res+=sap(S,inf));
  return res;
}
int main(){
  freopen("aa.in","r",stdin);
  int _;scanf("%d",&_);
  for(;_--;){
    scanf("%d%d%d",&n,&m,&kk);
    tot=n+m;S=++tot;T=++tot;
    ed=1;
    fill(deg+1,deg+1+n,0);
    fill(col+1,col+1+m,0);
    for(int i=1;i<=tot;i++){
      fir[i]=0;
    }
    for(int i=1;i<=m;i++){
      int x,y;scanf("%d%d",&x,&y);
      qe[i]=make_pair(x,y);
      deg[x]++;deg[y]++;
    }
    for(int i=1;i<=m;i++){
      adde(S,i,1);
      adde(i,qe[i].first+m,1);
      adde(i,qe[i].second+m,1);
    }
    int sum_need=0;
    for(int i=1;i<=n;i++){
      int need=max(deg[i]-kk,0)*2;
      sum_need+=need;
      adde(m+i,T,need);
    }
    int flow=max_flow();
    if(flow!=sum_need){
      for(int i=1;i<=m;i++)printf("0 ");
      puts("");
      continue;
    }
    int col_cnt=0;
    for(int x=1;x<=n;x++){
      vector<int>q;
      for(int i=fir[x+m];i;i=e[i].nxt)if(i%2==1 && e[i].w){
        q.push_back(e[i].v);
      }
      assert(q.size()%2==0);
      for(int i=1;i<q.size();i+=2)col[q[i]]=col[q[i-1]]=++col_cnt;
    }
    for(int i=1;i<=m;i++){
      if(!col[i])col[i]=++col_cnt;
      printf("%d ",col[i]);
    }
    puts("");
  }

  return 0;
}