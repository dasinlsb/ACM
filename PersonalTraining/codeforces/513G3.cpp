/*
cf513G2

*/
/*
直接模拟整个序列的移动肯定无法接受，移动单个会因为彼此不独立而无法计算答案，考虑对于每一对位置单独计算贡献
设f[k][l][r]表示l,r这对位置在k轮之后相对位置发生改概率，枚举一下第一次可能操作的O(n^2)个区间可以得到O(k*n^4)的做法
简单优化一下可以达到O(k*n^3)，注意到k较大时序列逆序对数会趋于稳定，调整一下阈值暴力跑即可
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=105;
int n,kk;
int a[maxn];
double f[2][maxn][maxn];
int Sum(int n){
  return n*(n+1)/2;
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d%d",&n,&kk);
  for(int i=1;i<=n;i++){
    scanf("%d",a+i);
  }
  kk=min(kk,900);
  for(int k=1;k<=kk;k++){
    for(int l=1;l<=n;l++){
      for(int r=l;r<=n;r++){
        f[k&1][l][r]=0.0;
        for(int s=1+r;s<=l+n;s++){
          f[k&1][l][r]+=max(0,min(n,s-1)-max(r,s-l)+1)*(1.0-f[~k&1][s-r][s-l]);
        }
        for(int s=1+l;s<=l+r-1;s++){
          f[k&1][l][r]+=max(0,min(r-1,s-1)-max(l,s-l)+1)*f[~k&1][s-l][r];
        }
        for(int s=l+1+r;s<=r+n;s++){
          f[k&1][l][r]+=max(0,min(n,s-1-l)-max(r,s-r)+1)*f[~k&1][l][s-r];
        }
        f[k&1][l][r]+=(Sum(l-1)+Sum(n-r)+Sum(r-l-1))*f[~k&1][l][r];
        f[k&1][l][r]/=((1+n)*n/2);
      }
    }
  }
  
  double ans=0.0;
  for(int i=1;i<=n;i++){
    for(int j=i+1;j<=n;j++){
      if(a[i]>a[j])ans+=1.0-f[kk&1][i][j];
      else ans+=f[kk&1][i][j];
    }
  }
  printf("%.12lf\n",ans);
  return 0;
}