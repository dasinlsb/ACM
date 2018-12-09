/*
将高度离散成排列后对于h[i]<h[j]，如果s[i][j]==1肯定无解，否则讨论一下s[j][i]
如果s[j][i]==1，那么j肯定位于以i为右上角的矩阵中，也就是x[j]<=x[i]
如果s[j][i]==0，那么j位于以(x[i]+1,y[i]-1)为左上角的矩阵中，有x[j]>=x[i]+1
根据上面两个约束判一下是否有正环(因为已经判了无解所以肯定不存在全零环)
否则，由于第一行的元素个数不小于其他行，所以min(dist[i])就是答案
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=1005;
int n,ed,fir[maxn],id[maxn],s[maxn][maxn],deg[maxn],q[maxn],dis[maxn];
pair<int,int> a[maxn];
char str[maxn];
struct Edge{
  int v,w,nxt;
}e[maxn*maxn];
void adde(int x,int y,int w){
  e[++ed].v=y;e[ed].w=w;e[ed].nxt=fir[x];fir[x]=ed;deg[y]++;
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d",&n);
  for(int i=1;i<=n;i++){
    scanf("%d",&a[i].first);
    a[i].second=i;
  }
  sort(a+1,a+1+n);
  for(int i=1;i<=n;i++){
    id[a[i].second]=i;
  }
  for(int i=1;i<=n;i++){
    scanf("%s",str+1);
    for(int j=1;j<=n;j++){
      s[id[i]][id[j]]=str[j]-'0';
    }
  }
  for(int i=1;i<=n;i++){
    for(int j=i+1;j<=n;j++){
      if(s[i][j])return puts("-1"),0;
      if(s[j][i]){
        adde(j,i,0);
      }else{
        adde(i,j,1);
      }
    }
  }
  int h=1,t=0;
  for(int i=1;i<=n;i++){
    if(!deg[i])q[++t]=i;
  }
  for(;h<=t;){
    int x=q[h++];
    for(int i=fir[x];i;i=e[i].nxt){
      dis[e[i].v]=max(dis[e[i].v],dis[x]+e[i].w);
      if(!(--deg[e[i].v]))q[++t]=e[i].v;
    }
  }
  if(t!=n)return puts("-1"),0;
  int ans=0;
  for(int i=1;i<=n;i++)ans=max(ans,dis[i]);
  printf("%d\n",ans+1);
  return 0;
}
