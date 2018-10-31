/*
k个物品和的期望等于期望的和，独立算每个物品即可
设f[i][j]表示还要打i只怪，当前等级为j，还能获得的期望收益
这一轮选到这个物品的概率为1/k,选到的情况下枚举获得的新等级[1,j+1]然后化简一下可以得到状态O(n^2)转移O(1)的dp方程
直觉上当轮数很大时，单个物品能被选中且从等级j升到j+1的期望收益十分小，试验一下把等级上界取到600左右可以直接用O(600n)来做
*/
#include <bits/stdc++.h>
using namespace std;
int n,kk;
double f[2][605];
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d%d",&n,&kk);
  for(int i=n-1;i>=0;i--){
    for(int j=1;j<=min(i+1,600);j++){
      f[i&1][j]=(f[~i&1][j]*(kk-1)+(f[~i&1][j]*j+f[~i&1][j+1]+0.5*(j+3)*j)/(j+1))/kk;
    }
  }
  double ans=f[0][1]*kk;
  printf("%.12lf\n",ans);
  return 0;
}