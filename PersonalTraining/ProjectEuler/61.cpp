#include <bits/stdc++.h>
using namespace std;
const int maxn=10005;
const int CIRCLES=6;
clock_t _st;
const int coef[6][2]={
{1,1},
{2,0},
{3,-1},
{4,-2},
{5,-3},
{6,-4}
};
vector<int> pre[6][100],suf[6][100];
int f[1<<6][100][100];
int solve(){
  int total=0;
  for(int i=0;i<6;i++){
    for(int j=1;;j++){
      int val=coef[i][0]*j*j+coef[i][1]*j;
      assert(val%2==0);
      val/=2;
      if(val<1000)continue;
      if(val>9999)break;
      pre[i][val/100].push_back(val);
      suf[i][val%100].push_back(val);
      total++;
    }
  }
  printf("total %d\n",total);
  for(int i=0;i<100;i++){
    for(int v:pre[0][i]){
      f[1][i][v%100]=v;
    }
  }
  for(int S=0;S<1<<6;S++){
    for(int l=0;l<100;l++){
      for(int r=0;r<100;r++){
        if(!f[S][l][r])continue;
        for(int k=0;k<6;k++){
          if(S>>k&1)continue;
          for(int v:pre[k][r]){
            if((S|1<<k)<63){
              f[S|1<<k][l][v%100]=f[S][l][r]+v;
            }else{
              if(v%100==l){
                printf("sum %d\n",f[S][l][r]+v);
                return 1;
              }
            }
          }
        }
      }
    }
  }
  return 0;
}
int main(){
  freopen("aa.in","r",stdin);
  _st=clock_t();
  printf("found %d\n",solve());
  clock_t _ed=clock();
  printf("time %.6lf\n",1.0*(_ed-_st)/CLOCKS_PER_SEC);
  return 0;
}