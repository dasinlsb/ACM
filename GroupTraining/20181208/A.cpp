/*
斯坦纳树模板题,f[i][S]表示以i为根，4个关键点的选取状态为S的答案
外层枚举S，先从S的子集更新答案，然后层内跑Dijkstra
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=50005;
const int maxm=300005;
const long long inf=1e12;
int n,m,ed,fir[maxn],vip[4];
long long f[maxn][16];
struct Edge{
  int v,w,nxt;
}e[maxm*2];
void adde(int x,int y,int w){
  e[++ed].v=y;e[ed].w=w;e[ed].nxt=fir[x];fir[x]=ed;
}
int main(){
  // freopen("aa.in","r",stdin);
  scanf("%d%d",&n,&m);
  vip[0]=1;
  for(int i=1;i<4;i++){
    scanf("%d",vip+i);
  }
  for(int i=1;i<=m;i++){
    int x,y,z;
    scanf("%d%d%d",&x,&y,&z);
    adde(x,y,z);
    adde(y,x,z);
  }
  memset(f,63,sizeof f);
  for(int i=0;i<4;i++)f[vip[i]][1<<i]=0;
  for(int S=0;S<1<<4;S++){
    for(int i=1;i<=n;i++){
      for(int _S=(S-1)&S;_S;_S=(_S-1)&S){
        f[i][S]=min(f[i][S],f[i][_S]+f[i][S^_S]);
      }
    }
    typedef pair<long long,int> P;
    priority_queue< P,vector<P>,greater<P> > q;
    for(int i=1;i<=n;i++){
      q.push(P(f[i][S],i));
    }
    for(;q.size();){
      P t=q.top();q.pop();
      int x=t.second;
      if(f[x][S]<t.first)continue;
      for(int i=fir[x];i;i=e[i].nxt){
        if(f[e[i].v][S]>f[x][S]+e[i].w){
          q.push(P(f[e[i].v][S]=f[x][S]+e[i].w,e[i].v));
        }
      }
    }
  }
  long long ans=inf;
  for(int i=1;i<=n;i++){
    ans=min(ans,f[i][15]);
  }
  printf("%lld\n",ans);
  return 0;
}