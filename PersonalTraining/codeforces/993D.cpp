/*
考虑二分答案，但是二分出一个答案后并不能直接确定最优的选取状况
目标是sum_power/sum_processor-ans<=0
移项之后就是\sum(per_power-per_processor*ans)<=0
接下来的问题可以用dp解决，按power_i排序后从大到小考虑
f[i][j][k]表示当前考虑第i个，power_j==power_i中有j个能提供第二个位置，power_j>power_i中有k个能提供第二个位置
*/
#include <bits/stdc++.h>
using namespace std;
#define SZ(x) (int((x).size()))
#define fi first
#define se second
#define pb push_back
#define VI vector<int>
typedef long long ll;
typedef pair<int,int> pii;
const int maxN=55;
const double eps=1e-6;
const double inf=1e11;
int n,a[maxN],b[maxN];
inline void cmin(double&x,double y){if(y<x)x=y;}
int chk(double rate){
  static pair<int,double>c[maxN];
  static double f[maxN][maxN][maxN];
  int i,j,k;
  for(i=1;i<=n;++i)c[i]=make_pair(a[i],a[i]-b[i]*rate);
  sort(c+1,c+1+n);
  for(i=1;i<=n+1;++i){
    for(j=0;j<=n;++j){
      for(k=0;k+j<=n;++k){
        f[i][j][k]=inf;
      }
    }
  }
  f[n+1][0][0]=0;
  for(i=n;i;--i){
    for(j=0;j<=n;++j){
      for(k=0;j+k<=n;++k)if(f[i+1][j][k]<5e10){
        if(c[i].fi!=c[i+1].fi){
          cmin(f[i][1][j+k],f[i+1][j][k]+c[i].se);
          if(j+k)cmin(f[i][0][j+k-1],f[i+1][j][k]);
        }else{
          cmin(f[i][j+1][k],f[i+1][j][k]+c[i].se);
          if(k)cmin(f[i][j][k-1],f[i+1][j][k]);
        }
      }
    }
  }
  double res=inf;
  for(i=0;i<=n;++i){
    for(j=0;j+i<=n;++j){
      res=min(res,f[1][i][j]);
    }
  }
  return res<0;
}
int main(){
  freopen("aa.in","r",stdin);
  int i,j;
  scanf("%d",&n);
  for(i=1;i<=n;++i)scanf("%d",a+i);
  for(i=1;i<=n;++i)scanf("%d",b+i);
  double l=0,r=1e8;
  for(;l+eps<r;){
    double mid=(l+r)/2;
    if(chk(mid))r=mid;
    else l=mid+eps;
  }
  //printf("%.10lf\n",r);
  printf("%.0lf\n",ceil((r-1e-5)*1000));
  return 0;
}