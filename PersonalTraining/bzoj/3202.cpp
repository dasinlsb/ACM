/*
首先求一下本质不同的珠子的种类数，也就是满足1<=x<=y<=z<=a,(x,y,z)==1的三元组(x,y,z)数，很简单，假设求出来种类数为m
等价关系是对于圆排列而言的，也就是现在有n个循环排列形成置换群
对于循环移位为i的置换[i,i+1,i+2...i-2,i-1]，每个循环节长度都是n/gcd(n,i+1),也就是有gcd(n,i+1)个循环节
显然在任意时刻，一个循环节内部不会有相邻的元素，原序列中相邻对应每个循环节两端点相邻，由于一个循环节内部要染同一种颜色，所以也就是要求长度为gcd(n,i+1)的圆排列相邻染色不同的方案数
这个可以dp,f[n]=f[n-2]*(m-1)+f[n-1]*(m-2)，枚举第1个和第n-1个颜色是否相同可以得到这个转移
直接快速幂优化矩阵乘法常数比较大，稍微推一下可以得到f[n]=(m-1)^n+(m-1)*(-1)^n，可以直接快速幂求出
那么答案=(\sum_{d|n}f[d]*phi[n/d])/n
用常数比较小的做法小心计算大于sqrt(n)的phi即可
*/
#include <bits/stdc++.h>
using namespace std;
const long long maxn=1e14+5;
const int maxa=1e7+5;
const long long mod=1e9+7;
const long long mod2=mod*mod;
int pn,prim[maxa/10],phi[maxa],mu[maxa],sum_mu[maxa];
bool vis[maxa];
void Add(long long&x,long long y,long long z){x=(x+y)%z;}
long long Mul(long long x,long long y,long long z){
  if(y<0)y+=z;
  long long t=0;
  for(;y;y>>=1){
    if(y&1LL)t=(t+x)%z;
    x=(x+x)%z;
  }
  return t;
}
long long Pow(long long x,long long y,long long z){
  if(y<0)y+=z-1;
  long long t=1;
  for(;y;y>>=1){
    if(y&1LL)t=Mul(t,x,z);
    x=Mul(x,x,z);
  }
  return t;
}
long long exgcd(long long a,long long b,long long&x,long long&y){
  if(!b)return x=1,y=0,a;
  long long d=exgcd(b,a%b,y,x);
  return y-=a/b*x,d;
}
long long Inv(long long x,long long z){
  long long y,_y;
  long long d=exgcd(x,z,y,_y);
  return (y%z+z)%z;
}
void init(){
  mu[1]=1;
  phi[1]=1;
  for(int i=2;i<maxa;i++){
    if(!vis[i]){
      prim[++pn]=i;
      mu[i]=-1;
      phi[i]=i-1;
    }
    for(int j=1;j<=pn && i*prim[j]<maxa;j++){
      vis[i*prim[j]]=1;
      if(i%prim[j]==0){
        phi[i*prim[j]]=phi[i]*prim[j];
        mu[i*prim[j]]=0;
        break;
      }else{
        phi[i*prim[j]]=phi[i]*phi[prim[j]];
        mu[i*prim[j]]=-mu[i];
      }
    }
  }
  for(int i=1;i<maxa;i++){
    sum_mu[i]=sum_mu[i-1]+mu[i];
  }
}
long long Adjust(long long x,long long z){if(x<0)x+=z;return x;}
long long getBeads(int a){
  long long g2=0,g3=0;
  for(int i=1;i<=a;i++){
    int j=a/(a/i);
    Add(g2,Mul(sum_mu[j]-sum_mu[i-1],Pow(a/i,2,mod2),mod2),mod2);
    Add(g3,Mul(sum_mu[j]-sum_mu[i-1],Pow(a/i,3,mod2),mod2),mod2);
    i=j;
  }
  long long res=0;
  Add(res,g3,mod2);
  Add(res,3*g2,mod2);
  Add(res,2,mod2);
  res=Mul(res,Inv(6,mod2),mod2);
  res=Adjust(res,mod2);
  return res;
}
long long askF(long long m,long long n){
  long long res=Pow(m-1,n,mod2);
  Add(res,(n&1LL)?1-m:m-1,mod2);

  return res;
}
vector< pair<long long,int> > decompose(long long n){
  long long init_n=n;
  vector< pair<long long,int> > res;
  for(int i=1;i<=pn && 1LL*prim[i]*prim[i]<=init_n && prim[i]<=n;i++){
    if(n%prim[i])continue;
    int cnt=0;
    for(;n%prim[i]==0;n/=prim[i])cnt++;
    res.push_back(make_pair(prim[i],cnt));
  }
  if(n>1){
    res.push_back(make_pair(n,1));
  }
  return res;
}
int solve(long long n,int a){
  long long m=getBeads(a);
  long long res=0;
  vector< pair<long long,int> > decn=decompose(n);
  for(long long d=1;d*d<=n;d++){
    if(n%d)continue;
    vector< pair<long long,int> > _decn=decn;
    long long big_phi=n/d;
    for(int i=0,j=d;i<_decn.size();i++){
      for(;j%_decn[i].first==0;j/=_decn[i].first){
        _decn[i].second--;
      }
      if(_decn[i].second){
        big_phi=big_phi/_decn[i].first*(_decn[i].first-1);
      }
    }
    Add(res,Mul(big_phi,askF(m,d),mod2),mod2);
    if(d*d!=n){
      Add(res,Mul(phi[d],askF(m,n/d),mod2),mod2);
    }
  }
  res=Adjust(res,mod2);
  if(n%mod){
    res=Mul(res,Inv(n%mod,mod),mod);
  }else{
    assert(res%mod==0);
    res/=mod;
    res=Mul(res,Inv(n/mod,mod),mod);
  }
  res=Adjust(res,mod);
  return (int)res;
}
int gcd(int x,int y){
  return y?gcd(y,x%y):x;
}
int baoli(int n,int a){
  int m=0;
  for(int i=1;i<=a;i++){
    for(int j=i;j<=a;j++){
      int x=gcd(i,j);
      for(int k=j;k<=a;k++){
        if(gcd(x,k)==1)m++;
      }
    }
  }
  int ans=0;
  for(int i=1;i<=n;i++){
    if(n%i)continue;
    int f=1;
    for(int j=0;j<i;j++)f*=m-1;
    f+=(m-1)*(i%2?-1:1);
    ans+=f*phi[n/i];
  }
  ans/=n;
  return ans;
}
int main(){
  freopen("aa.in","r",stdin);
  init();
  int _;scanf("%d",&_);
  for(;_--;){
    long long n;int a;
    scanf("%lld%d",&n,&a);
    int ans=solve(n,a);
    printf("%d\n",ans);
  }
  return 0;
}