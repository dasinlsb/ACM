/*
|L|=1/|G|*\sum_{}m^f，显然每种点的置换都对应一种边的置换，求出点的置换产生的边的置换有多少个循环节f就能算了
直接枚举点的全部n!种置换无法接受，考虑直接枚举n的划分也就是点的置换的循环节，假定枚举的划分a[i]满足\sum_{}a[i]==n && a[i]<=a[i+1]，这样的方案数也是可以算的，考虑在这样的点置换下边置换的形态
如果边(x,y)在同一个长度为L的循环节，由于这个循环节也就是点集内部一共有L*(L-1)/2条边，且循环周期为L，所以循环节就是(L-1)/2
但是这样当L为偶数算出的结果会有问题，以L=4为例，(1,3)->(2,4)->(3->1)->(4,2),这个在计算的时候由于循环长度为L/2没有被计入完整的循环节里面去，所以当L为偶数时循环节个数时L/2
如果边(x,y)在不同循环节L1,L2，显然循环节个数为gcd(L1,L2)
把循环节个数累加起来然后统计答案
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=55;
int n,m,P,ans;
int fac[maxn],inv[maxn],invs[maxn],g[maxn][maxn];
vector<int>a;
inline void up(int&x,int y){
  if(x+=y,x>=P)x-=P;
}
int Pow(long long x,int y){
  long long t=1;
  for(;y;y>>=1){
    if(y&1)t=t*x%P;
    x=x*x%P;
  }
  return t;
}
int calc(){
  // for(int x:a)printf("%d ",x);puts("");
  int f=0;
  int w=fac[n];
  int cnt=0;
  for(int i=0;i<a.size();i++){
    f+=a[i]/2;
    w=1LL*w*inv[a[i]]%P;
    if(i!=0 && a[i]!=a[i-1]){
      w=1LL*w*invs[cnt]%P;
      cnt=0;
    }
    cnt++;
    for(int j=i+1;j<a.size();j++){
      f+=g[a[i]][a[j]];
    }
  }
  w=1LL*w*invs[cnt]%P;
  f=1LL*Pow(m,f)*w%P;
  return f;
}

void dfs(int remain){
  if(remain==0){
    up(ans,calc());
    return;
  }
  for(int i=a.size()?a.back():1;i<=remain;i++){
    a.push_back(i);
    dfs(remain-i);
    a.pop_back();
  }
}
int gcd(int x,int y){
  return y?gcd(y,x%y):x;
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d%d%d",&n,&m,&P);
  fac[0]=1;
  for(int i=1;i<=n;i++)fac[i]=1LL*fac[i-1]*i%P;
  inv[0]=inv[1]=1;
  for(int i=2;i<=n;i++)inv[i]=P-1LL*P/i*inv[P%i]%P;
  invs[0]=1;
  for(int i=1;i<=n;i++)invs[i]=1LL*inv[i]*invs[i-1]%P;
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      g[i][j]=gcd(i,j);
    }
  }
  dfs(n);
  ans=1LL*ans*invs[n]%P;
  printf("%d\n",ans);
  return 0;
}