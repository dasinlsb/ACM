/*
所有直径肯定交于一点记为root，可以先求出任意一条直径，相当于一条链上的每个点挂着一棵树，预处理每个点在子树中的最长和次长链长度，经过这个点x的直径可能有3种形态
一种是最长和次长链组合起来，显然x就是root,否则可能是最长链和左边或者右边组合，可以前缀或者后缀+1然后取经过次数最多的点作为root即可
然后预处理root往下的每个子树的最长链，讨论一下最大长度有多少个
假设最大长度只有一个，那么要么把这个子树删掉，要么把次大的长度全部删掉
假设最大长度不止一个，设有k个，那么只要删代价最小的k-1个即可
以上的问题单独考虑就是求删除掉子树中的所有最长链的最小代价，可以树形dp解决
时间复杂度O(n)
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=200005;
int n,Len,ed=1,fir[maxn];
int in_path[maxn],dis[maxn];
int down[maxn],down1[maxn],down2[maxn];
int fae[maxn];
struct Edge{
  int u,v,w,c,nxt;
}e[maxn];
inline void adde(int x,int y,int w,int c){
  e[++ed].u=x;e[ed].v=y;e[ed].w=w;e[ed].c=c;
  e[ed].nxt=fir[x];fir[x]=ed;
}
void dfs1(int x,int y){
  for(int i=fir[x];i;i=e[i].nxt){
    if(e[i].v==y)continue;
    dis[e[i].v]=dis[x]+e[i].w;
    dfs1(e[i].v,x);
  }
}
vector<int> prepare(){
  dis[1]=0;
  dfs1(1,0);
  int from=1;
  for(int i=1;i<=n;i++){
    if(dis[i]>dis[from])from=i;
  }
  dis[from]=0;
  dfs1(from,0);
  int to=1;
  for(int i=1;i<=n;i++){
    if(dis[i]>dis[to])to=i;
  }
  Len=dis[to];
  vector<int>res;
  for(int x=to;;){
    res.push_back(x);
    if(x==from)break;
    for(int i=fir[x];i;i=e[i].nxt){
      if(dis[e[i].v]+e[i].w==dis[x]){
        x=e[i].v;
        break;
      }
    }
  }
  reverse(res.begin(),res.end());
  return res;
}
void dfs2(int x,int y){
  for(int i=fir[x];i;i=e[i].nxt){
    if(e[i].v==y || in_path[e[i].v])continue;
    dfs2(e[i].v,x);
    down[e[i].v]=down1[e[i].v]+e[i].w;
    if(down[e[i].v]>down1[x]){
      down2[x]=down1[x];
      down1[x]=down[e[i].v];
    }else if(down[e[i].v]>down2[x]){
      down2[x]=down[e[i].v];
    }
  }
}
void dfs3(int x,int y){
  for(int i=fir[x];i;i=e[i].nxt){
    if(e[i].v==y)continue;
    dfs3(e[i].v,x);
    fae[e[i].v]=i;
    down[e[i].v]=down1[e[i].v]+e[i].w;
    if(down[e[i].v]>down1[x])down1[x]=down[e[i].v];
  }
}
int sub[maxn];
vector<int>pri[maxn];
void dfs4(int x,int y){//del longest chain in subtree
  for(int i=fir[x];i;i=e[i].nxt){
    if(e[i].v==y)continue;
    dfs4(e[i].v,x);
  }
  vector<int>q;
  for(int i=fir[x];i;i=e[i].nxt){
    if(e[i].v==y)continue;
    q.push_back(e[i].v);
  }
  if(q.size()==0)sub[x]=(int)1e9;
  sort(q.begin(),q.end(),[&](int x,int y){
    return down[x]>down[y];
  });
  for(int i=0;i<q.size() && down[q[i]]==down[q[0]];i++){
    int v=q[i];
    pri[x].push_back(v);
    sub[v]=min(sub[v],e[fae[v]].c);
    sub[x]+=sub[v];
  }
}
vector<int>removed;
void dfs5(int x,int y){
  if(e[fae[x]].c==sub[x]){
    removed.push_back(fae[x]>>1);
    return;
  }
  for(int v:pri[x]){
    dfs5(v,x);
  }
}
int cost;
void remove(int x,int y){
  cost+=sub[x];
  dfs5(x,y);
}
void solve(int root){
  static int q[maxn];
  int cnt=0;
  for(int i=fir[root];i;i=e[i].nxt){
    q[++cnt]=e[i].v;
  }
  sort(q+1,q+1+cnt,[&](int x,int y){
    return down[x]>down[y];
  });
  int c1,c2;
  for(c1=1;c1<=cnt && down[q[c1]]==down[q[1]];c1++){
    int v=q[c1];
    dfs4(v,root);
    sub[v]=min(e[fae[v]].c,sub[v]);
  }
  for(c2=c1;c2<=cnt && down[q[c2]]==down[q[c1]];c2++){
    int v=q[c2];
    dfs4(v,root);
    sub[v]=min(e[fae[v]].c,sub[v]);
  }
  // for(int i=1;i<=n;i++){
  //   printf("sub %d %d\n",i,sub[i]);
  // }
  // for(int x=1;x<=n;x++){
  //   for(int v:pri[x]){
  //     printf("pri %d %d\n",x,v);
  //   }
  // }
  if(cnt==1){
    remove(q[1],root);
  }else
  if(c1==2){
    int small=0;
    for(int i=c1;i<c2;i++)small+=sub[q[i]];
    if(sub[q[1]]<small){
      remove(q[1],root);
    }else{
      for(int i=c1;i<c2;i++){
        remove(q[i],root);
      }
    }
  }else
  if(c1>2){
    sort(q+1,q+c1,[&](int x,int y){
      return sub[x]<sub[y];
    });
    for(int i=1;i<c1-1;i++){
      remove(q[i],root);
    }
  }else{
    assert(0);
  }
}
int sum[maxn];
int main(){
  // freopen("aa.in","r",stdin);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  scanf("%d",&n);
  for(int i=1;i<n;i++){
    int x,y,w,c;
    scanf("%d%d%d%d",&x,&y,&w,&c);
    adde(x,y,w,c);
    adde(y,x,w,c);
  }
  vector<int>path=prepare();
  for(int x:path)in_path[x]=1;
  for(int i=0;i<path.size();i++){
    int x=path[i];
    dfs2(x,0);

    if(down1[x]+down2[x]==Len){
      sum[i]++;
      sum[i+1]--;
    }
    if(down1[x]+dis[x]==Len){
      sum[0]++;
      sum[i+1]--;
    }
    if(down1[x]+dis[path.back()]-dis[x]==Len){
      sum[i]++;
      sum[path.size()]--;
    }
  }
  int root=0;
  for(int i=1;i<path.size();i++){
    sum[i]+=sum[i-1];
    if(sum[i]>sum[root])root=i;
  }
  root=path[root];
  // printf("root %d\n",root);
  dfs3(root,0);
  solve(root);
  sort(removed.begin(),removed.end());
  removed.resize(unique(removed.begin(),removed.end())-removed.begin());
  printf("%d\n%d\n",cost,int(removed.size()));
  for(int i:removed)printf("%d ",i);
  return 0;
}
