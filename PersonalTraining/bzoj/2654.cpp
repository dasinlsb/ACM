#include <bits/stdc++.h>
using namespace std;
const int maxn=50005;
const int maxm=100005;
int n,m,need,f[maxn];
struct Edge{
  int u,v,w,c;
  void read(){scanf("%d%d%d%d",&u,&v,&w,&c);}
}qe[maxm];
int F(int x){
  return x==f[x]?x:f[x]=F(f[x]);
}
bool cmp(const Edge&x,const Edge&y){
  return x.w<y.w || x.w==y.w && x.c<y.c;
}
pair<int,int>Kruscal(int v){
  for(int i=1;i<=m;i++)if(qe[i].c==0){
    qe[i].w+=v;
  }
  sort(qe+1,qe+1+m,cmp);
  pair<int,int>res=make_pair(0,0);
  for(int i=0;i<n;i++){
    f[i]=i;
  }
  for(int i=1;i<=m;i++){
    int x=qe[i].u,y=qe[i].v;
    if(F(x)==F(y))continue;
    f[f[x]]=f[y];
    if(qe[i].c==0)res.first++;
    res.second+=qe[i].w;
  }
  for(int i=1;i<=m;i++)if(qe[i].c==0){
    qe[i].w-=v;
  }
  return res;
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d%d%d",&n,&m,&need);
  for(int i=1;i<=m;i++){
    qe[i].read();
  }
  int l=-100,r=100;
  for(;l<=r;){
    int mid=l+r>>1;
    pair<int,int>now=Kruscal(mid);
    if(now.first>=need)l=mid+1;
    else r=mid-1;
  }
  // printf("r %d\n",r);
  pair<int,int>now=Kruscal(r);
  assert(now.first>=need);
  int ans=now.second-need*r;
  printf("%d\n",ans);
  return 0;
}