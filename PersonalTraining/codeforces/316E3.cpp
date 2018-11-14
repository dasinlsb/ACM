/*
记\sum_{L<=i<=R}f[i-L]*a[i]为s[i-L]，原题中的每次询问相当于求s[0]
可以先开两棵线段树分别表示
f[0]*a[1]+f[1]*a[2]+...f[n-1]*f[n]
f[1]*a[1]+f[2]*a[2]+...f[n]*f[n]
这样的话对于每个左端点L,s[L]和s[L+1]是可以求出的
s[i]也有s[i]=s[i-1]+s[i-2]这样的关系,所以由s[L]和s[L+1]可以倒过来用矩阵乘法快速求出s[0]
区间加，单点修改都是可以在线段树上维护的
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=200005;
const int maxm=1<<19;
const int mod=1e9;
int n,m,a[maxn];
inline void up(int&x,int y){
  if(x+=y,x>=mod)x-=mod;
}
struct Tree{
  int f[maxn],sum[maxn];
  int val[maxm],lp[maxm],rp[maxm],tag[maxm];
  void Add(int v,int x){
    up(tag[x],v);
    up(val[x],1LL*v*(sum[rp[x]]-sum[lp[x]-1]+mod)%mod);
  }
  void push_down(int x){
    if(tag[x]){
      Add(tag[x],x<<1);
      Add(tag[x],x<<1|1);
      tag[x]=0;
    }
  }
  void push_up(int x){
    val[x]=(val[x<<1]+val[x<<1|1])%mod;
  }
  void build(int l,int r,int x){
    lp[x]=l;rp[x]=r;
    if(l==r){
      val[x]=1LL*a[l]*f[l]%mod;
      return;
    }
    int mid=l+r>>1;
    build(l,mid,x<<1);
    build(mid+1,r,x<<1|1);
    push_up(x);
  }
  void change(int v,int p,int l,int r,int x){
    if(l==r){
      val[x]=1LL*v*f[l]%mod;
      return;
    }
    push_down(x);
    int mid=l+r>>1;
    if(p<=mid)change(v,p,l,mid,x<<1);
    else change(v,p,mid+1,r,x<<1|1);
    push_up(x);
  }
  void add(int v,int L,int R,int l,int r,int x){
    if(l>=L && r<=R){
      Add(v,x);
      return;
    }
    push_down(x);
    int mid=l+r>>1;
    if(L<=mid)add(v,L,R,l,mid,x<<1);
    if(R>mid)add(v,L,R,mid+1,r,x<<1|1);
    push_up(x);
  }
  int ask(int L,int R,int l,int r,int x){
    if(l>=L && r<=R){
      return val[x];
    }
    push_down(x);
    int mid=l+r>>1,res=0;
    if(L<=mid)up(res,ask(L,R,l,mid,x<<1));
    if(R>mid)up(res,ask(L,R,mid+1,r,x<<1|1));
    return res;
  }
  void init(int x,int y){
    f[0]=x;f[1]=y;
    for(int i=2;i<=n;i++)f[i]=(f[i-1]+f[i-2])%mod;
    for(int i=1;i<=n;i++)sum[i]=(f[i]+sum[i-1])%mod;
    build(1,n,1);
  }
}t[2];
int calc(int s0,int s1,int k){
  static int A[2],B[2][2];
  static int _A[2],_B[2][2];
  A[0]=s0,A[1]=s1;
  B[0][0]=mod-1;B[0][1]=1;
  B[1][0]=1;B[1][1]=0;
  for(;k;k>>=1){
    if(k&1){
      for(int j=0;j<2;j++){
        _A[j]=0;
        for(int k=0;k<2;k++){
          up(_A[j],1LL*A[k]*B[k][j]%mod);
        }
      }
      for(int i=0;i<2;i++)A[i]=_A[i];
    }
    for(int i=0;i<2;i++){
      for(int j=0;j<2;j++){
        _B[i][j]=0;
        for(int k=0;k<2;k++){
          up(_B[i][j],1LL*B[i][k]*B[k][j]%mod);
        }
      }
    }
    for(int i=0;i<2;i++)for(int j=0;j<2;j++){
      B[i][j]=_B[i][j];
    }
  }
  return A[0];
}
int main(){
  // freopen("aa.in","r",stdin);
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++)scanf("%d",a+i);
  t[0].init(1,1);
  t[1].init(1,2);
  for(;m--;){
    int op,x,y,d;
    scanf("%d%d%d",&op,&x,&y);
    if(op==1){
      t[0].change(y,x,1,n,1);
      t[1].change(y,x,1,n,1);
    }else
    if(op==2){
      int s0=t[0].ask(x,y,1,n,1);
      int s1=t[1].ask(x,y,1,n,1);
      int res=calc(s0,s1,x);
      printf("%d\n",res);
    }else
    if(op==3){
      scanf("%d",&d);
      t[0].add(d,x,y,1,n,1);
      t[1].add(d,x,y,1,n,1);
    }
  }
  return 0;
}