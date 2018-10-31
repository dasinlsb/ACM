/*
对于一个\sum_a[i]==\sum_b[i]的连通块，无论考虑哪个点，我们都可以花费至多n次调度使得这个点被满足且不影响其他点的合法性
由于边没有流量上限，所有对于一个连通块只需要考虑它的生成树，从叶子节点开始比较方便，如果a[i]>b[i]则每次尽量清空相邻节点，然后尽量把多余的a[i]送出去，由于删去叶子节点不影响连通性，所以直接贪心地调度是保证不会丢失合法解的
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=305;
int n,V,m,a[maxn],b[maxn],f[maxn],deg[maxn],vis[maxn];
vector<int>G[maxn],ans;
int F(int x){return x==f[x]?x:f[x]=F(f[x]);}
void trans(int x,int y,int z){
  a[x]-=z;
  a[y]+=z;
  ans.push_back(x);
  ans.push_back(y);
  ans.push_back(z);
}
void up(int x,int y,int to=V){
  if(a[x]>=to)return;
  for(int v:G[x])if(!vis[v] && v!=y){
    up(v,x);
    if(a[v]+a[x]>=to){
      trans(v,x,to-a[x]);
      break;
    }else{
      trans(v,x,a[v]);
    }
  }
}
void down(int x,int y,int to=0){
  if(a[x]<=to)return;
  for(int v:G[x])if(!vis[v] && v!=y){
    down(v,x);
    if(a[x]-(V-a[v])<=to){
      trans(x,v,a[x]-to);
      break;
    }else{
      trans(x,v,V-a[v]);
    }
  }
}
int work(){
  queue<int>q;
  for(int i=1;i<=n;i++)if(deg[i]==1){
    q.push(i);
  }
  for(;q.size();){
    int x=q.front();q.pop();
    vis[x]=1;
    if(a[x]<b[x]){
      up(x,0,b[x]);
    }else if(a[x]>b[x]){
      down(x,0,b[x]);
    }
    for(int v:G[x])if(!vis[v]){
      if((--deg[v])==1)q.push(v);
    }
  }
  for(int i=1;i<=n;i++)if(a[i]!=b[i])return 0;
  return 1;
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d%d%d",&n,&V,&m);
  for(int i=1;i<=n;i++){
    scanf("%d",a+i);
  }
  for(int i=1;i<=n;i++){
    scanf("%d",b+i);
    f[i]=i;
  }
  for(int i=1;i<=m;i++){
    int x,y;scanf("%d%d",&x,&y);
    if(F(x)==F(y))continue;
    f[f[x]]=f[y];
    G[x].push_back(y);
    G[y].push_back(x);
    deg[x]++;
    deg[y]++;
  }
  if(!work())return puts("NO"),0;
  printf("%d\n",int(ans.size())/3);
  for(int i=0;i<ans.size();i++){
    printf("%d%c",ans[i],i%3==2?'\n':' ');
  }
  return 0;
}