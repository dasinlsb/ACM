/*
考虑一个点x，在选x的时候其他点y能产生贡献的充要条件是x-y路径上任何一个点都还没有被删除
最终的操作序列显然是个1-n排列，只要在这个排列中x排在x-y路径上其他点前面就可以了，假设x-y路径上有k个点，那么方案数就是(n!/k!)*(k-1)!=n!/k
问题转化为对于1<=i<=n，统计树上距离为i的点对cnt[i]
点分治，对于当前整个连通块算一遍加到cnt中，然后对于每个子树都分别算一遍并在cnt中减去，fft加速
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
const int mod=1e9+7;
const double PI=acos(-1.0);
int n,ed=1,mnsz,blocksz,core,fir[maxn],sz[maxn],fa[maxn],dep[maxn],f[maxn];
long long paths[maxn];
struct Edge{
  int u,v,nxt,cut;
}e[maxn*2];
void adde(int x,int y){
  e[++ed].u=x;e[ed].v=y;e[ed].nxt=fir[x];fir[x]=ed;
}
int Pow(int x,int y){
  int t=1;
  for(;y;y>>=1){
    if(y&1)t=1LL*t*x%mod;
    x=1LL*x*x%mod;
  }
  return t;
}
const int fftmaxn=1<<19;
struct comp{
  double r,i;
  comp(){r=i=0;}
  comp(double _r,double _i){r=_r;i=_i;}
  comp operator+(comp t){return comp(r+t.r,i+t.i);}
  comp operator-(comp t){return comp(r-t.r,i-t.i);}
  comp operator*(comp t){return comp(r*t.r-i*t.i,r*t.i+i*t.r);}
}ff[fftmaxn];
int pos[fftmaxn];
void fft(comp a[],int n,int t){
  for(int i=0;i<n;i++)if(pos[i]>i)swap(a[i],a[pos[i]]);
  for(int d=1;d<n;d<<=1){
    double o=PI/d*t;
    comp _w(cos(o),sin(o));
    for(int i=0;i<n;i+=d+d){
      comp w(1,0);
      for(int j=0;j<d;j++){
        comp&A=a[i+j],&B=a[i+j+d],C=w*B;
        B=A-C;A=A+C;w=w*_w;
      }
    }
  }
  if(t==-1)for(int i=0;i<n;i++)a[i].r/=n;
}
void calc(int m,int sgn){
  int k,len;
  for(k=0,len=1;len<2*m+2;len<<=1,k++);
  for(int i=0;i<len;i++)pos[i]=pos[i>>1]>>1|((i&1)<<k-1);
  for(int i=0;i<=m;i++)ff[i]=comp(f[i],0);
  for(int i=m+1;i<len;i++)ff[i]=comp(0,0);
  fft(ff,len,1);
  for(int i=0;i<len;i++)ff[i]=ff[i]*ff[i];
  fft(ff,len,-1);
  for(int i=1;i<len && i-1<=n;i++){
    long long x=(long long)(ff[i].r+0.5)*sgn;
    paths[i-1]+=x;
  }
}
void findroot(int x,int y){
  sz[x]=1;
  int t=0;
  for(int i=fir[x];i;i=e[i].nxt)if(!e[i].cut && e[i].v!=y){
    findroot(e[i].v,x);
    sz[x]+=sz[e[i].v];
    t=max(t,sz[e[i].v]);
  }
  t=max(t,blocksz-sz[x]);
  if(t<mnsz)mnsz=t,core=x;
}
void dfs1(int x){
  sz[x]=1;
  for(int i=fir[x];i;i=e[i].nxt)if(!e[i].cut && e[i].v!=fa[x]){
    fa[e[i].v]=x;
    dep[e[i].v]=dep[x]+1;
    dfs1(e[i].v);
    sz[x]+=sz[e[i].v];
  }
}
void dfs2(int x){
  f[dep[x]+1]++;
  for(int i=fir[x];i;i=e[i].nxt)if(!e[i].cut && e[i].v!=fa[x]){
    dfs2(e[i].v);
  }
}
void solve(int x){
  fa[x]=0;
  dep[x]=0;
  dfs1(x);
  for(int i=fir[x];i;i=e[i].nxt)if(!e[i].cut){
    fill(f,f+sz[e[i].v]+2,0);
    dfs2(e[i].v);
    calc(sz[e[i].v]+1,-1);
  }
  fill(f,f+sz[x]+2,0);
  dfs2(x);
  calc(sz[x]+1,1);
  for(int i=fir[x];i;i=e[i].nxt)if(!e[i].cut){
    e[i^1].cut=1;
    blocksz=sz[e[i].v];
    mnsz=n;
    findroot(e[i].v,0);
    solve(core);
  }
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d",&n);
  for(int i=2;i<=n;i++){
    int x,y;
    scanf("%d%d",&x,&y);
    adde(x,y);
    adde(y,x);
  }
  if(n==1)return printf("1\n"),0;
  blocksz=n;
  mnsz=n;
  findroot(1,0);
  solve(core);
  int ans=0;
  for(int i=1;i<=n;i++){
    ans=(ans+1LL*Pow(i,mod-2)*paths[i])%mod;
  }
  for(int i=1;i<=n;i++){
    ans=1LL*ans*i%mod;
  }
  printf("%d\n",ans);
  return 0;
}