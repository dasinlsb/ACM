/*
边权从小到大考虑，相当于每次询问并合并两个连通块，可以用启发式的方法去做
假设当前边为(u,v,w),其中u,v所在的连通块的编号分别为fu,fv
枚举size小的那个连通块的所有点x，询问xorsum(x,u)^w^xorsum(v,y)的最大值
由于异或和有类似传递性的性质，可以预处理每个点x到1号点的路径异或和dis[x],那么上式可以拆成(dis[x]^dis[u]^w^dis[v])^dis[y]，可以直接在大连通块的trie里面询问
时间复杂度O(nlog^2(n))
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
const int maxk=18;
const int maxm=maxn*maxk*maxk/2;
int n,ed,fir[maxn],f[maxn],pos_e[maxn];
int root[maxn],dis[maxn];
vector<int>all[maxn];
int tot,val[maxm],son[maxm][2];
struct Edge{
  int u,v,w,nxt;
}e[maxn*2];
void adde(int x,int y,int z){
  e[++ed].u=x;e[ed].v=y;e[ed].w=z;
  e[ed].nxt=fir[x];fir[x]=ed;
}
void dfs1(int x,int y){
  for(int i=fir[x];i;i=e[i].nxt){
    if(e[i].v==y)continue;
    dis[e[i].v]=dis[x]^e[i].w;
    dfs1(e[i].v,x);
  }
}
int F(int x){
  return x==f[x]?x:f[x]=F(f[x]);
}
int ask(int v,int x){
  int res=0;
  for(int i=maxk-1;i>=0;i--){
    int w=v>>i&1;
    if(son[x][w^1])x=son[x][w^1],res|=1<<i;
    else x=son[x][w];
  }
  return res;
}
void ins(int v,int k,int&x){
  if(!x)x=++tot;
  val[x]++;
  if(k<0)return;
  ins(v,k-1,son[x][v>>k&1]);
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d",&n);
  for(int i=1;i<n;i++){
    int x,y,z;
    scanf("%d%d%d",&x,&y,&z);
    adde(x,y,z);
    adde(y,x,z);
    pos_e[z]=ed;
  }
  dfs1(1,0);
  for(int i=1;i<=n;i++){
    f[i]=i;
    all[i].push_back(i);
    ins(dis[i],maxk-1,root[i]);
  }
  for(int cl=1;cl<n;cl++){
    int p=pos_e[cl];
    int u=e[p].u,v=e[p].v;
    if(all[F(u)].size()>all[F(v)].size())swap(u,v);
    int res=0;
    for(int x:all[f[u]]){
      int tmp=dis[x]^dis[u]^e[p].w^dis[v];
      res=max(res,ask(tmp,root[f[v]]));
    }
    for(int x:all[f[u]]){
      ins(dis[x],maxk-1,root[f[v]]);
      all[f[v]].push_back(x);
      f[x]=f[v];
    }
    printf("%d ",res);
  }
  return 0;
}