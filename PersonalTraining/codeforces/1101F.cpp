/*
dp[r][i][j]表示从a[i]到a[j]可以加油r次的情况下油箱加满一次可以走多少公里，不难发现c是独立的变量，直接乘在dp上更新答案即可
dp[r][i][j]=min(max(dp[r][i][k],a[j]-a[k]))，暴力转移的复杂度是O(n)，不过在固定r,i的情况下k显然随着j增大而单调递增，直接双指针维护，每次在边界左右取最优即可
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=405;
const int maxm=250005;
int n,m,a[maxn];
long long dp[2][maxn][maxn];
struct Car{
  int r,s,f,c;
  void read(){scanf("%d%d%d%d",&s,&f,&c,&r);}
  bool operator<(const Car&x)const{
    if(r!=x.r)return r<x.r;
    if(s!=x.s)return s<x.s;
    if(f!=x.f)return f<x.f;
    return c<x.c;
  }
  bool operator==(const Car&x)const{
    return r==x.r
        && s==x.s
        && f==x.f;
  }
}car[maxm];
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++){
    scanf("%d",a+i);
  }
  for(int i=1;i<=m;i++){
    car[i].read();
    car[i].r++;
  }
  sort(car+1,car+1+m);
  for(int i=1;i<=n;i++){
    for(int j=i;j<=n;j++){
      dp[1][i][j]=a[j]-a[i];
    }
  }
  int pl=1;
  long long ans=0;
  for(int r=1;r<=n+1;r++){
    for(int i=1;i<=n;i++){
      int k=i;
      for(int j=i+1;j<=n;j++){
        // printf("dp %d %d %d : %lld\n",r,i,j,dp[r&1][i][j]);
        Car cur=(Car){r,i,j,0};
        for(;pl<=m && (car[pl]<cur||car[pl]==cur);pl++){
          if(car[pl]<cur)continue;
          ans=max(ans,dp[r&1][i][j]*car[pl].c);
        }
        for(;k<j && dp[r&1][i][k]<=a[j]-a[k];k++);k--;
        if(a[j]-a[k]<=dp[r&1][i][k+1]){
          dp[~r&1][i][j]=a[j]-a[k];
        }else{
          k++;
          dp[~r&1][i][j]=dp[r&1][i][k];
        }
      }
    }
  }
  printf("%I64d\n",ans);
  return 0;
}