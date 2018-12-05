/*
可以n^2做，但是分类写太麻烦..
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=1005;
int n,m,kk,a[maxn][maxn];
long long ld[maxn][maxn],rd[maxn][maxn];
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d%d%d",&n,&m,&kk);
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      scanf("%d",&a[i][j]);
    }
  }
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      rd[i][j]=rd[i-1][j-1]+a[i][j];
    }
    for(int j=m;j;j--){
      ld[i][j]=ld[i-1][j+1]+a[i][j];
    }
  }
  long long ans=-1;
  int R,C;
  for(int r=kk;r<=n-kk+1;r++){
    for(int c=kk;c<=m-kk+1;c++){
      long long res=1LL*kk*a[r][c];
      for(int d=1;d<kk;d++){
        long long tmp=0;
        tmp+=rd[r][c+d]-rd[r-d][c];
        tmp+=rd[r+d-1][c-1]-rd[r-1][c-d-1];
        tmp+=ld[r-1][c-d+1]-ld[r-d-1][c+1];
        tmp+=ld[r+d][c]-ld[r][c+d];
        res+=tmp*(kk-d);
      }
      if(res>ans){
        ans=res;
        R=r,C=c;
      }
    }
  }
  assert(ans!=-1);
  printf("%d %d\n",R,C);
  return 0;
}