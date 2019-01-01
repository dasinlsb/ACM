/*
可以把原问题转化一下，看作平面上n条(a[i],d[i])-(b[i],d[i])线段，现在要用若干条(0,t)-(y[i],t)的价值为y[i]的线段交所有之前给出的线段
对于每个x坐标如果枚举要放的竖直线段的高度会出现更高的横线状态无法记录的情况，所以可以考虑只交最高的横线的决策
用f[l][r]表示l所有满足<=a[i],b[i]<=r的线段的答案，暴力找出区间中最高的横线高度height以及合法的x坐标范围，暴力枚举切最高的横线要切在哪个x坐标,假设为p,那么就会转移到f[l][p-1]+f[p+1][r]+height
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=605;
const int inf=1e9;
int n,px[maxn],dp[maxn][maxn],pos[10005];
struct Item{
  int a,b,d;
  void read(){scanf("%d%d%d",&a,&b,&d);}
}item[maxn];
void update_dp(int maxd,int dl,int dr,int l,int r){
  dl=max(dl,l);
  dr=min(dr,r);
  for(int i=dl;i<=dr;i++){
    dp[l][r]=min(dp[l][r],dp[l][i-1]+dp[i+1][r]+maxd);
  }
}
int main(){
  freopen("aa.in","r",stdin);
  int _;scanf("%d",&_);
  for(;_--;){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
      item[i].read();
      px[i]=item[i].b;
      px[n+i]=item[i].a;
    }
    sort(item+1,item+1+n,[&](Item x,Item y){
      return x.a<y.a || x.a==y.a && x.b<y.b;
    });
    sort(px+1,px+1+n+n);
    int m=unique(px+1,px+1+n+n)-px-1;
    for(int i=1;i<=m;i++){
      pos[px[i]]=i;
    }
    for(int l=m;l;l--){
      for(int r=l;r<=m;r++){
        int maxd=0;
        for(int i=1;i<=n;i++){
          if(item[i].a>=px[l] && item[i].b<=px[r]){
            maxd=max(maxd,item[i].d);
          }
        }
        if(!maxd){
          dp[l][r]=0;
          continue;
        }
        dp[l][r]=inf;
        int dl=1,dr=0;
        for(int i=1;i<=n;i++){
          if(item[i].a>px[dr]){
            update_dp(maxd,dl,dr,l,r);
            dl=pos[item[i].a];
            dr=pos[item[i].b];
          }else{
            dr=max(dr,pos[item[i].b]);
          }
        }
        update_dp(maxd,dl,dr,l,r);
        assert(dp[l][r]!=inf);
      }
    }
    int ans=dp[1][m];
    printf("%d\n",ans);
  }

  return 0;
}